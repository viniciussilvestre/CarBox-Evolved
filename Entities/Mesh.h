#include <glm/glm.hpp>
#include "../Util/cg.h"
#include <GL/freeglut.h>
#include <vector>
#include <string>
#include "../Util/Const.h"
#ifndef CAR_CAR_H
#define CAR_CAR_H

class Mesh
{
    private:
        std::string meshId;
        std::vector<vetor3> coordinates;
        std::vector<vetor3> normals;
        std::vector<glm::vec2> texCoordinates;
        std::vector<vetor3> coordinatesInitial;
        std::vector<vetor3> normalsInitial;
        std::vector<glm::vec2> texCoordinatesInitial;
        vetor3 m_speed = {0, 0, 0};
        vetor3 m_jump = {0, 0.25, 0};
        vetor3 m_fall = {0, -0.25, 0};
        vetor3 m_direction = {0, 0 ,-1};
        float m_yaw{};
        float m_scl = carSpeed;
        float m_PI = 3.14159265;
        float height;

    public:
        explicit Mesh(std::string id, std::vector<vetor3> vertexCoord, std::vector<vetor3> normalCoords);
        ~Mesh();
        Mesh();

        void setName(std::string newId);
        void setCoordinates(std::vector<vetor3> newCoords);
        void setNormals(std::vector<vetor3> newNormals);
        void setTexture(std::vector<glm::vec2> newTexture);
        std::vector<vetor3> getCoordinates();
        std::vector<vetor3> getNormals();
        void forward();
        void backward();
        void jump();
        void fall();
        void update(float leftRightDirection, vetor3 camPosVec);
        void draw();
        void setSpeed(float newSpeed);
        void prepareCar();
        void resetPosition();

    private:
        static vetor3 rotate(vetor3 point, float ang, vetor3 axis);
        [[nodiscard]] float cvtToRad(float ang) const;
};

#endif //CAR_CAR_H
