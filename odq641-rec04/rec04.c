/*    Author: Lee Reese
 *    Assignment: Recitation 4
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct Point {
  double x;
  double y;
} PointT;

typedef struct Rect {
  PointT location;
  char color;
  double width;
  double height;
} RectT;

void buildRect(RectT *, char *);
int chk_overlap(RectT *, RectT *);
int point_in_rect(RectT, PointT);

int main() {
  RectT a, b;
  RectT *recs;
  
  buildRect(&a, "a");
  buildRect(&b, "b");

  // printf("%lf %lf %lf %lf", a.location.x, a.location.y, a.height, a.width);
printf( (chk_overlap(&a, &b)? "yes\n":"no\n" ) ); 

  return 0;
}

/* #TODO: make this easier for the user */
void buildRect(RectT *pRect, char *name) {
  /* Fill location */
  printf("Enter coordinates for %s.\n> ", name);
  scanf("%lf %lf", &pRect->location.x, &pRect->location.y);

  /* Fill height and width */
  printf("Enter height and width for %s.\n> ", name);
  scanf("%lf %lf", &pRect->height, &pRect->width);
}

int point_in_rect(RectT r, PointT p) {
  /* Establish bottom left and top right points on r */
  PointT bottom_left = r.location;
  PointT top_right;
  top_right.x = bottom_left.x + r.width;
  top_right.y = bottom_left.y + r.height;

  /* Determine if p is within the vertical lines of r */
  int bounded_in_x = 0;
  if (bottom_left.x < p.x && p.x < top_right.x)
    bounded_in_x = 1;
 
  /* Determine if p is within the horizontal lines of r */
  int bounded_in_y = 0;
  if (bottom_left.y < p.y && p.y < top_right.y)
    bounded_in_y = 1;

  return bounded_in_x && bounded_in_y;  
}

/* check any corners on r2 lie within r1, going clockwise from
 * bottom left
 */
int chk_overlap(RectT *r1, RectT *r2) {
  PointT corner;

  /* Bottom left */
  corner.x = r2->location.x;
  corner.y = r2->location.y;
  if (point_in_rect(*r1, corner))
    return 1;
  
  /* Top left */
  corner.y += r2->height;
  if (point_in_rect(*r1, corner))
    return 1;

  /* Top right */
  corner.x += r2->width;
  if (point_in_rect(*r1, corner))
    return 1;

  /* Bottom right */
  corner.y -= r2->height;
  if (point_in_rect(*r1, corner))
    return 1;

  return 0;
}
