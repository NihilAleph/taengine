#include "Texture.h"
#include <iostream>
#include <SOIL\SOIL.h>

namespace taengine {

Texture::Texture(const std::string& filePath)
{
    // Load an image file directly as a new OpenGL texture through SOIL library
    m_id = SOIL_load_OGL_texture
        (
            filePath.c_str(),
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
        );

    // If couldn't load texture, print error
    if (m_id == 0) {
        std::cerr << "Unable to load texture " << filePath << std::endl;
    }
}

Texture::~Texture()
{
    // Delete texture from GPU
    glDeleteTextures(1, &m_id);
}

void Texture::bind()
{
    // Bind this texture to gpu
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::unbind()
{
    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

}
