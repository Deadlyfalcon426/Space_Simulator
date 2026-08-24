#pragma once

#include <raylib.h>
#include <vector>

#include "CelestialBody.h"
#include "PhysicsVector3.h"

class Renderer
{
private:
    Camera3D camera;

    // Convert physics units (meters) into units more reasonable for raylib
    Vector3 toRenderPosition(const PhysicsVector3& position) const;

    // visual radius for each celestial body.
    float getRadius(const CelestialBody& body) const;

public:
    Renderer();
    ~Renderer();

    void update_frame(const std::vector<CelestialBody>& heavenly_vector);
};