/* Author: Lee Reese, odq641
 * Assignment: Recitation 6
 * Due: Monday 10/1
 */

#include "random.h"
#include <stdio.h>

int digitsUnique(int);
void storeDigits(int, int[]);
int secretGen();
int digitsInPlace(int[], int[]);
int matchingDigits(int[], int[]);
void fancyPrint(char *suffix, int quantity);

int main()
{
  Randomize();

  int i, guess, secret;
  int s_digits[4], g_digits[4];
  
  secret = secretGen();
  
  for (i=0; i<40; i++) {
    printf("(debug) Secret: %d\n", secret); 
    printf("Enter a 4-digit number: ");
    scanf("%d", &guess);
    
    while(!digitsUnique(guess)) {
      printf("Please enter a value without repeated digits: ");
      scanf("%d", &guess);
    }
    storeDigits(secret, s_digits);
    storeDigits(guess, g_digits);
    
    printf("\n");
  }

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

/* Generates a random integer in [1000, 9999] with non-repeating digits */
int secretGen()
{
  int secret = RandomInteger(1000, 9999);
  while (!digitsUnique(secret))
    secret = RandomInteger(1000, 9999);
  return secret;
}

/* Determines how many digits are placed correctly */
int digitsInPlace(int s_digits[4], int g_digits[4])
{
  int i, correct = 0;
  for(i=0; i<4; i++)
    if (s_digits[i] == g_digits[i])
      correct++;

  return correct;
}

int matchingDigits(int s_digits[4], int g_digits[4])
{
  int i, j, matching=0;
  for (i=0; i<4; ++i)
    for (j=0; j<4; ++j)
      if (s_digits[i] == g_digits[j])  ++matching;
}

void fancyPrint(char *suffix, int quantity)
{
  if (quantity == 1)
    printf("1 digit is %s\n", suffix);
  else
    printf("%d digits are %s\n", quantity, suffix);
}
