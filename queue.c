/****************************
 * queue.c
 *
 * Basic queue APIs and client
 * implementation using a circular queue
 *
 * create: 11/2/2013
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * globals
 */

#define MAX_SIZE 3

char * queue[MAX_SIZE] = {};
int head = 0; //head pointer
int tail = 0; //tail pointer
int qlen = 0;

/*
 * printq
 */
void printq(void)
{
  if (!qlen) {
    printf (" printq The queue is empty! qlen = %d, head = %d, tail = %d\n", qlen, head % MAX_SIZE, tail % MAX_SIZE);
    return;
  }
  
  int i,l;
  int start;

  printf ("+++ qlen = %d, head = %d, tail = %d +++\n",qlen, head % MAX_SIZE, tail % MAX_SIZE);

  for ( i = head % MAX_SIZE,l=qlen; l > 0; i++, l--) {
    printf ("%s ", queue[i % MAX_SIZE]);
    //i = i++ % MAX_SIZE;
  }

  printf ("\n----------------------------------------\n");

  return;
}

/*
 * enqueue
 */
static int enqueue(char* item)
{

  if (qlen == MAX_SIZE) {
    printf ("The queue is full!\n");
    printq();
    return -1;
  }

  queue[tail++] = strdup(item);
  qlen++;

  tail = tail % MAX_SIZE; //This takes care of the tail 
                          //pointer wrap around

  //printf (" Now tail = %d, qlen = %d\n",tail,qlen);

  return 0;
}


/*
 * dequeue
 */
static char* dequeue(void)
{

  if (!qlen) {
    printf (" dequeue, The queue is empty!\n");
    return NULL;
  }
  qlen--;
  head = head % MAX_SIZE;//In case the head pointer
                         //has wrapped around
  return queue[head++];

}




/*
 * main
 */

void main(void)
{


  char str[10];
  char * item;
  int qflag = 0; // 0 - enqueue 1 - dequeue

  printf ("Please enqueue strings, start with a  '+' \n");
  printf ("Please dequeue strings, start with a  '-' \n");

  while (scanf("%s", str)) {
    
    //printf(" Input: %s\n", str);

    if (memcmp(str,"+",1) == 0) { 
      qflag = 0;//enqueu
      printf (" Enqeue start!\n");
      continue;
    }
    else if (memcmp(str,"-",1) == 0) { 
      qflag = 1;//dequeu
      printf ("Dequeue start!\n");
      continue;
    }
    else {

      if (!qflag && !enqueue(str)){
	printf (" '%s' enqueued \n", str);
	printq();
	continue;
      }

      if (qflag && (item = dequeue())) {
	printf (" '%s' dequeued \n", item);
	printq();
	continue;
      }

    }//if-else
    
  }//while
  
}




