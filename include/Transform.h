#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

/************************************************
*
*   This class is used to represent the object in space.
*   It keeps the position, rotation and scale of the object
*   For math operations it should be used the model given
*   by the method below
*
*************************************************/

namespace taengine {

class Transform
{
    public:
        inline Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3 scale)
        {
            m_position = position;
            m_rotation = rotation;
            m_scale = scale;
        }
        //virtual ~Transform();

        // Returns the model matrix of this transform
        inline glm::mat4 getModel() const
        {
            glm::mat4 translate = glm::translate(m_position);
            glm::mat4 rotationX = glm::rotate(m_rotation.x, glm::vec3(1.0f,0.0f,0.0f));
            glm::mat4 rotationY = glm::rotate(m_rotation.y, glm::vec3(0.0f,1.0f,0.0f));
            glm::mat4 rotationZ = glm::rotate(m_rotation.z, glm::vec3(0.0f,0.0f,1.0f));
            glm::mat4 rotation = rotationX * rotationY * rotationZ;
            glm::mat4 scale = glm::scale(m_scale);

            return translate * rotation * scale;

        }

        inline const glm::vec3 getPosition() const { return m_position; }
        inline const glm::vec3 getRotation() const { return m_rotation; }
        inline const glm::vec3 getScale() const { return m_scale; }

        inline void setPosition(const glm::vec3& position) { m_position = position; }
        inline void setRotation(const glm::vec3& rotation) { m_rotation = rotation; }
        inline void setScale(const glm::vec3& scale) { m_scale = scale; }

        inline void translate(const glm::vec3& ds) { m_position += ds; }
        inline void rotate (const glm::vec3& da) { m_rotation += da; }

    protected:
    private:
        // Variables that store the transform information. Rotation is used as Euler Angles
        glm::vec3 m_position;
        glm::vec3 m_rotation;
        glm::vec3 m_scale;
};

}

#endif // TRANSFORM_H
