#ifndef __huffman_h_
#define __huffman_h_

#include <stdlib.h>
#include <stdio.h>


typedef struct tree {
	struct tree * left;
	struct tree * right;
	char value;
	long freq;
}treenode;

typedef struct list {
	struct list * next;
	treenode * tree;
}listnode;

void getCharArray(char *Filename);
treenode * Merge_tn(treenode * left, treenode * right);
void paths(treenode * t, long num, int count, int ** binArray);
void printHeader(treenode *t, FILE * fp, char cur, int i);
void unhuff(char * FileName);
void buildTree(treenode * head, FILE * fp, char cur);
void freetree(treenode * t);
treenode * findNext(treenode * current);

#endif
