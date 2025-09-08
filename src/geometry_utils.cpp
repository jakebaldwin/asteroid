#include "geometry_utils.h"
#include <cmath>

namespace GeometryUtils {

std::vector<Vertex> generateSphere(float radius, int lat_segments,
                                   int lon_segments) {
  std::vector<Vertex> vertices;
  vertices.reserve((lat_segments + 1) * (lon_segments + 1));

  for (int lat = 0; lat <= lat_segments; ++lat) {
    for (int lon = 0; lon <= lon_segments; ++lon) {
      // Convert to normalized coordinates [0,1]
      float lat_norm = static_cast<float>(lat) / lat_segments;
      float lon_norm = static_cast<float>(lon) / lon_segments;

      // Convert to spherical coordinates
      float theta = lat_norm * M_PI;      // Latitude: 0 to PI (north to south)
      float phi = lon_norm * 2.0f * M_PI; // Longitude: 0 to 2*PI (around)

      // Convert spherical to Cartesian coordinates
      float x = radius * sin(theta) * cos(phi);
      float y = radius * cos(theta); // Y is up
      float z = radius * sin(theta) * sin(phi);

      // For a unit sphere, normal = normalized position
      float nx = x / radius;
      float ny = y / radius;
      float nz = z / radius;

      vertices.push_back({x, y, z, nx, ny, nz});
    }
  }

  return vertices;
}

std::vector<uint32_t> generateSphereIndices(int lat_segments,
                                            int lon_segments) {
  std::vector<uint32_t> indices;
  indices.reserve(lat_segments * lon_segments * 6); // 2 triangles per quad

  for (int lat = 0; lat < lat_segments; ++lat) {
    for (int lon = 0; lon < lon_segments; ++lon) {
      // Calculate vertex indices for current quad
      uint32_t current = lat * (lon_segments + 1) + lon;
      uint32_t next = current + lon_segments + 1;

      // First triangle (current, next, current+1)
      indices.push_back(current);
      indices.push_back(next);
      indices.push_back(current + 1);

      // Second triangle (current+1, next, next+1)
      indices.push_back(current + 1);
      indices.push_back(next);
      indices.push_back(next + 1);
    }
  }

  return indices;
}

} // namespace GeometryUtils
