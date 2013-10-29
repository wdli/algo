/************************************

  Basic stack functions
  push and pop

  create: 10/29/2013

  
*************************************/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/*
 * globals
 */

#define MAX_SIZE 10

char * stack[MAX_SIZE] = {} ;
unsigned int  top = 0; // top pointer

/* 
 * init
 */

static void
init(int size)
{
  /*
  stack = (char*) malloc(sizeof(char *)*size);
  if (! stack) {
    printf(" Failed to allocate for stack size: %d\n", size);
    return;
  }
  printf(" Allocated for stack size: %d\n", size);
  */
  return;

}


/*
 * push
 */

int push(char * str)
{

  if ( (top + 1) == MAX_SIZE ) {
    printf(" stack full, top = %d\n", top);
    return -1;
  }

  if (!str) {
    printf(" Null string input!\n");
    return -1;
  }

  stack[top++] = strdup(str); //This is critical to use strdup
                              //to preserve the string in stack
  
  return 0;

}

/*
 * pop
 */
static char*
pop(void)
{
  
  char * ret;

  if (top != 0){
    
    ret = stack[--top];
    stack[top] = NULL;
    //printf ("Returning %s\n", ret);
    return ret;
  }
  else {

    printf (" Empty stack top = %d\n", top);
    return NULL;
  }
  
}

/*
 * print 
 */
static void
printStack(void)
{
  int i;
  for (i = 0; i < top; i++){
    printf(" %s ",stack[i]);
  }

  printf (" Done printing stack!\n");
}

/*
 * main
 */

void main (void)
{


  char str[MAX_SIZE];

  printf ("Please input strings, end with '-' \n");
  while (scanf("%s", str)) {
    
    printf(" Input: %s\n", str);
    if (memcmp(str,"-",1) == 0) { 
      break;
    }

    if (push(str) < 0){
      printf (" push failed\n");
      return;
    }
    printStack();

  }

  printf ("Now pop the stack\n");
  
  char * ret = NULL;
  while ((ret = pop())) {
    printf ( " %s ",ret);
  }
  printf ("\n");
  printf (" All done! \n");
}
    
    
    


