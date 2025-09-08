#include "simulation_orchestrator.h"
#include <iostream>

SimulationOrchestrator::SimulationOrchestrator()
    : open_gl_(std::make_unique<OpenGlManager>()),
      simulator_(std::make_unique<Simulator>()),
      renderer_(std::make_unique<Renderer>(*open_gl_)),
      logger_(std::make_unique<Logger>()),
      current_state_(std::make_unique<SimulationState>()),
      next_state_(std::make_unique<SimulationState>()) {}

void SimulationOrchestrator::run() {
  try {
    open_gl_->initialize();
    open_gl_->createWindow();
    renderer_->initializeShaders();
    initializeSimulationStates();
    runSimulationLoop();
  } catch (...) {
    std::cout << "error in main loop caught" << std::endl;
  }
}

void SimulationOrchestrator::runSimulationLoop() {
  double delta_time = 0.1;
  while (!glfwWindowShouldClose(open_gl_->getWindow())) {

    renderer_->draw(*current_state_);

    simulator_->update(*next_state_, delta_time);

    std::swap(next_state_, current_state_);

    glfwSwapBuffers(open_gl_->getWindow());
    glfwPollEvents();
  }

  glfwDestroyWindow(open_gl_->getWindow());
  glfwTerminate();
}

void SimulationOrchestrator::initializeSimulationStates() {
  Asteroid a1;

  current_state_->earth = Earth();
  current_state_->earth.setRadius(1);
  current_state_->asteroids.push_back(a1);

  next_state_->earth = Earth();
  next_state_->earth.setRadius(1);
  next_state_->asteroids.push_back(a1);
}
