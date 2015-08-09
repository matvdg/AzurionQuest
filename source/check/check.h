#ifndef CHECK_H_INCLUDED
#define CHECK_H_INCLUDED

#include "../init/init.h"
#include "../songs/songs.h"

void checkButton(int mouseX,int mouseY,int position,int buttonAction[4]);

void checkButtonGarage(int mouseX,int mouseY,int position,int buttonActionGarage[11]);

void checkReset(SDL_Surface *screen, int* azurites, int *world, int *level,int *worldReplay, int *levelReplay, int *difficulty, FMOD_SYSTEM *system, FMOD_SOUND *music);

void checkCollision(int map[NB_BLOCK_Y][NB_BLOCK_X][4],  SDL_Surface *screen, float componentsBall[11], int componentsPaddle[6], int timeInit, int* lives, int* gameover, FMOD_SYSTEM *systemNoise, FMOD_SOUND *noises[13], int* resetCounter, int* impactPaddle, SDL_Surface *cloud, SDL_Surface *shield, int* won);

bool checkBorder(int map[NB_BLOCK_Y][NB_BLOCK_X][4], SDL_Surface *screen, float componentsBall[11], int* lives, int* gameover, FMOD_SYSTEM *systemNoise, FMOD_SOUND *noises[13], int* resetCounter);

bool checkBrick_V41(int map[NB_BLOCK_Y][NB_BLOCK_X][4], SDL_Surface *screen, float componentsBall[11], FMOD_SYSTEM *systemNoise, FMOD_SOUND *noises[13], int* resetCounter, SDL_Surface *cloud, SDL_Surface *shield, int *won);

bool checkBrick_FireMode_V41(int map[NB_BLOCK_Y][NB_BLOCK_X][4], SDL_Surface *screen, float componentsBall[11], FMOD_SYSTEM *systemNoise, FMOD_SOUND *noises[13], int* resetCounter, SDL_Surface *cloud, SDL_Surface *shield, int *won);

void checkPaddle_V2(float componentsBall[11], int componentsPaddle[6], int timeInit, FMOD_SYSTEM *systemNoise, FMOD_SOUND *noises[13], int* impactPaddle);

void checkEndGame(int map[NB_BLOCK_Y][NB_BLOCK_X][4], int *won, FMOD_SYSTEM *systemNoise, FMOD_SOUND *noises[13]);

void checkBonus(SDL_Surface *screen, int powers[NB_BLOCK_X*NB_BLOCK_Y][4], int componentsPaddle[6], FMOD_SYSTEM *systemNoise, FMOD_SOUND *noises[13]);

void checkRockets(int map[NB_BLOCK_Y][NB_BLOCK_X][4], SDL_Surface *screen, int rockets[3], SDL_Surface *explosion, int *won, FMOD_SYSTEM *systemNoise, FMOD_SOUND *noises[13]);

#endif
