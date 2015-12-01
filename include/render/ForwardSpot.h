#ifndef FORWARDSPOT_H
#define FORWARDSPOT_H

#include "render/Shader.h"

namespace taengine {

class ForwardSpot : public Shader
{
    public:
        static Shader& getInstance();

        virtual void updateUniforms(const Transform& transform, const Camera& camera,
                                    const Material& material, const RenderingEngine* renderingEngine) const override;
    protected:
        ForwardSpot();
        virtual ~ForwardSpot();

        virtual void addUniforms() override;
    private:
};

}

#endif // FORWARDSPOT_H
