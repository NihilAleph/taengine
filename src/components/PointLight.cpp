#include "PointLight.h"
#include "render/ForwardPoint.h"

namespace taengine {

PointLight::PointLight(const glm::vec3& color, float intensity, Attenuation attenuation) :
    BaseLight(color, intensity), m_attenuation(attenuation)
{
    // Calculate point light attenuation
    float a = attenuation.exponent;
    float b = attenuation.linear;
    // factor c is subtracted by the max value of color there is times the color depth
    float c = attenuation.constant - 255 * m_intensity * glm::max(m_color.x, glm::max(m_color.y, m_color.z));
    m_range = sqrt(b * b - 4 * a * c) / (2 * a);

    m_shader = &ForwardPoint::getInstance();
}

PointLight::~PointLight()
{
    //dtor
}

}
