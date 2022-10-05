#include "libpoint.h"

#include "libpoint-v1.h"

#include <stdlib.h>

struct point *point_create(int x, int y) {
  struct point_v1* p = (struct point_v1 *)malloc(sizeof(struct point_v1));
  p->x = x;
  p->y = y;
  return (struct point *) p;
}

int point_get_x(struct point *p) {
  return ((struct point_v1 *)p)->x;
}

int point_get_y(struct point *p) {
  return ((struct point_v1 *)p)->y;
}

void point_destroy(struct point *p) {
  free(p);
}
