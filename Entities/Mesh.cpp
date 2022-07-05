#include "Mesh.h"

#include <utility>

Mesh::Mesh(std::string id, std::vector<vetor3> vertexCoord, std::vector<vetor3> normalCoords)
{
    meshId = std::move(id);
    coordinates = std::move(vertexCoord);
    normals = std::move(normalCoords);
    height = 0;
}

Mesh::~Mesh()
= default;

Mesh::Mesh()
= default;

float Mesh::cvtToRad(float ang) const
{
    return (ang * m_PI)/180.0;
}

vetor3 Mesh::rotate(vetor3 point, float ang, vetor3 axis)
{
    vetor3 result;
    result.x = axis.x + (point.x - axis.x) * cos(ang) - (point.z - axis.z) * sin(ang);
    result.z = axis.z + (point.x - axis.x) * sin(ang) + (point.z - axis.z) * cos(ang);
    result.y = point.y;
    return result;
}

void Mesh::update(float leftRightDirection, vetor3 camPosVec)
{
    m_yaw += leftRightDirection;
    float ang = cvtToRad(leftRightDirection);
    for (auto & coordinate : coordinates)
    {
        coordinate = rotate(coordinate, ang, camPosVec);
    }
    ang = cvtToRad(m_yaw);
    m_direction.x = sin(ang);
    m_direction.z = -cos(ang);
    m_direction.normalize();
}

void Mesh::forward()
{
    m_speed = m_direction * (m_scl);
    for (auto & coordinate : coordinates)
    {
        coordinate = coordinate + m_speed;
    }
}

void Mesh::jump()
{
    if (height <= maxHeight)
    {
        height++;
    }
    for (auto & coordinate : coordinates)
    {
        if (height <= maxHeight)
        {
            coordinate = coordinate + m_jump;
        }
    }
}

void Mesh::fall()
{
    if (height >= 0)
    {
        height--;
    }
    for (auto & coordinate : coordinates)
    {
        if (height >= 0)
        {
            coordinate = coordinate + m_fall;
        }
    }
}

void Mesh::backward()
{
    m_speed = m_direction * (-m_scl);
    for (auto & coordinate : coordinates)
    {
        coordinate = coordinate + m_speed;
    }
}

void Mesh::setName(std::string newId)
{
    meshId = std::move(newId);
}

void Mesh::setCoordinates(std::vector<vetor3> newCoords)
{
    coordinates = std::move(newCoords);
}

void Mesh::setNormals(std::vector<vetor3> newNormals)
{
    normals = std::move(newNormals);
}

void Mesh::setTexture(std::vector<glm::vec2> newTexture)
{
    texCoordinates = std::move(newTexture);
}

std::vector<vetor3> Mesh::getCoordinates()
{
    return coordinates;
}

std::vector<vetor3> Mesh::getNormals()
{
    return normals;
}

void Mesh::setSpeed(float newSpeed)
{
    m_scl = newSpeed;
}

void Mesh::prepareCar()
{
    vetor3 initialAxis = {-22, 2, 14};
    float ang = cvtToRad(180);
    for (auto & coordinate : coordinates)
    {
        coordinate.x -= 22;
        coordinate.z += 14;
        coordinate = rotate(coordinate, ang, initialAxis);
    }
    coordinatesInitial = coordinates;
    normalsInitial = normals;
    texCoordinatesInitial = texCoordinates;
}

void Mesh::draw()
{
    if (coordinates.size() == 2)
    {
        int i = 0;
        while (i < coordinates.size())
        {
            glBegin(GL_LINES);
                glNormal3f(normals[i].x, normals[i].y, normals[i].z);
                glVertex3f(coordinates[i].x, coordinates[i].y, coordinates[i].z);
            glEnd();
            i++;
        }
    }
    else if (coordinates.size() >= 3)
    {
        int i = 0;
        while (i < coordinates.size())
        {
            glBegin(GL_POLYGON);
                glNormal3f(normals[i].x, normals[i].y, normals[i].z);
                glVertex3f(coordinates[i].x, coordinates[i].y, coordinates[i].z);
                glNormal3f(normals[i + 1].x, normals[i + 1].y, normals[i + 1].z);
                glVertex3f(coordinates[i + 1].x, coordinates[i + 1].y, coordinates[i + 1].z);
                glNormal3f(normals[i + 2].x, normals[i + 2].y, normals[i + 2].z);
                glVertex3f(coordinates[i + 2].x, coordinates[i + 2].y, coordinates[i + 2].z);
            glEnd();
            i += 3;
        }
    }
}

void Mesh::resetPosition()
{
    for (int i = 0; i < coordinates.size(); ++i)
    {
        coordinates[i] = coordinatesInitial[i];
    }
    for (int i = 0; i < normals.size(); ++i)
    {
        normals[i] = normalsInitial[i];
    }
    for (int i = 0; i < texCoordinates.size(); ++i)
    {
        texCoordinates[i] = texCoordinatesInitial[i];
    }
    m_speed = {0, 0, 0};
    m_direction = {0, 0, -1};
    m_yaw = 0.0;
}
