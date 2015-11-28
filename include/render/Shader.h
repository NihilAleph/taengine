#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include "core/Transform.h"
#include "render/Camera.h"
#include "render/Material.h"
#include <unordered_map>

namespace taengine {

class Shader
{
    public:

        static Shader& getInstance();

        // Updates uniforms of the shader. Must be overridden if Shader demands other uniforms
        // This shader only use the uniform MVP for transform
        virtual void updateUniforms(const Transform& transform, const Camera& camera, const Material& material) const;

        // Bind everything necessary to render using this Shader
        void bind() const;
        // Unbind this shader to GPU so other shader can be used
        void unbind() const;



    protected:

        GLuint m_programID;

        // Hash map for all uniforms in the shader
        std::unordered_map<std::string, GLuint> m_uniformMap;

        Shader();
        virtual ~Shader();

        void init(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

        // Load shader from file to specified ID
        bool loadShader(const GLuint shaderID, const std::string& filePath);
        // Add all uniforms to be used by the shader
        virtual void addUniforms();
        // Add uniform to map
        void addUniform(const std::string& name);

        // Generic update functions for uniforms
        void setUniform(const std::string& name, int value) const;
        void setUniform(const std::string& name, float value) const;
        void setUniform(const std::string& name, const glm::vec3& value) const;
        void setUniform(const std::string& name, const glm::vec4& value) const;
        void setUniform(const std::string& name, const glm::mat4& value) const;

    private:

        // Bind attributes of the shader. Must be overridden if Shader demands other attributes
        // This method is called during constructor before shaders' linking
        // This shader only use the attribute position
//        virtual void bindAttributes();


};

}

#endif // SHADER_H
