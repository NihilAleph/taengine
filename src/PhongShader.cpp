#include "PhongShader.h"

namespace taengine {

PhongShader::PhongShader()
{
    //ctor
}

PhongShader::~PhongShader()
{
    //dtor
}

void PhongShader::addUniforms()
{
    addUniform("MVP");
    addUniform("baseColor");
    addUniform("ambientLight");
}

void PhongShader::updateUniforms(const Transform& transform, const Camera& camera, const Material& material) const
{

    // Get transform and camera matrix
    //glm::mat4 MVP = transform.getMVP(camera);
    glm::mat4 MVP = camera.getProjection() * transform.getModel();

    // Update uniform values
    setUniform("MVP", MVP);
    setUniform("baseColor", material.getColor());
    setUniform("ambientLight", m_ambientLight);

    // Bind texture (if any)
    material.bind();
}

void PhongShader::setAmbientLight(const glm::vec3& ambientLight)
{
    m_ambientLight = ambientLight;
}

glm::vec3 PhongShader::getAmbientLight()
{
    return m_ambientLight;
}

}
