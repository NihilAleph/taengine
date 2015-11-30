#include "components/BaseLight.h"

namespace taengine {

BaseLight::BaseLight(const glm::vec3& color, float intensity)
{
    m_color = color;
    m_intensity = intensity;
}

BaseLight::~BaseLight()
{
    //dtor
}

void BaseLight::addToEngine(RenderingEngine* renderingEngine)
{
    renderingEngine->addLight(this);
}

}
