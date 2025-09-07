#include "simulation_orchestrator.h"
#include <iostream>
int main() {
  try {
    SimulationOrchestrator simulation;
    simulation.run();
  } catch (...) {
    std::cerr << "main() caught error from sim" << std::endl;
  }
}
