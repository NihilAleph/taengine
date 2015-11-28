#ifndef GAMECOMPONENT_H
#define GAMECOMPONENT_H

#include "core/Transform.h"
#include "render/Shader.h"
#include "render/Camera.h"

namespace taengine {

class GameComponent
{
    public:
//        GameComponent() {};
//        virtual ~GameComponent() {};

        virtual void update(Transform& transform, float deltaTime) {};
        virtual void draw(const Transform& transform, Shader& shader, const Camera& camera) {};
    protected:
    private:
};

}

#endif // GAMECOMPONENT_H
