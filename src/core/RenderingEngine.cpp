#include "core/RenderingEngine.h"

#include "render/Window.h"

namespace taengine {

RenderingEngine::RenderingEngine()
{
    //ctor
}

RenderingEngine::~RenderingEngine()
{
    //dtor
}

void RenderingEngine::draw(GameObject& gameObject, Camera& camera, Window& window)
{

    gameObject.draw(Shader::getInstance(), camera);

    // Swap buffer and clear window
    window.swapBuffers();
    window.clear(0.0f,0.0f,0.0f,1.0f);
}


}
