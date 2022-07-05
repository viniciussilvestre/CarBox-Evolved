#include "Camera.h"

Camera::Camera(vetor3 pos)
{
    m_pos = vetor3(pos);
    m_dir = vetor3(0, 0, -1);
    m_left = vetor3(1, 0, 0);
    m_up = vetor3 (0, 1, 0);
    m_speed = vetor3(0, 0, 0);
}

Camera::~Camera()
= default;

void Camera::activate()
{
    vetor3 look = m_pos + m_dir;
    gluLookAt(m_pos.x, m_pos.y, m_pos.z, look.x, look.y, look.z, m_up.x, m_up.y, m_up.z);
}

void Camera::forward()
{
    m_speed = m_dir * m_scl;
    m_pos = m_pos + m_speed;
}

void Camera::jump()
{
    
}

void Camera::backward()
{
    m_speed = m_dir * (-m_scl);
    m_pos = m_pos + m_speed;
}

float Camera::cvtToRad(float ang) const
{
    return (ang * m_PI)/180.0;
}

void Camera::updateYaw(float dYaw)
{
    m_yaw += dYaw;
}

void Camera::update()
{
    float ang = cvtToRad(m_yaw);
    m_dir.x = sin(ang);
    m_dir.z = -cos(ang);
    m_dir.normalize();
}

vetor3 Camera::getMPos()
{
    return m_pos;
}

vetor3 Camera::getMDir()
{
    return m_dir;
}

vetor3 Camera::getSpeed()
{
    return m_speed;
}

void Camera::resetCamera()
{
    m_pos = vetor3(cameraInitialPos);
    m_dir = vetor3(0, 0, -1);
    m_yaw = 0.0;
    m_speed = vetor3(0, 0, 0);
}

void Camera::setMDir(vetor3 newMDir)
{
    m_dir = newMDir;
}

void Camera::cameraFrontView()
{

}

void Camera::cameraBackView()
{

}

void Camera::upView()
{

}

