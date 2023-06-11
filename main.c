#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//global variable
typedef enum COLOR COLOR;
int numVertax;
#define VERTAX_SIZE 100
int adjMartix[VERTAX_SIZE][VERTAX_SIZE];
int gCount;
COLOR drawTable[VERTAX_SIZE];
enum COLOR {
	noColor,
	color1,
	color2,
	color3,
	color4,
	color5,
	color6
};
//function prototype
void readGraph(char*);
void initGlobalVariable();
void runColor6();
int findVertex();
int* findIncidentEdge(int);
void clearEdge(int , int*);
void putEdge(int, int*);
COLOR pickColor(int, int*);
//function implement
COLOR pickColor(int v,int* E) {
	int colorTable[7];
	for (int i = 1; i < 7; i++)
		colorTable[i] = 1;
	for (int i = 1; i < E[0]/*flag*/; i++) {
		int myColor = (int)drawTable[E[i]];
		colorTable[myColor] = 0;
	}
	for (int i = 1; i < 7; i++) {
		if (colorTable[i] == 1)
			return (COLOR)i;
	}
}
void putEdge(int v, int* E) {
	for (int i = 1; i < E[0]/*flag*/; i++) {
		adjMartix[v][E[i]] = 1;
		adjMartix[E[i]][v] = 1;
	}
	adjMartix[v][v] = 0;//enable
}
void clearEdge(int v,int* E) {
	for (int i = 1; i < E[0]/*flag*/; i++) {
		adjMartix[v][E[i]] = 0;
		adjMartix[E[i]][v] = 0;
	}
	adjMartix[v][v] = -1;//disable
}
int* findIncidentEdge(int v) {
	int* incidentTable = malloc(VERTAX_SIZE * sizeof(int));
	incidentTable[0] = 1;//flag
	for (int i = 0; i < VERTAX_SIZE; i++) {
		if (adjMartix[v][i] == 1) {
			int flag = incidentTable[0];
			incidentTable[flag] = i;
			incidentTable[0]++ ;
		}
	}
	return incidentTable;
}
int findVertex() {//return -1 means no found
	for (int i = 0; i < VERTAX_SIZE; i++) {
		if (drawTable[i] != noColor)
			continue;
		if (adjMartix[i][i] == -1)//vertex disable
			continue;
		int count = 0;
		for (int j = 0; j < VERTAX_SIZE; j++) {
			if (adjMartix[i][j] == 1)
				count++;
		}
		if (count < 6) {//found
			gCount = count;
			return i;
		}
	}
	return -1;
}
void runColor6() {
	while (true) {
		int v = findVertex();//找到一個還沒著色的vertex
		if (v == -1)//no found
			return;
		if (gCount == 0) {//no neighbor
			drawTable[v] = color1;
		}
		else {
			int* E = findIncidentEdge(v);
			clearEdge(v, E);//將v和N[v]改為未著色
			runColor6();
			putEdge(v, E);//將v與N[v]標記為已著色
			drawTable[v] = pickColor(v, E);//找到一個顏色給v
		}
	}
	printf("error return");
	return;
}
void initGlobalVariable() {

	//adjList
	for (int i = 0; i < VERTAX_SIZE; i++) {
		for (int j = 0; j < VERTAX_SIZE; j++) {
			adjMartix[i][j] = 0;
		}
	}
}
void readGraph(char* fileName) {
	FILE *in_file = fopen(fileName, "r"); // read only 
	// test for files not existing. 
	if (in_file == NULL)
	{
		printf("Error! Could not open file\n");
		exit(-1); // must include stdlib.h 
	}

	char smp[1000];
	memset(smp, '\0', 1000);

	int firstV, secondV;
	int storeNum;
	int turn = 0;
	fscanf(in_file, "%d", &numVertax);
	while (fscanf(in_file, "%d", &storeNum) == 1) {
		if (turn == 0) {
			firstV = storeNum;
			turn = 1;
		}
		else if (turn == 1) {
			secondV = storeNum;
			turn = 0;
			adjMartix[firstV][secondV] = 1;
			adjMartix[secondV][firstV] = 1;
		}
	}
}



int main() {
	initGlobalVariable();
	char fileName[] = "input1.txt";

	readGraph(fileName);
	runColor6();
	printf("done");
}