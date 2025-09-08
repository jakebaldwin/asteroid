#include "renderer.h"

#include <fstream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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

  shader_program_id_ =
      createShaderProgram(shaders.vertex_source, shaders.fragment_source);
  glUseProgram(shader_program_id_);
}

void Renderer::drawAsteroid(const Asteroid &asteroid) {
  // upload asteroid data to GPU buffer

  // set shader uniforms (position, color, MVP matrix)

  // issue draw call
}

void Renderer::drawEarth(const Earth &earth) {
  auto vertices = GeometryUtils::generateSphere(earth.getRadius(), 20, 20);
  auto indices = GeometryUtils::generateSphereIndices(20, 20);

  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  // 3. Bind and upload data
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GeometryUtils::Vertex),
               vertices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t),
               indices.data(), GL_STATIC_DRAW);

  // 4. Set vertex attributes (matches your shader)
  // Position attribute (location = 0)
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GeometryUtils::Vertex),
                        (void *)0);
  glEnableVertexAttribArray(0);

  // Normal attribute (location = 1)
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GeometryUtils::Vertex),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // 5. Use shader and set uniforms
  glUseProgram(shader_program_id_);

  // 6. Set MVP matrix uniform
  glm::mat4 model = glm::mat4(1.0f); // Identity matrix (Earth at origin)

  glm::mat4 view = glm::lookAt(
      glm::vec3(10.0f, 5.0f, 10.0f), // Camera position (back and up from Earth)
      glm::vec3(0.0f, 0.0f, 0.0f),   // Look at origin (where Earth is)
      glm::vec3(0.0f, 1.0f, 0.0f)    // Up vector (Y is up)
  );

  glm::mat4 proj =
      glm::perspective(glm::radians(45.0f), // Field of view
                       800.0f / 600.0f,     // Aspect ratio (your window size)
                       0.1f,                // Near clipping plane
                       100.0f               // Far clipping plane
      );

  glm::mat4 mvp = proj * view * model;

  // 7. Set color uniform (blue for Earth)
  GLint color_location = glGetUniformLocation(shader_program_id_, "uColor");
  glUniform3f(color_location, 0.0f, 0.5f, 1.0f); // Blue color
  // 8. Send to shader
  GLint mvp_location = glGetUniformLocation(shader_program_id_, "uMVP");
  glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));

  // Check if shader program is valid
  if (shader_program_id_ == 0) {
    std::cout << "No valid shader program!" << std::endl;
    return;
  }

  // Check OpenGL errors
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    std::cout << "OpenGL error: " << error << std::endl;
  }

  // 9. Draw
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

  // 10. Cleanup
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
}

unsigned int Renderer::compileShader(const std::string &source,
                                     unsigned int type) {
  unsigned int shader_id = glCreateShader(type);
  const char *src = source.c_str();
  glShaderSource(shader_id, 1, &src, nullptr);
  glCompileShader(shader_id);

  int result;
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    int length;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
    char *message = (char *)alloca(length * sizeof(char));
    glGetShaderInfoLog(shader_id, length, &length, message);
    std::cout << "Failed to compile "
              << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader"
              << std::endl;
    std::cout << message << std::endl;
    glDeleteShader(shader_id);
    return 0;
  }

  return shader_id;
}

unsigned int Renderer::createShaderProgram(const std::string &vertex_src,
                                           const std::string &fragment_src) {
  unsigned int program = glCreateProgram();
  vs_ = compileShader(vertex_src, GL_VERTEX_SHADER);
  fs_ = compileShader(fragment_src, GL_FRAGMENT_SHADER);
  glAttachShader(program, vs_);
  glAttachShader(program, fs_);
  glLinkProgram(program);
  glValidateProgram(program);
  glDeleteShader(vs_);
  glDeleteShader(fs_);
  return program;
}
