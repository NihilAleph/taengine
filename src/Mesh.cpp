#include "Mesh.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

namespace taengine {

// Support function that split string with a delimiter
// Used when loading mesh from obj
static std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        if (!item.empty())
            elems.push_back(item);
    }
    return elems;
}


static std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

Mesh::Mesh(std::string objFilePath)
{

    // Vertices and indices vector that will be populated by the file
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // Open file for stream
    std::ifstream fileStream;
    fileStream.open(objFilePath.c_str(), std::ios::in);

    // If file opened
    if (fileStream.is_open()) {

        // Line read from the file
        std::string line = "";

        // While file still has lines to be read
        while (fileStream.good()) {
            getline(fileStream, line);

            if (!line.empty()) {

                // Split line by space character
                std::vector<std::string> lineVector = split(line, ' ');


                switch (lineVector[0].at(0))
                {
                // If first character of the line is v, then it's a vertex
                case 'v':
                    vertices.push_back(Vertex(glm::vec3(std::atof(lineVector[1].c_str()),
                                                        std::atof(lineVector[2].c_str()),
                                                        std::atof(lineVector[3].c_str()))));
                    break;
                // If first character is a f, then it's a face
                case 'f':
                    // Obj file format has indices starting from 1
                    indices.push_back(std::atoi(lineVector[1].c_str()) - 1);
                    indices.push_back(std::atoi(lineVector[2].c_str()) - 1);
                    indices.push_back(std::atoi(lineVector[3].c_str()) - 1);
                    break;
                default:
                    break;
                }
            }
        }

        fileStream.close();

        initMesh(vertices, indices);

    } else {
        std::cerr << "Unable to open OBJ file " << objFilePath << std::endl;
    }

}


Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
    // Retain number of vertices
    initMesh(vertices, indices);

}

Mesh::~Mesh()
{
    // Delete buffers associated to this mesh from GPU
    glDeleteBuffers(1, &m_iboID);
    glDeleteBuffers(1, &m_vboID);
    glDeleteVertexArrays(1, &m_vaoID);
}

void Mesh::draw()
{
    // Bind mesh vertex array
    glBindVertexArray(m_vaoID);

    // Draw vertices as triangles
    // glDrawArrays(GL_TRIANGLES, 0, m_numVertices);
    glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);

    // Unbind vertex array object
    glBindVertexArray(0);
}

void Mesh::initMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
    m_numIndices = indices.size();

    // Create and bind vertex array object
    glGenVertexArrays(1, &m_vaoID);
    glBindVertexArray(m_vaoID);

    // Create and bind vertex buffer object
    glGenBuffers(1, &m_vboID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

    // Enables attribute for position and uvCoord to be passed to vertex shader
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // Specifies the attribute pointer to position from vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, position));

    // Specifies the attribute pointer to uvCoord from vertex
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, uvCoord));

    // Send vertex data to GPU
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(taengine::Vertex), &vertices[0], GL_STATIC_DRAW);

    // Create and bind index buffer object
    glGenBuffers(1, &m_iboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboID);

    // Send indices to GPU
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // Unbind vertex buffer and array
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

}
