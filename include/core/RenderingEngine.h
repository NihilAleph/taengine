#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

#include "core/GameObject.h"
#include "render/Camera.h"
#include "render/Window.h"

namespace taengine {

class RenderingEngine
{
    public:
        RenderingEngine();
        virtual ~RenderingEngine();

        void draw(GameObject& gameObject, Camera& camera, Window& window);
    protected:
    private:
};

}
#endif // RENDERINGENGINE_H
