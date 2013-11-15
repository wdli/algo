/************************
 * create 11/5/2013
 *
 * Basic sorting algorithms
 *    Insertion sort
 *    Selection sort
 *    Merge sort
 *
 * Use: input an array of strings on the cmdline
 *
 * Todo:
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/**
 * Globals
 */
#define MAX_SIZE 10
static char* str[MAX_SIZE];
static char* straux[MAX_SIZE]; //for merge sort

/*
 * swap item at i with item at j
 */
static void swap(char *a[], int i, int j)
{

  if (!a[i] || !a[j]) {
    //printf (" Invalide strings in swap\n");
    return;
  }

  char * temp = a[i];
  a[i] = a[j];
  a[j] = temp;
}




/*
 * compare item i and j
 *
 * item i < item j --> < 0
 *
 */
static int compare(char* a[], int i, int j)
{
  if (!a[i] || !a[j]) {
    //printf (" Invalide strings in compare\n");
    return;
  }

  return strcmp(a[i], a[j]);
}

/**
 * printStr
 */
static void 
printStr(char * a[])
{
  int i;
  
  printf ("+++ String array dump +++\n");
  for ( i = 0; i < MAX_SIZE; i++) {
    if (a[i])
      printf ("%s ", a[i]);
  }
  printf ("\n+++\n");

}



/*
 * selectionSort
 *
 * Invariants:
 *
 * To the left of pointer: sorted
 * To the right of pointer: unsorted.
 *
 * Algo:
 *    find the min to the right and swap with the
 *    item at the pointer
 *    "search to the right"
 * Perf:
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
      if (compare(str, j, min) < 0 ) {
	min = j;
      }
    }
    //swap

    swap(str, i,min);

  }//end
  
  return;
}




/*
 * insertionSort
 *
 * Invariants
 *
 * To left of the current pointer: sorted
 * To right of the pointer: unsorted
 *
 * Algo:
 *    current pointer++
 *    compare the entry[pointer] with its previous entry
 *    if less, then swap and continue, otherwise break
 *    " search to the left " 
 * Perf:
 *   1/4 N**2
 *  
 */

static void
insertionSort(void)
{
  
  int i,j;
  
  for (i=0; i<MAX_SIZE; i++) {
    
    if (!str[i])
      break;

    for (j = i; j > 0; j--) {
      
      if (compare(str, j, j-1) < 0 ) {
	swap(str, j,j-1);
      }
      
    }//for j

  } //for i

  return;
}

/**
 * merge function
 * This does the merge of two sorted sub-arrays
 *
 */
static mergeSortMerge(int lo, int mid, int hi)
{
  int k;

  //copy the original array

  for (k = 0; k < MAX_SIZE; k++) {
    straux[k] = str[k];
  }
  
  int  i = lo;   //track the first half of the sorted array
  int  j = mid+1;//track the second half

  for ( k = lo; k <= hi; k++) {

    if ( i > mid ) {
      // first half has been exhausted, copy rest of the right half
      str[k] = straux[j++];
    }
    else if ( j > hi ) {
      // second half has been exhausted, copy rest of the first half
      str[k] = straux[i++];
    }
    else if (compare(straux, i,j) > 0 ) {
      // the jth in the second half is less than the ith in the
      // first half, copy jth over and advance j
      str[k] = straux[j++];
    }
    else {
      // the ith in the first half is less than the jth in the
      // second half, copy jth over and advance i
      str[k] = straux[i++];
    }
  }

}

/*
 * mergeSortRecursive
 *
 * This merge sort API that recursively sorts the two sub arrays
 *
 * 
 */
static
void mergeSortRecursive(int lo, int hi)
{
  
  if (hi <= lo) {
    printf (" * Stop: lo = %d, hi = %d\n", lo, hi);
    return;
  }

  int mid = lo + (hi-lo)/2;
  printf (" + Recur: lo = %d, mid = %d, hi = %d\n",lo, mid, hi);

  mergeSortRecursive(lo,mid);
  mergeSortRecursive(mid+1, hi);

  mergeSortMerge(lo,mid,hi);

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

  int num = argc -1;
  printf (" Number of items : %d\n",num);
  printStr(str);

  //Uncomment the next 2 lines: selection sort
  //printf (" Selection sort test\n");
  //selectionSort();

  //Uncomment the next 2 lines: insertion sort
  //printf (" Insertion sort test\n");
  //insertionSort();

  printf (" Merge sort\n");
  mergeSortRecursive(0, num-1);

  printStr(str);
  
  return 0;
}
