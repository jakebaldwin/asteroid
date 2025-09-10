#ifndef ASTEROID_H
#define ASTEROID_H

#include "geometry_utils.h"
#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Asteroid {
public:
  Asteroid() = default;

  const std::vector<GeometryUtils::Vertex> &getVertices() const {
    return vertices_;
  };

  const std::vector<uint32_t> &getIndices() const { return indices_; };

private:
  std::vector<GeometryUtils::Vertex> vertices_;
  std::vector<uint32_t> indices_;
  glm::vec3 position_;
  glm::quat rotation_;
  glm::vec3 velocity_; // position rotation or colors?
};
#endif
