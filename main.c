#include "vol.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

static const int polygons = 1000;
static const int loops = 1000000;

int main() {
  // dummy data, all zero so we are sure to stay in cache (no memory bottleneck)
  vertex* vertices = (vertex*) calloc(sizeof(vertex), 3);
  int* indices = (int*) calloc(sizeof(int)*3, polygons);
  T sum = 0;
  int i = 0;
  
  clock_t start = clock();
  #pragma omp parallel for private(i) reduction(+:sum) schedule(static)
  for(i=0; i<loops; i++) {
    sum += getVol(vertices, indices, polygons);
  }
  clock_t ende = clock();
  double clocks = (ende-start) / (double) CLOCKS_PER_SEC;
  double zeit = clocks / omp_get_max_threads();
  double d_polys = (double)polygons * loops;
  
  printf("%d mal %d Polygone in %f Sekunden mit %d Threads\n"
         "%f ns pro Polygon\n"
         "%f GB/s Vertices (wenn jeder Vertex für drei Polygone verwendet wird)\n",
         loops, polygons, zeit, omp_get_max_threads(), 1e9*clocks/d_polys,
         sizeof(vertex) * d_polys / zeit / (1024*1024*1024)
        );
  
  return 0;
}
