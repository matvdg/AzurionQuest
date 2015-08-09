#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

// librairies
#include <SDL/SDL.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL_image.h>

#define BLOCK_SIZE      50
#define NB_BLOCK_X      34
#define NB_BLOCK_Y      21

enum{
    VIDE, GREENBOX, BLUEBOX, REDBOX, METAL, TELEPORT, AZURIONPART, NOTHING, INCPAD, DECPAD, INCSPEED, DECSPEED, MAGNETBALL, DOUBLEBALL, FIREBALL, LASER, DEATH, NOAZURITE, LIFE, AZURITE2, AZURITE3, AZURITE4, AZURITE5, AZURITE6, AZURITE7, AZURITE8, AZURITE9
};

enum{
    TYPE, POWER,  AZURITE
};

void loadNumbers(SDL_Surface *numbers[10]){
    numbers[0] = IMG_Load("images/Numbers/0.png");
    numbers[1] = IMG_Load("images/Numbers/1.png");
    numbers[2] = IMG_Load("images/Numbers/2.png");
    numbers[3] = IMG_Load("images/Numbers/3.png");
    numbers[4] = IMG_Load("images/Numbers/4.png");
    numbers[5] = IMG_Load("images/Numbers/5.png");
    numbers[6] = IMG_Load("images/Numbers/6.png");
    numbers[7] = IMG_Load("images/Numbers/7.png");
    numbers[8] = IMG_Load("images/Numbers/8.png");
    numbers[9] = IMG_Load("images/Numbers/9.png");
   }

void loadSprites(SDL_Surface *sprites[27]){

    // BRICKS
    sprites[VIDE] = NULL; //0
    sprites[GREENBOX] = IMG_Load("images/Bricks/greenbox.png");//1
    sprites[BLUEBOX] = IMG_Load("images/Bricks/bluebox.png");//2
    sprites[REDBOX] = IMG_Load("images/Bricks/redbox.png");//3
    sprites[METAL] = IMG_Load("images/Bricks/metal.png");//4
    sprites[TELEPORT] = IMG_Load("images/Bricks/vortex.png");//5
    sprites[AZURIONPART] = IMG_Load("images/Bricks/azurionpart.png");//6

    // POWERS (BONUS & MALUS)
    sprites[NOTHING] = NULL;//7
    sprites[INCPAD] = IMG_Load("images/Powers/incpaddle.png");//8 BONUS
    sprites[DECPAD] = IMG_Load("images/Powers/decpaddle.png");//9 MALUS
    sprites[INCSPEED] = IMG_Load("images/Powers/incspeed.png");//10 MALUS
    sprites[DECSPEED] = IMG_Load("images/Powers/decspeed.png");//11 BONUS
    sprites[MAGNETBALL] = IMG_Load("images/Powers/magnetball.png");//12 BONUS
    sprites[DOUBLEBALL] = IMG_Load("images/Powers/doubleball.png");//13 BONUS
    sprites[FIREBALL] = IMG_Load("images/Powers/fireball.png");//14 BONUS
    sprites[LASER] = IMG_Load("images/Powers/laser.png");//15 BONUS
    sprites[DEATH] = IMG_Load("images/Powers/death.png");//16 MALUS

    // AZURITES (COINS)
    sprites[NOAZURITE] = NULL;//17
    sprites[LIFE] = IMG_Load("images/Powers/life.png");//18
    sprites[AZURITE2] = IMG_Load("images/Powers/azurite2.png");//19
    sprites[AZURITE3] = IMG_Load("images/Powers/azurite3.png");//20
    sprites[AZURITE4] = IMG_Load("images/Powers/azurite4.png");//21
    sprites[AZURITE5] = IMG_Load("images/Powers/azurite5.png");//22
    sprites[AZURITE6] = IMG_Load("images/Powers/azurite6.png");//23
    sprites[AZURITE7] = IMG_Load("images/Powers/azurite7.png");//24
    sprites[AZURITE8] = IMG_Load("images/Powers/azurite8.png");//25
    sprites[AZURITE9] = IMG_Load("images/Powers/azurite9.png");//26

}

void renderMap(int map[NB_BLOCK_Y][NB_BLOCK_X][3], SDL_Surface *screen, SDL_Surface *sprites[27]){

    int i = 0, j = 0;
    int blockSize = BLOCK_SIZE;

    SDL_Rect brickCoord;
    SDL_Rect powerCoord;
    SDL_Rect azuriteCoord;

    for (i = 0; i < NB_BLOCK_Y; i++){

        for (j = 0; j < NB_BLOCK_X; j++){

            switch(map[i][j][TYPE]){

                case 0 :
                    brickCoord.x = blockSize*j;
                    brickCoord.y = blockSize*i;
                    SDL_BlitSurface(sprites[VIDE], NULL, screen, &brickCoord);
                    break;

                case 1 :
                    brickCoord.x = blockSize*j;
                    brickCoord.y = blockSize*i;
                    SDL_BlitSurface(sprites[GREENBOX], NULL, screen, &brickCoord);
                    break;

                case 2 :
                    brickCoord.x = blockSize*j;
                    brickCoord.y = blockSize*i;
                    SDL_BlitSurface(sprites[BLUEBOX], NULL, screen, &brickCoord);
                    break;

                case 3 :
                    brickCoord.x = blockSize*j;
                    brickCoord.y = blockSize*i;
                    SDL_BlitSurface(sprites[REDBOX], NULL, screen, &brickCoord);
                    break;

                case 4 :
                    brickCoord.x = blockSize*j;
                    brickCoord.y = blockSize*i;
                    SDL_BlitSurface(sprites[METAL], NULL, screen, &brickCoord);
                    break;

                case 5 :
                    brickCoord.x = blockSize*j;
                    brickCoord.y = blockSize*i;
                    SDL_BlitSurface(sprites[TELEPORT], NULL, screen, &brickCoord);
                    break;

                case 6 :
                    brickCoord.x = blockSize*j;
                    brickCoord.y = blockSize*i;
                    SDL_BlitSurface(sprites[AZURIONPART], NULL, screen, &brickCoord);
                    break;

            }

            switch(map[i][j][POWER]){

                case 0 :
                    powerCoord.x = blockSize*j;
                    powerCoord.y = blockSize*i;
                    SDL_BlitSurface(sprites[NOTHING], NULL, screen, &powerCoord);
                    break;

                case 1 :
                    powerCoord.x = blockSize*j;
                    powerCoord.y = blockSize*i;
                    SDL_BlitSurface(sprites[INCPAD], NULL, screen, &powerCoord);
                    break;

                case 2 :
                    powerCoord.x = blockSize*j;
                    powerCoord.y = blockSize*i;
                    SDL_BlitSurface(sprites[DECPAD], NULL, screen, &powerCoord);
                    break;

                case 3 :
                    powerCoord.x = blockSize*j;
                    powerCoord.y = blockSize*i;
                    SDL_BlitSurface(sprites[INCSPEED], NULL, screen, &powerCoord);
                    break;

                case 4 :
                    powerCoord.x = blockSize*j;
                    powerCoord.y = blockSize*i;
                    SDL_BlitSurface(sprites[DECSPEED], NULL, screen, &powerCoord);
                    break;

                case 5 :
                    powerCoord.x = blockSize*j;
                    powerCoord.y = blockSize*i;
                    SDL_BlitSurface(sprites[MAGNETBALL], NULL, screen, &powerCoord);
                    break;

                case 6 :
                    powerCoord.x = blockSize*j;
                    powerCoord.y = blockSize*i;
                    SDL_BlitSurface(sprites[DOUBLEBALL], NULL, screen, &powerCoord);
                    break;

                case 7 :
                    powerCoord.x = blockSize*j;
                    powerCoord.y = blockSize*i;
                    SDL_BlitSurface(sprites[FIREBALL], NULL, screen, &powerCoord);
                    break;

                case 8 :
                    powerCoord.x = blockSize*j;
                    powerCoord.y = blockSize*i;
                    SDL_BlitSurface(sprites[LASER], NULL, screen, &powerCoord);
                    break;

                case 9 :
                    powerCoord.x = blockSize*j;
                    powerCoord.y = blockSize*i;
                    SDL_BlitSurface(sprites[DEATH], NULL, screen, &powerCoord);
                    break;

            }

            switch(map[i][j][AZURITE]){

                case 0 :
                    azuriteCoord.x = blockSize*j;
                    azuriteCoord.y = blockSize*i;
                    SDL_BlitSurface(sprites[NOAZURITE], NULL, screen, &azuriteCoord);
                    break;

                case 1 :
                    azuriteCoord.x = blockSize*j;
                    azuriteCoord.y = blockSize*i;
                    SDL_BlitSurface(sprites[LIFE], NULL, screen, &azuriteCoord);
                    break;

                case 2 :
                    azuriteCoord.x = blockSize*j;
                    azuriteCoord.y = blockSize*i;
                    SDL_BlitSurface(sprites[AZURITE2], NULL, screen, &azuriteCoord);
                    break;

                case 3 :
                    azuriteCoord.x = blockSize*j;
                    azuriteCoord.y = blockSize*i;
                    SDL_BlitSurface(sprites[AZURITE3], NULL, screen, &azuriteCoord);
                    break;

                case 4 :
                    azuriteCoord.x = blockSize*j;
                    azuriteCoord.y = blockSize*i;
                    SDL_BlitSurface(sprites[AZURITE4], NULL, screen, &azuriteCoord);
                    break;

                case 5 :
                    azuriteCoord.x = blockSize*j;
                    azuriteCoord.y = blockSize*i;
                    SDL_BlitSurface(sprites[AZURITE5], NULL, screen, &azuriteCoord);
                    break;

                case 6 :
                    azuriteCoord.x = blockSize*j;
                    azuriteCoord.y = blockSize*i;
                    SDL_BlitSurface(sprites[AZURITE6], NULL, screen, &azuriteCoord);
                    break;

                case 7 :
                    azuriteCoord.x = blockSize*j;
                    azuriteCoord.y = blockSize*i;
                    SDL_BlitSurface(sprites[AZURITE7], NULL, screen, &azuriteCoord);
                    break;

                case 8 :
                    azuriteCoord.x = blockSize*j;
                    azuriteCoord.y = blockSize*i;
                    SDL_BlitSurface(sprites[AZURITE8], NULL, screen, &azuriteCoord);
                    break;

                case 9 :
                    azuriteCoord.x = blockSize*j;
                    azuriteCoord.y = blockSize*i;
                    SDL_BlitSurface(sprites[AZURITE9], NULL, screen, &azuriteCoord);
                    break;

            }

        }

    }

}

void save(int map[NB_BLOCK_Y][NB_BLOCK_X][3], char world[10], char level[10], SDL_Surface *screen){

    char mapName[100] = {NULL};
    strcat(mapName, "maps/map_w");
    strcat(mapName, world);
    strcat(mapName, "_l");
    strcat(mapName, level);
    strcat(mapName, ".txt");



    FILE *file = NULL;
    file = fopen(mapName, "w+");

    if(file != NULL){

        int i = 0, j = 0;

        for (i = 0; i < NB_BLOCK_Y; i++){

            for (j = 0; j < NB_BLOCK_X; j++){

                fprintf(file, "%d ", map[i][j][TYPE]);
                fprintf(file, "%d ", map[i][j][POWER]);
                fprintf(file, "%d ", map[i][j][AZURITE]);

            }

            fputc('\n', file);

        }

        fclose(file);

    }else{
        fprintf(stderr, "Failed open.");
    }

}

int main ( int argc, char** argv ){

    // initialize SDL video
    if ( SDL_Init(  SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Impossible d'ouvrir la SDL : %s\n", SDL_GetError() );
        return 1;
    }


    // make sure SDL cleans up before exit
    atexit(SDL_Quit);


    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(1680, 1050, 32, SDL_HWSURFACE | SDL_FULLSCREEN | SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Impossible d'ouvrir le programme en plein ecran : %s\n", SDL_GetError());
        return 1;
    }



    // preload surfaces

    //background
    SDL_Surface *backgroundImg[5];
    SDL_Rect backgroundCoord;
    backgroundCoord.x = 0;
    backgroundCoord.y = 0;
    backgroundImg[0] = IMG_Load("images/Backgrounds/bricks.jpg");
    backgroundImg[1] = IMG_Load("images/Backgrounds/powers.jpg");
    backgroundImg[2] = IMG_Load("images/Backgrounds/azurites.jpg");
    backgroundImg[3] = IMG_Load("images/Backgrounds/backup.jpg");
    backgroundImg[4] = IMG_Load("images/Backgrounds/saved.jpg");

    //legend
    SDL_Surface *legend;
    SDL_Rect legendCoord;
    legendCoord.x = 100;
    legendCoord.y = screen->h - 50;
    legend = IMG_Load("images/Bricks/legend.png");


    //all the items
    SDL_Surface *objects[27] = {NULL};
    loadSprites(objects);
    SDL_Surface *numbers[10] = {NULL};
    loadNumbers(numbers);
    SDL_Rect numbersCoord;
    SDL_Surface *currentObject = objects[VIDE];
    SDL_Rect coordObjectLegend;
    coordObjectLegend.x = screen->w - 150;
    coordObjectLegend.y = screen->h - 50;

    SDL_WarpMouse(screen->w/2-106, screen->h/2);



    //   loop for creating types of bricks
    int map[NB_BLOCK_Y][NB_BLOCK_X][3] = {NULL};
    int typeCurrentObject = 0;
    bool done = false;
    while (!done)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                // exit if the window is closed
                case SDL_QUIT:
                    done = true;
                    break;

                    // check for keyboard
                case SDL_KEYDOWN:
                    // exit if ESCAPE is pressed
                    switch(event.key.keysym.sym){
                        case SDLK_ESCAPE :
                            done = true;
                            break;
                        case SDLK_KP0 :
                            currentObject = objects[VIDE];
                            typeCurrentObject = 0;
                            break;
                        case SDLK_KP1 :
                            currentObject = objects[GREENBOX];
                            typeCurrentObject = 1;
                            break;
                        case SDLK_KP2 :
                            currentObject = objects[BLUEBOX];
                            typeCurrentObject = 2;
                            break;
                        case SDLK_KP3 :
                            currentObject = objects[REDBOX];
                            typeCurrentObject = 3;
                            break;
                        case SDLK_KP4 :
                            currentObject = objects[METAL];
                            typeCurrentObject = 4;
                            break;
                        case SDLK_KP5 :
                            currentObject = objects[TELEPORT];
                            typeCurrentObject = 5;
                            break;
                        case SDLK_KP6 :
                            currentObject = objects[AZURIONPART];
                            typeCurrentObject = 6;
                            break;
                        case SDLK_0 :
                            currentObject = objects[VIDE];
                            typeCurrentObject = 0;
                            break;
                        case SDLK_1 :
                            currentObject = objects[GREENBOX];
                            typeCurrentObject = 1;
                            break;
                        case SDLK_2 :
                            currentObject = objects[BLUEBOX];
                            typeCurrentObject = 2;
                            break;
                        case SDLK_3 :
                            currentObject = objects[REDBOX];
                            typeCurrentObject = 3;
                            break;
                        case SDLK_4 :
                            currentObject = objects[METAL];
                            typeCurrentObject = 4;
                            break;
                        case SDLK_5 :
                            currentObject = objects[TELEPORT];
                            typeCurrentObject = 5;
                            break;
                        case SDLK_6 :
                            currentObject = objects[AZURIONPART];
                            typeCurrentObject = 6;
                            break;
                        default:
                            continue;
                            break;

                    }
                    break;



                case SDL_MOUSEBUTTONDOWN :

                    if(event.button.button == SDL_BUTTON_LEFT)
                        map[event.button.y / BLOCK_SIZE][event.button.x / BLOCK_SIZE][TYPE] = typeCurrentObject;
                    else if(event.button.button == SDL_BUTTON_RIGHT)
                        map[event.button.y / BLOCK_SIZE][event.button.x / BLOCK_SIZE][TYPE] = 0;

                    break;

                default:
                        continue;
                    break;


            } // end switch

        }



        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        // DRAWING STARTS HERE

        // draw backgroundImage
        SDL_BlitSurface(backgroundImg[0], NULL, screen, &backgroundCoord);
        SDL_BlitSurface(legend, NULL, screen, &legendCoord);
        SDL_BlitSurface(currentObject, NULL, screen, &coordObjectLegend);
        renderMap(map, screen, objects);


        // DRAWING ENDS HERE

        // finally, update the screen
        SDL_Flip(screen);

    } // end types loop


    SDL_WarpMouse(screen->w/2-106, screen->h/2);
    currentObject = objects[NOTHING];
    typeCurrentObject = 0;
    legend = IMG_Load("images/Powers/legendpower.png");

    //   loop for creating types of powers (bonus&malus)
    bool backPower = false;
    while(!backPower){

        SDL_Event event2;
        while(SDL_PollEvent(&event2))
        {
            switch (event2.type)
            {
                // exit if the window is closed
                case SDL_QUIT:
                    backPower = true;
                    break;

                    // check for keyboard
                case SDL_KEYDOWN:
                    // exit if ESCAPE is pressed
                    switch(event2.key.keysym.sym){
                        case SDLK_ESCAPE :
                            backPower = true;
                            break;
                        case SDLK_KP0 :
                            currentObject = objects[NOTHING];
                            typeCurrentObject = 0;
                            break;
                        case SDLK_KP1 :
                            currentObject = objects[INCPAD];
                            typeCurrentObject = 1;
                            break;
                        case SDLK_KP2 :
                            currentObject = objects[DECPAD];
                            typeCurrentObject = 2;
                            break;
                        case SDLK_KP3 :
                            currentObject = objects[INCSPEED];
                            typeCurrentObject = 3;
                            break;
                        case SDLK_KP4 :
                            currentObject = objects[DECSPEED];
                            typeCurrentObject = 4;
                            break;
                        case SDLK_KP5 :
                            currentObject = objects[MAGNETBALL];
                            typeCurrentObject = 5;
                            break;
                        case SDLK_KP6 :
                            currentObject = objects[DOUBLEBALL];
                            typeCurrentObject = 6;
                            break;
                        case SDLK_KP7 :
                            currentObject = objects[FIREBALL];
                            typeCurrentObject = 7;
                            break;
                        case SDLK_KP8 :
                            currentObject = objects[LASER];
                            typeCurrentObject = 8;
                            break;
                        case SDLK_KP9 :
                            currentObject = objects[DEATH];
                            typeCurrentObject = 9;
                            break;
                        case SDLK_0 :
                            currentObject = objects[NOTHING];
                            typeCurrentObject = 0;
                            break;
                        case SDLK_1 :
                            currentObject = objects[INCPAD];
                            typeCurrentObject = 1;
                            break;
                        case SDLK_2 :
                            currentObject = objects[DECPAD];
                            typeCurrentObject = 2;
                            break;
                        case SDLK_3 :
                            currentObject = objects[INCSPEED];
                            typeCurrentObject = 3;
                            break;
                        case SDLK_4 :
                            currentObject = objects[DECSPEED];
                            typeCurrentObject = 4;
                            break;
                        case SDLK_5 :
                            currentObject = objects[MAGNETBALL];
                            typeCurrentObject = 5;
                            break;
                        case SDLK_6 :
                            currentObject = objects[DOUBLEBALL];
                            typeCurrentObject = 6;
                            break;
                        case SDLK_7 :
                            currentObject = objects[FIREBALL];
                            typeCurrentObject = 7;
                            break;
                        case SDLK_8 :
                            currentObject = objects[LASER];
                            typeCurrentObject = 8;
                            break;
                        case SDLK_9 :
                            currentObject = objects[DEATH];
                            typeCurrentObject = 9;
                            break;
                        default:
                            continue;
                            break;
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN :

                    if(event2.button.button == SDL_BUTTON_LEFT)
                        map[event2.button.y / BLOCK_SIZE][event2.button.x / BLOCK_SIZE][POWER] = typeCurrentObject;
                    else if(event2.button.button == SDL_BUTTON_RIGHT)
                        map[event2.button.y / BLOCK_SIZE][event2.button.x / BLOCK_SIZE][POWER] = 0;

                    break;

                default:
                    continue;
                    break;
            }
        }


        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        // DRAWING STARTS HERE

        // draw backgroundImage
        SDL_BlitSurface(backgroundImg[1], NULL, screen, &backgroundCoord);
        SDL_BlitSurface(legend, NULL, screen, &legendCoord);
        SDL_BlitSurface(currentObject, NULL, screen, &coordObjectLegend);
        renderMap(map, screen, objects);


        // DRAWING ENDS HERE

        // finally, update the screen
        SDL_Flip(screen);

    }



    SDL_WarpMouse(screen->w/2-106, screen->h/2);
    currentObject = objects[NOAZURITE];
    typeCurrentObject = 0;
    legend = IMG_Load("images/Powers/legendazurite.png");

    //   loop for creating azurites
    bool backAzurite = false;
    while(!backAzurite){

        SDL_Event event3;
        while(SDL_PollEvent(&event3))
        {
            switch (event3.type)
            {
                // exit if the window is closed
                case SDL_QUIT:
                    backAzurite = true;
                    break;

                    // check for keyboard
                case SDL_KEYDOWN:
                    // exit if ESCAPE is pressed
                    switch(event3.key.keysym.sym){
                        case SDLK_ESCAPE :
                            backAzurite = true;
                            break;
                        case SDLK_KP0 :
                            currentObject = objects[NOAZURITE];
                            typeCurrentObject = 0;
                            break;
                        case SDLK_KP1 :
                            currentObject = objects[LIFE];
                            typeCurrentObject = 1;
                            break;
                        case SDLK_KP2 :
                            currentObject = objects[AZURITE2];
                            typeCurrentObject = 2;
                            break;
                        case SDLK_KP3 :
                            currentObject = objects[AZURITE3];
                            typeCurrentObject = 3;
                            break;
                        case SDLK_KP4 :
                            currentObject = objects[AZURITE4];
                            typeCurrentObject = 4;
                            break;
                        case SDLK_KP5 :
                            currentObject = objects[AZURITE5];
                            typeCurrentObject = 5;
                            break;
                        case SDLK_KP6 :
                            currentObject = objects[AZURITE6];
                            typeCurrentObject = 6;
                            break;
                        case SDLK_KP7 :
                            currentObject = objects[AZURITE7];
                            typeCurrentObject = 7;
                            break;
                        case SDLK_KP8 :
                            currentObject = objects[AZURITE8];
                            typeCurrentObject = 8;
                            break;
                        case SDLK_KP9 :
                            currentObject = objects[AZURITE9];
                            typeCurrentObject = 9 ;
                            break;
                         case SDLK_0 :
                            currentObject = objects[NOAZURITE];
                            typeCurrentObject = 0;
                            break;
                        case SDLK_1 :
                            currentObject = objects[LIFE];
                            typeCurrentObject = 1;
                            break;
                        case SDLK_2 :
                            currentObject = objects[AZURITE2];
                            typeCurrentObject = 2;
                            break;
                        case SDLK_3 :
                            currentObject = objects[AZURITE3];
                            typeCurrentObject = 3;
                            break;
                        case SDLK_4 :
                            currentObject = objects[AZURITE4];
                            typeCurrentObject = 4;
                            break;
                        case SDLK_5 :
                            currentObject = objects[AZURITE5];
                            typeCurrentObject = 5;
                            break;
                        case SDLK_6 :
                            currentObject = objects[AZURITE6];
                            typeCurrentObject = 6;
                            break;
                        case SDLK_7 :
                            currentObject = objects[AZURITE7];
                            typeCurrentObject = 7;
                            break;
                        case SDLK_8 :
                            currentObject = objects[AZURITE8];
                            typeCurrentObject = 8;
                            break;
                        case SDLK_9 :
                            currentObject = objects[AZURITE9];
                            typeCurrentObject = 9 ;
                            break;
                        default:
                            continue;
                            break;
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN :

                    if(event3.button.button == SDL_BUTTON_LEFT)
                        map[event3.button.y / BLOCK_SIZE][event3.button.x / BLOCK_SIZE][AZURITE] = typeCurrentObject;
                    else if(event3.button.button == SDL_BUTTON_RIGHT)
                        map[event3.button.y / BLOCK_SIZE][event3.button.x / BLOCK_SIZE][AZURITE] = 0;

                    break;
                default:
                    continue;
                    break;
            }
        }


        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        // DRAWING STARTS HERE

        // draw backgroundImage
        SDL_BlitSurface(backgroundImg[2], NULL, screen, &backgroundCoord);
        SDL_BlitSurface(legend, NULL, screen, &legendCoord);
        SDL_BlitSurface(currentObject, NULL, screen, &coordObjectLegend);
        renderMap(map, screen, objects);


        // DRAWING ENDS HERE

        // finally, update the screen
        SDL_Flip(screen);

    }



      //   loop for backing up
    SDL_WarpMouse(screen->w/2-106, screen->h/2);
    bool backup = false;
    int worldEntered = 0, levelEntered = 0;
    char world[10] = {NULL}, level[10] = {NULL};
    while (!backup)
    {
        SDL_Event event4;
        while(SDL_PollEvent(&event4))
        {
            switch (event4.type)
            {
                // exit if the window is closed
                case SDL_QUIT:
                    done = true;
                    break;

                    // check for keyboard
                case SDL_KEYDOWN:
                    // exit if ESCAPE is pressed
                    switch(event4.key.keysym.sym){
                        case SDLK_ESCAPE :
                            backup = true;
                            break;
                        case SDLK_KP1 :
                            if(worldEntered == 0){
                                worldEntered = 1;
                            }else{
                                levelEntered = 1;
                            }
                            break;
                        case SDLK_KP2 :
                            if(worldEntered == 0){
                                worldEntered = 2;
                            }else{
                                levelEntered = 2;
                            }
                            break;
                        case SDLK_KP3 :
                            if(worldEntered == 0){
                                worldEntered = 3;
                            }else{
                                levelEntered = 3;
                            }
                            break;
                        case SDLK_KP4 :
                            if(worldEntered == 0){
                                worldEntered = 4;
                            }else{
                                levelEntered = 4;
                            }
                            break;
                        case SDLK_KP5 :
                            if(worldEntered == 0){
                                worldEntered = 5;
                            }else{
                                levelEntered = 5;
                            }
                            break;
                        case SDLK_KP6 :
                            if(worldEntered == 0){
                                worldEntered = 6;
                            }else{
                                levelEntered = 6;
                            }
                            break;
                        case SDLK_KP7 :
                            if(worldEntered == 0){
                                worldEntered = 7;
                            }else{
                                levelEntered = 7;
                            }
                            break;
                        case SDLK_KP8 :
                            if(worldEntered == 0){
                                worldEntered = 8;
                            }else{
                                levelEntered = 8;
                            }
                            break;
                        case SDLK_KP9 :
                            if(worldEntered == 0){
                                worldEntered = 9;
                            }else{
                                levelEntered = 9;
                            }
                            break;
                        case SDLK_1 :
                            if(worldEntered == 0){
                                worldEntered = 1;
                            }else{
                                levelEntered = 1;
                            }
                            break;
                        case SDLK_2 :
                            if(worldEntered == 0){
                                worldEntered = 2;
                            }else{
                                levelEntered = 2;
                            }
                            break;
                        case SDLK_3 :
                            if(worldEntered == 0){
                                worldEntered = 3;
                            }else{
                                levelEntered = 3;
                            }
                            break;
                        case SDLK_4 :
                            if(worldEntered == 0){
                                worldEntered = 4;
                            }else{
                                levelEntered = 4;
                            }
                            break;
                        case SDLK_5 :
                            if(worldEntered == 0){
                                worldEntered = 5;
                            }else{
                                levelEntered = 5;
                            }
                            break;
                        case SDLK_6 :
                            if(worldEntered == 0){
                                worldEntered = 6;
                            }else{
                                levelEntered = 6;
                            }
                            break;
                        case SDLK_7 :
                            if(worldEntered == 0){
                                worldEntered = 7;
                            }else{
                                levelEntered = 7;
                            }
                            break;
                        case SDLK_8 :
                            if(worldEntered == 0){
                                worldEntered = 8;
                            }else{
                                levelEntered = 8;
                            }
                            break;
                        case SDLK_9 :
                            if(worldEntered == 0){
                                worldEntered = 9;
                            }else{
                                levelEntered = 9;
                            }
                            break;
                        default:
                            continue;
                        break;

                    }
                    break;
                    default:
                        continue;
                    break;


            } // end switch

        }




        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        // DRAWING STARTS HERE

        // draw backgroundImage
        SDL_BlitSurface(backgroundImg[3], NULL, screen, &backgroundCoord);


        if(worldEntered > 0){
            sprintf(world, "%d", worldEntered);
            numbersCoord.x = 730;
            numbersCoord.y = 255;
            SDL_BlitSurface(numbers[worldEntered], NULL, screen, &numbersCoord);
        }
        if(levelEntered > 0){
            sprintf(level, "%d", levelEntered);
            SDL_BlitSurface(backgroundImg[4], NULL, screen, &backgroundCoord);
            numbersCoord.x = 730;
            numbersCoord.y = 255;
            SDL_BlitSurface(numbers[worldEntered], NULL, screen, &numbersCoord);
            numbersCoord.x = 730;
            numbersCoord.y = 405;
            SDL_BlitSurface(numbers[levelEntered], NULL, screen, &numbersCoord);
            save(map, world, level, screen);

            backup = true;
        }


        // DRAWING ENDS HERE

        // finally, update the screen
        SDL_Flip(screen);

        if(backup == true && levelEntered > 0)
            SDL_Delay(4000);

    } // end backup loop



    // free loaded
    SDL_FreeSurface(*backgroundImg);
    SDL_FreeSurface(*numbers);
    SDL_FreeSurface(*objects);
    SDL_FreeSurface(legend);
    SDL_FreeSurface(screen);
    SDL_FreeSurface(currentObject);
    SDL_Quit();

    return EXIT_SUCCESS;
}

