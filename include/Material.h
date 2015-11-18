#ifndef MATERIAL_H
#define MATERIAL_H

#include "Texture.h"
#include <glm/glm.hpp>

namespace taengine {

class Material
{
    public:
        Material(const std::string& filePath = "", const glm::vec4& color = glm::vec4(1.0f,1.0f,1.0f,1.0f));
        virtual ~Material();

        // Bind and unbind texture
        void bind() const;
        void unbind() const;

        inline glm::vec4 getColor() const { return m_color; }
    protected:
    private:
        // Not ideal, stil thinking how should I do this
        Texture* m_texture = nullptr;
        glm::vec4 m_color;
};

}

#endif // MATERIAL_H
