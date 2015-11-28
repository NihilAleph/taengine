#include "render/Material.h"

namespace taengine {

Material::Material()
{

}

Material::~Material()
{

}

void Material::init(const std::string& filePath, const glm::vec3& color,
                    float specularIntensity, float specularExponent)
{

    m_texture.init(filePath);

    m_color = color;
    m_specularIntensity = specularIntensity;
    m_specularExponent = specularExponent;
}

void Material::bind() const
{
    m_texture.bind();
}

void Material::unbind() const
{
    m_texture.unbind();
}

}
