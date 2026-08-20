#include <vector>
#include <string>
#pragma once
void all_g_acceleration(std::vector<CelestialBody>& gravitational_influences);
void applyForce(CelestialBody& body_of_interest, Vector3 force);
void updateVelocity(CelestialBody& target, double dt);

void euler_step(std::vector<CelestialBody>& heavenly_vector, double dt);
void runge_kutta_4_step(std::vector<CelestialBody>& heavenly_vector, double dt);
void sim(std::vector<CelestialBody>& heavenly_vector, double time_passed, double step, std::string choice);
void print_heavenly_vector(std::vector<CelestialBody>& heavenly_vector);