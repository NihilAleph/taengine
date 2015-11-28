#include "render/Shader.h"
#include <fstream>
#include <vector>
#include <iostream>

namespace taengine {

Shader& Shader::getInstance()
{
    static Shader instance;

    return instance;
}

Shader::Shader()
{
    init("res/basicShader.vs", "res/basicShader.fs");
}

Shader::~Shader()
{
    // Delete shader from GPU
//    glDeleteProgram(m_programID);
}

void Shader::init(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    // Create shaders ID
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // If successfully load both shaders
    if (loadShader(vertexShaderID, vertexShaderPath) && loadShader(fragmentShaderID, fragmentShaderPath)) {
        // Create program object
        m_programID = glCreateProgram();

        // Link shaders to program
        glAttachShader(m_programID, vertexShaderID);
        glAttachShader(m_programID, fragmentShaderID);
        glLinkProgram(m_programID);

        // Variable to check link
        GLint success = GL_FALSE;

        // Check if link status
        glGetProgramiv(m_programID, GL_LINK_STATUS, &success);

        // If link wasn't successful then load info log
        if (success == GL_FALSE) {
            // Get size of info log
            int infoLogLength;
            glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);

            // Get Info Log
            std::vector<char> infoLog(infoLogLength);
            glGetProgramInfoLog(m_programID, infoLogLength, NULL, &infoLog[0]);

            // Print info log
            for (const auto& i : infoLog) {
                std::cerr << i;
            }
            std::cerr << std::endl;
        }

        // Detach shaders
        glDetachShader(m_programID, vertexShaderID);
        glDetachShader(m_programID, fragmentShaderID);
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
    }

    // Call the function that add uniforms to be used by the shader accordingly to implementation (overridden)
    addUniforms();
}

bool Shader::loadShader(const GLuint shaderID, const std::string& filePath)
{

    // Open file for stream
    std::ifstream fileStream;
    fileStream.open(filePath.c_str(), std::ios::in);


    // If file opened
    if (fileStream.is_open()) {

        // Variable to hold the code
        std::string code = "";
        std::string line = "";
        // While file still has line append to code variable
        while (fileStream.good()) {
            getline(fileStream,line);
            code += "\n" + line;
        }

        // After finish stream close the file
        fileStream.close();

        // Transform code into const GLchar* so glShaderSource accept it
        const GLchar* constCode[1];
        constCode[0] = code.c_str();

        // Load shader source to compile
        glShaderSource(shaderID, 1, constCode, NULL);
        // Compile shader
        glCompileShader(shaderID);


        // Variables to check shader
        GLint success = GL_FALSE;
        // Check compile status of shader
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

        // If compile wasn't successful then load info log
        if (success == GL_FALSE) {
            // Get size of info log
            int infoLogLength;
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

            // Get Info Log
            std::vector<char> infoLog(infoLogLength);
            glGetShaderInfoLog(shaderID, infoLogLength, NULL, &infoLog[0]);

            // Print info log
            for (const auto& i : infoLog) {
                std::cerr << i;
            }
            std::cerr << std::endl;

            return false;

        }

    } else {
        std::cerr << "Unable to load shader " << filePath << std::endl;
        return false;
    }

    return true;

}

//void Shader::updateUniforms(const Transform& transform, const Camera& camera)
void Shader::updateUniforms(const Transform& transform, const Camera& camera, const Material& material) const
{
    // Get transform and camera matrix
    //glm::mat4 MVP = transform.getMVP(camera);
    glm::mat4 MVP = camera.getProjection() * transform.getModel();

    // Update uniform values
    setUniform("MVP", MVP);
    setUniform("color", material.getColor());

    // Bind texture (if any)
    material.bind();

}

void Shader::bind() const
{
    // Set this shader to render
    glUseProgram(m_programID);

}

void Shader::unbind() const
{
    // Unbind gpu shader
    glUseProgram(0);

    // Unbind textures
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Shader::addUniforms()
{
    addUniform("MVP");
    addUniform("color");
}

void Shader::addUniform(const std::string& name)
{
    GLuint uniformLocation = glGetUniformLocation(m_programID, name.c_str());

    // Check if uniform exists
    if (uniformLocation == 0xFFFFFFFF) {
        std::cerr << "Uniform " << name << " could not be added!" << std::endl;
    } else {

        m_uniformMap[name] = uniformLocation;
    }
}


void Shader::setUniform(const std::string& name, int value) const
{
    // Search for value in current state hash map
    auto it = m_uniformMap.find(name);
    // Verify if key exists in map and it's a
    if (it != m_uniformMap.end()) {
        glUniform1i(it->second, value);
    } else {
        std::cerr << "Uniform " << name << " not found" << std::endl;
    }

}
void Shader::setUniform(const std::string& name, float value) const
{
    // Search for value in current state hash map
    auto it = m_uniformMap.find(name);
    // Verify if key exists in map and it's a
    if (it != m_uniformMap.end()) {
        glUniform1f(it->second, value);
    } else {
        std::cerr << "Uniform " << name << " not found" << std::endl;
    }
}
void Shader::setUniform(const std::string& name, const glm::vec3& value) const
{
    // Search for value in current state hash map
    auto it = m_uniformMap.find(name);
    // Verify if key exists in map and it's a
    if (it != m_uniformMap.end()) {
        glUniform3fv(it->second, 1, &value[0]);
    } else {
        std::cerr << "Uniform " << name << " not found" << std::endl;
    }
}
void Shader::setUniform(const std::string& name, const glm::vec4& value) const
{
    // Search for value in current state hash map
    auto it = m_uniformMap.find(name);
    // Verify if key exists in map and it's a
    if (it != m_uniformMap.end()) {
        glUniform4fv(it->second, 1, &value[0]);
    } else {
        std::cerr << "Uniform " << name << " not found" << std::endl;
    }
}
void Shader::setUniform(const std::string& name, const glm::mat4& value) const
{
    // Search for value in current state hash map
    auto it = m_uniformMap.find(name);
    // Verify if key exists in map and it's a
    if (it != m_uniformMap.end()) {
        glUniformMatrix4fv(it->second, 1, GL_FALSE, &value[0][0]);
    } else {
        std::cerr << "Uniform " << name << " not found" << std::endl;
    }
}


}
