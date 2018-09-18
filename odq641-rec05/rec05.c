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

int openCritPathInfo(FILE **in, FILE **out, char *argv[]) {
  char *inputFilename, *outputFilename;

  /* CASE 1: The first file is input and the second is output. */
  if (strcmp(argv[1], "-input")==0 && strcmp(argv[3], "-output")==0) {
    inputFilename = argv[2];
    outputFilename = argv[4];
  }

  /* CASE 2: The first file is output and the second is input. */
  else if (strcmp(argv[1], "-output")==0 && strcmp(argv[3], "-input")==0) {
    inputFilename = argv[4];
    outputFilename = argv[2];
  }

  /* CASE 3: Nothing is correct */
  else {
    printf("BAD INPUT: To properly run this program, type\n");
    printf("  rec05 –input data1.txt –output output1.txt OR\n");
    printf("  rec05 –output output1.txt –input data1.txt\n");
    return 0;
  }

  /* Build input file pointer */
  *in = fopen(inputFilename, "r");
  if (*in == NULL) {
    printf("File could not be open.\n");
    return 0;
  }

  /* Build ouput file pointer */
  *out = fopen(outputFilename, "w");
  if (*out == NULL) {
    printf("File could not be open.\n");
    return 0;
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
