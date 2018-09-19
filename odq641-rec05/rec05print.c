#include "rec05print.h"

int openCritPathInfo(FILE **in, FILE **out, char *argv[]) {
  char *inputFilename, *outputFilename;

  /* Assign input and ouput file names */
  if (strcmp(argv[1], "-input")==0 && strcmp(argv[3], "-output")==0) {
    inputFilename = argv[2];
    outputFilename = argv[4];
  } else if (strcmp(argv[1], "-output")==0 && strcmp(argv[3], "-input")==0) {
    inputFilename = argv[4];
    outputFilename = argv[2];
  } else { /* User gives bad input */
    printf("BAD INPUT: To properly run this program, type\n");
    printf("  rec05 –input <your input file> –output <your output file> OR\n");
    printf("  rec05 –output <your output file> –input <your input file>\n");
    return 0;
  }

  /* Build input file pointer */
  if ((*in = fopen(inputFilename, "r")) == NULL) {
    printf("File could not be open.\n");
    return 0;
  }

  /* Build ouput file pointer */
  if ((*out = fopen(outputFilename, "w")) == NULL) {
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
