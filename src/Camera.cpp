#include "Camera.h"


namespace taengine {

Camera::Camera(const glm::vec3& position, float fieldOfView, float aspectRation, float zNear, float zFar)
{
    m_position = position;
    m_forward = glm::vec3(0.0f,0.0f,1.0f);
    m_up = glm::vec3(0.0f,1.0f,0.0f);
    m_projection = glm::perspective(fieldOfView, aspectRation, zNear, zFar);
}

Camera::~Camera()
{
    //dtor
}

glm::mat4 Camera::getProjection() const
{
    return m_projection * glm::lookAt(m_position, m_position + m_forward, m_up);
}

}
