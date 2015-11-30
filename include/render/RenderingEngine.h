#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

#include "render/Camera.h"
#include "render/Window.h"
#include <vector>

namespace taengine {

class GameObject;
class BaseLight;

class RenderingEngine
{
    public:
        RenderingEngine();
        virtual ~RenderingEngine();

        void draw(GameObject& gameObject, Camera& camera, Window& window);
        void addLight(BaseLight* light) { m_lights.emplace_back(light); }
        BaseLight* getLight() const { return m_activeLight; };
    protected:
    private:

        BaseLight* m_activeLight;
        std::vector<BaseLight*> m_lights;
};

}
#endif // RENDERINGENGINE_H
