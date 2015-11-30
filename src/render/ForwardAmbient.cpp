#include "ForwardAmbient.h"

namespace taengine {

Shader& ForwardAmbient::getInstance()
{
    static ForwardAmbient shader;
    return shader;
}

ForwardAmbient::ForwardAmbient()
{
    init("res/forward-ambient.vs", "res/forward-ambient.fs");
    m_ambientLight = glm::vec3(0.1f);
}

ForwardAmbient::~ForwardAmbient()
{
    //dtor
}

void ForwardAmbient::setAmbientLight(const glm::vec3& ambientLight)
{
    m_ambientLight = ambientLight;
}

void ForwardAmbient::updateUniforms(const Transform& transform, const Camera& camera,
                                    const Material& material, const RenderingEngine* renderingEngine) const
{
    // Get transform and camera matrix
    glm::mat4 MVP = camera.getProjection() * transform.getModel();

    // Update uniform values
    setUniform("MVP", MVP);
    setUniform("ambientLight", m_ambientLight);
    setUniform("color", material.getColor());


    // Bind texture
    material.bind();

}

void ForwardAmbient::addUniforms()
{
    addUniform("MVP");
    addUniform("ambientLight");
    addUniform("color");
}

}
