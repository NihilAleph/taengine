#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "components/BaseLight.h"

namespace taengine {

class DirectionalLight : public BaseLight
{
    public:
        DirectionalLight(const glm::vec3& color, float intensity, const glm::vec3& direction);
        virtual ~DirectionalLight();

        void setDirection(const glm::vec3 direction) { m_direction = direction; }
        glm::vec3 getDirection() { return m_direction; }
    protected:
    private:

        glm::vec3 m_direction;
};

}

#endif // DIRECTIONALLIGHT_H
