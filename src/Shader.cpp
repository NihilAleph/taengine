#include "Shader.h"
#include <fstream>
#include <vector>
#include <iostream>

namespace taengine {

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    // Create shaders ID
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // If successfully load both shaders
    if (loadShader(vertexShaderID, vertexShaderPath) && loadShader(fragmentShaderID, fragmentShaderPath)) {
        // Create program object
        m_programID = glCreateProgram();

        // Bind attributes to program
        bindAttributes();

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
}

Shader::~Shader()
{
    glDeleteProgram(m_programID);
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

void Shader::bindAttributes()
{
    // Bind attribute position to index 0
//    glBindAttribLocation(m_programID, 0, "position");
}

//void Shader::updateUniforms(const Transform& transform, const Camera& camera)
void Shader::updateUniforms(const Transform& transform, const Camera& camera)
{
    // Get transform and camera matrix
    //glm::mat4 MVP = transform.getMVP(camera);
    glm::mat4 MVP = camera.getProjection() * transform.getModel();

    // Get uniform location
    GLuint mvpUniform = glGetUniformLocation(m_programID, "MVP");

    // Check if uniform exists
    if (mvpUniform == 0xFFFFFFFF) {
        std::cerr << "Uniform MVP not found" << std::endl;
    }

    // Update uniform value
    glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, &MVP[0][0]);

}

void Shader::bind()
{
    // Set this shader to render
    glUseProgram(m_programID);

}

void Shader::unbind()
{
    // Unbind gpu shader
    glUseProgram(0);
}



}
