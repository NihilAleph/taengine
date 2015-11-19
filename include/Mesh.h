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
        Vertex(const glm::vec3& pos) : position(pos), uvCoord(glm::vec2(0.0f)) {};
        Vertex(const glm::vec3& pos, const glm::vec2& uv) : position(pos), uvCoord(uv) {};
};

class Mesh
{
    public:
        Mesh();
        virtual ~Mesh();

        // Init mesh by loading obj file
        void init(const std::string& objFilePath);
        // Init mesh by vertices and indices vector
        void init (const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

        void draw() const;
    protected:
    private:

        // Vertex Array Object ID
        GLuint m_vaoID = 0;
        // Vertex Buffer ID
        GLuint m_vboID = 0;
        // Index Buffer ID
        GLuint m_iboID = 0;
        // Number of vertices applied to mesh
        unsigned int m_numIndices = 0;

        // Initialize mesh with vertices and indices vector
        void initMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

};

}

#endif // MESH_H
