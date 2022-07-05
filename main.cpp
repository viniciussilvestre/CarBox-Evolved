//Vinicius de Paula Silvestre
#include <GL/freeglut.h>
#include <vector>
#include <glm/glm.hpp>
#include "Util/OBJ_Loader.h"
#include "Entities/Camera.h"
#include "Collision/AABB.h"
#include "Entities/Mesh.h"
#include "Util/Const.h"

using namespace std;

float leftRightDirection = 0;
float upDownDirection = 0;
bool keyPressed[keyPressedSize];
Mesh Road; // NOLINT(cert-err58-cpp)
Mesh GrassField; // NOLINT(cert-err58-cpp)
Mesh MiddleOfRoad; // NOLINT(cert-err58-cpp)
Mesh Walls; // NOLINT(cert-err58-cpp)
Mesh car; // NOLINT(cert-err58-cpp)
AABB trackOuterCollisionBox; // NOLINT(cert-err58-cpp)
AABB carCollisionBox; // NOLINT(cert-err58-cpp)
int deathCount;

GLfloat fAspect;

Camera cameraFPV(cameraInitialPos); // NOLINT(cert-err58-cpp)

Mesh loadOBJInOpenGL(const char * fileName)
{
    vector<vetor3> vertices;
    vector<vetor3> normals;
    vector<glm::vec2> texture;
    Mesh tempMesh;
    objl::Loader Loader;
    bool loadout = Loader.LoadFile(fileName);
    if (loadout)
    {
        for (const auto& currentMesh : Loader.LoadedMeshes)
        {
            for (auto & Vertex : currentMesh.Vertices)
            {
                vetor3 temp_vertices;
                temp_vertices.x = Vertex.Position.X;
                temp_vertices.y = Vertex.Position.Y;
                temp_vertices.z = Vertex.Position.Z;
                vertices.push_back(temp_vertices);
                vetor3 temp_normals;
                temp_normals.x = Vertex.Normal.X;
                temp_normals.y = Vertex.Normal.Y;
                temp_normals.z = Vertex.Normal.Z;
                normals.push_back(temp_normals);
                glm::vec2 temp_texture;
                temp_texture.x = Vertex.TextureCoordinate.X;
                temp_texture.y = Vertex.TextureCoordinate.Y;
                texture.push_back(temp_texture);
            }
            tempMesh.setName(currentMesh.MeshName);
            tempMesh.setCoordinates(vertices);
            tempMesh.setNormals(normals);
            tempMesh.setTexture(texture);
            return tempMesh;
        }
    }
    return tempMesh;
}

void init()
{
    GLfloat ambientLight[4] = {0.2, 0.2, 0.2, 1.0};
    GLfloat diffusedLight[4] = {0.7,0.7,0.7,1.0};
    GLfloat specularLight[4] = {1.0, 1.0, 1.0, 1.0};
    GLfloat lightPosition[4] = {0.0, 50.0, 50.0, 1.0};

    GLfloat specularity[4] = {1.0,1.0,1.0,1.0};
    GLint specMaterial = 60;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glShadeModel(GL_SMOOTH);

    glMaterialfv(GL_FRONT,GL_SPECULAR, specularity);
    glMateriali(GL_FRONT,GL_SHININESS,specMaterial);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffusedLight );
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight );
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition );

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    Road = loadOBJInOpenGL(R"(C:\Users\vinic\OneDrive\Trabalhos legais\CarBox Evolved\Blender Files\Road.obj)");
    GrassField = loadOBJInOpenGL(R"(C:\Users\vinic\OneDrive\Trabalhos legais\CarBox Evolved\Blender Files\GrassField.obj)");
    MiddleOfRoad = loadOBJInOpenGL(R"(C:\Users\vinic\OneDrive\Trabalhos legais\CarBox Evolved\Blender Files\MiddleRoad.obj)");
    Walls = loadOBJInOpenGL(R"(C:\Users\vinic\OneDrive\Trabalhos legais\CarBox Evolved\Blender Files\Walls.obj)");
    car = loadOBJInOpenGL(R"(C:\Users\vinic\OneDrive\Trabalhos legais\CarBox Evolved\Blender Files\car.obj)");
    car.prepareCar();
    trackOuterCollisionBox.setId("outerWall");
    trackOuterCollisionBox.setDistances(outerDistances);
    trackOuterCollisionBox.setCenter(outerCenter);
    trackOuterCollisionBox.createBox();
    carCollisionBox.setId("Mesh");
    carCollisionBox.setDistances(carCollisionBoxDistances);
    carCollisionBox.setCenter({cameraFPV.getMPos().x, static_cast<float>(cameraFPV.getMPos().y - 1.5), cameraFPV.getMPos().z - 3});
    carCollisionBox.createBox();
    deathCount = 0;
}

void showDeath()
{
    string deathText = "Death's: ";
    string full = deathText + std::to_string(deathCount);
    glColor3f(1.0, 0.0, 0.0);
    glRasterPos3f(cameraFPV.getMPos().x, cameraFPV.getMPos().y + 2, cameraFPV.getMPos().z);
    for (char i : full)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, i);
    }
    glColor3f(1.0, 1.0, 1.0);
}

void visualizationParameter()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angle, fAspect, zNear, zFar);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    cameraFPV.activate();
}

void OnEachFrame()
{
    if (keyPressed[(int)'w'])
    {
        if ((carCollisionBox.getCenter().x + carCollisionBoxDistances.x < outerDistances.x && carCollisionBox.getCenter().x - carCollisionBoxDistances.x > -outerDistances.x) &&
        (carCollisionBox.getCenter().z + carCollisionBoxDistances.z < outerDistances.z && carCollisionBox.getCenter().z - carCollisionBoxDistances.z > -outerDistances.z))
        {
            cameraFPV.forward();
            carCollisionBox.forward();
            car.forward();
        }
        else
        {
            cameraFPV.resetCamera();
            carCollisionBox.reset(cameraFPV.getMPos());
            car.resetPosition();
        }
    }
    if (keyPressed[(int)'s'])
    {
        if ((carCollisionBox.getCenter().x + carCollisionBoxDistances.x + 0.5 < outerDistances.x && carCollisionBox.getCenter().x - carCollisionBoxDistances.x - 0.5 > -outerDistances.x) &&
        (carCollisionBox.getCenter().z + carCollisionBoxDistances.z + 0.5 < outerDistances.z && carCollisionBox.getCenter().z - carCollisionBoxDistances.z - 0.5 > -outerDistances.z))
        {
            cameraFPV.backward();
            carCollisionBox.backward();
            car.backward();
        }
        else
        {
            cameraFPV.resetCamera();
            carCollisionBox.reset(cameraFPV.getMPos());
            car.resetPosition();
        }
    }
    if (keyPressed[(int)'a'])
    {
        if ((carCollisionBox.getCenter().x + carCollisionBoxDistances.x < outerDistances.x && carCollisionBox.getCenter().x - carCollisionBoxDistances.x > -outerDistances.x) &&
        (carCollisionBox.getCenter().z + carCollisionBoxDistances.z < outerDistances.z && carCollisionBox.getCenter().z - carCollisionBoxDistances.z > -outerDistances.z))
        {
            leftRightDirection -= leftRightSpeed;
            cameraFPV.updateYaw(leftRightDirection);
            cameraFPV.update();
            carCollisionBox.update(leftRightDirection, cameraFPV.getMPos());
            car.update(leftRightDirection, cameraFPV.getMPos());
            leftRightDirection = 0;
        }
        else
        {
            cameraFPV.resetCamera();
            carCollisionBox.reset(cameraFPV.getMPos());
            car.resetPosition();
        }
    }
    if (keyPressed[(int)'d'])
    {
        if ((carCollisionBox.getCenter().x + carCollisionBoxDistances.x < outerDistances.x && carCollisionBox.getCenter().x - carCollisionBoxDistances.x > -outerDistances.x) &&
        (carCollisionBox.getCenter().z + carCollisionBoxDistances.z < outerDistances.z && carCollisionBox.getCenter().z - carCollisionBoxDistances.z > -outerDistances.z))
        {
            leftRightDirection += leftRightSpeed;
            cameraFPV.updateYaw(leftRightDirection);
            cameraFPV.update();
            carCollisionBox.update(leftRightDirection, cameraFPV.getMPos());
            car.update(leftRightDirection, cameraFPV.getMPos());
            leftRightDirection = 0;
        }
        else
        {
            cameraFPV.resetCamera();
            carCollisionBox.reset(cameraFPV.getMPos());
            car.resetPosition();
        }
    }
    if (keyPressed[(int)' '])
    {
        car.jump();
        carCollisionBox.jump();
    }
    if (!keyPressed[(int)' '])
    {
        car.fall();
        carCollisionBox.fall();
    }
    visualizationParameter();
}

void draw()
{
    glClearColor(0.74902f, 0.847059f, 0.997059f, 0.0f);
    float lastTime = 0.0;
    float now;
    float dt;
    do
    {
        now = glutGet(GLUT_ELAPSED_TIME); // NOLINT(cppcoreguidelines-narrowing-conversions)
        dt = now - lastTime;
    }
    while (dt < 1.0 / fps);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    OnEachFrame();
    glColor3f(0, 0, 0);
    Road.draw();
    glColor3f(0, 1, 0);
    GrassField.draw();
    glColor3f(1, 1, 1);
    MiddleOfRoad.draw();
    glColor3f(0.2, 0.2, 0.2);
    Walls.draw();
    glColor3f(1, 1, 1);
    //trackOuterCollisionBox.drawBox();
    //carCollisionBox.drawBox();
    car.draw();
    showDeath();
    glutSwapBuffers();
}

void idle()
{
    glutPostRedisplay();
}

void resizeWindow(GLsizei w, GLsizei h)
{
    if (h == 0)
    {
        h = 1;
    }
    glViewport(0, 0, w, h);
    fAspect = (GLfloat)w/(GLfloat)h;
    visualizationParameter();
}

void keyboardManagementUp(unsigned char key, [[maybe_unused]] int x, [[maybe_unused]] int y)
{
    keyPressed[(int)key] = false;
}

void keyboardManagement(unsigned char key, [[maybe_unused]] int x, [[maybe_unused]] int y)
{
    keyPressed[(int)key] = true;
}

int main(int argc, char *argv[])
{
    glutInit(& argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (resX,resY);
    glutInitWindowPosition (initialWinPosX,initialWinPosY);
    glutCreateWindow("Car Game");
    glutDisplayFunc(draw);
    glutReshapeFunc(resizeWindow);
    glutKeyboardFunc(keyboardManagement);
    glutKeyboardUpFunc(keyboardManagementUp);
    glutIdleFunc(idle);
    init();
    glutMainLoop();
    return 0;
}
