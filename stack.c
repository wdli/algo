/************************************

  Basic stack functions
  push and pop

  create: 10/29/2013

  
*************************************/


#include <stdlib.h>
#include <stdio.h>



//globals
//

char * stack;


/* 
 * init
 */

static void
init(int size)
{

  stack = (char*) malloc(sizeof(char *)*size);
  if (! stack)
    printf(" Failed to allocate for stack size: %d\n", size);

  return;

}


/*
 * push
 */



/*
 * pop
 */




/*
 * main
 */

void main (void)
{

  int s = 10;
  
  init(s);

}

