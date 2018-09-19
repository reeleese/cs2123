/*      Author: Lee Reese
 *          ID: odq641
 *  Assignment: Recitation 5 DUE: Monday 9/24
 *  Depends on: rec05print.h, rec05print.c
 */

#include <stdio.h>
#include "rec05print.h"

int main(int argc, char *argv[]) {
  FILE *infp=NULL, *outfp=NULL;
  int prevEvent, currEvent=3, numTasks;
  int days, maxDays, totalDays=0;

  /* Ensure correct # of args passed */
  if (argc != 5) {
    printf("Incorrect number of arguments.\n");
    return -1;
  }

  /* Open infp and oufp */
  if (!openCritPathInfo(&infp, &outfp, argv)) {
    printf("Exiting...\n");
    return -1;
  }

  printHeader(outfp);

  /* In order to compare current data with the preceding entry,
   * we're gonna need the values from entry 1 */
  fscanf(infp, "%d %*d %d", &prevEvent, &days);
  numTasks = 1;

  /* For each task, starting with the second */
  while(fscanf(infp, "%d %*d %d", &currEvent, &days) == 2) {
    /* If new event, dump data for previous event and reset accumulators */
    if (prevEvent != currEvent) {
      printEvent(outfp, prevEvent, numTasks, maxDays);
      totalDays += maxDays;
      numTasks = 0;
      maxDays = 0; /* No task should take <0 days */
    }
    prevEvent = currEvent;
    numTasks++;
    if (days > maxDays)
      maxDays = days;
  }
 
  /* Dump the final event */
  printEvent(outfp, currEvent, numTasks, maxDays);

  /* Write the footer */
  totalDays += maxDays;
  printFooter(outfp, totalDays);

  fclose(infp);
  fclose(outfp);
  
  return 0;
}
