#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include "core/GameComponent.h"
#include "render/Material.h"
#include "render/Mesh.h"

namespace taengine {

class MeshRenderer : public GameComponent
{
    public:
        MeshRenderer(const Mesh* mesh, const Material* material);
        virtual ~MeshRenderer();

        virtual void update(float deltaTime) override;
        virtual void draw(const Shader& shader,
                          const Camera& camera, const RenderingEngine* renderingEngine) override;
    protected:
    private:

        const Mesh* m_mesh;
        const Material* m_material;
};

}
#endif // MESHRENDERER_H
