/*      Author: Lee Reese
 *          ID: odq641
 *  Assignment: Recitation 5 DUE: Monday 9/24
 */

#include <stdio.h>
#include <string.h>

int openCritPathInfo(FILE **, FILE **, char *argv[]);
void printHeader(FILE *);
void printFooter(FILE *, int);
void printEvent(FILE *, int, int, int);

int main(int argc, char *argv[]) {
  FILE *infp=NULL, *outfp=NULL;
  int prevEvent, currEvent, numTasks;
  int days, maxDays, totalDays=0;

  if (argc != 5)
    printf("Incorrect number of arguments.\n");

  if (!openCritPathInfo(&infp, &outfp, argv)) {
    printf("Failed to open file(s). Exiting...\n");
    return -1;
  }
  
  /* Prime loop */
  printHeader(outfp);
  fscanf(infp, "%d %*d %d", &prevEvent, &days);
  numTasks = 1;
 
  /* Loop */
  while(fscanf(infp, "%d %*d %d", &currEvent, &days) == 2) {
    if (prevEvent != currEvent) {
      printEvent(outfp, prevEvent, numTasks, maxDays);
      totalDays += maxDays;
      numTasks = 0;
      maxDays = 0;
    }
    prevEvent = currEvent;
    numTasks++;
    if (days > maxDays)
      maxDays = days;
  }
 
  /* Offload loop */
  printEvent(outfp, currEvent, numTasks, maxDays);
  totalDays += maxDays;
  printFooter(outfp, totalDays);

  fclose(infp);
  fclose(outfp);
  
  return 0;
}

int openCritPathInfo(FILE **in, FILE **out, char *argv[]) {
  /* Currently only accupting -input then -output.
   * #TODO: make this more general */
  if (!strcmp(argv[1], "-input") && !strcmp(argv[3], "-output")) {
    *in = fopen(argv[2], "r");
    if (*in == NULL) {
      printf("File could not be open\n");
      return 0;
    }

    *out = fopen(argv[4], "w");
    if (*out == NULL) {
      printf("File could not be open\n");
      return 0;
    }
  }
  
  return 1;
}

void printHeader(FILE *out) {
  fprintf(out, "Project Completion Timetable\n");
  fprintf(out, "------------------------------------------------\n");
  fprintf(out, "Event   Num of Tasks   Max Num of Days\n");
  fprintf(out, "------  ------         ------\n");
}

void printFooter(FILE *out, int total) {
  fprintf(out, "------------------------------------------------\n");
  fprintf(out, "Total number of days to finish the project: %d days\n", total);
}

void printEvent(FILE *out, int eventNum, int numTasks, int maxDays) {
  fprintf(out, "%-7d %-14d %-d\n", eventNum, numTasks, maxDays);
}
