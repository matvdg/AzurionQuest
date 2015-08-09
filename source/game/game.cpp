#include "../game/game.h"


void play(SDL_Surface *screen, int *world, int *level, int *azurites, int* difficulty, bool powersShop[8]){

    //you can modify these vars :
    int lives = 3;
    int speed = 14 + *world; //set the game's speed ! (here 15 to 21)
    int speedTimer = SDL_GetTicks();

    //don't modify these vars !
    int timeInit = 0;
    int gameover = 0;
    int won = 0;
    int resetCounter = 0;
    int impactPaddle = 0;
    int loopCounter = 0;
    int activeBalls = 0;
    bool pause = false;
    int map[NB_BLOCK_Y][NB_BLOCK_X][4] = {NULL};

    // LOOP VARS
    int i;
    int j;

    bool continuer = true;

    //////////////////////////INIT VARS//////////////////////////////////////////

    // for awesome noises !
    FMOD_SYSTEM *systemNoise = NULL;
    FMOD_SOUND *noises[13] = {NULL};
    FMOD_System_Create(&systemNoise);
    FMOD_System_Init(systemNoise, 32, FMOD_INIT_NORMAL, NULL);
    initNoises(systemNoise,noises); // init sounds

    /* PADDLE VAR */
    int componentsPaddle[6] = {NULL};
    componentsPaddle[HALFSIZE] = 75;
    componentsPaddle[X] = screen->w/2-componentsPaddle[HALFSIZE];
    componentsPaddle[Y] = screen->h-100;
    componentsPaddle[WIDTH] = MEDIUMPADDLE;

    /* BALL VAR */
    /*BALLX, BALLY, DIRX, DIRY, SPEED, ANGLE, STATE, LAST_IMPACT_TIME, XHIT, YHIT*/
    float componentsBall[16][11] = {screen->w/2-RADIUS, screen->h-180, 1, -1, speed, 45, INACTIVE, 0, -1, -1, CLONE};
    componentsBall[0][STATE] = STUCKSTATE;
    componentsBall[0][RANK] = MASTER;
    int offSetPaddle = NULL;

    /* BONUS VAR */
    int powers[NB_BLOCK_X*NB_BLOCK_Y][4] = {{0, 0, 0, OFF}};
    int rockets[300][3] = {0, 0, OFF}, rocketIndex = 0;


    /* PRELOAD IMAGES */
    SDL_Surface *sprites[31] = {NULL};
    SDL_Surface *speedImg[4] = {NULL};
    SDL_Surface *bonusShop[9] = {NULL};
    loadSprites(sprites, speedImg, bonusShop, *world);

    SDL_Surface *bonus[19] = {NULL};
    loadBonus(bonus);

    SDL_Surface *numbers[10] = {NULL};
    loadNumbers(numbers);

    SDL_Surface *balls[40] = {NULL};
    loadBalls(balls);

    SDL_Surface *ballsFire[27] = {NULL};
    loadBallsFire(ballsFire);

    loadMap(map, powers, *world, *level);

    SDL_Rect endGameCoord;
    endGameCoord.x = (screen->w /2) - 250;
    endGameCoord.y = (screen->h /2) - 250;

    //DRAWING INTRO IF BEGINNING A NEW WORLD
    if (loopCounter == 0 && *level == 1)
    {
        SDL_Rect intro;
        intro.x = 0;
        intro.y = 0;
        SDL_BlitSurface(sprites[INTRO], NULL, screen, &intro);
        SDL_Flip(screen);
        SDL_Delay(7000); //TIME FOR INTRO
    }

    //Before playing, hide the mouse and place it to the center
    SDL_WarpMouse(screen->w/2-componentsPaddle[HALFSIZE], screen->h-100);
    SDL_ShowCursor(SDL_DISABLE);
    SDL_WarpMouse(screen->w/2-componentsPaddle[HALFSIZE], screen->h-100);

    while (continuer) {

           // DRAWING STARTS HERE
           drawBackground(screen, numbers, *world, *level, lives, *azurites, balls, loopCounter, componentsBall[0][STATE], componentsBall[0][SPEED], speedImg, bonusShop, powersShop, pause, sprites, systemNoise, noises); // we blit the background

           if (pause)
            {
                pause = false;
                speedTimer = SDL_GetTicks();
            }

           if (gameover > 0)
                continuer = false;
           else if(won > 0)
                continuer = false;
           else
           {
               renderMap(map, screen, sprites,loopCounter); //we blit the map
               //we blit over it the ball then the paddle


                for (j = 0; j < 16; j++)
                {
                    if (componentsBall[j][STATE] != INACTIVE)
                        activeBalls++;

                }


               drawPaddle(map, screen, componentsPaddle, sprites[componentsPaddle[WIDTH]], rockets, bonus[LASER], sprites[EXPLOSION], &impactPaddle, systemNoise, noises, &won);
               if(componentsPaddle[ROCKET] == OFF && rocketIndex > 0)
                    rocketIndex = 0;

               for(i = 0; i < 16; ++i){
                    if(componentsBall[i][STATE] != INACTIVE){
                        drawBall(screen, map, balls, ballsFire, componentsBall[i], componentsPaddle, &offSetPaddle, timeInit, &lives, &gameover, systemNoise, noises, &resetCounter, &impactPaddle, loopCounter, sprites[CLOUD], sprites[TELEPORT], &won);
                        drawBonus(screen, componentsPaddle, componentsBall[i], powers, bonus, activeBalls, systemNoise, noises);
                    }
               }

               launchBonus(powers, &lives, &speed, azurites, componentsPaddle, componentsBall);
               launchBonusShop(powersShop, &lives, &speed, azurites, componentsPaddle, componentsBall, resetCounter);


               // Has the player broken all bricks ? (only for level 1 to 8)
               if (*level != 9)
                checkEndGame(map, &won, systemNoise, noises);

           }
           // DRAWING ENDS HERE, NOW THE SWITCH :



            SDL_Event evenement;
            while(SDL_PollEvent(&evenement))
            {
                switch(evenement.type)
                {
                    case SDL_MOUSEMOTION:
                        componentsPaddle[X] = evenement.motion.x;

                        if (componentsPaddle[X] < 0)
                            componentsPaddle[X] = 0;
                        if (componentsPaddle[X] > screen->w-2*componentsPaddle[HALFSIZE])
                            componentsPaddle[X] = screen->w-2*componentsPaddle[HALFSIZE];
                        break;

                    case SDL_QUIT:
                        continuer = false;
                        break;

                    case SDL_MOUSEBUTTONUP:
                        if(evenement.button.button == SDL_BUTTON_LEFT){
                            for(i = 0; i < 16; ++i){
                                if(componentsBall[i][STATE] == STUCKSTATE){
                                    componentsBall[i][STATE] = ALIVESTATE;
                                    timeInit = SDL_GetTicks();
                                    offSetPaddle = NULL;
                                }
                            }
                        }else if(evenement.button.button == SDL_BUTTON_RIGHT){
                            if(componentsPaddle[ROCKET] == ON){
                                rockets[rocketIndex][X] = componentsPaddle[X];
                                rockets[rocketIndex][Y] = componentsPaddle[Y] - 10;
                                rockets[rocketIndex][2] = FALLING;

                                rockets[rocketIndex+1][X] = componentsPaddle[X] + 2*componentsPaddle[HALFSIZE] - 30;
                                rockets[rocketIndex+1][Y] = componentsPaddle[Y] - 10;
                                rockets[rocketIndex+1][2] = FALLING;

                                rocketIndex += 2;
                            }
                        }
                        break;

                    case SDL_KEYDOWN:
                        switch(evenement.key.keysym.sym)
                        {

                            case SDLK_UP:
                                for(i = 0; i < 16; ++i){
                                    if(componentsBall[i][STATE] == STUCKSTATE){
                                        componentsBall[i][STATE] = ALIVESTATE;
                                        timeInit = SDL_GetTicks();
                                        offSetPaddle = NULL;
                                    }
                                }
                                break;

                            case SDLK_LEFT:
                                componentsPaddle[X] -= 50;
                                if (componentsPaddle[X] < 0)
                                    componentsPaddle[X] = 0;
                                break;

                            case SDLK_RIGHT:
                                componentsPaddle[X] += 50;
                                if (componentsPaddle[X] > screen->w-2*componentsPaddle[HALFSIZE])
                                    componentsPaddle[X] = screen->w-2*componentsPaddle[HALFSIZE];
                                break;

                            case SDLK_ESCAPE:
                                continuer = false;
                                break;

                            case SDLK_KP0 :
                                continuer = false;
                                break;

                            case SDLK_0 :
                                continuer = false;
                                break;

                            case SDLK_p :
                                pause = true;
                                SDL_EnableKeyRepeat(0, SDL_DEFAULT_REPEAT_INTERVAL);
                                break;

                            /* developer access */

                            case SDLK_r : // reload map & graphics
                                loadMap(map, powers, *world, *level);
                                SDL_WarpMouse(screen->w/2-componentsPaddle[HALFSIZE], screen->h-100);
                                offSetPaddle = componentsPaddle[HALFSIZE] - RADIUS;
                                componentsBall[0][STATE] = STUCKSTATE;
                                componentsPaddle[X] = screen->w/2-componentsPaddle[HALFSIZE];
                                componentsPaddle[Y] = screen->h-100;
                                componentsBall[0][BALLX] = screen->w/2 - RADIUS;
                                componentsBall[0][DIRX] = 1;
                                componentsBall[0][DIRY] = -1;
                                componentsBall[0][ANGLE] = 45;
                                loadSprites(sprites, speedImg, bonusShop, *world);
                                break;
                            case SDLK_z : // win instantly
                                won = 1;
                                break;

                            case SDLK_KP_PLUS : // increase speed
                                componentsBall[0][SPEED]++;
                                break;

                            case SDLK_KP_MINUS : // decrease speed
                                componentsBall[0][SPEED]--;
                                break;

                            case SDLK_PLUS :
                                componentsBall[0][SPEED]++;
                                break;

                            case SDLK_MINUS :
                                componentsBall[0][SPEED]--;
                                break;

                            /* end of developer access*/

                            default:
                                continue;
                                break;

                        }
                        break;

                     default:
                        continue;
                        break;
                }
            } //event loop ENDS

            // finally, update the screen
            SDL_Flip(screen);
            SDL_Delay(25);

            if (resetCounter > 0) // reset the counter if animation
            {
                loopCounter = (resetCounter == 1) ? 0 : loopCounter;
                resetCounter = 0;
            }
            else
            {
                loopCounter++;
            }

            activeBalls = 0;

            //SPEED OF THE GAME !!

            if (SDL_GetTicks() - speedTimer > 30000) //increase the difficulty each half minute !
            {
                componentsBall[0][SPEED] = componentsBall[0][SPEED] + *difficulty;
                speedTimer = SDL_GetTicks();
            }
            componentsBall[0][SPEED] = (componentsBall[0][SPEED] < 11) ? 11 : componentsBall[0][SPEED];
            componentsBall[0][SPEED] = (componentsBall[0][SPEED] > 35) ? 35 : componentsBall[0][SPEED];

            if (powersShop[SPEEDMIN] == TRUE)
                componentsBall[0][SPEED] = 11;

    }//MAIN LOOP ENDS

    // disable the bonus shop used
    for (i = 0; i < 8; i++)
    {
        if (powersShop[i] == TRUE)
        {
            powersShop[i] = FALSE;
        }
    }

    //GAMEOVER
    if (gameover > 0)
    {
        SDL_BlitSurface(sprites[GAMEOVER], NULL, screen, &endGameCoord);
        SDL_Flip(screen);
        SDL_Delay(2000); //TIME FOR GAMEOVER LOGO
    }

    //WON
    else if(won > 0)
    {
        SDL_BlitSurface(sprites[WON], NULL, screen, &endGameCoord);
        SDL_Flip(screen);
        SDL_Delay(2000); //TIME FOR WON LOGO

        if (*level >= 1 && *level <= 8)
        {
           *level = *level + 1 ;
           play(screen, world, level, azurites, difficulty, powersShop); //PLAY NEXT LEVEL
        }

        else  //WE DRAW THE CONCLUSION OF THE WORLD IF FINISHED (LEVEL 9)
        {
            SDL_Rect conclusion;
            conclusion.x = 0;
            conclusion.y = 0;
            SDL_BlitSurface(sprites[CONCLUSION], NULL, screen, &conclusion);
            SDL_Flip(screen);
            SDL_Delay(7000); //TIME FOR CONCLUSION
            *level = 1;
            *world = *world +1;
            if ( *world == 8) //THE END OF THE GAME !
            {
                loadEnd(screen);
                *level = 1;
                *world = 1;
                *difficulty = (*difficulty > 4) ? 5 : *difficulty + 1; //increase difficulty for next new game
             }
            // ELSE : if world between 1 & 7 then back to menu to refresh memory !
        }


    }

}//end of play()

void launchBonus(int powers[NB_BLOCK_X*NB_BLOCK_Y][4], int *lives, int *speed, int *azurites, int componentsPaddle[6], float balls[16][11]){

    int i;
    int j, activeBalls = 0;

    for(i = 0; i < NB_BLOCK_X*NB_BLOCK_Y; i++){

        if(powers[i][3] == ON){
        //NOBONUS, INCPAD, DECPAD, INCSPEED, DECSPEED, MAGNETBALL, DOUBLEBALL, FIREBALL, LASER, DEATH, LIFE, AZURITE2, AZURITE3, AZURITE4, AZURITE5, AZURITE6, AZURITE7, AZURITE8, AZURITE9

            if (powers[i][2] >= 11)
            {
                *azurites = *azurites + powers[i][2] - 9;
                powers[i][3] = OFF;
            }
            else if (powers[i][2] == LIFE)
            {
                *lives = *lives + 1;
                powers[i][3] = OFF;
            }
            else if (powers[i][2] == DEATH)
            {
                *lives = (*lives < 1 ) ? 0 : *lives - 1;
                powers[i][3] = OFF;
            }
            else if (powers[i][2] == INCSPEED)
            {
                for (j = 0; j < 16; j++)
                {
                   balls[j][SPEED] = balls[j][SPEED] + 3;
                }

                powers[i][3] = OFF;
            }
            else if (powers[i][2] == DECSPEED)
            {
                for (j = 0; j < 16; j++)
                {
                   balls[j][SPEED] = balls[j][SPEED] - 3;
                }

                powers[i][3] = OFF;
            }
            else if (powers[i][2] == MAGNETBALL)
            {
                componentsPaddle[MODE] = WAITINGSTUCK;
                powers[i][X] = (powers[i][X] == 0) ? SDL_GetTicks() : powers[i][X];
                if(SDL_GetTicks() - powers[i][X] > 10000)
                {
                    powers[i][3] = OFF;
                    componentsPaddle[MODE] = NORMAL;
                }
            }
            else if (powers[i][2] == DOUBLEBALL)
            {
                powers[i][3] = OFF;
                for (j = 0; j < 16; j++)
                {
                    if (balls[j][STATE] != INACTIVE)
                        activeBalls++;
                }
                for (j = 0; j < 16; j++)
                {
                    if (balls[j][STATE] == INACTIVE && activeBalls > 0){
                        balls[j][STATE] = ALIVESTATE;
                        balls[j][X] = balls[0][X];
                        balls[j][Y] = balls[0][Y];
                        balls[j][DIRX] = balls[0][DIRX];
                        balls[j][DIRY] = balls[0][DIRY];
                        balls[j][ANGLE] = balls[0][ANGLE]+5;
                        balls[j][SPEED] = balls[0][SPEED];
                        balls[j][RANK] = CLONE;
                        balls[j][XHIT] = -1;
                        balls[j][YHIT] = -1;
                        --activeBalls;
                    }
                }

                activeBalls = 0;

            }

            else if (powers[i][2] == FIREBALL)
            {
                if(balls[0][STATE] == DEADSTATE){
                    powers[i][3] = OFF;
                }else{
                    powers[i][X] = (powers[i][X] == 0) ? SDL_GetTicks() : powers[i][X];
                    balls[0][RANK] = (balls[0][RANK] != FIREBALLSTATE) ? FIREBALLSTATE : balls[0][RANK];
                    if(SDL_GetTicks() - powers[i][X] > 10000)
                    {
                        powers[i][3] = OFF;
                        balls[0][RANK] = MASTER;
                    }
                }
            }

            else if (powers[i][2] == DECPAD)
            {
                componentsPaddle[WIDTH] = SMALLPADDLE;
                componentsPaddle[HALFSIZE] = 50;
                powers[i][X] = (powers[i][X] == 0) ? SDL_GetTicks() : powers[i][X];
                if(SDL_GetTicks() - powers[i][X] > 20000)
                {
                    powers[i][3] = OFF;
                    componentsPaddle[WIDTH] = MEDIUMPADDLE;
                    componentsPaddle[HALFSIZE] = 75;
                }
            }

            else if (powers[i][2] == INCPAD)
            {
                componentsPaddle[WIDTH] = LARGEPADDLE;
                componentsPaddle[HALFSIZE] = 100;
                powers[i][X] = (powers[i][X] == 0) ? SDL_GetTicks() : powers[i][X];
                if(SDL_GetTicks() - powers[i][X] > 20000)
                {
                    powers[i][3] = OFF;
                    componentsPaddle[WIDTH] = MEDIUMPADDLE;
                    componentsPaddle[HALFSIZE] = 75;
                }
            }

            else if (powers[i][2] == LASER)
            {
                componentsPaddle[ROCKET] = ON;
                powers[i][X] = (powers[i][X] == 0) ? SDL_GetTicks() : powers[i][X];
                if(SDL_GetTicks() - powers[i][X] > 6000)
                {
                    powers[i][3] = OFF;
                    componentsPaddle[ROCKET] = OFF;
                }
            }

        }

    }

}

void launchBonusShop(bool powersShop[8], int *lives, int *speed, int *azurites, int componentsPaddle[6], float balls[16][11], int resetCounter){


    int i;
    int j, activeBalls = 0;

    for(i = 0; i < 8; i++){

        if(powersShop[i] == true){
        //MAGNET, MAGNETINF, HEART, PADDLEINC, CLONEBALL, CLONEBALLINF, SPEEDMIN, REDBALL

            if (i == MAGNET)
            {
                componentsPaddle[MODE] = WAITINGSTUCK;
                if (resetCounter > 0)
                {
                    componentsPaddle[MODE] = NORMAL;
                    powersShop[i] = FALSE;
                }

            }

            else if (i == MAGNETINF)
            {
                componentsPaddle[MODE] = WAITINGSTUCK;
            }

            else if (i == HEART)
            {
                *lives = *lives + 1;
                powersShop[i] = FALSE;
            }

            else if (i == PADDLEINC)
            {
                componentsPaddle[WIDTH] = LARGEPADDLE;
                componentsPaddle[HALFSIZE] = 100;
            }

            else if (i == CLONEBALL)
            {
                if (resetCounter > 0)
                {
                    powersShop[i] = FALSE;
                }

                if (balls[1][STATE] == INACTIVE){
                    balls[1][STATE] = ALIVESTATE;
                    balls[1][X] = balls[0][X];
                    balls[1][Y] = balls[0][Y];
                    balls[1][DIRX] = balls[0][DIRX];
                    balls[1][DIRY] = balls[0][DIRY];
                    balls[1][ANGLE] = balls[0][ANGLE]+5;
                    balls[1][SPEED] = balls[0][SPEED];
                    balls[1][RANK] = CLONE;
                    balls[1][XHIT] = -1;
                    balls[1][YHIT] = -1;
                }
            }

            else if (i == CLONEBALLINF)
            {
                if (balls[1][STATE] == INACTIVE){
                    balls[1][STATE] = ALIVESTATE;
                    balls[1][X] = balls[0][X];
                    balls[1][Y] = balls[0][Y];
                    balls[1][DIRX] = balls[0][DIRX];
                    balls[1][DIRY] = balls[0][DIRY];
                    balls[1][ANGLE] = balls[0][ANGLE]+5;
                    balls[1][SPEED] = balls[0][SPEED];
                    balls[1][RANK] = CLONE;
                    balls[1][XHIT] = -1;
                    balls[1][YHIT] = -1;
                }
            }

            else if (i == REDBALL)
            {
                balls[0][RANK] = (balls[0][RANK] != FIREBALLSTATE) ? FIREBALLSTATE : balls[0][RANK];
                if (resetCounter > 0)
                {
                    powersShop[i] = FALSE;
                    balls[0][RANK] = MASTER;
                }
            }
        }
    }
}


