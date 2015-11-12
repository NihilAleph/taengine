#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <GL/glew.h>

namespace taengine {

// Vertex used by the mesh
struct Vertex
{
        glm::vec3 position;
        Vertex(const glm::vec3& pos) : position(pos) {};
};

class Mesh
{
    public:
        Mesh(Vertex* vertices, unsigned int numVertices);
        virtual ~Mesh();

        void draw();
    protected:
    private:

        // Vertex Array Object ID
        GLuint m_vaoID;
        // Vertex Buffer ID
        GLuint m_vboID;
        // Number of vertices applied to mesh
        unsigned int m_numVertices = 0;
};

}

#endif // MESH_H
