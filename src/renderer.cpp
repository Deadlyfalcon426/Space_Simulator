#include "renderer.h"

#include <string>

Renderer::Renderer()
{
    InitWindow(1280, 800, "Orbital System View");

    camera = { 0 };

    camera.position = { 0.0f, 40.0f, 35.0f };
    camera.target = { 0.0f, 0.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 55.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(120);
}

Renderer::~Renderer()//destructor! closes the class, useful for resource management
{
    CloseWindow();
}

Vector3 Renderer::toRenderPosition(const PhysicsVector3& position) const
{
    //main program uses meters, raylib can have a smaller coord system
    constexpr double SCALE = 1.0e10;//a constant expression, wont change and we can pass like complex stuff to it, like the e

    return {
        static_cast<float>(position.getX() / SCALE),
        static_cast<float>(position.getY() / SCALE),
        static_cast<float>(position.getZ() / SCALE)
    };
}

float Renderer::getRadius(const CelestialBody& body) const
{
    // These aren't real radii, they are for visual purposes
    if (body.get_name() == "sun")
        return 2.0f;

    if (body.get_name() == "earth")
        return 0.5f;

    if (body.get_name() == "mars")
        return 0.4f;

    return 0.3f;
}

void Renderer::update_frame(
    const std::vector<CelestialBody>& heavenly_vector)
{
    BeginDrawing();

    ClearBackground(BLACK);

    BeginMode3D(camera);

    // draw all celestial bodies at their current physical position.
    for (const CelestialBody& body : heavenly_vector)
    {
        Vector3 position = toRenderPosition(body.get_position());
        float radius = getRadius(body);

        if (body.get_name() == "sun")
        {
            DrawSphere(position, radius, YELLOW);
        }
        else if (body.get_name() == "earth")
        {
            DrawSphere(position, radius, BLUE);
        }
        else if (body.get_name() == "mars")
        {
            DrawSphere(position, radius, RED);
        }
        else
        {
            DrawSphere(position, radius, BLACK);
        }
    }

    DrawGrid(120, 1.0f);

    EndMode3D();

    DrawText("Orbital System View", 20, 20, 24, WHITE);

    EndDrawing();
}