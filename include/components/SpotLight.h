#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "components/PointLight.h"
#include "core/GameObject.h"

namespace taengine {

class SpotLight : public PointLight
{
    public:
        SpotLight(const glm::vec3& color, float intensity, float cutoff, Attenuation attenuation = Attenuation(0.0f,0.0f,1.0f));
        virtual ~SpotLight();

        // Spot light initial forward is pointing to X axis
        glm::vec3 getDirection() { return m_parent->getTransform().getRotation() * glm::vec3(1.0f,0.0f,0.0f); }
        float getCutoff() { return m_cutoff; }

        void setCutoff(float cutoff) { m_cutoff = cutoff; }
    protected:

        // Cutoff is the min cos that will be rendered
        float m_cutoff;
    private:
};

}

#endif // SPOTLIGHT_H
