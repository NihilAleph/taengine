#include "Material.h"

namespace taengine {

Material::Material(const std::string& filePath, const glm::vec4& color)
{
    if (!filePath.empty()) {
        m_texture = new Texture(filePath);
    }

    m_color = color;
}

Material::~Material()
{
    delete m_texture;
}

void Material::bind() const
{
    if (m_texture != nullptr)
        m_texture->bind();
}

void Material::unbind() const
{
    if (m_texture != nullptr)
        m_texture->unbind();
}

}
