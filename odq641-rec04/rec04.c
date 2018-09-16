/*    Author: Lee Reese
 *    Assignment: Recitation 4
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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

void buildUserRect(RectT *, char *);
void buildRandomRect(RectT *);
int chk_overlap(RectT *, RectT *);
double randomReal(double low, double high);

int main() {
  /* Seed RNG */
  srand( time(NULL) );

  
  RectT a, b;
  RectT *recs;
  
  /* Build user's rectangles */  
  buildUserRect(&a, "a");
  buildUserRect(&b, "b");

  /* Allocate recs */
  recs = (RectT *) malloc(50*sizeof(RectT));
  if (recs == NULL) {
    printf("Failed to allocate recs. Exiting...\n");
    return -1;
  }

  /* Initialize recs */
  int i;
  for(i=0; i<50; i++)
    buildRandomRect(&recs[i]);

  /* For each RectT in recs, check for overlapping with user RectTs */
  int over_a=0, over_b=0, over_both=0;
  for(i=0; i<50; i++) {
    if(chk_overlap(&recs[i], &a))
      over_a++;
    if (chk_overlap(&recs[i], &b))
      over_b++;
    if(chk_overlap(&recs[i], &a) && chk_overlap(&recs[i], &b))
       over_both++;
  }

  /* Print results */
  printf("For each random rectangle,\n");
  printf("%2d overlapped with a\n", over_a);
  printf("%2d overlapped with b\n", over_b);
  printf("%2d overlapped with both\n", over_both);
  
  return 0;
}

/* #TODO: make this easier for the user */
void buildUserRect(RectT *pRect, char *name) {
  /* Fill location */
  printf("Enter coordinates for %s.\n> ", name);
  scanf("%lf %lf", &pRect->location.x, &pRect->location.y);

  /* Fill height and width */
  printf("Enter height and width for %s.\n> ", name);
  scanf("%lf %lf", &pRect->height, &pRect->width);
}

void buildRandomRect(RectT *pRect) {
  /* Bounds for random attributs of pRect */
  int point_low = 0;
  int point_high = 50;
  int dim_low = 0;
  int dim_high = 15;

  pRect->location.x = randomReal(point_low, point_high);
  pRect->location.y = randomReal(point_low, point_high);
  pRect->height = randomReal(dim_low, dim_high);
  pRect->width = randomReal(dim_low, dim_high);
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
    return 0;

  /* Check if r1 is above r2 OR r1 is below r2 */
  if (r1_bl.y > r2_tr.y || r1_tr.y < r2_bl.y)
    return 0;

  return 1;
}

double randomReal(double low, double high){
  double d;
  d = (double) rand() / ((double) RAND_MAX + 1);
  return (low + d * (high - low));
}
