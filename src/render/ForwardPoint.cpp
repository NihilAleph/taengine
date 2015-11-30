#include "ForwardPoint.h"

#include "components/PointLight.h"
#include "core/GameObject.h"

namespace taengine {

Shader& ForwardPoint::getInstance()
{
    static ForwardPoint shader;
    return shader;
}

ForwardPoint::ForwardPoint()
{
    init("res/forward-point.vs", "res/forward-point.fs");
}


ForwardPoint::~ForwardPoint()
{
    //dtor
}




void ForwardPoint::addUniforms()
{
    addUniform("MVP");
    addUniform("transform");
    addUniform("baseColor");
    addUniform("pointLight.baseLight.color");
    addUniform("pointLight.baseLight.intensity");
    addUniform("pointLight.attenuation.constant");
    addUniform("pointLight.attenuation.linear");
    addUniform("pointLight.attenuation.exponent");
    addUniform("pointLight.position");
    addUniform("pointLight.range");
    addUniform("specularIntensity");
    addUniform("specularExponent");
    addUniform("eyePosition");
}

void ForwardPoint::updateUniforms(const Transform& transform, const Camera& camera,
                                        const Material& material, const RenderingEngine* renderingEngine) const
{

    // Get transform and camera matrix
    //glm::mat4 MVP = transform.getMVP(camera);
    glm::mat4 MVP = camera.getProjection() * transform.getModel();

    // Update uniform values
    setUniform("MVP", MVP);
    setUniform("transform", transform.getModel());
    setUniform("baseColor", material.getColor());
    setUniform("pointLight.baseLight.color", renderingEngine->getLight()->getColor());
    setUniform("pointLight.baseLight.intensity", renderingEngine->getLight()->getIntensity());
    setUniform("pointLight.attenuation.constant", static_cast<PointLight*>(renderingEngine->getLight())->getAttenuation().constant);
    setUniform("pointLight.attenuation.linear", static_cast<PointLight*>(renderingEngine->getLight())->getAttenuation().linear);
    setUniform("pointLight.attenuation.exponent", static_cast<PointLight*>(renderingEngine->getLight())->getAttenuation().exponent);
    setUniform("pointLight.position", static_cast<PointLight*>(renderingEngine->getLight())->getParent()->getTransform().getPosition());
    setUniform("pointLight.range", static_cast<PointLight*>(renderingEngine->getLight())->getRange());

    setUniform("specularIntensity", material.getSpecularIntensity());
    setUniform("specularExponent", material.getSpecularExponent());
    setUniform("eyePosition", camera.getPosition());

    // Bind texture (if any)
    material.bind();
}

}
