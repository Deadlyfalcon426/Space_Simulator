#include <vector>
#include <string>
#include "Vector3.h"
#include "CelestialBody.h"
#include "rk4_variables.h"
#pragma once

void all_g_acceleration(std::vector<CelestialBody>& gravitational_influences);
void all_g_acceleration_theoretical(std::vector<CelestialBody>& gravitational_influences, std::vector<RK4::rk4_variables>& variables);
Vector3 applyForce(CelestialBody& body_of_interest, Vector3 force);
void updateVelocity(CelestialBody& target, double dt);

void update_runge_kutta_acceleration(std::vector<CelestialBody>& gravitational_influences, std::vector<RK4::rk4_variables>& variables);
void euler_step(std::vector<CelestialBody>& heavenly_vector, double dt);
void runge_kutta_4_step(std::vector<CelestialBody>& heavenly_vector, double dt);
void sim(std::vector<CelestialBody>& heavenly_vector, double time_passed, double step, std::string choice);
void print_heavenly_vector(std::vector<CelestialBody>& heavenly_vector);