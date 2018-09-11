/******************** HW01 **************************************
Author:  Lee Reese

Purpose:
    Accepts a finished or unfinished sudoku puzzle and returns a correct
    solution check or the possible values that could be entered into every
    empty square.
Parameters:
    arvg[1] 	name of sudoku file
Returns:
    n/a
Notes:
    None
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>

void inputPuzzle(char puzzValues[][9], char *type, char *argv[]);
void printPuzzle(char puzzValues[][9], char type);

//These are the prototypes for the functions you will code!!!
void analyzePuzzle(char puzzValues[][9], char type, char check[]);
void checkRow(char puzzValues[][9], char check[], int row, int column);
void checkColumn(char puzzValues[][9], char check[], int row, int column);
void checkSquare(char puzzValues[][9], char check[], int row, int column);
void printPossibleNums(char puzzValues[][9], char check[], int row, int column);
int checkSolution(char puzzValues[][9], char check[]);


int main(int argc, char *argv[]) {
  int solution;
  char puzzValues[9][9];
  char type;
  char check[10];

  //Check to make sure a puzzle file was given
  if (argc != 2) {
    printf("Command line error\n");
    exit(-1);
  }

  inputPuzzle(puzzValues, &type, argv);
  
  printPuzzle(puzzValues, type);

  if (type == 1)
    analyzePuzzle(puzzValues, type, check);
  
  else if (type == 2) {
      solution = checkSolution(puzzValues, check);
	
      if (solution == 0)
        printf("Yes\n");
      else if (solution == 1)
        printf("No\n");
      else
        printf("Finish your code!\n");
  }/* end elif */

  return 0;
}

/******************** inputPuzzle **************************************
void inputPuzzle(char puzzValues[][9], char *type, char *argv[])
Purpose:
    Reads a sudoku puzzle in from a file.  Stores the values.
Parameters:
    I 	char 	puzzValues[][]
    I 	char* 	type
    I 	char* 	argv[]
Returns:
    Returns the type of puzzle being entered and the sudoku numbers using pointers.
Notes:
    The puzzle file is opened and input is error checked.  The lower bound
    is set by the puzzle type.  Puzzles to be checked cannot have 0s.  Puzzles
    to find possible solutions use 0s to indicate a blank space.  Nested for
    loops are used to traverse the 2d array and input values.
**************************************************************************/
void inputPuzzle(char puzzValues[][9], char *type, char *argv[]) {
  int userChoice, tmp, i, j;
  int lBound, uBound = 9;

  FILE *puzzleInput = fopen(argv[1], "r");

  if (puzzleInput == NULL) {
    printf("Error opening the file: %s", argv[1]);
    exit(-1);
  }

  //Read the puzzle type
  fscanf(puzzleInput, "%d\n", &userChoice);
  
  if (userChoice != 1 && userChoice !=2) {
    printf("Invalid puzzle type: %d\n", userChoice);
    exit(-1);
  }

  *type = userChoice;

  if (userChoice == 1)
    lBound = 0;
  else
    lBound = 1;


  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      if (fscanf(puzzleInput, "%d ", &tmp) == 1) {
        if (tmp < lBound || tmp > uBound) {
          printf("Input value outside of bounds: %d", tmp);
          exit(-1);
        }
        else
          puzzValues[i][j] = tmp;
      }/* end if */
      
      else {
        printf("Error reading file\n");
        exit(-1);
      }
    }/* end for j */
  }/* end for i */
  
  fclose(puzzleInput);
}/* end function */

/******************** printPuzzle **************************************
void printPuzzle(char puzzValues[][9], char type)
Purpose:
    Prints out the two dimensional array as a sudoku table.
Parameters:
    I 	char 	puzzValues[][]
    I 	char 	type
Returns:
    n/a
Notes:
    Nested for loops are used to traverse the two dimensional array.
**************************************************************************/
void printPuzzle(char puzzValues[][9], char type) {
  int i, j;

  printf("%d\n", type);

  for (i=0; i<9; i++) {
    for (j=0; j<9; j++)
      printf("%d ", puzzValues[i][j]);

    printf("\n");
  }
}

/******************** analyzePuzzle **************************************
void analyzePuzzle(char puzzValues[][9], char type, char check[])
Purpose:
    Analyzes an unfinished puzzle to determine possible values for each
    empty square.
Parameters:
    I 	char 	puzzValues[][]
    I 	char 	type
    I 	char 	check[]
Returns:
    n/a
Notes:
    Nested for loops are used to traverse the 2d array.  For each sudoku value
    at puzzValues[i][j], its row, column, and small square are checked.  The
    possible values are then printed.
**************************************************************************/
void analyzePuzzle(char puzzValues[][9], char type, char check[]) {
  int i, j, k;

  /* For each element in the puzzle */
  for(i=0; i<9; i++) {
    for (j=0; j<9; j++) {
      
      /* Ignore populated cells */
      if (puzzValues[i][j] != 0)
        continue;
      
      /* 0 out check */
      for (k=0; k<10; k++)
        check[k] = 0;

      /* Analyze surrounding cells for available values */
      checkRow(puzzValues, check, i, j);
      checkColumn(puzzValues, check, i, j);
      checkSquare(puzzValues, check, i, j);

      /* Print results */
      printPossibleNums(puzzValues, check, i, j);
      
    }/* end for j */
  } /* end for i */
} /* end function */

/******************** checkRow **************************************
void checkRow(char puzzValues[][9], char check[], int row, int column)
Purpose:
    Checks the other elements in the row of the square being checked.
Parameters:
    I 	char 	puzzValues[][]
    I 	char 	check[]
    I 	int 	row
    I 	int 	column
Returns:
    Increments values in check[] based on values found in the row.
Notes:
    int row and int column are the coordinates of the square currently
    being checked.
**************************************************************************/
void checkRow(char puzzValues[][9], char check[], int row, int column) {
  int j;
  for (j=0; j<9; j++)
    check[ (int) puzzValues[row][j] ]++;
}

/******************** checkColumn **************************************
void checkColumn(char puzzValues[][9], char check[], int row, int column)
Purpose:
    Checks the other elements in the column of the square being checked.
Parameters:
    I 	char 	puzzValues[][]
    I 	char 	check
    I - int 	row
    I - int 	column
Returns:
    Increments values in check[] based on values found in the row.
Notes:
    int row and int column are the coordinates of the square currently
    being checked.
**************************************************************************/
void checkColumn(char puzzValues[][9], char check[], int row, int column) {
  int i;
  for (i=0; i<9;i++)
    check[ (int) puzzValues[i][column] ]++;
}

/******************** checkSquare **************************************
	void checkSquare(char puzzValues[][9], char check[], int row, int column)
Purpose:
    Checks the other elements in the small square of the square being checked.
Parameters:
    I 	char 	puzzValues[][]
    I 	char 	check[]
    I - int 	row
    I - int 	column
Returns:
    Increments values in check[] based on values found in the small square.
Notes:
    int row and int column are the coordinates of the square currently
    being checked.  Integer division is used to identify the 3x3 square
    containing [i][j].  Nested for loops are used to move through the small
    square, incrementing check[].
**************************************************************************/
void checkSquare(char puzzValues[][9], char check[], int row, int column) {
  /* puzzValues[x][y] = top left corner of box containing puzzValues[i][j] */
  int x = row / 3 * 3;
  int y = column / 3 * 3;

  /* For each element in the box, increment check[element] */
  int i, j;
  for(i=x; i<x+3; i++)
    for(j=y; j<y+3; j++)
      check[ (int) puzzValues[i][j] ]++;
}

/******************** printPossibleNums **************************************
	void printPossibleNums(char puzzValues[][9], char check[], int row, int column)
Purpose:
    Prints the possible solutions to an empty square in a sudoku puzzle.
Parameters:
    I 	char 	puzzValues[][]
    I 	char 	check[]
    I - int 	row
    I - int 	column
Returns:
    n/a
Notes:
    A nested for loop is used to traverse the check[] array.  If the
    value at check[i] is zero, it means that i is a possible solution
    for that square.
**************************************************************************/
void printPossibleNums(char puzzValues[][9], char check[], int row, int column) {
  printf("[%d][%d]:", row, column);

  /* If check[i] != 0, then i is not a valid solution for this square */
  int k;
  for(k=1; k<10; k++)
    if(check[k] == 0)
      printf(" %d,", k);

  /* remove final comma and newline */
  printf("\b \n");
}

/******************** checkSolution **************************************
	int checkSolution(char puzzValues[][9], char check[])
Purpose:
    Checks a sudoku solution using sudoku rules.
Parameters:
    I 	char 	puzzValues[][]
    I 	char 	check[]
Returns:
    O - int 	0 = good solution, 1 = wrong solution
Notes:
    The check[] array is used to identify if a solution is correct or not.
**************************************************************************/
int checkSolution(char puzzValues[][9], char check[]) {
  int i, j, k;

  for (i=0; i<9; i++) {
    for (j=0; j<9; j++) {
      /* 0 out check */
      for (k=0; k<10; k++)
        check[k] = 0;

      /* Analyze surrounding cells for available values */
      checkRow(puzzValues, check, i, j);
      checkColumn(puzzValues, check, i, j);
      checkSquare(puzzValues, check, i, j);

      /* for every cell, every possibility should appear once in the
       * row, once in the column, and once in the box. Thus, each slot
       * in check should read 3 in a valid puzzle */
      for (k=1; k<10; k++)
        if(3 < check[k] || check[k] > 3)
          return 1;
    }/* end for j */
  }/* end for i */
  
  return 0;
}
