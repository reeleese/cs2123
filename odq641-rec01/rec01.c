/*
  Author: Lee Reese odq641
  Recitation Excercise 1
*/

#include <stdio.h>

void print(int);
void subPrint(int);

int main() {
  /* menu loop */
  char done = 0;
  int number;
  while(done == 0) {
    printf("Give a number [0, 999,999]\n>");
    scanf("%d", &number);
    if (number < 0)
      done = 1;
    else if (number == 0)
      printf("Result: zero\n\n");
    else if (number < 1000000)
      print(number);
    else
      printf("Number must be in the range [0, 999,999]");
  }
  
  return 0;
}

void print(int value) {
  printf("Result:");
  /* For XXX,YYY front chunk = XXX, back chunk = YYY */
  int frontChunk = value / 1000;
  int backChunk  = value % 1000;
  
  if (frontChunk > 0) {
    subPrint(frontChunk);
    printf(" thousand");
  }
  
  if (backChunk > 0)
    subPrint(backChunk);

  printf("\n\n");
}

void subPrint(int chunk) {
  /* important arrays for decoding by digit */
  static const char* ones[]    = {"", "one", "two", "three", "four", "five",
                                  "six", "seven", "eight", "nine"};
  static const char* tens[]    = {"", "", "twenty", "thirty", "forty", "fifty",
                                  "sixty", "seventy", "eighty", "ninety"};
  static const char* special[] = {"ten", "eleven", "twelve", "thirteen",
                                  "fourteen", "fifteen", "sixteen", "seventeen",
                                  "eighteen", "nineteen"};

  /* each digit in chunk by place value */
  int pv1   = chunk % 10;
  int pv10  = (chunk / 10) % 10;
  int pv100 = (chunk / 100) % 10;

  if (pv100 > 0)
    printf(" %s hundred", ones[pv100]);
  if (pv10 == 1)
    printf(" %s", special[pv1]);
  else {
    if (pv10 > 0)
      printf(" %s", tens[pv10]);
    if (pv1 > 0)
      printf(" %s", ones[pv1]);
  }
}

