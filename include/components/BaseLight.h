#ifndef BASELIGHT_H
#define BASELIGHT_H

#include "core/GameComponent.h"

namespace taengine {

class BaseLight : public GameComponent
{
    public:
        BaseLight(const glm::vec3& color, float intensity);
        virtual ~BaseLight();

        virtual void draw(const Transform& transform, const Shader& shader, const Camera& camera) {};

        virtual void addToEngine(RenderingEngine* renderingEngine) override;

        void setColor(const glm::vec3& color) { m_color = color; }
        void setIntensity(float intensity) { m_intensity = intensity; }
        void setShader(Shader* shader) { m_shader = shader; }

        glm::vec3 getColor() { return m_color; }
        float getIntensity() { return m_intensity; }
        Shader* getShader() { return m_shader; }
    protected:

        glm::vec3 m_color;
        float m_intensity;

        Shader* m_shader = nullptr;
    private:
};

}

#endif // BASELIGHT_H
