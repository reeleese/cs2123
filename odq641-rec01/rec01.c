/*
  Author: Lee Reese odq641
  Recitation Excercise 1
*/

#include <stdio.h>
#include <string.h>

void intToString(int);
void printo(int);
char* ones(int);
char* tens(int);


int main() {
  int iUser;
  
  /* Loop */
  while(iUser != -1) {
    /* Get value */
    printf("Enter a value.\n> ");
    iUser = -1;
    scanf("%d", &iUser);

    printo(iUser);

  }
  return 0;
}
void printo(int i) {
  printf("Result: ");
  if (i > 999) {
    intToString(i/1000);
    printf(" thousand ");
  }
  intToString(i % 100000);
  printf("\n\n");
}

void intToString(int i) {
  int pv1 = i % 10;
  int pv10 = (i % 100) / 10;
  int pv100 = i / 100;

  /* Compose 'suffix', the 0-99 part */
  char suffix[100];
  char* teens[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen",
                   "sixteen", "seventeen", "eighteen", "nineteen"};
  if (pv10 == 1)
    strcpy(suffix, teens[pv1]);
  else {
    strcpy(suffix, tens(pv10));
    strcat(suffix, " ");
    strcat(suffix, ones(pv1));
  }

  /* compose 'prefix', the hundreds place */
  char prefix[80];
  if (pv100 > 0) {
    strcpy(prefix, ones(pv100));
    strcat(prefix, " hundred ");
  }
  else
    strcpy(prefix, "");

  /* return prefix + suffix */
  strcat(prefix, suffix);
  printf("%s", prefix);
}

char* ones(int digit) {
  char* stuff[] = {"", "one", "two", "three", "four", "five", "six",
                  "seven", "eight", "nine"};
  if (digit < 0 || digit > 9)
    return "<REALLY BAD>";
  return stuff[digit];
}

char* tens(int digit) {
  char* stuff[] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty",
                  "seventy", "eighty", "ninety"};
  if (digit < 0 || digit > 9)
    return "<REALLY BAD>";
  return stuff[digit];

}


