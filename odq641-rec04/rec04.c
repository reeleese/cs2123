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

int main() {
  RectT a, b;
  RectT *recs;
  
  buildRect(&a, "a");
  buildRect(&b, "b");

// printf("%lf %lf %lf %lf", a.location.x, a.location.y, a.height, a.width);
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
