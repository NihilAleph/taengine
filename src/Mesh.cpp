#include "Mesh.h"
#include <iostream>
#include <fstream>
#include <sstream>

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



Mesh::Mesh()
{

}

Mesh::~Mesh()
{
    // Delete buffers associated to this mesh from GPU
    glDeleteBuffers(1, &m_iboID);
    glDeleteBuffers(1, &m_vboID);
    glDeleteVertexArrays(1, &m_vaoID);
}


void Mesh::init(const std::string& objFilePath)
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
                    vertices.push_back(Vertex(glm::vec3(std::stof(lineVector[1]),
                                                        std::stof(lineVector[2]),
                                                        std::stof(lineVector[3]))));
                    break;
                // If first character is a f, then it's a face
                case 'f':
                    // Obj file format has indices starting from 1
                    indices.push_back(std::stoi(lineVector[1]) - 1);
                    indices.push_back(std::stoi(lineVector[2]) - 1);
                    indices.push_back(std::stoi(lineVector[3]) - 1);
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



void Mesh::init(std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, bool hasNormals)

{
    // Calculate Normals
    if (!hasNormals)
        calculateNormals(vertices, indices);

    // Retain number of vertices
    initMesh(vertices, indices);


}

void Mesh::draw() const
{
    // Bind mesh vertex array
    glBindVertexArray(m_vaoID);

    // Enables vertex attribute arrays for draw
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // Draw vertices as triangles
    // glDrawArrays(GL_TRIANGLES, 0, m_numVertices);
    glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);

    // Disables again the arrays
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

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

    // Enables attribute for position, uvCoord and normals to be passed to vertex shader
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // Specifies the attribute pointer to position from vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, position));

    // Specifies the attribute pointer to uvCoord from vertex
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, uvCoord));

    // Specifies the attribute pointer to normal from vertex
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, normal));

    // Send vertex data to GPU
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(taengine::Vertex), &vertices[0], GL_STATIC_DRAW);

    // Create and bind index buffer object
    glGenBuffers(1, &m_iboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboID);

    // Send indices to GPU
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // Disable all Vertex Attrib Array

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

    // Unbind vertex buffer and array
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::calculateNormals(std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
    // Iterate through all faces
    for (unsigned int i = 0; i < indices.size(); i+= 3) {
        // Get all indices of a face
        int i0 = indices[i];
        int i1 = indices[i + 1];
        int i2 = indices[i + 2];

        // Get vertices and transform to normal of the face
        glm::vec3 v1 = vertices[i1].position - vertices[i0].position;
        glm::vec3 v2 = vertices[i2].position - vertices[i0].position;

        glm::vec3 normal = glm::normalize(glm::cross(v1,v2));

        // Add normal to vertex
        vertices[i0].normal += normal;
        vertices[i1].normal += normal;
        vertices[i2].normal += normal;
    }

    // Normalize all vertex normals
    for (auto &i : vertices) {
        i.normal = glm::normalize(i.normal);
    }
}


}
