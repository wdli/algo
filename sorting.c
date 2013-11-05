/************************
 * create 11/5/2013
 *
 * Basic sorting algorithms
 *    Insertion sort
 *
 *
 *
 * Todo
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/**
 * Globals
 */
#define MAX_SIZE 10
static char* str[MAX_SIZE];

/*
 * swap
 */
static void swap(int i, int j)
{

  if (!str[i] || !str[j]) {
    printf (" Invalide strings in swap\n");
    return;
  }

  char * temp = str[i];
  str[i] = str[j];
  str[j] = temp;
}




/*
 * compare
 */
static int compare(int i, int j)
{
  if (!str[i] || !str[j]) {
    //printf (" Invalide strings in compare\n");
    return;
  }

  return strcmp(str[i], str[j]);
}

/**
 * printStr
 */
static void 
printStr(void)
{
  int i;
  
  printf ("+++ String array dump +++\n");
  for ( i = 0; i < MAX_SIZE; i++) {
    if (str[i])
      printf ("%s ", str[i]);
  }
  printf ("\n+++\n");

}



/*
 * selectionSort
 *
 * Invariants:
 *
 * To the left of pointer: sorted
 * To the right of pointer: unsorted,
 *    find the min and swap with the
 *    item at the pointer
 *    1/2 N**2 time
 */
static void selectionSort(void)
{
  int i,j; 
  int min;

  for (i = 0; i < MAX_SIZE; i++) {

    if (!str[i])
      break;

    //find the min to the right of i

    min = i;
    for (j = i+1 ; j < MAX_SIZE; ++j) {
      if (compare(j, min) < 0 ) {
	min = j;
      }
    }
    //swap

    swap(i,min);

  }//end
  
  return;
}


/*
 * main
 */
int main(int argc, char *argv[])
{
  


  if (argc < 2 ) {
    printf (" Missing input strings\n");
    return 0;
  }
  
  // Get the input strings
  if ( argc >= MAX_SIZE ) {

    printf (" Number of strings is too large %d\n",argc);
    return 0;
  }

  int i = 0;
  while ( i < argc ){
    
    if (argv[i]) {
      str[i-1] = strdup(argv[i]);
      i++;
    }
    else {
      break;
    }
  }
 
  printStr();

  //selection sort

  selectionSort();
  printStr();
  
  return 0;
}
