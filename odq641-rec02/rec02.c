/*
  Author: Lee Reese
  Due: Monday 9/3
*/

#include <stdio.h>

/* swaps pointer variables */
void exchange(int **pp1, int **pp2);

/* Given functions */
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
  printf("sum:%d\n\n", sum);

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
  printf("a:%d b:%d\n\n", a, b);
  /*
    At this point pa points to b and pb points to a. Therefore, *pb == a and
    *pa == b. However, the values of a and b themselves have not been touched.
   */

  /* Call the mystery functions */
  increaseA(a);
  printf("After A, a:%d\n", a);
  increaseB(&a);
  printf("After B, a:%d\n", a);
  increaseC(&a);
  printf("After C, a:%d\n", a);
  increaseD(&a);
  printf("After D, a:%d\n\n", a);
  /*
    increaseA: increments the local variable val (copy of a).
               -> no change to a
    increaseB: increments the local variable pval (copy of &a).
               -> no change to a
    increaseC: increments the local variable pval and dereferences the result.
               -> no change to a (the dereference happens too late)
    increaseD: dereferences pval (&a) and increments it.
               -> a is changed because the dereference occurs first
   */

  /* Call exchange() */
  exchange(&pa, &pb);
  printf("exchange(&pa, &pb);\n");
  printf(" pa:%15p  pb:%15p\n", pa, pb);
  printf("*pa:%15d *pb:%15d\n\n", *pa, *pb);
  /*
    This works b/c we pass references to pa and pb. These references will
    always point to the proper address because they are calculated at run-time.
   */

  exchange(&pa, ppb);
  printf("exchange(&pa, ppb);\n");
  printf(" pa:%15p  pb:%15p\n", pa, pb);
  printf("*pa:%15d *pb:%15d\n\n", *pa, *pb);
  /*
    This only works if ppb == &pb. If ppb does not point to pb, it will not
    work. In this case, it works.
   */

  exchange(ppa, ppb);
  printf("exchange(ppa, ppb);\n");
  printf(" pa:%15p  pb:%15p\n", pa, pb);
  printf("*pa:%15d *pb:%15d\n\n", *pa, *pb);
  /*
    This only works if ppa == &pa AND ppb == &pb. If either ppa or ppb do not
    point to pa or pb, respectively, it will not work. In this case, it works.
   */

  return 0;
}

void exchange(int **pp1, int **pp2) {
  int *temp = *pp1;
  *pp1 = *pp2;
  *pp2 = temp;
}
