#ifndef _rec05print_h
#define _rec05print_h

#include <string.h>
#include <stdio.h>


int openCritPathInfo(FILE **, FILE **, char *argv[]);
/**openCritPath(FILE **inputFile, FILE **outputFILE, char *argv[])**************
 * 
 * Input: File pointer pointers for the desired input and output file streams
 *        along with the string arguments passed to main
 * Processing: Determines whether the user passed the input file before the 
 *             output file or the other way around. Then, builds the input
 *             and output file pointers accordingly.
 * Output: Returns 0 and prints an appropriate error message if the 
 *         process fails. Returns 1 if the process succeeds.
 *******************************************************************************/


void printHeader(FILE *);
/**printHeader(FILE *outputFile)************************************************
 *
 * Input: File pointer for the desired output file
 * Processing: Prints a static header.
 *******************************************************************************/


void printFooter(FILE *, int);
/**printFooter(FILE *outputFile, int totalNumberOfDays)*************************
 *
 * Input: File pointer for the desired output file, total days required
 * Processing: Prints a footer including the total number of days required for
 *             the project.
 *******************************************************************************/


void printEvent(FILE *, int, int, int);
/**printEvent(FILE *outputFile, int eventNumber, int numTasks, int maximumDays)*
 *
 * Input: File pointer for the desired output file, the event number, the number
 *        of tasks required to complete the event, the most days required
 *        by any single task
 * Processing: Documents a single event in the output file with relevant data
 *******************************************************************************/

#endif
