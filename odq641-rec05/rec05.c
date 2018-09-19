/*      Author: Lee Reese
 *          ID: odq641
 *  Assignment: Recitation 5 DUE: Monday 9/24
 *  Depends on: rec05print.h, rec05print.c
 */

#include <stdio.h>
#include "rec05print.h"

int main(int argc, char *argv[]) {
  FILE *infp=NULL, *outfp=NULL;
  int prevEvent, currEvent, numTasks;
  int days, maxDays=0, totalDays=0;

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

  /* Write the header */
  printHeader(outfp);

  /* In order to compare task 2 with it's preceding task,
   * we're gonna need the values for task 1 */
  if (fscanf(infp, "%d %*d %d", &prevEvent, &days) == 2) {
    maxDays = days;
    numTasks = 1;
  } else { /* There is no task 1. No tasks at all as a matter of fact */
    printFooter(outfp, 0);
    return 0;
  }
    

  /* For each task, starting with task 2 */
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
  printEvent(outfp, prevEvent, numTasks, maxDays);

  /* Write the footer */
  totalDays += maxDays;
  printFooter(outfp, totalDays);

  /* Close our file pointers */
  fclose(infp);
  fclose(outfp);
  
  return 0;
}
