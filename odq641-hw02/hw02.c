/***************************
Name: Lee Reese
UTSA ID: odq641
****************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct courseT {
  char code[8];      // "CS 2123"
  char inst[20];     // "Korkmaz"
  char room[10];     // "NPB 1.226"
} courseT;

typedef struct scheduleT {
  char start[6];     // "10:00"
  char end[6];       // "10:50"
  int numc;          // number of courses
  courseT *courses;  // dynamic array of courseT
} scheduleT;

int x = 0;
char inputBuffer[20];
char *token = inputBuffer;

scheduleT *LoadSchedule(FILE *inFile, int *numTS);
void PrintSchedule(scheduleT *sch, int numTS);

scheduleT *CopySchedule(scheduleT *oldSch, int numTS);
void PrintInstructorConflicts(scheduleT *sch, int numTS);
void PrintRoomConflict(scheduleT *sch, int numTS);
void FreeSchedule(scheduleT *sch, int numTS);


int main(int argc, char *argv[]) {
  scheduleT *oldSchedule, *newSchedule;
  int numOfTimeSlots = -1;
  FILE *inFile;
  if(argc<2){
    printf("Enter the input file as the second command line argument\n");
    return -1;
  }
  inFile = fopen(argv[1], "r");
  if(inFile == NULL){
    printf("file not found or no permissions\n");
    return -1;
  }
  oldSchedule = LoadSchedule(inFile, &numOfTimeSlots);	
  fclose(inFile);
  PrintSchedule(oldSchedule, numOfTimeSlots);

  /* 
   * The followings will work after you implement them 
   */
  newSchedule = CopySchedule(oldSchedule, numOfTimeSlots);
  printf("\n***Copied Schedule***\n");
  PrintSchedule(newSchedule, numOfTimeSlots);

  PrintInstructorConflicts(oldSchedule, numOfTimeSlots);

  PrintRoomConflict(oldSchedule, numOfTimeSlots);

  FreeSchedule(oldSchedule, numOfTimeSlots);
  FreeSchedule(newSchedule, numOfTimeSlots);

  return 0;
}

scheduleT *LoadSchedule(FILE *inFile, int *numTS){
  scheduleT *newSch;
  int i,j=0;

  fscanf(inFile, "%d",  numTS);

  newSch = (scheduleT*)malloc(*numTS * sizeof(scheduleT));
  if(!newSch){
    printf("bad scheduleT malloc\n");
    exit (0);
  }
  for(i=0;i<*numTS;i++){
    fscanf(inFile, "%s %s %d \n",
           newSch[i].start,
           newSch[i].end,
           &newSch[i].numc);
    
    newSch[i].courses=(courseT*)malloc(newSch[i].numc * sizeof(courseT));
    if(newSch[i] == NULL){
      printf("courses malloc error\n");
      for(j = 0; j < i; j++)  
        free(newSch[i].courses);
      free(newSch);
      exit (0);
    }
    
    for(j = 0; j < newSch[i].numc; j++){
      fscanf(inFile,"%[^\n] %[^\n] %[^\n] ",
             newSch[i].courses[j].code,
             newSch[i].courses[j].inst,
             newSch[i].courses[j].room);
    }
  }
  return newSch;
}


void PrintSchedule(scheduleT *sch, int numTS){
  //iterate through schedule printing all information in specified format
  int i,j;

  if (sch == NULL || numTS == 0) return; 

  printf("***************Schedule**************\n\n");
  for(i=0; i<numTS; ++i){
    printf("Start\tEnd\n");
    printf("%s\t%s\n", sch[i].start, sch[i].end);
    if (sch[i].numc == 0) {
      printf("No courses schedule at this time\n");
    } else {
      printf("Course\tInstructor\tRoom\n");
      for(j=0; j<sch[i].numc; ++j){
        printf("%s\t%s\t\t%s\n",
               sch[i].courses[j].code,
               sch[i].courses[j].inst,
               sch[i].courses[j].room);
      }
    }
    printf("\n");
  }
  printf("*****************End*****************\n");
}


/********************************************************
 * The rest must be coded and commented by students
 ********************************************************/

/*
 * this function copies oldSch to newSch and returns it
 */  
scheduleT *CopySchedule(scheduleT *oldSch, int numTS){
  scheduleT *newSch;
  int i,j;

  newSch = NULL;
 
  /* YOUR CODE */

  return newSch;
}


/* iterate through schedule to look for intructors who have
 * multiple classes at the same time
 * print all conflicting instructor information and time */
void PrintInstructorConflicts(scheduleT *sch, int numTS)
{
  int i,j,k;

  /* YOUR CODE */
}

/* iterate through schedule to find all classrooms that have
 * multiple classes booked at the same time
 * print all conflictin rooms and time */
void PrintRoomConflict(scheduleT *sch, int numTS)
{
  int i,j,k;
  /* YOUR CODE */
}


/* free the given schedule structure */
void FreeSchedule(scheduleT *sch, int numTS)
{
  /* YOUR CODE */
}

