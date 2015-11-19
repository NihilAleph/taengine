#include "Camera.h"


namespace taengine {

Camera::Camera()
{
}

Camera::~Camera()
{
    //dtor
}

void Camera::init(const glm::vec3& position,  const glm::vec3& forward, const glm::vec3 up,
                float fieldOfView, float aspectRation, float zNear, float zFar)
{

    m_position = position;
    m_forward = glm::normalize(forward);
    m_up = glm::normalize(up);
    m_projection = glm::perspective(fieldOfView, aspectRation, zNear, zFar);
}

glm::mat4 Camera::getProjection() const
{
    return m_projection * glm::lookAt(m_position, m_position + m_forward, m_up);
}

void Camera::move(const glm::vec3& delta)
{
    m_position += delta;
}

void Camera::moveForward(float delta)
{
    m_position += m_forward * delta;
}

void Camera::moveRight(float delta)
{

    glm::vec3 right = glm::cross(m_forward, m_up);
    m_position += right * delta;
}

void Camera::pitch(float angle)
{
    glm::vec3 right = glm::cross(m_forward, m_up);
    m_forward = glm::vec3(glm::rotate(angle, right) * glm::vec4(m_forward,0.0f));
    m_up = glm::cross(right, m_forward);
}

void Camera::rotateY(float angle)
{
    // Rotation axis is y
    glm::mat4 rotation = glm::rotate(angle, glm::vec3(0.0f,1.0f,0.0f));

    m_forward = glm::vec3(rotation * glm::vec4(m_forward, 0.0f));
    m_up = glm::vec3(rotation * glm::vec4(m_up,0.0f));
}

void Camera::lookAt(const glm::vec3& target)
{
    m_forward = target - m_position;
}

}
