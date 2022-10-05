#include <stdio.h>
#include <stdlib.h>

#include "libpoint.h"

#include "libpoint-v1.h"
#include "libpoint-v2.h"

int main(int argc, char **argv)
{
  struct point *p = point_create(1, 2);

  printf("point (x, y) = %d, %d (using library)\n", point_get_x(p), point_get_y(p));

  struct point_v1 *p_v1 = (struct point_v1 *) p;
  printf("point (x, y) = %d, %d (using v1)\n", p_v1->x, p_v1->y);

  struct point_v2 *p_v2 = (struct point_v2 *) p;
  printf("point (x, y) = %d, %d (using v2)\n", p_v2->x, p_v2->y);

  point_destroy(p);
  return 0;
}
