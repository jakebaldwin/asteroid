#ifndef OPEN_GL_MANAGER_H
#define OPEN_GL_MANAGER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class OpenGlManager {
public:
  OpenGlManager() = default;

  void initialize();

  void createWindow();

  GLFWwindow *getWindow();

private:
  GLFWwindow *window_;
};
#endif
