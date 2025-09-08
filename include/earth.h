#ifndef EARTH_H
#define EARTH_H

#include "geometry_utils.h"
#include <cstdlib>
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

private:
  std::vector<GeometryUtils::Vertex> vertices_;
  std::vector<uint32_t> indices_;
  float radius_;
  // position rotation or colors?
};
#endif
