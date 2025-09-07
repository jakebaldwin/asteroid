#ifndef SIMULATION_ORCHESTRATOR_H
#define SIMULATION_ORCHESTRATOR_H

#include "logger.h"
#include "open_gl_manager.h"
#include "renderer.h"
#include "simulation_state.h"
#include "simulator.h"
#include "thread_manager.h"

class SimulationOrchestrator {

public:
  SimulationOrchestrator();

  void run();

  void runSimulationLoop();

private:
  void initializeSimulationStates();

  std::unique_ptr<OpenGlManager> open_gl_;
  std::unique_ptr<Simulator> simulator_;
  std::unique_ptr<Renderer> renderer_;
  std::unique_ptr<Logger> logger_;

  std::unique_ptr<SimulationState> current_state_;
  std::unique_ptr<SimulationState> next_state_;
};
#endif
