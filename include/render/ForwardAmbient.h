#ifndef FORWARDAMBIENT_H
#define FORWARDAMBIENT_H

#include "render/Shader.h"

namespace taengine {

class ForwardAmbient : public Shader
{
    public:
        static Shader& getInstance();

        virtual void updateUniforms(const Transform& transform, const Camera& camera,
                                    const Material& material, const RenderingEngine* renderingEngine) const override;
        void setAmbientLight(const glm::vec3& ambientLight);
    protected:
        ForwardAmbient();
        virtual ~ForwardAmbient();

        virtual void addUniforms() override;
    private:

        glm::vec3 m_ambientLight;
};

}
#endif // FORWARDAMBIENT_H
