#define T double

struct vertex {
  T x;
  T y;
  T z;
  T w; // padding
};
typedef struct vertex vertex;

T getVol(const vertex* vertices, const int* indices, int elements);

