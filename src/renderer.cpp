#include <raylib.h>
#include "PhysicsVector3.h"
#include "renderer.h"

Renderer::Renderer(){
    camera = { 0 };
}

void Renderer::setup(){
    InitWindow(1280,800,"Orbital System View");

    camera.position = { 16.0f, 16.0f, 16.0f }; //passes a 3d vector, obvs position
    camera.target = {0.0f, 0.0f, 0.0f}; //looking at...
    camera.up = {0.0f, 2.0f, 0.0f}; //rotation towards target
    camera.fovy = 45.0f; //camera y-field of view, vertical stretch? FOV=field of view, sort of like minecraft, just stretches it yeah
    camera.projection
    


    SetTargetFPS(60);
    //check if escape, or close window button has been pressed
    
}


void end_render(){

}
