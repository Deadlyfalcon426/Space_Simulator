#include "rk4_variables.h"

RK4::rk4_variables::rk4_variables(
    PhysicsVector3 current_r,
    PhysicsVector3 current_v
)
    : current_r(current_r),
      current_v(current_v),
      r_0(current_r),
      v_0(current_v),
      current_a(0,0,0,"m/s^2"),
      k1_r(0,0,0,"m"),
      k2_r(0,0,0,"m"),
      k3_r(0,0,0,"m"),
      k4_r(0,0,0,"m"),
      k1_v(0,0,0,"m/s"),
      k2_v(0,0,0,"m/s"),
      k3_v(0,0,0,"m/s"),
      k4_v(0,0,0,"m/s")
{}