#include "SpotLight.h"
#include "render/ForwardSpot.h"

namespace taengine {

SpotLight::SpotLight(const glm::vec3& color, float intensity, float cutoff, Attenuation attenuation) :
    PointLight(color, intensity, attenuation)
{
    m_cutoff = cutoff;

    m_shader = &ForwardSpot::getInstance();
}

SpotLight::~SpotLight()
{
    //dtor
}

}
