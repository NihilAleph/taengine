#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include "Transform.h"
#include "Camera.h"
#include "Material.h"
#include <unordered_map>

namespace taengine {

class Shader
{
    public:
        Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        virtual ~Shader();

        // Updates uniforms of the shader. Must be overridden if Shader demands other uniforms
        // This shader only use the uniform MVP for transform
        virtual void updateUniforms(const Transform& transform, const Camera& camera, const Material& material) const;

        // Draw vetices. Must be overridden if shader demands other attributes
        // virtual void draw();

        // Bind everything necessary to render using this Shader
        void bind() const;
        // Unbind this shader to GPU so other shader can be used
        void unbind() const;

        // Add uniform to map
        void addUniform(const std::string& name);

        // Generic update functions for uniforms
        void setUniform(const std::string& name, int value) const;
        void setUniform(const std::string& name, float value) const;
        void setUniform(const std::string& name, const glm::vec3& value) const;
        void setUniform(const std::string& name, const glm::vec4& value) const;
        void setUniform(const std::string& name, const glm::mat4& value) const;

    protected:
        GLuint m_programID;

        // Hash map for all uniforms in the shader
        std::unordered_map<std::string, GLuint> m_uniformMap;

        // Load shader from file to specified ID
        bool loadShader(const GLuint shaderID, const std::string& filePath);

    private:

        // Bind attributes of the shader. Must be overridden if Shader demands other attributes
        // This method is called during constructor before shaders' linking
        // This shader only use the attribute position
//        virtual void bindAttributes();


};

}

#endif // SHADER_H
