#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include "../glsdl.h"
#include <SDL/SDL_image.h>
#include <fmodex/fmod.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include <time.h>

#define BLOCK_SIZE      50
#define NB_BLOCK_X      34 //1700px
#define NB_BLOCK_Y      21 //1050px
#define PI 3.14159265
#define RADIUS 20


enum{ //buttons
    PLAY, GARAGE, QUIT, MUTE, PLAYINVERT, GARAGEINVERT, QUITINVERT, MUTEINVERT, SWITCHON, SWITCHOFF
};

enum{ //buttons GarageBay
    LEFT, RIGHT, HOME, ESC, RESET, LEFTWORLD, RIGHTWORLD, LEFTLEVEL, RIGHTLEVEL, REPLAY, PLAYINTRO, LEFTINVERT, RIGHTINVERT, HOMEINVERT, ESCINVERT, RESETINVERT, REPLAYINVERT, LEFTWORLDINVERT, RIGHTWORLDINVERT, LEFTLEVELINVERT, RIGHTLEVELINVERT,PLAYINTROINVERT, BOUGHT
};
enum{ //state of buttons
    NONE, PRESSED, RELEASED, SWITCHED
};

enum{ //for sprites
    VIDE, GREENBOX, BLUEBOX, REDBOX, METAL, TELEPORT, AZURIONPART, V1, V2, V3, V4, V5, V6, V7, V8, V9, CLOUD, BACKGROUND, SMALLPADDLE, MEDIUMPADDLE, LARGEPADDLE, GAMEOVER, WON, EXPLOSION, INTRO, CONCLUSION, PAUSE, P1, P2, P3, GO
};

enum { // for speed bar
    SPEEDBAR, SPEEDBARINVERT, SPEEDBARMIN, SPEEDBARMAX
};

enum{ //for bonus
    NOBONUS, INCPAD, DECPAD, INCSPEED, DECSPEED, MAGNETBALL, DOUBLEBALL, FIREBALL, LASER, DEATH, LIFE, AZURITE2, AZURITE3, AZURITE4, AZURITE5, AZURITE6, AZURITE7, AZURITE8, AZURITE9
};

enum{ //for bonusShop
    MAGNET, MAGNETINF, HEART, PADDLEINC, CLONEBALL, CLONEBALLINF, SPEEDMIN, REDBALL, BONUSSHOP
};

enum{ //for map
    TYPE, POWER, AZURITE
};

enum{ //for componentsPaddle
    X, Y, HALFSIZE, MODE, WIDTH, ROCKET
};

enum{ //mode of paddle
    NORMAL, WAITINGSTUCK
};

enum{ //for componentsBall
    BALLX, BALLY, DIRX, DIRY, SPEED, ANGLE, STATE, LAST_IMPACT_TIME, XHIT, YHIT, RANK
};

enum{ //rank of balls
    MASTER, CLONE, FIREBALLSTATE
};

enum{ //state of balls
    INACTIVE, DEADSTATE, ALIVESTATE, STUCKSTATE, VORTEXSTATE
};

enum{ //for collisions
    BL, BR // B = Bottom, L = Left, R = Right
};

enum{ //for collisions
    TL, TR // T = Top, L = Left, R = Right
};

enum{ //noises
    BOUNCE, METALBOUNCE, PADDLEBOUNCE, DIENOISE, GAMEOVERNOISE, LASERNOISE, VORTEXNOISE, VICTORYNOISE, READYNOISE, GEMSTONENOISE, BONUSNOISE, HEARTBEAT, BUZZ
};

enum { //state of bonus
    OFF, FALLING, ON
};

#endif
