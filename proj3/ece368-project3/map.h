#ifndef __huffman_h_
#define __huffman_h_

#include <stdlib.h>
#include <stdio.h>

typedef struct list {
	struct list * next;
	int val;
	int dist;
}listnode;

void dijkstra(char *Fmap, char *Fquery);
void maps(char *Fmap, char *Fquery);
void adjacent(int ** cons, int * c1, int * c2, int verts, int edges);
void getPath(int ** adj, listnode * used, int current, int target, int numV, int * x, int * y, int * min);
int findDist(int x1, int y1, int x2, int y2);
void getShort(int ** adj, listnode * used, int current, int target, int numV, int * x, int * y, int * min);
void minPaths(int * dists, int * visited, int * prev, int ** adjMatrix, int numV);
void minPaths2(int * dists, int * visited, int * prev, listnode ** adjMatrix, int numV);

#endif
