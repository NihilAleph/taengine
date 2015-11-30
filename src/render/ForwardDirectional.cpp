#include "ForwardDirectional.h"
#include "components/DirectionalLight.h"

namespace taengine {

Shader& ForwardDirectional::getInstance()
{
    static ForwardDirectional shader;
    return shader;
}

ForwardDirectional::ForwardDirectional()
{
    init("res/forward-directional.vs", "res/forward-directional.fs");
}


ForwardDirectional::~ForwardDirectional()
{
    //dtor
}




void ForwardDirectional::addUniforms()
{
    addUniform("MVP");
    addUniform("transform");
    addUniform("baseColor");
    addUniform("directionalLight.baseLight.color");
    addUniform("directionalLight.baseLight.intensity");
    addUniform("directionalLight.direction");
    addUniform("specularIntensity");
    addUniform("specularExponent");
    addUniform("eyePosition");
}

void ForwardDirectional::updateUniforms(const Transform& transform, const Camera& camera,
                                        const Material& material, const RenderingEngine* renderingEngine) const
{

    // Get transform and camera matrix
    //glm::mat4 MVP = transform.getMVP(camera);
    glm::mat4 MVP = camera.getProjection() * transform.getModel();

    // Update uniform values
    setUniform("MVP", MVP);
    setUniform("transform", transform.getModel());
    setUniform("baseColor", material.getColor());
    setUniform("directionalLight.baseLight.color", renderingEngine->getLight()->getColor());
    setUniform("directionalLight.baseLight.intensity", renderingEngine->getLight()->getIntensity());
    setUniform("directionalLight.direction", static_cast<DirectionalLight*>(renderingEngine->getLight())->getDirection());

    setUniform("specularIntensity", material.getSpecularIntensity());
    setUniform("specularExponent", material.getSpecularExponent());
    setUniform("eyePosition", camera.getPosition());

    // Bind texture (if any)
    material.bind();
}

}
