#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "weapons.h"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#define MAX_X 30
#define MAX_Y 30
#define MIN_X 10
#define MIN_Y 10
#define BASE_SCORE 5

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

void printSelect(){
	printf("Select your weapon: n (neurogun), b (bombing), p (plasmagun), x (Exit)\n");
    printf("Example: n 6,6 (6,6 are the coordinates in x and y)\n");
    printf("~> ");
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
// A function that creates buildings using the ((x * y) / 100) + 4 formula to calculate the
// number of buildings. Then builds it in a random direction
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
// A function that fills the table with as many zombie types as the user gave
void addZombies(char** table , int x,int y,int z_num){
	for(int i =0;i<x;i++){
		for(int j = 0 ; j < y ; j++){
			if(table[i][j]== '.'){
				table[i][j] = (rand() % z_num)+1 + '0';
			}
		}
	}
	
}
bool checkWin(char** table, int x, int y){
	for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++){
			if(table[i][j] >= '1' && table[i][j] <= '9'){
				return false;
			}
		}
	}
	return true;
}

// A function that adds a sound source in a random direction so that zombies move in that way
// int moveToSound(char** table , int x,int y){
// 	int direction=  rand() % 4; 
// 	switch(direction){
// 		case UP:
// 			
// 			break;
// 		case DOWN:
// 		
// 			break;
// 		case LEFT:
// 
// 			break;
// 		case RIGHT:
// 
// 			break;
// 		default:
// 			printf("Wrong Direction\n");
// 			break;
// 	}
// }

int main(void) {
	printf("======================================================================\n");
	printf("=====================Welcome to the Zombicide game====================\n");
	printf("======================================================================\n");
    int x, y, z;
    srand(time(NULL));

    printf("Select Dimensions: x = ");
    scanf("%d", &x);
    while (x > MAX_X || x < MIN_X) {
        printf("Give a number from 10 to 50: ");
        scanf("%d", &x);
    }

    printf("y = ");
    scanf("%d", &y);
    while (y > MAX_Y || y < MIN_Y) {
        printf("Give a number from 10 to 50: ");
        scanf("%d", &y);
    }

    printf("Give number of zombies[1-9]: ");
    scanf("%d", &z);
    while (z > 9 || z < 1) {
        printf("Give a number from 1 to 9: ");
        scanf("%d", &z);
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    char **table = malloc(x * sizeof(*table));
    if (!table) return 1;

    for (int i = 0; i < x; i++) {
        table[i] = (char*)malloc(sizeof(char) * y);
        if (!table[i]) {
            for (int j = 0; j < i; j++) free(table[j]);
            free(table);
            return 1;
        }
    }

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            table[i][j] = '.';
        }
    }

    int num_buildings = ((x * y) / 100) + 4;
    makeBuildings(table, x, y, num_buildings);
    addZombies(table, x, y, z);

	int level = 1;
	int score = 0;
	int z_killed = 0;
    int game_running = 1;
    int multiplier = 1;
    while (game_running) {
    	z_killed = 0;
    	if (checkWin(table,x,y)){
        	printf("\n\nCongratulations you successfuly cleared this level!!!\n");

        	fflush(stdout);
        	#ifdef _WIN32
        	        Sleep(2000);
        	#else
        	        sleep(2);
        	#endif

        	cleanTable(table,x);
        	level++;
			x++;
			y++;
			if (x > MAX_X || y > MAX_Y) {
                printf("CONGRATULATIONS! The zombie outbreak is fully eradicated\n");
                printf("Now the only danger is humanity itself\n");
                table = NULL;
                break;
            }
            table = malloc(x * sizeof(*table));
                if (!table) return 1;
            for (int i = 0; i < x; i++) {
                 table[i] = (char*)malloc(sizeof(char) * y);
                 if (!table[i]) {
                     for (int j = 0; j < i; j++) free(table[j]);
                     free(table);
                     return 1;
                 }
             }
             for (int i = 0; i < x; i++) {
                 for (int j = 0; j < y; j++) {
                     table[i][j] = '.';
                 }
             }
             int num_buildings = ((x * y) / 100) + 4;
             makeBuildings(table, x, y, num_buildings);
             addZombies(table, x, y, z);	

             continue;
        }
        printf("======================================================================\n");
        printTable(table, x, y);
        printf("\nLevel %d - Score %d\n\n",level,score);

		printSelect();
		char move[50];
        
        fgets(move, sizeof(move), stdin);

        char weapon = ' ';
        int target_x = -1, target_y = -1;
        char direction = ' ';
        
        sscanf(move, " %c", &weapon);
        
        if (weapon == 'n' || weapon == 'N') {
             if (sscanf(move, " %c %d,%d", &weapon, &target_x, &target_y) == 3) {
                 printf("Firing Neurogun at %d, %d!\n", target_x, target_y);
                 fireNeurogun(x,y,target_x-1,target_y-1,table,&z_killed);
             } else {
                 printf("Error: Invalid neurogun format. Use n X,Y (e.g., n 4,8)\n");
             }
         } 
         else if (weapon == 'b' || weapon == 'B') {
             if (sscanf(move, " %c %d,%d", &weapon, &target_x, &target_y) == 3) {
                 printf("Dropping Bomb at %d, %d!\n", target_x, target_y);
                 fireBombing(x,y,target_x-1,target_y-1,table,&z_killed);
             } else {
                 printf("Error: Invalid bomb format. Use b X,Y (e.g., b 5,5)\n");
             }
         }
         else if (weapon == 'p' || weapon == 'P') {
             if (sscanf(move, " %c %c%d", &weapon, &direction, &target_x) == 3) {
             	 firePlasmagun(x,y,target_x-1,direction,table,&z_killed);
                 printf("Firing Plasma gun from side '%c' at line %d!\n", direction, target_x);
             } else {
                 printf("Error: Invalid plasma format. Use p D L (e.g., p l 15)\n");
             }
         }
         else if (weapon == 'x' || weapon == 'X') {
             printf("Exiting game...\n");
             game_running = 0;
         }
         else {
             printf("Error: Unknown command.\n");
         }
         multiplier = (z_killed * (z_killed + 1)) / 2;
         score += multiplier * 10 * level;
         if (z_killed > 6) {
             printf("\n\nPERFECT!!! You just wiped a huge horde of zombies!!!\n");
             fflush(stdout);
        	#ifdef _WIN32
        	        Sleep(3000);
        	#else
        	        sleep(3);
        	#endif
         }
     
    }
    if (table != NULL) {
        cleanTable(table, x);
    }
    return 0;
}
