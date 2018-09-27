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
void positionPrint(int, char *);
void existencePrint(int);

int main()
{
  Randomize();

  int attempt, guess, secret;
  int s_digits[4], g_digits[4];
  int d_matching, d_notExist, d_inPlace, d_outPlace;
  char playAgain;

  /* Play a game */
  int playing = 1;
  while (playing) {
    /* Get a secret value for user to guess */
    secret = secretGen();
    storeDigits(secret, s_digits);
    
    /* Play a round */
    for (attempt=1; attempt<=40; ++attempt) {
      /* Menu */
      printf("\nAttempt #%-2d\nEnter a 4-digit number: ", attempt);
      scanf("%d", &guess);

      /* Ensure user's digits are uniquee */
      while(!digitsUnique(guess)) {
        printf("Please enter a value without repeated digits: ");
        scanf("%d", &guess);
      }

      /* Did the user win? */
      if (secret == guess) {
        printf("You did it! The number was %d.\n", secret);
        break;
      }
        

      /* store guess in array */
      storeDigits(guess, g_digits);

      /* How good is the user's guess? */
      d_matching = matchingDigits(s_digits, g_digits);
      d_notExist = 4-d_matching;
      d_inPlace = digitsInPlace(s_digits, g_digits);
      d_outPlace = d_matching - d_inPlace;

      /* Print results of guess */
      positionPrint(d_inPlace, "in place");
      positionPrint(d_outPlace, "out of place");
      existencePrint(d_notExist);
    }/* end round */
    
    /* Determine whether the user will play again */
    printf("Play again? (y/n): ");
    scanf(" %c", &playAgain);
    if (playAgain == 'n' || playAgain == 'N')
      playing = 0;
  }/* end game */

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

/* Returns number of digits in g_digits that appear in s_digits */
int matchingDigits(int s_digits[4], int g_digits[4])
{
  int i, j, matching=0;
  for (i=0; i<4; ++i)
    for (j=0; j<4; ++j)
      if (s_digits[i] == g_digits[j])  ++matching;
  return matching;
}

/* prints "digits/digit are/is <suffix>" with good grammar */
void positionPrint(int quantity, char *suffix)
{
  if (quantity == 1)
    printf("1 digit is %s\n", suffix);
  else
    printf("%d digits are %s\n", quantity, suffix);
}

/* Prints "digit/digits does/do not exist" with good grammar */
void existencePrint(int quantity)
{
  if (quantity == 1)
    printf("1 digit does not exist\n");
  else
    printf("%d digits do not exist\n", quantity);
}
