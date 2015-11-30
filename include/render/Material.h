#ifndef MATERIAL_H
#define MATERIAL_H

#include "Texture.h"
#include <glm/glm.hpp>

namespace taengine {

class Material
{
    public:
        Material(const std::string& filePath, const glm::vec3& color = glm::vec3(1.0f),
                  float specularIntensity = 2.0f, float specularExponent = 32.0f);
        virtual ~Material();


        // Bind and unbind texture
        void bind() const;
        void unbind() const;

        inline glm::vec3 getColor() const { return m_color; }
        inline float getSpecularIntensity() const { return m_specularIntensity; }
        inline float getSpecularExponent() const { return m_specularExponent; }
    protected:
    private:
        // Not ideal, stil thinking how should I do this
        Texture m_texture;
        glm::vec3 m_color;

        // Reflection intensity
        float m_specularIntensity;
        // Reflection spreading
        float m_specularExponent;
};

}

#endif // MATERIAL_H
