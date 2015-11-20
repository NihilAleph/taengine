#ifndef PHONGSHADER_H
#define PHONGSHADER_H

#include "Shader.h"
#include <vector>

namespace taengine {

struct BaseLight
{
    glm::vec3 color;
    float intensity;
    void init(const glm::vec3& color, float intensity)
    {
        this->color = color;
        this->intensity = intensity;
    };
};

struct DirectionalLight
{
    BaseLight baseLight;
    glm::vec3 direction;

    void init(const glm::vec3& color, float intensity, const glm::vec3& direction) {
         baseLight.init(color,intensity);
         this->direction = glm::normalize(direction);
    };
};

struct PointLight
{
    struct Attenuation
    {
        // Physical accurate values would be 0, 0, 1
        float constant;
        float linear;
        float exponent;
        void init(float constant, float linear, float exponent)
        {
            this->constant = constant;
            this->linear = linear;
            this->exponent = exponent;
        }
    } attenuation;
    BaseLight baseLight;
    glm::vec3 position;
    float range;

    void init(float constant, float linear, float exponent, const glm::vec3& color, float intensity, const glm::vec3& position, float range)
    {
        attenuation.init(constant, linear, exponent);
        baseLight.init(color, intensity);
        this->position = position;
        this->range = range;
    }
};

struct SpotLight
{
    PointLight pointLight;
    glm::vec3 direction;
    float cutOff;



    void init(float constant, float linear, float exponent, const glm::vec3& color, float intensity, const glm::vec3& position, float range
              , const glm::vec3& direction, float cutOff)
    {
        pointLight.init(constant, linear, exponent, color, intensity, position, range);
        this->direction = direction;
        this->cutOff = cutOff;
    }
};


class PhongShader : public Shader
{
    public:
        PhongShader();
        virtual ~PhongShader();

        // Change how shader updates uniform
        void updateUniforms(const Transform& transform, const Camera& camera, const Material& material) const override;

        static void setAmbientLight(const glm::vec3& ambientLight);
        static glm::vec3 getAmbientLight();

        static void setDirectionalLight(const DirectionalLight& directionalLight);
        static void setDirectionalLight(const glm::vec3& color, float intensity, const glm::vec3& direction);
        static DirectionalLight getDirectionalLight();

        static void setPointLights(const std::vector<PointLight>& pointLights);
        static std::vector<PointLight>& getPointLights();

        static void setSpotLights(const std::vector<SpotLight>& spotLights);
        static std::vector<SpotLight>& getSpotLights();
    protected:
        // Change the uniforms used in this shader
        void addUniforms() override;
    private:

        // All lights will be static so there is no inconsistent lights
        static glm::vec3 s_ambientLight;
        static DirectionalLight s_directionalLight;
        static std::vector<PointLight> s_pointLights;
        static std::vector<SpotLight> s_spotLights;

        static const unsigned int MAX_POINT_LIGHTS;
        static const unsigned int MAX_SPOT_LIGHTS;
};

}

#endif // PHONGSHADER_H
