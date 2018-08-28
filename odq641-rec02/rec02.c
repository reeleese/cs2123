/*
  Author: Lee Reese
  Due: Monday 9/3
*/

#include <stdio.h>

void increaseA(int val) {
  val++;
}
void increaseB(int *pval) {
  pval++;    
}
void increaseC(int *pval) {
  *pval++;
}
void increaseD(int *pval) { 
  (*pval)++;
}

int main() {
  int temp, *ptemp,  sum;
  int a=10, b=20, c=30;
  int *pa=&a, *pb=&b, *pc=&c;
  int **ppa=&pa, **ppb=&pb, **ppc=&pc;

  /* Print initial values of a, b, c */
  printf("a:%d b:%d c:%d\n", a, *pb, **ppc);

  /* Print a+b+c */
  sum = a + *pb + **ppc;
  printf("sum:%d\n", sum);

  /* Swap values of a and b */
  temp = *pa;
  *pa = **ppb;
  **ppb = temp;
  printf("a:%d b:%d\n", a, b);

  /* Swap the values of pa and pb */
  ptemp = pa;
  pa = *ppb;
  *ppb = ptemp;
  printf("*pa:%d *pb:%d\n", *pa, *pb);
  printf("a:%d b:%d\n", a, b);
  /*
    At this point pa points to b and pb points to a. Therefore, *pb == a and
    *pa == b. However, the values of a and b themselves have not been touched.
  */



  return 0;
}
