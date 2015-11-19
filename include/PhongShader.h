#ifndef PHONGSHADER_H
#define PHONGSHADER_H

#include "Shader.h"

namespace taengine {

struct BaseLight
{
    glm::vec3 color;
    float intensity;
    void init(const glm::vec3& c, float i)
    {
        color = c;
        intensity = i;
    };
};

struct DirectionalLight
{
    BaseLight baseLight;
    glm::vec3 direction;

    void init(const glm::vec3& c, float i, const glm::vec3& d) {
         baseLight.init(c,i);
         direction = glm::normalize(d);
    };
};


class PhongShader : public Shader
{
    public:
        PhongShader();
        virtual ~PhongShader();

        // Change how shader updates uniform
        void updateUniforms(const Transform& transform, const Camera& camera, const Material& material) const override;

        void setAmbientLight(const glm::vec3& ambientLight);
        glm::vec3 getAmbientLight();

        void setDirectionalLight(const DirectionalLight& directionalLight);
        void setDirectionalLight(const glm::vec3& color, float intensity, const glm::vec3& direction);
        DirectionalLight getDirectionalLight();
    protected:
        // Change the uniforms used in this shader
        void addUniforms() override;
    private:
        glm::vec3 m_ambientLight;
        DirectionalLight m_directionalLight;

};

}

#endif // PHONGSHADER_H
