#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

namespace taengine {

class Shader
{
    public:
        Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        virtual ~Shader();

        // Updates uniforms of the shader. Must be overridden if Shader demands other uniforms
        // This shader only use the uniform MVP for transform
        // virtual void updateUniforms(const Transform& transform, const Camera& camera);

        // Draw vetices. Must be overridden if shader demands other attributes
        // virtual void draw();

        // Bind everything necessary to render using this Shader
        virtual void bind();
        // Unbind this shader to GPU so other shader can be used
        virtual void unbind();

    protected:
        GLuint m_programID;

    private:
        // Load shader from file to specified ID
        bool loadShader(const GLuint shaderID, const std::string& filePath);

        // Bind attributes of the shader. Must be overridden if Shader demands other attributes
        // This method is called during constructor before shaders' linking
        // This shader only use the attribute position
        virtual void bindAttributes();


};

}

#endif // SHADER_H
