#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace taengine {

class Camera
{
    public:
        // Constructor for perspective projection
        Camera(const glm::vec3& position, float fieldOfView, float aspectRation, float zNear, float zFar);
        virtual ~Camera();

        glm::mat4 getProjection() const;
    protected:
    private:

        glm::mat4 m_projection;
        glm::vec3 m_position;
        glm::vec3 m_forward;
        glm::vec3 m_up;


};

}
#endif // CAMERA_H
