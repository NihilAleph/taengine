#include "Mesh.h"
#include <iostream>

namespace taengine {

Mesh::Mesh(Vertex *vertices, unsigned int *indices, unsigned int numIndices)
{
    // Retain number of vertices
    m_numIndices = numIndices;

    // Create and bind vertex array object
    glGenVertexArrays(1, &m_vaoID);
    glBindVertexArray(m_vaoID);

    // Create and bind vertex buffer object
    glGenBuffers(1, &m_vboID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

    // Enables attribute for position to be passed to vertex shader
    glEnableVertexAttribArray(0);

    // Specifies the attribute pointer to position from vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, position));

    // Send vertex data to GPU
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * sizeof(taengine::Vertex), vertices, GL_STATIC_DRAW);

    // Create and bind index buffer object
    glGenBuffers(1, &m_iboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboID);

    // Send indices to GPU
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    // Unbind vertex buffer and array
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Mesh::~Mesh()
{
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
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboID);
    glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);

    // Unbind vertex array object
    glBindVertexArray(0);
}

}
