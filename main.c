#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_X 50 
#define MAX_Y 50
#define MIN_X 10
#define MIN_Y 10

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

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

void makeBuildings(char** table, int x, int y, int num_buildings) {
    for (int b = 0; b < num_buildings; b++) {

        int current_x = rand() % x;
        int current_y = rand() % y;
        table[current_x][current_y] = '#';

        int building_size = (rand() % 11) + 5;

        for (int step = 0; step < building_size; step++) {
            
            int rand_dir = rand() % 4; 

            int next_x = current_x;
            int next_y = current_y;

            if (rand_dir == UP) { 
                next_x--;
            } else if (rand_dir == DOWN) { 
                next_x++;
            } else if (rand_dir == LEFT) {
                next_y--;
            } else if (rand_dir == RIGHT) {
                next_y++;
            }

            if (next_x < 0 || next_x >= x || next_y < 0 || next_y >= y) {
                step--; 
                continue; 
            }
            current_x = next_x;
            current_y = next_y;
            table[current_x][current_y] = '#';
        }
    }
}

void addZombies(char** table , int x,int y,int z_num){
	for(int i =0;i<x;i++){
		for(int j = 0 ; j < y ; j++){
			if(table[i][j]== '.'){
				table[i][j] = (rand() % z_num)+1 + '0';
			}
		}
	}
	
}

int main(void){
	srand(time(NULL));
	// Starting by the user input
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

	// Allocating memory for the table according to the dimensions the user gave (x,y)
	char **table = malloc(x * sizeof(*table));
	if (!table) {
		printf("failed to initialize table\n");
		return 1;
	}

	for(int i = 0; i < x; i++) {
		table[i] = (char*)malloc(sizeof(char) * y);
		if (!table[i]) {
			printf("failed to initialize table row %d\n", i);
			for (int j = 0; j < i; j++) {
				free(table[j]);
			}
			free(table);
			return 1;
		}
	}
	
	// filling the table with dots that mean "Empty space"
	for(int i = 0; i < x; i++){
	    for(int j = 0; j < y; j++){
	        table[i][j] = '.';
	    }
	}
	int num_buildings = ((x * y) / 100) + 4;
	makeBuildings(table,x,y, num_buildings);
	addZombies(table,x,y,z);
	
	printTable(table,x,y);
	cleanTable(table,x);

	
	return 0;
}
