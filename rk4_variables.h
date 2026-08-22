#pragma once
#include "Vector3.h"
namespace RK4{
    struct rk4_variables {
        Vector3 const v_0;
        Vector3 const r_0;

        Vector3 current_r;
        Vector3 current_v;
        Vector3 current_a;

        Vector3 k1_r;
        Vector3 k2_r;
        Vector3 k3_r;
        Vector3 k4_r;

        Vector3 k1_v;
        Vector3 k2_v;
        Vector3 k3_v;
        Vector3 k4_v;

        rk4_variables(Vector3 current_r, Vector3 current_v);
    };
}