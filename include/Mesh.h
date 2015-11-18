#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include <vector>

namespace taengine {

// Vertex used by the mesh
struct Vertex
{
        glm::vec3 position;
        glm::vec2 uvCoord;
        Vertex(const glm::vec3& pos) : position(pos), uvCoord(glm::vec2(0.0f,0.0f)) {};
        Vertex(const glm::vec3& pos, const glm::vec2& uv) : position(pos), uvCoord(uv) {};
};

class Mesh
{
    public:
        // Create mesh by loading obj file
        Mesh(std::string objFileName);
        // Create mesh by vertices and indices vector
        Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
        virtual ~Mesh();

        void draw() const;
    protected:
    private:

        // Vertex Array Object ID
        GLuint m_vaoID;
        // Vertex Buffer ID
        GLuint m_vboID;
        // Index Buffer ID
        GLuint m_iboID;
        // Number of vertices applied to mesh
        unsigned int m_numIndices = 0;

        // Initialize mesh with vertices and indices vector
        void initMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

};

}

#endif // MESH_H
