/*****************
 * bst.c
 *
 * Implement basic binary search tree 
 *           basic Red-black tree ops
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/**
 * Globals
 */
#define MAX_SIZE 10
char * str[MAX_SIZE];


typedef enum _bool {
  
  BOOL_START,
  FALSE,
  TRUE,
  BOOL_END,

} BOOL;

typedef enum _color {

  COLOR_START,
  BLACK,
  RED,
  COLOR_END,

} COLOR;

typedef struct _node {

  char * key;
  struct _node * left;
  struct _node * right;
  COLOR  color;   // For RB tree, the color of parent link
  int marked; // 0 unmarked 1 -marked

} NODE;

NODE * root = NULL;

// 
// Queueing for BSF
// using a singular link list
//
typedef struct _queue
{
  NODE* node;
  struct _queue * next;

} QUEUE;

QUEUE * head = NULL, * tail = NULL;



/**
 * compare two items
 *
 * item i < item j --> < 0
 *
 */
static int compare(char* itemi, char * itemj)
{
  
  if (!itemi || !itemj) {
    printf (" Invalide strings in compare\n");
    return;
  }

  return strcmp(itemi, itemj);
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



/** 
 * printBst
 * 
 * Traverse inorder a BST and print out the key
 * This is also DFS. 
 * It prints out the keys in ascending order
 *
 *
 */
void printBst(NODE * n)
{

  if (!n)
    return;
  
  printBst(n->left);
  printf (" %s\n", n->key);  
  printBst(n->right);

  return;
}



/*
 * bstEnqueue
 */
static void bstEnqueue (NODE* n)
{

  QUEUE * q = (QUEUE*) malloc(sizeof(QUEUE));
  q->node = n;
  q->next = NULL;
  
  if (!tail && ! head) {
    
    // first node

    head = q;
    tail = head;
    return;
  }

  tail->next = q;
  tail = q;
  
  return;

}

/*
 * bstDequeue
 */

static NODE* bstDequeue(void)
{
  if (!head) {
    return NULL;
  }
  
  QUEUE * q = head;
  head = head->next;

  q->next = NULL;

  // todo: should free the q now
  return q->node;
}



/* 
 * bstPrintQueue
 */
static void bstPrintQueue(void)
{


  QUEUE * q = head;
  printf ("--- Print Queue Start ---\n");
  
  if (!q) {
    printf (" Empty queue!\n");
    return;
  }

  while (q) {
    printf ("%s, ", q->node->key);
    q = q->next;
  }
 
  printf ("\n--- Print Queue End ---\n");

}
/*
 * printBstBSF
 *
 * Use BSF to walk the BST tree. 
 * The NODE struct doesn't have graph adj-list, but
 * we can use left and right link as if they are the adj list
 *
 * BSF Breath Search First: 
 * Put unvisited nodes into a queue. Dequeue and find out 
 * its left and right child, enqueue them. 
 * 
 */

void printBstBSF(NODE *n)
{
  if (!n) {
    return;
  }

  // put the starting node in the queue

  bstEnqueue(n);
  n->marked = 1;

  // start dequeue

  NODE* v;
  while (v = bstDequeue()) {

    if (v->marked == 1) {
      // if marked (visited) keep going
      continue;
    }

    printf (" %s\n", v->key);
    // put the left and right child in queue
    // and mark them

    if (v->left) {
      bstEnqueue(v->left);
      v->left->marked = 1;
    }
    else if (v->right) {
      bstEnqueue(v->right);
      v->right->marked = 1;
    }
    else {
      continue;
    }

  }// while
  
}

/*
 * printBstDSF
 *
 * Use DSF to walk the BST tree. 
 * The NODE struct doesn't have graph adj-list, but
 * we can use left and right link as if they are the adj list
 *
 *
 */






/*
 * RBIsRed
 */
static BOOL
RBIsRed(NODE *n)
{

  if (!n)
    return FALSE;
  /*
  if (n->color == RED ) 
    return TRUE;
  else
    return FALSE;
  */

  return n->color == RED ? TRUE: FALSE;
}

/**
 * RBRotateLeft
 * RB basic op
 */
static NODE*
RBRotateLeft(NODE *n)
{
  //
  // n is the node to be rotated to the left, x is its 
  // current right child
  // 
  // The rotation requires n to change its right child
  // and x to change its left child to maintain the RB tree invariant
  // also update the coloring of both 
  // 

  if (!n || RBIsRed(n->right) == FALSE) {
    printf (" %s, Node is invalid\n",__FUNCTION__);
    return NULL;
  }

  NODE *x = n->right; // save the right child

  n->right = x->left; // Change n's rigth child: move the left child of the right child 
                      // under the node to be rotated to the left
  
  x->left = n; // Change x's left child: make n the new left child of x

  x->color = n->color; // let x inherit n's color

  n->color = RED; // let n parent link be in RED after rotation

  return x; 


}

/*
 * RBRotateRight
 * RB basic op: orient a left-leaning red link to temporarily lean right
 */
static NODE*
RBRotateRight(NODE *n)
{

  //
  // This is the exact opposite of RBRotateLeft
  // 

  if (!n || RBIsRed(n->left) == FALSE) {
    printf (" %s, Invalid note to roate\n",__FUNCTION__);
    return NULL;
  }

  // change the children of n and x
  // 

  NODE* x = n->left;
  n->left = x->right;
  x->right = n;

  // update the coloring
  // 

  x->color = n->color;
  n->color = RED;
  
  return x;
  
}





/*
 * RBFlipColors
 */
static void
RBFlipColors(NODE* n)
{

  // 
  // For a "4-node", if both children have RED links, then
  // change them to BLACK and give RED to the parent
  // 
  if (!n ||
      RBIsRed(n->left) == FALSE ||
      RBIsRed(n->right) == FALSE ) {

    printf ("%s, Invalid node\n",__FUNCTION__);
    return;
  }

  n->color = RED;
  n->left->color = BLACK;
  n->right->color = BLACK;

  return;
}





/*
 * bstInsert
 *
 * recurisively insert an item
 *
 */
NODE * bstInsert(NODE * parent, char * item)
{
  
  NODE * new;
  int cmp;

  if ( parent == NULL)
    {
      new = (NODE*) malloc(sizeof(NODE));
      new->left  = NULL;
      new->right = NULL;
      new->key   = item;
      printf ("Inserted new node: %s\n", item);
      return new;
    }
  
  cmp = compare (item, parent->key);
  if ( cmp < 0 ) {
    
    //Goto the left tree if the new key is less 
    printf ("   Go to the left of %s for item %s\n", parent->key, item);
    parent->left = bstInsert(parent->left, item);

  }

  else if ( cmp > 0 ) {
   
    //goto the right tree
    printf ("   Go to the right of %s for item %s\n", parent->key, item);
    parent->right = bstInsert(parent->right, item);
  }
  
  else {
    // it's a match
    // do nothing for now
    printf (" Matched!\n");
  }

  return parent;

}



/* 
 * RBTreeInsert
 */

NODE* 
RBTreeInsert(NODE* parent, char * item)
{
  NODE* new;
  int cmp;

  // 
  // Recursion termination condition
  // 
  if (!parent) {
    new = (NODE*) malloc(sizeof(NODE));
    new->left  = NULL;
    new->right = NULL;
    new->key   = item;
    new->color = RED; // all new nodes have parent link in RED
    printf ("Inserted a new node with key: %s\n", item);
    return new;
  }

  cmp = compare (item, parent->key);  
  
  if (cmp < 0 ) {
    // go to the left subtree
    printf ("   Go to the left of %s for item %s\n", parent->key, item);
    parent->left = RBTreeInsert(parent->left, item);
  }
  else if ( cmp > 0 ) {
   
    //goto the right tree
    printf ("   Go to the right of %s for item %s\n", parent->key, item);
    parent->right = RBTreeInsert(parent->right, item);
  }
  else {
    // it's a match
    // do nothing for now
    printf (" Matched!\n");
  }

  // For RB tree, perform rotation if necessary 
  // to keep the invariants

  if ( RBIsRed(parent->right) == TRUE &&
       RBIsRed(parent->left) == FALSE ) {
    // RED on the right, rotate to the left
    // to lean left
    printf (" Rotate to the left of %s\n",parent->key);
    parent = RBRotateLeft(parent); 
  }


  if ( RBIsRed(parent->left) == TRUE &&
       RBIsRed(parent->left->left) == TRUE ) {
    // RED on the left and also left of left, rotate to the right
    // to balance a 4 node
    printf (" Rotate to the right of %s\n",parent->key);
    parent = RBRotateRight(parent); 
  }
  
  if ( RBIsRed(parent->right) == TRUE &&
       RBIsRed(parent->left) == TRUE ) {
    // RED on the right and left, flip colors
    //
    printf (" Flip the color of %s\n",parent->key);
    RBFlipColors(parent); 
  }

  return parent;
}

/*
 * main (took from sorting.c)
 *
 * Take user input as an array of strings
 * The array index 0,1,... will be used as key
 * and the string used as value in BST
 *
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

  for ( i = 0; i<MAX_SIZE; i++) {

    //BST or RB tree insert

    if (str[i]) {
      printf ("+ Client asks to insert %s to the Tree\n", str[i]);

      // uncomment the following line for regular BST tree
      //root = bstInsert(root, str[i]);

      // uncomment the following line for RB tree
      //root = RBTreeInsert(root, str[i]);

      // testing bst queueing
      NODE *n = (NODE*) malloc(sizeof(NODE));
      n->key = str[i];
      bstEnqueue(n);
      bstPrintQueue();
      
      
    }
  }



  // testing dequeue only
  // 
  for ( i = 0; i<MAX_SIZE; i++) {

    NODE * n = bstDequeue();
    if (n) 
      printf (" Dequeued: %s\n", n->key);

    bstPrintQueue();

  }



  /*
  printf (" === BST Print Start===\n");
  printBst(root);
  printf (" === BST Print End===\n");
  */


  return 0;

}
