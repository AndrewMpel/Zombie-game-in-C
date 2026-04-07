#include "weapons.h"
#include <stdio.h>

void neurogunSpread(int max_x, int max_y, int current_x, int current_y, char targetType, char** table) {
    if (current_x < 0 || current_x >= max_x || current_y < 0 || current_y >= max_y) return; 
    
    if (table[current_x][current_y] != targetType) return;

    table[current_x][current_y] = '.';

    neurogunSpread(max_x, max_y, current_x - 1, current_y, targetType, table); // UP
    neurogunSpread(max_x, max_y, current_x + 1, current_y, targetType, table); // DOWN
    neurogunSpread(max_x, max_y, current_x, current_y - 1, targetType, table); // LEFT
    neurogunSpread(max_x, max_y, current_x, current_y + 1, targetType, table); // RIGHT
}

void fireNeurogun(int max_x, int max_y, int target_x, int target_y, char** table) {
    if (target_x < 0 || target_x >= max_x || target_y < 0 || target_y >= max_y) {
        printf("Error: Coordinates are out of bounds!\n");
        return;
    }

    char targetType = table[target_x][target_y];

    if (targetType == '.' || targetType == '#') {
        printf("Error: You can only fire at a zombie!\n");
        return;
    }

    int has_friends = 0;
    if(target_x > 0 && table[target_x - 1][target_y] == targetType) has_friends = 1;
    if (target_x < max_x - 1 && table[target_x + 1][target_y] == targetType) has_friends = 1;
    if(target_y > 0 && table[target_x][target_y - 1] == targetType) has_friends = 1;
    if (target_y < max_y - 1 && table[target_x][target_y + 1] == targetType) has_friends = 1;

    if (has_friends == 0) {
        printf("Error: Waste of resources You cannot shoot a lone zombie.\n");
        return; 
    }

    neurogunSpread(max_x, max_y, target_x, target_y, targetType, table);
}

void fireBombing(int max_x, int max_y, int target_x, int target_y, char** table){
    if(target_x < 0 || target_x >= max_x || target_y < 0 || target_y >= max_y) {
        perror("out of bounds\n");
        return;
    }
    for(int i = target_x - 1; i <= target_x + 1; i++) {
        for(int j = target_y - 1; j <= target_y + 1; j++) {
            if (i >= 0 && i < max_x && j >= 0 && j < max_y) {
                if (table[i][j] != '#') {
                    table[i][j] = '.';
                }
            }
        }
    }
    printf("Bombing Successful\n");
}
