#ifndef EARTH_H
#define EARTH_H

#include "geometry_utils.h"
#include <cstdlib>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class Earth {
public:
  Earth() = default;

  const std::vector<GeometryUtils::Vertex> &getVertices() const {
    return vertices_;
  };

  const std::vector<uint32_t> &getIndices() const { return indices_; };

  float getRadius() const { return radius_; };

  void setRadius(float radius) { radius_ = radius; };

  glm::vec3 getPosition() const { return position_; };

  void setPosition(glm::vec3 position) { position_ = position; };

  float getRotation() const { return rotation_; };

  void setRotation(float rotation) { rotation_ = rotation; };

private:
  std::vector<GeometryUtils::Vertex> vertices_;
  std::vector<uint32_t> indices_;
  float radius_;
  glm::vec3 position_;

  // angle in radians of rotation
  float rotation_;
  // position rotation or colors?
};
#endif
