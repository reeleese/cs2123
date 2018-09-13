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

int main() {
  RectT a, b;
  RectT *recs;
  while (1) {
  
    buildRect(&a, "a");
    buildRect(&b, "b");

    printf( (chk_overlap(&a, &b)? "not overlapping\n":"overlapping\n" ) );
  }

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

/* check any corners on r2 lie within r1, going clockwise from
 * bottom left
 */
int chk_overlap(RectT *r1, RectT *r2) {
  /* establish points for bottom left (bl) and top right (tr) of r1 */
  PointT r1_bl = r1->location;
  PointT r1_tr = r1->location;
  r1_tr.x += r1->width;
  r1_tr.y += r1->height;
  
  /* similarly, for r2 */
  PointT r2_bl = r2->location;
  PointT r2_tr = r2->location;
  r2_tr.x += r2->width;
  r2_tr.y += r2->height;

  /* Check if r1 is to the right of r2 OR r1 is to the left of r2 */
  if (r1_bl.x > r2_tr.x || r1_tr.x < r2_bl.x)
    return 1;

  /* Check if r1 is above r2 OR r1 is below r2 */
  if (r1_bl.y > r2_tr.y || r1_tr.y < r2_bl.y)
    return 1;

  return 0;
}
