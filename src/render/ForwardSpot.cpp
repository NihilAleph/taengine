#include "ForwardSpot.h"

#include "components/SpotLight.h"
#include "core/GameObject.h"

namespace taengine {

Shader& ForwardSpot::getInstance()
{
    static ForwardSpot shader;
    return shader;
}

ForwardSpot::ForwardSpot()
{
    init("res/forward-spot.vs", "res/forward-spot.fs");
}


ForwardSpot::~ForwardSpot()
{
    //dtor
}




void ForwardSpot::addUniforms()
{
    addUniform("MVP");
    addUniform("transform");
    addUniform("baseColor");
    addUniform("spotLight.pointLight.baseLight.color");
    addUniform("spotLight.pointLight.baseLight.intensity");
    addUniform("spotLight.pointLight.attenuation.constant");
    addUniform("spotLight.pointLight.attenuation.linear");
    addUniform("spotLight.pointLight.attenuation.exponent");
    addUniform("spotLight.pointLight.position");
    addUniform("spotLight.pointLight.range");
    addUniform("spotLight.direction");
    addUniform("spotLight.cutoff");
    addUniform("specularIntensity");
    addUniform("specularExponent");
    addUniform("eyePosition");
}

void ForwardSpot::updateUniforms(const Transform& transform, const Camera& camera,
                                        const Material& material, const RenderingEngine* renderingEngine) const
{

    // Get transform and camera matrix
    //glm::mat4 MVP = transform.getMVP(camera);
    glm::mat4 MVP = camera.getProjection() * transform.getModel();

    // Update uniform values
    setUniform("MVP", MVP);
    setUniform("transform", transform.getModel());
    setUniform("baseColor", material.getColor());
    setUniform("spotLight.pointLight.baseLight.color", renderingEngine->getLight()->getColor());
    setUniform("spotLight.pointLight.baseLight.intensity", renderingEngine->getLight()->getIntensity());
    setUniform("spotLight.pointLight.attenuation.constant", static_cast<SpotLight*>(renderingEngine->getLight())->getAttenuation().constant);
    setUniform("spotLight.pointLight.attenuation.linear", static_cast<SpotLight*>(renderingEngine->getLight())->getAttenuation().linear);
    setUniform("spotLight.pointLight.attenuation.exponent", static_cast<SpotLight*>(renderingEngine->getLight())->getAttenuation().exponent);
    setUniform("spotLight.pointLight.position", static_cast<SpotLight*>(renderingEngine->getLight())->getParent()->getTransform().getPosition());
    setUniform("spotLight.pointLight.range", static_cast<SpotLight*>(renderingEngine->getLight())->getRange());
    setUniform("spotLight.direction", static_cast<SpotLight*>(renderingEngine->getLight())->getDirection());
    setUniform("spotLight.cutoff", static_cast<SpotLight*>(renderingEngine->getLight())->getCutoff());

    setUniform("specularIntensity", material.getSpecularIntensity());
    setUniform("specularExponent", material.getSpecularExponent());
    setUniform("eyePosition", camera.getPosition());

    // Bind texture (if any)
    material.bind();
}

}
