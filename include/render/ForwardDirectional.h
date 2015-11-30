#ifndef FORWARDDIRECTIONAL_H
#define FORWARDDIRECTIONAL_H

#include "render/Shader.h"

namespace taengine {

class ForwardDirectional : public Shader
{
    public:
        static Shader& getInstance();

        virtual void updateUniforms(const Transform& transform, const Camera& camera,
                                    const Material& material, const RenderingEngine* renderingEngine) const override;
    protected:
        ForwardDirectional();
        virtual ~ForwardDirectional();

        virtual void addUniforms() override;
    protected:
    private:
};

}

#endif // FORWARDDIRECTIONAL_H
