#include <vector>
#pragma once
Vector3 get_all_gravitational_force_for_a_body(CelestialBody& body_of_interest, std::vector<CelestialBody>& gravitational_influences);
void applyForce(CelestialBody& body_of_interest, Vector3 force);
void updateKinematics(CelestialBody& target, double dt);

void euler_step(std::vector<CelestialBody>& heavenly_vector, double dt);
void runge_kutta_4_step(std::vector<CelestialBody>& heavenly_vector, double dt);
