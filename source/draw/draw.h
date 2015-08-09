#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#include "../init/init.h"
#include "../songs/songs.h"
#include "../check/check.h"

void renderMap(int map[NB_BLOCK_Y][NB_BLOCK_X][4], SDL_Surface *screen, SDL_Surface *sprites[31],int loopCounter);

void drawBackground(SDL_Surface *screen, SDL_Surface *numbers[10], int world, int lvl, int lives, int azurites, SDL_Surface *balls[40], int loopCounter, int stateBall, float speed, SDL_Surface *speedImg[4], SDL_Surface *bonusShop[9], bool powersShop[8], bool pause, SDL_Surface *sprites[31], FMOD_SYSTEM *systemNoise, FMOD_SOUND *noises[13]);

void drawBall(SDL_Surface *screen, int map[NB_BLOCK_Y][NB_BLOCK_X][4], SDL_Surface *balls[40], SDL_Surface *ballsFire[27], float componentsBall[11], int componentsPaddle[6], int *offSetPaddle, int timeInit, int* lives, int* gameover, FMOD_SYSTEM *systemNoise, FMOD_SOUND *noises[13], int* resetCounter, int* impactPaddle, int loopCounter, SDL_Surface *cloud, SDL_Surface *shield, int *won);

void drawPaddle(int map[NB_BLOCK_Y][NB_BLOCK_X][4], SDL_Surface *screen, int componentsPaddle[6], SDL_Surface *paddle, int rockets[300][3], SDL_Surface *rocket, SDL_Surface *explosion, int *impactPaddle, FMOD_SYSTEM *systemNoise, FMOD_SOUND *noises[13], int* won);

void drawBonus(SDL_Surface *screen, int componentsPaddle[6], float componentsBall[11], int powers[NB_BLOCK_X*NB_BLOCK_Y][4], SDL_Surface *bonus[19], int activeBalls, FMOD_SYSTEM *systemNoise, FMOD_SOUND *noises[13]);

void drawRockets(int map[NB_BLOCK_Y][NB_BLOCK_X][4], SDL_Surface *screen, int rockets[300][3], SDL_Surface *rocket, SDL_Surface *explosion, FMOD_SYSTEM *systemNoise, FMOD_SOUND *noises[13], int* won);

#endif
