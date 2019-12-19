#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"


void getCharArray(char *Filename){
	FILE* fp = fopen(Filename, "r");
	char* OutFileName = strcat(Filename, ".huff");
	FILE* fpo = fopen(OutFileName, "w");
	listnode *head = NULL;
	listnode *t = malloc(sizeof(listnode));
	char current;
	int size, i, present;
	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	current = fgetc(fp);
	t -> tree = malloc(sizeof(treenode));
	t -> tree -> value = current;
	t -> tree -> freq = 1;
	head = t;
	for(i = 0; i < size - 1; i++){
		current = fgetc(fp);
		t = head;
		present = 0;
		while(present == 0 && t -> next != NULL){
			if(t -> tree -> value == current){
				t -> tree -> freq++;
				present = 1;
			}
			t = t -> next;
		}
		if(t -> tree -> value == current){
			t -> tree -> freq++;
			present = 1;
		}
		if(!present){
			t -> next = malloc(sizeof(listnode));
			t -> next -> tree = malloc(sizeof(treenode));
			t -> next -> tree -> value = current;
			t -> next -> tree -> freq = 1;
		}
	}
	t = NULL;
	t = malloc(sizeof(listnode));
	t -> tree = malloc(sizeof(treenode));
	t -> tree -> freq = 1;
	t -> tree -> value = 3;
	t -> next = head;
	head = t;
	int low1, low2;
	listnode * t1;
	listnode * t2;
	while(head -> next != NULL){
		t = head;
		if(t -> tree -> freq > t -> next -> tree -> freq){
			low1 = t -> next -> tree -> freq;
			low2 = t -> tree -> freq;
			t1 = t -> next;
			t2 = t;
		}
		else{
			low2 = t -> next -> tree -> freq;
			low1 = t -> tree -> freq;
			t2 = t -> next;
			t1 = t;
		}
		t = t -> next;
		while(t -> next != NULL){
			if(t -> next -> tree -> freq < low2){
				if(t -> next -> tree -> freq < low1){
					low2 = low1;
					low1 = t -> next -> tree -> freq;
					t2 = t1;
					t1 = t -> next;
				}
				else{
					low2 = t -> next -> tree -> freq;
					t2 = t -> next;
				}
			}
			t = t -> next;
		}
		t1 -> tree = Merge_tn(t1 -> tree, t2 -> tree);
		if(head == t2){
			head = head -> next;
		}
		else{
			t = head;
			while(t -> next != t2){
				t = t -> next;
			}
			if(t2 -> next == NULL){
				t -> next = NULL;
			}
			else{
				t -> next = t -> next -> next;
			}
		}
		free(t2);
	}
	head = t;
	long bin = 0;
	int count = 0;
	int ** binArray = malloc(sizeof(int*) * 256);
	for(i = 0; i < 256; i++){
		binArray[i] = malloc(sizeof(int) * 2);
	}
	paths(head -> tree, bin, count, binArray);
	fseek(fp, 0, SEEK_SET);
	printHeader(head -> tree, fpo, 0, 8);
	int loc = 8;
	char byte = 0;
	while((current = fgetc(fp)) != EOF){
		for(i = 0; i < binArray[(int)current][0]; i++){
			byte |= ((binArray[(int)current][1] >> (binArray[(int)current][0] - 1 - i)) & 1) << --loc;
			if(!loc){
				loc = 8;
				fwrite(&byte, 1, 1, fpo);
				byte = 0;
			}
			
		}
	}
	for(i = 0; i < binArray[3][0]; i++){
		byte |= ((binArray[3][1] >> (binArray[3][0] - 1 - i)) & 1) << --loc;
		if(!loc){
			loc = 8;
			fwrite(&byte, 1, 1, fpo);
			byte = 0;
		}		
	}
	freetree(head -> tree);
	free(head);
	free(binArray);
	fwrite(&byte, 1, 1, fpo);
	fclose(fp);
	fclose(fpo);
	return;
}

void paths(treenode * t, long num, int count, int ** binArray){
	if(t -> value){
		binArray[(int) t -> value][0] = count;
		binArray[(int) t -> value][1] = num;
	}
	else{
		paths(t -> left, 2 * num, count + 1, binArray);
		paths(t -> right, 2 * num + 1, count + 1, binArray);
	}
	return;
}

void printHeader(treenode *t, FILE * fp, char byte, int loc){
	if(t -> value){
		byte |= 1 << --loc;
		loc = 8;
		fwrite(&byte, 1, 1, fp);
		byte = 0;
		fwrite(&(t -> value), sizeof(char), 1, fp);
	}
	else{
		byte |= 0 << --loc;
		if(!loc){
			loc = 8;
			fwrite(&byte, 1, 1, fp);
			byte = 0;
		}
		printHeader(t -> left, fp, byte, loc);
		printHeader(t -> right, fp, 0, 8);
	}
	return;
}

treenode * Merge_tn(treenode * left, treenode * right)
{
	treenode * mergedtreenode = malloc(sizeof(treenode));
	mergedtreenode -> left = left;
	mergedtreenode -> right = right;
	mergedtreenode -> value = 0;
	mergedtreenode -> freq = left -> freq + right -> freq;
	return mergedtreenode;
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
	getCharArray(argv[1]);
	return 0;
}
