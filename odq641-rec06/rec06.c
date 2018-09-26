/* Author: Lee Reese, odq641
 * Assignment: Recitation 6
 * Due: Monday 10/1
 */

#include "random.h"
#include <stdio.h>

int digitsUnique(int);
void storeDigits(int, int[]);

int main()
{
  Randomize();

  int digit = 1234;
  int digits[4];

  storeDigits(digit, digits);
  int i;
  for (i=1000; i<10000; i+=100)
    printf("%4d: %d\n", i, digitsUnique(i));
  
  return 0;
}

/* Determines if the digits in a 4-digit integer are unique */
int digitsUnique(int num)
{
  int digits[4];
  storeDigits(num, digits);

  int i, j;
  for (i=0; i<3; i++)
    for (j=i+1; j<4; j++)
      if (digits[i] == digits[j]) return 0;
  return 1;
}

/* Sores the digits of int in [1000, 9999] in an array of size 4
 * little-endian */
void storeDigits(int num, int digits[])
{
  int i, *digit=digits;
  for (i=1; i<=1000; i*=10)
    *digit++ = (num / i) % 10;
}
