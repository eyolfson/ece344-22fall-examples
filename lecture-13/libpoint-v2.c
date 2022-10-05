#include "libpoint.h"

#include "libpoint-v2.h"

#include <stdlib.h>

struct point *point_create(int x, int y) {
  struct point_v2* p = (struct point_v2 *)malloc(sizeof(struct point_v2));
  p->x = x;
  p->y = y;
  return (struct point *) p;
}

int point_get_x(struct point *p) {
  return ((struct point_v2 *)p)->x;
}

int point_get_y(struct point *p) {
  return ((struct point_v2 *)p)->y;
}

void point_destroy(struct point *p) {
  free(p);
}
