#include "open_gl_manager.h"

#include <stdexcept>

void OpenGlManager::initialize() {
  if (!glfwInit()) {
    throw std::runtime_error("failed to init glfw");
  }
  // Set OpenGL version (Mac wants >=3.2 Core Profile)
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void OpenGlManager::createWindow() {
  window_ = glfwCreateWindow(1600, 1000, "OpenGL Setup", nullptr, nullptr);
  if (!window_) {
    glfwTerminate();
    throw std::runtime_error("failed to create GLFW window");
  }

  glfwMakeContextCurrent(window_);

  // Initialize GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    throw std::runtime_error("failed to init GLEW");
  }
}

GLFWwindow *OpenGlManager::getWindow() { return window_; }
