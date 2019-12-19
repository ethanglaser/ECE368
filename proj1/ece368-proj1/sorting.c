#include <stdio.h>
#include <math.h>
#include "sorting.h"


long *Load_File(char *Filename, int *Size){
	FILE* fp = fopen(Filename, "r");
	int num;
	fscanf(fp, "%d", &num);
	long *array = malloc(num * sizeof(long));
	int index;
	for(index = 0; index < num; index++){
		fscanf(fp, "%ld", &array[index]);
	}
	*Size = num;
	fclose(fp);
	return array;
}
int Save_File(char *Filename, long *Array, int Size){
	FILE* fp = fopen(Filename, "w");
	fprintf(fp, "%d\n", Size);
	int index;
	int success = 0;
	for(index = 0; index < Size; index++){
		fprintf(fp, "%ld\n", Array[index]);
		success++;
	}
	fclose(fp);
	return success;
}
void Shell_Insertion_Sort(long *Array, int Size, double *N_Comp, double *N_Move){
	int k;
	int num;
	long tempval;
	int i, j;
	int comps = 0;
	int moves = 0;	
	for(k = Size; k > 0; k--){
		num = k;
		while(!(num % 3)){
			num /= 3;
		}
		while(!(num % 2)){
			num /= 2;
		}
		if(num == 1){
			for(j = k; j < Size; j++){
				tempval = Array[j];
				i = j;
				while(i >= k && Array[i - k] > tempval){
					moves++;
					comps++;
					Array[i] = Array[i - k];
					i = i - k;
				}
				comps++;
				Array[i] = tempval;
			}			
		}			
	}
	*N_Comp = comps;
	*N_Move = moves;
	return;			
}
void Improved_Bubble_Sort(long *Array, int Size, double *N_Comp, double *N_Move){
	int N = Size;
	int index2;
	int col;
	long tempval;
	int i, j, last;
	int comps = 0;
	int moves = 0;
	while(N > 1){
		N = N / 1.3;
		if(N == 9 || N == 10){
			N = 11;
		}
		for(index2 = 0; index2 < N; index2++){
			col = 0;
			while(col * N + index2 < Size){
				col++;
			}
			i = col - 1;
			do{
				last = -1;
				for(j = 0; j < i; j++){
					comps++;
					if(Array[N * j + index2] > Array[N * (1 + j) + index2]){
						moves++;
						tempval = Array[j * N + index2];
						Array[j * N + index2] = Array[N * (j + 1) + index2];
						Array[N * (j + 1) + index2] = tempval;
						last = j - 1;
					}
				}
				i = last - 1;
			}while(last >= 0);
		}
	}
	*N_Comp = comps;
	*N_Move = moves;
	return;			
}
void Save_Seq1 (char *Filename, int N){
	int index;
	int num;
	FILE* fp = fopen(Filename, "w");
	for(index = N; index > 0; index--){
		num = index;
		while(!(num % 3)){
			num /= 3;
		}
		while(!(num % 2)){
			num /= 2;
		}
		if(num == 1){
			fprintf(fp, "%d", index);
		}
	}
	fclose(fp);
	return;
}
void Save_Seq2 (char *Filename, int N){
	FILE* fp = fopen(Filename, "w");
	while(N > 1){
		N = N / 1.3;
		if(N == 9 || N == 10){
			N = 11;
		}
		fprintf(fp, "%d", N);
	}
	fclose(fp);
	return;
}
