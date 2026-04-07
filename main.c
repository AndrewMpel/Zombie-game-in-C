#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_X 50 
#define MAX_Y 50
#define MIN_X 10
#define MIN_Y 10

void printSelect(){
	printf("=================\n");
	printf("====Zombicide====\n");
	printf(" ");
}

void cleanTable(char **table,int x){
	for (int i = 0; i < x; i++) {
	   free(table[i]);
	}
	free(table);
}
void printTable(char **table, int x, int y){
    printf("   ");
    for (int j = 0; j < y; j++) {
        printf("%2d ", j+1);
    }
    printf("\n");
    printf("---");
    for (int j = 0; j < y; j++) {
        printf("---");
    }
    printf("\n");

    for (int i = 0; i < x; i++) {
        printf("%2d|", i+1);

        for (int j = 0; j < y; j++) {
            printf(" %c ", table[i][j]);
        }
        printf("\n");
    }
}

int main(void){
	int x , y , z;
	printf("Select Dimensions: x = ");
	scanf("%d",&x);
	while(x>MAX_X || x<MIN_X){
		printf("Give a number from 10 to 50: ");
		scanf("%d",&x);
	}
	printf("y = ");
	scanf("%d",&y);
	while(y>MAX_Y || y<MIN_Y){
		printf("Give a number from 10 to 50: ");
		scanf("%d",&y);
	}
	printf("Give number of zombies[1-9]: ");
	scanf("%d",&z);
	while(z>9 || z<1){
		printf("Give a number from 1 to 9: ");
		scanf("%d",&z);
	}

	char **table = malloc(x * sizeof(*table));

	for(int i=0 ; i<x ; i++){
		table[i] = (char*)malloc(sizeof(char)*y);
	}

	for(int i = 0; i < x; i++){
	    for(int j = 0; j < y; j++){
	        table[i][j] = '.';
	    }
	}
	printTable(table,x,y);
	cleanTable(table,x);

	
	return 0;
}
