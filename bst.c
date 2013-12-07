/*****************
 * bst.c
 *
 * Implement basic binary search tree 
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

typedef struct _node {
  char * key;
  struct _node * left;
  struct _node * right;
} NODE;

NODE * root = NULL;


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

    //BST insert
    if (str[i]) {
      printf ("+ Client asks to insert %s\n", str[i]);
      root = bstInsert(root, str[i]);
    }
  }

  printf (" === BST Print Start===\n");
  printBst(root);
  printf (" === BST Print End===\n");

  return 0;

}
