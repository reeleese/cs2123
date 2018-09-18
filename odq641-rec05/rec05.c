/*      Author: Lee Reese
 *          ID: odq641
 *  Assignment: Recitation 5 DUE: tba 
 */

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  FILE *infp=NULL, *outfp=NULL;
  int prevEvent, currEvent, numTasks, days, maxDays;

  /* Currently only accupting -input then output.
   * #TODO: make this more general */
  if (strcmp(argv[1], "-input") && strcmp(argv[3], "-output")) {
    infp = fopen(argv[2], "r");
    if (infp == NULL) {
      printf("File could not be open\n");
      return -1;
    }

    outfp = fopen(argv[4], "w");
    if (outfp == NULL) {
      printf("File could not be open\n");
      return -1;
    }
  }/* end if */

  /* Prime loop */
  fscanf(infp, "%d %d %d", &prevEvent, &numTasks, &days);

  /* Loop */
  while(fscanf(infp, "%d %d %d", &currEvent, &numTasks, &days)) {
    if (prevEvent != currEvent) {
      fprintf(outfp, "%5d %5d %5d", prevEvent, numTasks, maxDays);
      numTasks = 0;
      maxDays = 0;
    }
    currEvent = prevEvent;
    numTasks++;
    if (days > maxDays)
      maxDays = days;
  }

  /* Offload loop */
  fprintf(outfp, "%5d %5d %5d", currEvent, numTasks, maxDays);
  
  return 0;
}
