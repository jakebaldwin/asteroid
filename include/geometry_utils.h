#ifndef GEOMETRY_UTILS_H
#define GEOMETRY_UTILS_H

#include <vector>

namespace GeometryUtils {
struct Vertex {
  float x, y, z;    // Position
  float nx, ny, nz; // Normal
};

std::vector<Vertex> generateSphere(float radius, int lat_segments,
                                   int lon_segments);
std::vector<uint32_t> generateSphereIndices(int lat_segments, int lon_segments);
} // namespace GeometryUtils

#endif
