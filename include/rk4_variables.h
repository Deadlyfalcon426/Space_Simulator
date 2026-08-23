#pragma once
#include "PhysicsVector3.h"
namespace RK4{
    struct rk4_variables {
        PhysicsVector3 const v_0;
        PhysicsVector3 const r_0;

        PhysicsVector3 current_r;
        PhysicsVector3 current_v;
        PhysicsVector3 current_a;

        PhysicsVector3 k1_r;
        PhysicsVector3 k2_r;
        PhysicsVector3 k3_r;
        PhysicsVector3 k4_r;

        PhysicsVector3 k1_v;
        PhysicsVector3 k2_v;
        PhysicsVector3 k3_v;
        PhysicsVector3 k4_v;

        rk4_variables(PhysicsVector3 current_r, PhysicsVector3 current_v);
    };
}