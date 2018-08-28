/*
  Author: Lee Reese
  Due: Monday 9/3
*/

#include <stdio.h>

int main() {
  int temp, sum;
  int a=10, b=20, c=30;
  int *pa=&a, *pb=&b, *pc=&c;
  int **ppa=&pa, **ppb=&pb, **ppc=&pc;

  printf("a:%d b:%d c:%d\n", a, *pb, **ppc);

  sum = a + *pb + **ppc;
  printf("sum:%d\n", sum);
  
  return 0;
}
