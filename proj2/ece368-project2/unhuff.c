#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"


void unhuff(char * Filename){
	FILE* fp = fopen(Filename, "r");
	char* OutFileName = strcat(Filename, ".unhuff");
	FILE* fpo = fopen(OutFileName, "w");
	char current;
	short cur;
	fread(&cur, 1, 1, fp);
	treenode * head = malloc(sizeof(treenode));
	treenode * t;
	if(((cur >> 7) & 1) == 0){
		head -> value = 0;
	}
	else{
		printf("ERROR\n");
		return;
	}
	buildTree(head, fp, cur);
	current = fgetc(fp);
	int loc = 8;
	t = head;
	int val = (current >> --loc) & 1;
	while(feof(fp) == 0){
		while(loc){
			if(t -> value == 3){
				break;
			}
			else if(t -> value != 0){
				fprintf(fpo, "%c", t -> value);
				t = head;
			}
			else if(val == 0){
				t = t -> left;
				val = (current >> --loc) & 1;
			}
			else if(val == 1){
				t = t -> right;
				val = (current >> --loc) & 1;
			}
		}
		loc = 8;
		current = fgetc(fp);
	}
	freetree(head);
	fclose(fp);
	fclose(fpo);
	return;
}

void buildTree(treenode * head, FILE * fp, char current){
	int loc = 7;
	treenode * next = findNext(head);
	int val;
	while(next != NULL){
		val = (current >> --loc) & 1;
		if(!loc){
			loc = 8;
			current = fgetc(fp);
		}
		if(val){
			if(loc != 8){
				current = fgetc(fp);
				loc = 8;
			}
			next -> value = current;
			next = findNext(head);
			if(next){
				current = fgetc(fp);
			}
		}
		else{
			next -> value = 0;
			next = findNext(head);
		}
	}
	return;
}

treenode * findNext(treenode * current){
	treenode * next = NULL;
	if(current -> left == NULL){
		next = malloc(sizeof(treenode));
		current -> left = next;
		return next;
	}
	else if(current -> left -> value == 0){
		next = findNext(current -> left);
		if(next){
			return next;
		}
		else{
			if(!(current -> right)){
				next = malloc(sizeof(treenode));
				current -> right = next;
				return next;
			}
			else if(current -> right -> value != 0){
				return NULL;
			}
			return findNext(current -> right);
		}
	}
	else if(current -> right == NULL && current -> left -> value != 0){
		next = malloc(sizeof(treenode));
		current -> right = next;
		return next;
	}
	else if(current -> right -> value == 0 && current -> left -> value != 0){
		next = findNext(current -> right);
		if(next){
			return next;
		}
		else{
			return NULL;
		}
	}
	else{
		return NULL;
	}
}

void freetree(treenode * tree1){
	if(tree1 -> left != NULL && tree1 -> right != NULL)
	{
		freetree(tree1 -> left);
		freetree(tree1 -> right);
	}
	else if(tree1 -> left != NULL)
	{
		freetree(tree1 -> left);
	}
	else if(tree1 -> right != NULL)
	{
		freetree(tree1 -> right);
	}
	free(tree1);
	return;
}

int main(int argc, char ** argv){
	unhuff(argv[1]);
	return 0;
}
