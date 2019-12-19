#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "map.h"

void dijkstra2(char *Fmap, char *Fquery){
	FILE* fpm = fopen(Fmap, "r");
	FILE* fpq = fopen(Fquery, "r");
	int numV, numE, numQ;
	int i, j;
	int value, distance;
	fscanf(fpm, "%d%d", &numV, &numE);
	int *xCoords = malloc(sizeof(int) * numV);
	int *yCoords = malloc(sizeof(int) * numV);
	int *coordOnes = malloc(sizeof(int) * numE);
	int *coordTwos = malloc(sizeof(int) * numE);
	for(i = 0; i < numV; i++){
		fscanf(fpm, "%d%d%d", &value, &xCoords[i], &yCoords[i]);
	}
	for(i = 0; i < numE; i++){
		fscanf(fpm, "%d%d", &coordOnes[i], &coordTwos[i]);
	}
	listnode ** adjMatrix = malloc(sizeof(listnode) * numV);
	for(i = 0; i < numV; i++){
		adjMatrix[i] = malloc(sizeof(listnode));
		adjMatrix[i] -> next = NULL;
		adjMatrix[i] -> val = -1;
	}
	int * visited = malloc(sizeof(int) * numV);
	int * dists = malloc(sizeof(int) * numV);
	int * prev = malloc(sizeof(int) * numV);
	for(i = 0; i < numE; i++){
		distance = findDist(xCoords[coordOnes[i]], yCoords[coordOnes[i]], xCoords[coordTwos[i]], yCoords[coordTwos[i]]);
		if(adjMatrix[coordOnes[i]] -> val == -1){
			adjMatrix[coordOnes[i]] -> val = coordTwos[i];
			adjMatrix[coordOnes[i]] -> dist = distance;
		}
		else{
			listnode * new = malloc(sizeof(listnode));
			new -> val = coordTwos[i];
			new -> dist = distance;
			new -> next = adjMatrix[coordOnes[i]];
			adjMatrix[coordOnes[i]] = new;
		}
		if(adjMatrix[coordTwos[i]] -> val == -1){
			adjMatrix[coordTwos[i]] -> val = coordOnes[i];
			adjMatrix[coordTwos[i]] -> dist = distance;
		}
		else{
			listnode * new = malloc(sizeof(listnode));
			new -> val = coordOnes[i];
			new -> dist = distance;
			new -> next = adjMatrix[coordTwos[i]];
			adjMatrix[coordTwos[i]] = new;
		}
	}

	free(xCoords);
	free(yCoords);
	free(coordOnes);
	free(coordTwos);

	int orig, dest;
	fscanf(fpq, "%d", &numQ);
	for(i = 0; i < numQ; i++){
		for(j = 0; j < numV; j++){
			visited[j] = 0;
			dists[j] = 2147283647;
			prev[j] = -1;
		}
		fscanf(fpq, "%d%d", &orig, &dest);
		dists[orig] = 0;
		for(j = 0; j < numV; j++){
			minPaths2(dists, visited, prev, adjMatrix, numV);
		}
		if(dists[dest] != 2147283647){
			printf("%d\n", dists[dest]);
			listnode * order = NULL;
			listnode * new = NULL;
			value = dest;
			while(value != orig){
				new = malloc(sizeof(listnode));
				new -> val = value;
				new -> next = order;
				order = new;
				value = prev[value];
			}
			new = malloc(sizeof(listnode));
			new -> val = value;
			new -> next = order;
			order = new;
			printf("%d", order -> val);
			while(new -> next != NULL){
				order = new;
				printf(" %d", new -> next -> val);
				new = new -> next;
				free(order);
			}
			free(new);
		}
		else{
			printf("INF\n%d %d", orig, dest);
		}
		printf("\n");
	}

	listnode * new = NULL;
	for(i = 0; i < numV; i++){
		while(adjMatrix[i] -> next != NULL){
			new = adjMatrix[i];
			adjMatrix[i] = adjMatrix[i] -> next;
			free(new);
		}
		free(adjMatrix[i]);
	}
	free(adjMatrix);
	free(visited);
	free(dists);
	free(prev);

	fclose(fpm);
	fclose(fpq);
}

void minPaths2(int * dists, int * visited, int * prev, listnode ** adjMatrix, int numV){
	int i;
	int min = 2147283647;
	int minIndex = -1;
	for(i = 0; i < numV; i++){
		if(!visited[i] && dists[i] < min){
			minIndex = i;
			min = dists[i];
		}
	}
	if(minIndex != -1){
		visited[minIndex] = 1;
		listnode * current = adjMatrix[minIndex];
		if(current -> dist != -1 && (min + current -> dist < dists[current -> val])){
			dists[current -> val] = min + current -> dist;
			prev[current -> val] = minIndex;
		}
		while(current -> next != NULL){
			current = current -> next;
			if(current -> dist != -1 && (min + current -> dist < dists[current -> val])){
				dists[current -> val] = min + current -> dist;
				prev[current -> val] = minIndex;
			}
		}

	}
}

void dijkstra(char *Fmap, char *Fquery){
	FILE* fpm = fopen(Fmap, "r");
	FILE* fpq = fopen(Fquery, "r");
	int numV, numE, numQ;
	int i, j;
	int val, dist;
	fscanf(fpm, "%d%d", &numV, &numE);
	int *xCoords = malloc(sizeof(int) * numV);
	int *yCoords = malloc(sizeof(int) * numV);
	int *coordOnes = malloc(sizeof(int) * numE);
	int *coordTwos = malloc(sizeof(int) * numE);
	for(i = 0; i < numV; i++){
		fscanf(fpm, "%d%d%d", &val, &xCoords[i], &yCoords[i]);
	}
	for(i = 0; i < numE; i++){
		fscanf(fpm, "%d%d", &coordOnes[i], &coordTwos[i]);
	}
	int **adjMatrix = malloc(sizeof(int*) * numV);
	int * visited = malloc(sizeof(int) * numV);
	int * dists = malloc(sizeof(int) * numV);
	int * prev = malloc(sizeof(int) * numV);
	for(i = 0; i < numV; i++){
		adjMatrix[i] = malloc(sizeof(int) * numV);
		for(j = 0; j < numV; j++){
			adjMatrix[i][j] = -1;
		}
	}
	for(i = 0; i < numE; i++){
		dist = findDist(xCoords[coordOnes[i]], yCoords[coordOnes[i]], xCoords[coordTwos[i]], yCoords[coordTwos[i]]);
		adjMatrix[coordOnes[i]][coordTwos[i]] = dist;
		adjMatrix[coordTwos[i]][coordOnes[i]] = dist;
	}

	free(xCoords);
	free(yCoords);
	free(coordOnes);
	free(coordTwos);

	int orig, dest, value;
	fscanf(fpq, "%d", &numQ);
	for(i = 0; i < numQ; i++){
		for(j = 0; j < numV; j++){
			visited[j] = 0;
			dists[j] = 2147283647;
			prev[j] = -1;
		}
		fscanf(fpq, "%d%d", &orig, &dest);
		dists[orig] = 0;
		for(j = 0; j < numV; j++){
			minPaths(dists, visited, prev, adjMatrix, numV);
		}
		printf("%d\n", dists[dest]);
		listnode * order = NULL;
		listnode * new = NULL;
		value = dest;
		while(value != orig){
			new = malloc(sizeof(listnode));
			new -> val = value;
			new -> next = order;
			order = new;
			value = prev[value];
		}
		new = malloc(sizeof(listnode));
		new -> val = value;
		new -> next = order;
		order = new;
		printf("%d", order -> val);
		while(new -> next != NULL){
			order = new;
			printf(" %d", new -> next -> val);
			new = new -> next;
			free(order);
		}
		free(new);
		printf("\n");
	}

	for(i = 0; i < numV; i++){
		free(adjMatrix[i]);
	}
	free(adjMatrix);
	free(visited);
	free(dists);
	free(prev);

	fclose(fpm);
	fclose(fpq);
}

void minPaths(int * dists, int * visited, int * prev, int ** adjMatrix, int numV){
	int i;
	int min = 2147283647;
	int minIndex = -1;
	for(i = 0; i < numV; i++){
		if(!visited[i] && dists[i] < min){
			minIndex = i;
			min = dists[i];
		}
	}
	if(minIndex != -1){
		visited[minIndex] = 1;
		for(i = 0; i < numV; i++){
			if(adjMatrix[minIndex][i] != -1 && (min + adjMatrix[minIndex][i] < dists[i])){
				dists[i] = min + adjMatrix[minIndex][i];
				prev[i] = minIndex;
			}
		}
	}
}

int findDist(int x1, int y1, int x2, int y2){
	int dist = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	return dist;
}

/*void maps(char *Fmap, char *Fquery){
	FILE* fpm = fopen(Fmap, "r");
	FILE* fpq = fopen(Fquery, "r");
	int numV, numE, numQ;
	int i;
	int val;
	fscanf(fpm, "%d%d", &numV, &numE);
	int *xCoords = malloc(sizeof(int) * numV);
	int *yCoords = malloc(sizeof(int) * numV);
	int *coordOnes = malloc(sizeof(int) * numE);
	int *coordTwos = malloc(sizeof(int) * numE);
	//int *connects = malloc(sizeof(int*) * numV * numE);
	for(i = 0; i < numV; i++){
		fscanf(fpm, "%d%d%d", &val, &xCoords[i], &yCoords[i]);
	}
	for(i = 0; i < numE; i++){
		fscanf(fpm, "%d%d", &coordOnes[i], &coordTwos[i]);
	}
	//adjacent(connects, coordOnes, coordTwos, numV, numE);
	int **adjMatrix = malloc(sizeof(int*) * numV);
	for(i = 0; i < numV; i++){
		adjMatrix[i] = malloc(sizeof(int) * numV);
	}
	for(i = 0; i < numE; i++){
		adjMatrix[coordOnes[i]][coordTwos[i]] = 1;
		adjMatrix[coordTwos[i]][coordOnes[i]] = 1;
	}

	int orig, dest;
	int minDist = -1;
	fscanf(fpq, "%d", &numQ);
	for(i = 0; i < numQ; i++){
		listnode * init = NULL;
		fscanf(fpq, "%d%d", &orig, &dest);
		getPath(adjMatrix, init, orig, dest, numV, xCoords, yCoords, &minDist);		
	}

	printf("\nDistance of route: %d\nAs the crow flies: %d\n", minDist, findDist(xCoords[orig], yCoords[orig], xCoords[dest], yCoords[dest]));

	fclose(fpm);
	fclose(fpq);
}

void getShort(int ** adj, listnode * used, int current, int target, int numV, int * x, int * y, int * min){
	int i, status;
	listnode * new = malloc(sizeof(listnode));
	new -> val = current;
	new -> next = used;

	if(current == target){
		int dist = 0;
		printf("%d", new -> val);
		while(new -> next != NULL){
			printf(" %d", new -> next -> val);
			dist += findDist(x[new -> val], y[new -> val], x[new -> next -> val], y[new -> next -> val]);
			new = new -> next;
		}
		printf(" -> %d\n", dist);
		if(*min == -1 || *min > dist){
			*min = dist;
		}
		return;
	}
	listnode * head = malloc(sizeof(listnode)); //idk if this is needed
	head = new;


	int minDist = -1;
	int minIndex = 0;
	int dist;
	for(i = 0; i < numV; i++){
		if(adj[current][i]){
			status = 1;
			new = head;
			while(new -> next != NULL){
				if(i == new -> next -> val){
					status = 0;
				}
				new = new -> next;
			}
			if(status){
				dist = findDist(x[current], y[current], x[i], y[i]) + findDist(x[i], y[i],  x[target], y[target]) - findDist(x[current], y[current], x[target], y[target]);
				if(minDist == -1){
					minDist = dist;
					minIndex = i;
				}
				else if(minDist > dist){
					minDist = dist;
					minIndex = i;
				}
			}
		}
	}
	printf("mindist: %d\n", minDist);
	getShort(adj, head, minIndex, target, numV, x, y, min);
	return;
}

void getPath(int ** adj, listnode * used, int current, int target, int numV, int * x, int * y, int * min){
	int i, status;
	listnode * new = malloc(sizeof(listnode));
	new -> val = current;
	new -> next = used;

	if(current == target){
		int dist = 0;
		printf("%d", new -> val);
		while(new -> next != NULL){
			printf(" %d", new -> next -> val);
			dist += findDist(x[new -> val], y[new -> val], x[new -> next -> val], y[new -> next -> val]);
			new = new -> next;
		}
		printf(" -> %d\n", dist);
		if(*min == -1 || *min > dist){
			*min = dist;
		}
		return;
	}
	listnode * head = malloc(sizeof(listnode)); //idk if this is needed
	head = new;


	for(i = 0; i < numV; i++){
		if(adj[current][i]){
			status = 1;
			new = head;
			while(new -> next != NULL){
				if(i == new -> next -> val){
					status = 0;
				}
				new = new -> next;
			}
			if(status && findDist(x[i], y[i], x[target], y[target]) < findDist(x[current], y[current], x[target], y[target])){
				getPath(adj, head, i, target, numV, x, y, min);
			}
		}
	}
	return;
}

void adjacent(int ** cons, int * c1, int * c2, int verts, int edges){
	int i, j;
	int count = 0;
	for(i = 0; i < verts; i++){
		for(j = 0; j < edges; j++){
			if(c1[j] == i || c2[j] == i){
				count++;
			}
		}
		cons[i] = malloc(sizeof(int) * count);
		for(j = 0; j < edges; j++){
			if(c1[j] == i){
				printf(" %d", c2[j]);
			}
			if(c2[j] == i){
				printf(" %d", c1[j]);
			}
		}
		count = 0;
	}
}*/


int main(int argc, char ** argv){
	//maps(argv[1], argv[2]);
	//dijkstra(argv[1], argv[2]);
	dijkstra2(argv[1], argv[2]);
	return 0;
}
