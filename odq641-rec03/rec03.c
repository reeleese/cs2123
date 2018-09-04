/* Recitation 03
 * Author: Lee Reese
 * Due: Monday 9/10
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Returns a random number in [low, high] */
double RandomReal(double low, double high){
  double d;
  d = (double) rand() / ((double) RAND_MAX + 1);
  return (low + d * (high - low));
}

int main() {
  /* Used to define 2D Array */
  int X, Y;
  double minZ, maxZ;
  double **Arr2D;

  /* iterators and accumulators */
  int i, j;
  double sum_total=0, sum_row=0, sum_col=0;

  /* seed RNG */
  srand(time(NULL));

  /* Get dimensions for array */
  printf("Enter X Y minZ maxZ\n> ");
  scanf("%d %d %lf %lf", &X, &Y, &minZ, &maxZ);

  /* Allocate memory for array */
  Arr2D = (double **) malloc(X * sizeof(double *));
  for (i = 0; i < X; i++)
    Arr2D[i] = (double *) malloc(Y * sizeof(double));

  /* Assign each slot in array a random (or not) number */
  for (i = 0; i < X; i++) {
    for (j = 0; j < Y; j++) {
      if (minZ == maxZ)
        Arr2D[i][j] = minZ;
      else
        Arr2D[i][j] = RandomReal(minZ, maxZ);
    }
  }

  /* Calculate and return overall sum of all entries */
  for (i = 0; i < X; i++)
    for(j = 0; j < Y; j++)
      sum_total += Arr2D[i][j];
  printf("Overall sum = %.1lf\n", sum_total);

  /* Calculate and return sum of each row */
  printf("Sum of each row\n");
  for(i = 0; i < X; i++) {
    for(j = 0; j < Y; j++) {
      sum_row += Arr2D[i][j];
    }
    printf("Row%d = %.1lf\n", i, sum_row);
    sum_row = 0;
  }

  /* Calculate and return sum of each column */
  printf("Sum of each column\n");
  for(j = 0; j < Y; j++) {
    for(i = 0; i < X; i++) {
      sum_col += Arr2D[i][j];
    }
    printf("%.1lf ", sum_col);
    sum_col = 0;
  }
  printf("\n");
          
  /* Free allocated memoryy */
  for (i = 0; i < X; i++)
    free(Arr2D[i]);
  free(Arr2D);
  
  return 0;
}
