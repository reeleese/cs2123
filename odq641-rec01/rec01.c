/*
  Author: Lee Reese odq641
  Recitation Excercise 1
*/

#include <stdio.h>
#include <string.h>

char* intToString(int);
char* thingy(int);

int main() {
  int iUser;
  
  /* Loop */
  while(iUser != -1) {
    /* Get value */
    printf("Enter a value.\n> ");
    iUser = -1;
    scanf("%d", &iUser);

    char* result = intToString(iUser);
    printf("result: %s\n\n", result);
  }
  return 0;
}

char* intToString(int i) {
  printf("intToString IN\n");
  int pv1 = i % 10;
  int pv10 = (i % 100) / 10;
  int pv100 = i / 100;

  char suffix[100];
  char* teens[] = {"eleven", "twelve", "thirteen", "fourteen", "fifteen",
                    "sixteen", "seventeen", "eighteen", "nineteen"};
  if (pv10 == 1)
    strcpy(suffix, teens[pv1 -1]);
  printf("intToString OUT\n");

  return suffix;
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


