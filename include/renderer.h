#include <raylib.h>
#include "PhysicsVector3.h"
class Renderer {
    private:
        Camera3D camera;
    public:
        Renderer();
        void setup();
        void end_render();
        bool shouldClose() const;
        void beginFrame();
        void endFrame();

};