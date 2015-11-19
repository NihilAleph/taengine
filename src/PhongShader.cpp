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
    addUniform("transform");
    addUniform("baseColor");
    addUniform("ambientLight");
    addUniform("directionalLight.baseLight.color");
    addUniform("directionalLight.baseLight.intensity");
    addUniform("directionalLight.direction");
    addUniform("specularIntensity");
    addUniform("specularExponent");
    addUniform("eyePosition");
}

void PhongShader::updateUniforms(const Transform& transform, const Camera& camera, const Material& material) const
{

    // Get transform and camera matrix
    //glm::mat4 MVP = transform.getMVP(camera);
    glm::mat4 MVP = camera.getProjection() * transform.getModel();

    // Update uniform values
    setUniform("MVP", MVP);
    setUniform("transform", transform.getModel());
    setUniform("baseColor", material.getColor());
    setUniform("ambientLight", m_ambientLight);
    setUniform("directionalLight.baseLight.color", m_directionalLight.baseLight.color);
    setUniform("directionalLight.baseLight.intensity", m_directionalLight.baseLight.intensity);
    setUniform("directionalLight.direction", m_directionalLight.direction);
    setUniform("specularIntensity", material.getSpecularIntensity());
    setUniform("specularExponent", material.getSpecularExponent());
    setUniform("eyePosition", camera.getPosition());

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

void PhongShader::setDirectionalLight(const DirectionalLight& directionalLight)
{
    m_directionalLight = directionalLight;
}

void PhongShader::setDirectionalLight(const glm::vec3& color, float intensity, const glm::vec3& direction)
{
    m_directionalLight.init(color, intensity, direction);
}

DirectionalLight PhongShader::getDirectionalLight()
{
    return m_directionalLight;
}

}
