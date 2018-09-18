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
  int days, maxDays, totalDays=0;

  /* Ensure correct # of args passed */
  if (argc != 5)
    printf("Incorrect number of arguments.\n");

  /* Open infp and oufp */
  if (!openCritPathInfo(&infp, &outfp, argv)) {
    printf("Exiting...\n");
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
