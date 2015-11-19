#ifndef PHONGSHADER_H
#define PHONGSHADER_H

#include "Shader.h"

namespace taengine {

class PhongShader : public Shader
{
    public:
        PhongShader();
        virtual ~PhongShader();

        // Change how shader updates uniform
        void updateUniforms(const Transform& transform, const Camera& camera, const Material& material) const override;

        void setAmbientLight(const glm::vec3& ambientLight);
        glm::vec3 getAmbientLight();
    protected:
        // Change the uniforms used in this shader
        void addUniforms() override;
    private:
        glm::vec3 m_ambientLight;

};

}

#endif // PHONGSHADER_H
