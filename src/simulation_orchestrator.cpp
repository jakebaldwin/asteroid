#include "simulation_orchestrator.h"
#include "logger.h"
#include <iostream>

using DebugLogger = Logger<LogLevel::Debug>;

SimulationOrchestrator::SimulationOrchestrator()
    : open_gl_(std::make_unique<OpenGlManager>()),
      simulator_(std::make_unique<Simulator>()),
      renderer_(std::make_unique<Renderer>(*open_gl_)),
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
    DebugLogger::log("error in main loop caught");
  }
}

void SimulationOrchestrator::runSimulationLoop() {
  double delta_time = 1.5;
  DebugLogger::log("Starting render loop...");
  while (!glfwWindowShouldClose(open_gl_->getWindow())) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Add this!

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
  current_state_->earth.setRotation(kEarthAxisTiltRads);
  current_state_->earth.setPosition({0, 0, 0});
  current_state_->asteroids.push_back(a1);

  next_state_->earth = Earth();
  next_state_->earth.setRadius(1);
  next_state_->earth.setRotation(kEarthAxisTiltRads);
  next_state_->earth.setPosition({0, 0, 0});
  next_state_->asteroids.push_back(a1);
}
