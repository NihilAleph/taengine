#include "render/RenderingEngine.h"
#include "render/Window.h"
#include "render/ForwardAmbient.h"
#include "core/GameObject.h"
#include "components/BaseLight.h"

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

    m_lights.clear();

    gameObject.addToEngine(this);
    gameObject.draw(ForwardAmbient::getInstance(), camera, this);

    // To draw lighting, add alpha blending and disable depth mask

    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_EQUAL);

    for (auto &light : m_lights)
    {
        m_activeLight = light;
        gameObject.draw(*m_activeLight->getShader(), camera, this);
    }


    // Return to original configuration
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);



    // Swap buffer and clear window
    window.swapBuffers();
    window.clear(0.0f,0.0f,0.0f,1.0f);
}


}
