#include "DirectionalLight.h"
#include "ForwardDirectional.h"

namespace taengine {

DirectionalLight::DirectionalLight(const glm::vec3& color, float intensity, const glm::vec3& direction) : BaseLight(color, intensity)
{
    m_direction = direction;
    m_shader = &ForwardDirectional::getInstance();
}

DirectionalLight::~DirectionalLight()
{
    //dtor
}

}
