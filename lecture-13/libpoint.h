#ifndef LIBPOINT_H
#define LIBPOINT_H

struct point;

struct point *point_create(int x, int y);
int point_get_x(struct point *p);
int point_get_y(struct point *p);
void point_destroy(struct point *p);

#endif
