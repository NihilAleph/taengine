#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include <GL/glew.h>

namespace taengine {
class Texture
{
    public:
        Texture(const std::string& filePath);
        virtual ~Texture();

        // Bind and unbind texture to GPU
        void bind() const;
        void unbind() const;
    protected:
    private:

        GLuint m_id;
};

}

#endif // TEXTURE_H
