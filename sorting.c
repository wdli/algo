/************************
 * create 11/5/2013
 *
 * Basic sorting algorithms
 *    Insertion sort
 *    Selection sort
 *    Merge sort
 *    Quick sort
 *    Heap sort
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
 * qsortPart
 *
 * Partition an array in a quick sort
 * Find a place in the array such that
 * all items to the left is less and
 * all items to the right is larger
 * That's the invariat of quick sort
 *
 */
static int 
qsortPart(char* a[], int lo, int hi)
{
  int i = lo;    
  int j = hi+1;

  printf ("    === The partion starts===\n");

  while (1) {
    //
    // scan from left to right as long as 
    // i is less than lo
    //
    printf ("    +Scan left start, cur index = %d\n", i);
    while (compare(a, ++i, lo) < 0) {
      printf ("    Scan left, cur index = %d\n", i);
      if ( i == hi)
	break;
    }
    printf ("    -Scan left end, cur index = %d\n", i);
    

    //
    // scan from right to left as long as
    // j is larger than lo
    //
    printf ("    +Scan right start, cur index = %d\n", j);
    while (compare(a, lo, --j) < 0 ) {
      printf ("    Scan right, cur index = %d\n", j);
      if (j == lo)
	break;
    }
    printf ("    -Scan right end, cur index = %d\n", j);
    // 
    // if i and j crossed
    // means there are no two items 
    // that need to be exchanged or swapped
    // 
    if ( i >= j) {
      printf ("    %d and %d crossed\n", i,j);
      break;
    }

    // 
    // swap i and j as they are
    // out of the place
    // keep going
    // 
    swap(a, i, j);
    printf ("    exchanged %d and %d\n",i,j);
    printStr(a);

  }//while(1)

  // 
  // Once we are there, we have found
  // a place that can be used as a partion point
  // that is the j
  // 
  swap(a, lo, j);
  printf ("    exchanged %d and %d\n",lo,j);
  printStr(a);
  printf ("    ===The partition ends index %d===\n",j);
  
  
  return j; // the partition index

}


/*
 * qsort
 *
 */
void qsortSort(char* a[], int lo, int hi)
{
  
  if (hi <= lo)
    return;

  // partition the array at j, ie, 
  // j is in the right place
  // 
  int j = qsortPart(a,lo,hi);
  printf (" lo = %d, hi = %d, partition index = %d\n",lo,hi,j);

  // sort the left partition
  qsortSort(a,lo,j-1); 

  // sort the right partition
  qsortSort(a,j+1,hi);
  
}




/**
 * heapSortSwim
 *
 * If a node index is k, the its parent index is k/2
 * it's child index is 2k and 2k+1
 *
 * This function finds if the child is smaller than its parent
 * then move it up and move its parent node down to maintain the
 * heap order or invariant
 *
 */
static void
heapSortSwim(char* a[], int k)
{
  
  while( k > 1 && compare(a, k/2, k) < 0 ) {
    swap(a, k/2, k);
    k = k/2; // update the node to its parent index
  }

}


/**
 * If the array is indexed by zero
 * If a node is k, it's children are at 2k+1 and 2k+2
 *
 * If it's less than its largest child, then
 * swap them
 *
 * Note: N is not the largest index, N-1 is.
 */
static void
heapSortSink(char * a[], int k, int N)
{

  printf (" %s: k = %d, N = %d\n",__FUNCTION__, k, N);
  while (2*k+1 <= N-1) {

    int j = 2*k+1;
    printf (" Sink looking at node %d, its children %d and %d\n",
	    k, j, j+1);

    // 
    // find out which child node is larger
    // j+1 is the right child of k, make sure 
    // its index can't be larger than the largest index N-1
    // 
    if (j+1 <= N-1 && compare(a, j, j+1) < 0 ) {
      j++;
    }

    printf ("  Now compare k = %d to %d\n", k, j);
    //
    // compare node k to the larger of its two children
    // if larger, we are done
    //

    if ( compare(a,k,j) > 0 ) {
      printf ("  k = %d is larger than %d, we are OK\n", k, j);
      break;
    }
    
    //
    // if node k is less than the child then swap them
    //
    printf ("   Sink %d with %d\n", k, j);
    swap(a,k,j);
    k = j;
    
  }
}


/*
 * This function sort a random binary tree
 * into a heap order
 * First pass:  build a heap by bottom-up approach
 * Second pass: remove the root but leave it in the array
 *
 */
void
binaryHeapSort(char* a[], int N)
{
  int k;
  
  // first pass:
  printf (" +++ Heap sort first pass to creat heap order, N = %d\n", N);
  printf ("======================================================\n");
  for (k = N/2; k>=0; k--) {
    heapSortSink(a, k, N);
  }

  printStr(a);

  //second pass:
  printf (" +++ Heap sort second pass to remove the root\n");
  printf ("======================================================\n");
  while(N > 0) {

    printf (" swap node 0 and %d\n", N-1);
    swap(a, 0, --N);
    printStr(a);
    printf (" Sink new node 0, size N = %d\n", N);
    heapSortSink(a, 0, N);
    printStr(a);
  }


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

  // printf (" Merge sort\n");
  // mergeSortRecursive(0, num-1);

  // uncomment for quick sort
  //printf (" Quick sort\n");
  //qsortSort(str, 0, num-1);

  printf (" Heap sort\n");
  binaryHeapSort(str,num);

  printStr(str);
  
  return 0;
}
