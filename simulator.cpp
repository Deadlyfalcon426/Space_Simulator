#include <iostream>
#include <vector>
#include "CelestialBody.h"
#include "Vector3.h"
#include <cmath>

signed main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    CelestialBody sun = CelestialBody("Sun", 1.989*std::pow(10, 30), "km");

    return 0;
}

void setCourse(CelestialBody& body_of_interest, std::vector<CelestialBody>& gravitational_influences){
    Vector3 net_force = Vector3(0, 0, 0, "kg*m/s", "Force");

    for(CelestialBody& body : gravitational_influences){
        body_of_interest.get_gravitational_force(body, body_of_interest.get_position().distanceTo(body.get_position()));
    }
}

