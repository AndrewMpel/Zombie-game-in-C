#ifndef WEAPONS_H
#define WEAPONS_H

void fireNeurogun(int max_x, int max_y, int target_x, int target_y, char** table,int* z_killed);

void fireBombing(int max_x, int max_y, int target_x, int target_y, char** table,int* z_killed);

void firePlasmagun(int max_x, int max_y, int target_x, char direction, char** table,int* z_killed);

#endif
