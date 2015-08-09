#ifndef LOAD_H_INCLUDED
#define LOAD_H_INCLUDED

#include "../init/init.h"
#include "../songs/songs.h"
#include "../game/game.h"

void loadBackgrounds(SDL_Surface *backgroundImg[9]);

void loadIntro(SDL_Surface *screen, FMOD_SYSTEM *system, FMOD_SOUND *music);

void loadStory(SDL_Surface *screen, FMOD_SYSTEM *system, FMOD_SOUND *music);

void loadBonus(SDL_Surface *bonus[19]);

void loadButtons(SDL_Surface *buttons[10]);

void loadButtonsGarage(SDL_Surface *buttonsGarage[23]);

void loadGarage(SDL_Surface *screen, int *menu, bool *done, SDL_Surface *numbers[10], int *world, int *level, int *difficulty, int *azurites, FMOD_SYSTEM *system, FMOD_SOUND *music, bool powersShop[8]);

void loadGame(SDL_Surface *screen, bool powersShop[8]);

void loadBackUp(int *world, int *level, int *azurites, int* difficulty);

void saveBackUp(int world, int level, int azurites, int difficulty);

void loadBalls(SDL_Surface *balls[40]);

void loadBallsFire(SDL_Surface *ballsFire[27]);

void loadSprites(SDL_Surface *sprites[31], SDL_Surface *speedImg[4], SDL_Surface *bonusShop[9], int world);

void loadEnd(SDL_Surface *screen);

void loadMap(int map[NB_BLOCK_Y][NB_BLOCK_X][4], int powers[18][4], int world, int lvl);

void loadNumbers(SDL_Surface *numbers[10]);

SDL_Surface* loadImageOptimised(const char* spritePath);

#endif // LOAD_H_INCLUDED
