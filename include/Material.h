#ifndef MATERIAL_H
#define MATERIAL_H

#include "Texture.h"
#include <glm/glm.hpp>

namespace taengine {

class Material
{
    public:
        Material();
        virtual ~Material();

        void init(const std::string& filePath, const glm::vec3& color = glm::vec3(1.0f));

        // Bind and unbind texture
        void bind() const;
        void unbind() const;

        inline glm::vec3 getColor() const { return m_color; }
    protected:
    private:
        // Not ideal, stil thinking how should I do this
        Texture m_texture;
        glm::vec3 m_color;
};

}

#endif // MATERIAL_H
