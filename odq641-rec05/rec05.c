/*      Author: Lee Reese
 *          ID: odq641
 *  Assignment: Recitation 5 DUE: tba 
 */

#include <stdio.h>
#include <string.h>

void printFileHeader(FILE *);

int main(int argc, char *argv[]) {
  FILE *infp=NULL, *outfp=NULL;
  int prevEvent, currEvent, numTasks;
  int days, maxDays, totalDays;

  /* Currently only accupting -input then output.
   * #TODO: make this more general */
  if (!strcmp(argv[1], "-input") && !strcmp(argv[3], "-output")) {
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
  printFileHeader(outfp);
  fscanf(infp, "%d %*d %d", &prevEvent, &days);
  numTasks = 1;
 
  /* Loop */
  while(fscanf(infp, "%d %*d %d", &currEvent, &days) == 2) {
    if (prevEvent != currEvent) {
      fprintf(outfp, "%-7d %-14d %-d\n", prevEvent, numTasks, maxDays);
      numTasks = 0;
      maxDays = 0;
    }
    printf("made it\n");
    prevEvent = currEvent;
    numTasks++;
    if (days > maxDays)
      maxDays = days;
  }
 
  /* Offload loop */
  fprintf(outfp, "%-7d %-14d %-d\n", currEvent, numTasks, maxDays);
  
  return 0;
}

void printFileHeader(FILE *out) {
  fprintf(out, "Project Complettion Timetable\n");
  fprintf(out, "------------------------------------------------\n");
  fprintf(out, "Event   Num of Tasks   Max Num of Tasks\n");
  fprintf(out, "------  ------         ------\n");
}
