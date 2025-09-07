#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "simulation_state.h"

class Simulator {

public:
  Simulator() = default;

  void update(SimulationState &state, double delta_time);

private:
  SimulationState state_;
};

#endif
