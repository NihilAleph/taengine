#include "components/MeshRenderer.h"
#include "render/Shader.h"
#include "core/GameObject.h"

namespace taengine {


MeshRenderer::MeshRenderer(const Mesh* mesh, const Material* material)
{
    m_mesh = mesh;
    m_material = material;
}

MeshRenderer::~MeshRenderer()
{
    //dtor
}

void MeshRenderer::update(float deltaTime) {}
void MeshRenderer::draw(const Shader& shader, const Camera& camera, const RenderingEngine* renderingEngine)
{
    shader.bind();
    shader.updateUniforms(m_parent->getTransform(), camera, *m_material, renderingEngine);
    m_mesh->draw();
    shader.unbind();
}

}
