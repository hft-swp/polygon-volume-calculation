#include "vol.h"

static inline T det(const vertex a, const vertex b, const vertex c) {
  return
    a.x * b.y * c.z +
    a.y * b.z * c.x +
    a.z * b.x * c.z -
    a.z * b.y * c.x -
    a.y * b.x * c.z -
    a.x * b.z * c.y;
}

T getVol(const vertex* vertices, const int* indices, int elements) {
  T sum = 0;
  for(int i=0; i<elements; i++) {
    sum += det(vertices[indices[3*i+0]],
               vertices[indices[3*i+1]],
               vertices[indices[3*i+2]]);
  }
  return sum / 6;
}
