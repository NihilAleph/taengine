#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "components/BaseLight.h"

namespace taengine {

struct Attenuation
{
	// Physical accurate values would be 0, 0, 1
    float constant;
    float linear;
    float exponent;
    Attenuation(float c, float l, float e)
    {
        constant = c;
        linear = l;
        exponent = e;
    }
};

class PointLight : public BaseLight
{
    public:
        PointLight(const glm::vec3& color, float intensity, Attenuation attenuation = Attenuation(0.0f,0.0f,1.0f));
        virtual ~PointLight();

        void setAttenuation(Attenuation attenuation)
        {
            m_attenuation = attenuation;

            // Calculate point light attenuation
            float a = attenuation.exponent;
            float b = attenuation.linear;
            // factor c is subtracted by the max value of color there is times the color depth
            float c = attenuation.constant - 255 * m_intensity * glm::max(m_color.x, glm::max(m_color.y, m_color.z));
            m_range = sqrt(b * b - 4 * a * c) / (2 * a);
        }

        Attenuation getAttenuation() { return m_attenuation; }
        float getRange() { return m_range; }
    protected:
        Attenuation m_attenuation;
        float m_range;
    private:
};

}

#endif // POINTLIGHT_H
