#include "PhongShader.h"
#include <string>
#include <iostream>

namespace taengine {

// All lights will be static so there is no inconsistent lights
glm::vec3 PhongShader::s_ambientLight;
DirectionalLight PhongShader::s_directionalLight;
std::vector<PointLight> PhongShader::s_pointLights;

const unsigned int PhongShader::MAX_POINT_LIGHTS = 4;

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

    for (unsigned int i = 0; i < MAX_POINT_LIGHTS; i++) {
        addUniform("pointLights[" + std::to_string(i) + "].baseLight.color");
        addUniform("pointLights[" + std::to_string(i) + "].baseLight.intensity");
        addUniform("pointLights[" + std::to_string(i) + "].attenuation.constant");
        addUniform("pointLights[" + std::to_string(i) + "].attenuation.linear");
        addUniform("pointLights[" + std::to_string(i) + "].attenuation.exponent");
        addUniform("pointLights[" + std::to_string(i) + "].position");
        addUniform("pointLights[" + std::to_string(i) + "].range");
    }
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
    setUniform("ambientLight", s_ambientLight);
    setUniform("directionalLight.baseLight.color", s_directionalLight.baseLight.color);
    setUniform("directionalLight.baseLight.intensity", s_directionalLight.baseLight.intensity);
    setUniform("directionalLight.direction", s_directionalLight.direction);

    for (unsigned int i = 0; i < s_pointLights.size(); i++) {
        setUniform("pointLights[" + std::to_string(i) + "].baseLight.color", s_pointLights[i].baseLight.color);
        setUniform("pointLights[" + std::to_string(i) + "].baseLight.intensity", s_pointLights[i].baseLight.intensity);
        setUniform("pointLights[" + std::to_string(i) + "].attenuation.constant", s_pointLights[i].attenuation.constant);
        setUniform("pointLights[" + std::to_string(i) + "].attenuation.linear", s_pointLights[i].attenuation.linear);
        setUniform("pointLights[" + std::to_string(i) + "].attenuation.exponent", s_pointLights[i].attenuation.exponent);
        setUniform("pointLights[" + std::to_string(i) + "].position", s_pointLights[i].position);
        setUniform("pointLights[" + std::to_string(i) + "].range", s_pointLights[i].range);
    }

    setUniform("specularIntensity", material.getSpecularIntensity());
    setUniform("specularExponent", material.getSpecularExponent());
    setUniform("eyePosition", camera.getPosition());

    // Bind texture (if any)
    material.bind();
}

void PhongShader::setAmbientLight(const glm::vec3& ambientLight)
{
    s_ambientLight = ambientLight;
}

glm::vec3 PhongShader::getAmbientLight()
{
    return s_ambientLight;
}

void PhongShader::setDirectionalLight(const DirectionalLight& directionalLight)
{
    s_directionalLight = directionalLight;
}

void PhongShader::setDirectionalLight(const glm::vec3& color, float intensity, const glm::vec3& direction)
{
    s_directionalLight.init(color, intensity, direction);
}

DirectionalLight PhongShader::getDirectionalLight()
{
    return s_directionalLight;
}

void PhongShader::setPointLights(const std::vector<PointLight>& pointLights)
{
    if (pointLights.size() > MAX_POINT_LIGHTS) {
        std::cerr << "Invalid number of Point Lights!";
    } else {
        s_pointLights = pointLights;
    }
}
std::vector<PointLight>& PhongShader::getPointLights()
{
    return s_pointLights;
}

}
