/*      Author: Lee Reese
 *          ID: odq641
 *  Assignment: Recitation 5 DUE: Monday 9/24
 */

#include <stdio.h>
#include <string.h>

void printFileHeader(FILE *);
void printFileFooter(FILE *, int);

int main(int argc, char *argv[]) {
  FILE *infp=NULL, *outfp=NULL;
  int prevEvent, currEvent, numTasks;
  int days, maxDays, totalDays=0;

  /* Currently only accupting -input then -output.
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
      totalDays += maxDays;
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
  totalDays += maxDays;
  printFileFooter(outfp, totalDays);

  fclose(infp);
  fclose(outfp);
  
  return 0;
}

void printFileHeader(FILE *out) {
  fprintf(out, "Project Completion Timetable\n");
  fprintf(out, "------------------------------------------------\n");
  fprintf(out, "Event   Num of Tasks   Max Num of Days\n");
  fprintf(out, "------  ------         ------\n");
}

void printFileFooter(FILE *out, int total) {
  fprintf(out, "------------------------------------------------\n");
  fprintf(out, "Total number of days to finish the project: %d days\n", total);
}
