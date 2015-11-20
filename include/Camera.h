#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace taengine {

class Camera
{
    public:
        // Constructor for perspective projection
        Camera();
        virtual ~Camera();

        void init(const glm::vec3& position,  const glm::vec3& forward, const glm::vec3 up,
                float fieldOfView, float aspectRation, float zNear, float zFar);

        glm::mat4 getProjection() const;

        void move(const glm::vec3& delta);
        void moveForward(float delta);
        void moveRight(float delta);

        void pitch(float angle);
        void rotateY(float angle);

        void lookAt(const glm::vec3& target);

        inline glm::vec3 getPosition() const { return m_position; };
        inline glm::vec3 getForward() const { return m_forward; };
    protected:
    private:

        glm::mat4 m_projection;
        glm::vec3 m_position;
        glm::vec3 m_forward;
        glm::vec3 m_up;


};

}
#endif // CAMERA_H
