/***************************************
 union find problem

 create: 10/18/2013
 
****************************************/

#include <stdio.h>
#include <stdlib.h>


///static int union()


void main (void)
{

  //user inputs
  //
  int s, p, q;
  int * a;

  printf ("Please enter the size of the array\n");
  scanf("%d", &s);
  
  a = (int *) malloc(sizeof(int)*s);
  if (!a) {
    printf(" Error in allocation array memory \n" );
    return;
  }
    
  
  printf ("Please enter two random integers (0 0 to end):\n");
  while (scanf("%d %d", &p, &q)) {
    if ( p && q)
      printf (" p = %d, q = %d\n",p,q);
    else 
      break;
  }


  free(a);
  printf(" Done all inputs\n");
}
