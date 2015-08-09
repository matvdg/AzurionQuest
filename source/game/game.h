#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "../init/init.h"
#include "../songs/songs.h"
#include "../load/load.h"
#include "../draw/draw.h"
#include "../check/check.h"

void play(SDL_Surface *screen, int *world, int *level, int *azurites, int* difficulty, bool powersShop[8]);

void launchBonus(int powers[NB_BLOCK_X*NB_BLOCK_Y][4], int *lives, int *speed, int *azurites, int componentsPaddle[6], float balls[16][11]);

void launchBonusShop(bool powersShop[8], int *lives, int *speed, int *azurites, int componentsPaddle[6], float balls[16][11], int resetCounter);

#endif // GAME_H_INCLUDED
