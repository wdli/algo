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
 * enqueue
 */
static int enqueue(char* item)
{

  if (qlen == MAX_SIZE) {
    printf ("The queue is full!\n");
    return -1;
  }

  queue[tail++] = strdup(item);
  qlen++;
  tail = tail % MAX_SIZE;
  printf (" Now tail = %d, qlen = %d\n",tail,qlen);

  return 0;
}


/*
 * dequeue
 */
static char* dequeue(void)
{

  if (head == tail) {
    printf (" The queue is empty!\n");
    return NULL;
  }

  head = head % MAX_SIZE;
  return queue[head++];

}


/*
 * printq
 */
void printq(void)
{

}

/*
 * main
 */

void main(void)
{


  char str[10];

  printf ("Please input strings, end with '-' \n");

  while (scanf("%s", str)) {
    
    printf(" Input: %s\n", str);
    if (memcmp(str,"-",1) == 0) { 
      break;
    }

    if (enqueue(str) < 0){
      printf (" enqueue failed\n");
      return;
    }

    //gprintq();

  }

  

}




