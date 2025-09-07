#include "renderer.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

Renderer::Renderer(OpenGlManager &open_gl) : open_gl_(open_gl) {}

Renderer::~Renderer() { glDeleteShader(shader_program_id_); }

void Renderer::draw(SimulationState &state) {
  drawEarth(state.earth);
  for (const Asteroid &asteroid : state.asteroids) {
    drawAsteroid(asteroid);
  }
}

ShaderProgramSource Renderer::parseShaderFile() {

  std::ifstream stream(ShaderPath);

  if (!stream.is_open()) {
    std::cout << "Failed to open shader file!" << std::endl;
    throw std::runtime_error("Could not open shader file");
  }

  enum class ShaderType { None = -1, Vertex = 0, Fragment = 1 };

  std::string line;
  ShaderType type = ShaderType::None;
  // one for vertex, one for fragment
  std::stringstream ss[2];
  while (getline(stream, line)) {
    if (line.find("#shader") != std::string::npos) {
      if (line.find("vertex") != std::string::npos) {
        type = ShaderType::Vertex;

      } else if (line.find("fragment") != std::string::npos) {
        type = ShaderType::Fragment;
      }
    } else {
      ss[(int)type] << line << '\n';
    }
  }

  return {ss[0].str(), ss[1].str()};
}

void Renderer::initializeShaders() {
  ShaderProgramSource shaders = parseShaderFile();

  unsigned int shader =
      createShaderProgram(shaders.vertex_source, shaders.fragment_source);
  glUseProgram(shader);
}

void Renderer::drawAsteroid(const Asteroid &asteroid) {}

void Renderer::drawEarth(const Earth &earth) {}

unsigned int Renderer::compileShader(const std::string &source,
                                     unsigned int type) {
  shader_program_id_ = glCreateShader(type);
  const char *src = source.c_str();
  glShaderSource(shader_program_id_, 1, &src, nullptr);
  glCompileShader(shader_program_id_);

  int result;
  glGetShaderiv(shader_program_id_, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    int length;
    glGetShaderiv(shader_program_id_, GL_INFO_LOG_LENGTH, &length);
    char *message = (char *)alloca(length * sizeof(char));
    glGetShaderInfoLog(shader_program_id_, length, &length, message);
    std::cout << "Failed to compile "
              << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader"
              << std::endl;
    std::cout << message << std::endl;
    glDeleteShader(shader_program_id_);
    return 0;
  }

  return shader_program_id_;
}

unsigned int Renderer::createShaderProgram(const std::string &vertex_src,
                                           const std::string &fragment_src) {
  unsigned int program = glCreateProgram();
  unsigned int vs = compileShader(vertex_src, GL_VERTEX_SHADER);
  unsigned int fs = compileShader(fragment_src, GL_FRAGMENT_SHADER);
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glValidateProgram(program);
  glDeleteShader(vs);
  glDeleteShader(fs);
  return program;
}
