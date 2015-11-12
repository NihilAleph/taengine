#include "Mesh.h"
#include <iostream>

namespace taengine {

Mesh::Mesh(Vertex *vertices, unsigned int numVertices)
{
    // Retain number of vertices
    m_numVertices = numVertices;

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

    // Send data to GPU
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vertex), vertices, GL_STATIC_DRAW);

    // Unbind vertex buffer and array
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &m_vboID);
    glDeleteVertexArrays(1, &m_vaoID);
}

void Mesh::draw()
{
    // Bind mesh vertex array
    glBindVertexArray(m_vaoID);

    // Draw vertices as triangles
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Unbind vertex array object
    glBindVertexArray(0);
}

}
