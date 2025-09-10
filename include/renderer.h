#ifndef RENDERER_H
#define RENDERER_H

#include "open_gl_manager.h"
#include "simulation_state.h"
#include <string>

constexpr const char *ShaderPath = "res/shaders/shader.shader";

struct ShaderProgramSource {
  std::string vertex_source;
  std::string fragment_source;
};

class Renderer {

public:
  Renderer(OpenGlManager &open_gl);

  ~Renderer();

  void draw(SimulationState &state);

  void initializeShaders();

  void initializeEarthGeometry(const Earth &earth);

private:
  ShaderProgramSource parseShaderFile();
  void drawAsteroid(const Asteroid &asteroid);
  void drawEarth(const Earth &earth);

  unsigned int compileShader(const std::string &source, unsigned int type);
  unsigned int createShaderProgram(const std::string &vertex_src,
                                   const std::string &fragment_src);
  unsigned int vs_;
  unsigned int fs_;
  unsigned int shader_program_id_;

  OpenGlManager &open_gl_;

  /* cache earth geometry */
  std::vector<GeometryUtils::Vertex> earth_vertices_;
  std::vector<uint32_t> earth_indices_;
  GLuint earth_vao_, earth_vbo_, earth_ebo_;
  bool earth_geometry_initialized_ = false;
};
#endif
