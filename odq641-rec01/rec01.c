/*
  Author: Lee Reese odq641
  Recitation Excercise 1
*/
#include <stdio.h>

char* intToString(int);
char* thingy(int);

int main() {
  int iUser;
  
  /* Loop */
  while(iUser != -1) {
    printf("Enter a value.\n> ");
    iUser = -1;
    scanf("%d", &iUser);
  }
  
  printf("result: %d\n\n");
  return 0;
}

char* intToString(int i) {
  int ones = i % 10;
  int tens = (i % 100) / 10;
  int hundreds = i / 100;

  char suffix[50];
  if (tens == 1) {
    switch(ones) {
    case 0: return "";
    case 1: return "eleven";
    case 2: return "twelve";
    case 3: return "thirteen";
    case 4: return "fourteen";
    case 5: return "fifteen";
    case 6: return "sixteen";
    case 7: return "seventeen";
    case 8: return "eighteen";
    case 9: return "nineteen";
    }/*end switch*/
  }/*end if*/
  
}

char* ones(int digit) {
  switch(digit) {
    case 0: return "";
    case 1: return "one";
    case 2: return "two";
    case 3: return "three";
    case 4: return "four";
    case 5: return "five";
    case 6: return "six";
    case 7: return "seven";
    case 8: return "eight";
    case 9: return "nine";
  }
  return "<too_big>";
}

char* tens(int digit) {
  switch(digit) {
    case 0: return "";
    case 1: return ""; /*special cases*/
    case 2: return "twenty";
    case 3: return "thirty";
    case 4: return "forty";
    case 5: return "fifty";
    case 6: return "sixty";
    case 7: return "seventy";
    case 8: return "eighty";
    case 9: return "ninety";
  }
  return "<too_big>";

}


