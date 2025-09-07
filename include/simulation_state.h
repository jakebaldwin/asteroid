#ifndef SIMULATION_STATE_H
#define SIMULATION_STATE_H

#include "asteroid.h"
#include "earth.h"
#include <vector>

struct SimulationState {
  std::vector<Asteroid> asteroids;
  Earth earth;
};

#endif
