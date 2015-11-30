#ifndef FORWARDPOINT_H
#define FORWARDPOINT_H

#include "render/Shader.h"

namespace taengine {

class ForwardPoint : public Shader
{
    public:
        static Shader& getInstance();

        virtual void updateUniforms(const Transform& transform, const Camera& camera,
                                    const Material& material, const RenderingEngine* renderingEngine) const override;
    protected:
        ForwardPoint();
        virtual ~ForwardPoint();

        virtual void addUniforms() override;
    private:
};

}

#endif // FORWARDPOINT_H
