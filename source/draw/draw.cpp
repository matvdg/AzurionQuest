#include "../draw/draw.h"

void renderMap(int map[NB_BLOCK_Y][NB_BLOCK_X][4], SDL_Surface *screen, SDL_Surface *sprites[31], int loopCounter){

    int i = 0, j = 0;

    SDL_Rect brickCoord;
    //draw the bricks map

    for (i = 0; i < NB_BLOCK_Y; i++){

        for (j = 0; j < NB_BLOCK_X; j++){

            brickCoord.x = BLOCK_SIZE*j;
            brickCoord.y = BLOCK_SIZE*i;

            switch(map[i][j][TYPE]){

                case TELEPORT :
                    SDL_BlitSurface(sprites[(loopCounter/4)%9+7], NULL, screen, &brickCoord);
                    break;

                case AZURIONPART :
                    SDL_BlitSurface(sprites[AZURIONPART], NULL, screen, &brickCoord);
                    break;

                case METAL :
                    SDL_BlitSurface(sprites[METAL], NULL, screen, &brickCoord);
                    break;

                case REDBOX :
                    SDL_BlitSurface(sprites[REDBOX], NULL, screen, &brickCoord);
                    break;

                case BLUEBOX :
                    SDL_BlitSurface(sprites[BLUEBOX], NULL, screen, &brickCoord);
                    break;

                case GREENBOX :
                    SDL_BlitSurface(sprites[GREENBOX], NULL, screen, &brickCoord);
                    break;

            }

        }

    }



}

void drawBackground(SDL_Surface *screen, SDL_Surface *numbers[10], int world, int lvl, int lives, int azurites, SDL_Surface *balls[40], int loopCounter, int stateBall, float speed, SDL_Surface *speedImg[4], SDL_Surface *bonusShop[9], bool powersShop[8], bool pause, SDL_Surface *sprites[31], FMOD_SYSTEM *systemNoise, FMOD_SOUND *noises[13]){

    int i = 0;

    //display background depending on the world
    SDL_Rect planetCoord;
    planetCoord.x = 0;
    planetCoord.y = 0;
    SDL_BlitSurface(sprites[BACKGROUND], NULL, screen, &planetCoord);

    // display world
    SDL_Rect numbersCoord;
    numbersCoord.x = 450;
    numbersCoord.y = 15;
    SDL_BlitSurface(numbers[world], NULL, screen, &numbersCoord);

    // display level
    numbersCoord.x = 730;
    numbersCoord.y = 15;
    SDL_BlitSurface(numbers[lvl], NULL, screen, &numbersCoord);

    // display azurites coins
    numbersCoord.x = 1030;
    numbersCoord.y = 15;
    SDL_BlitSurface(numbers[(azurites/1000)%10], NULL, screen, &numbersCoord); //thousand
    numbersCoord.x = 1070;
    numbersCoord.y = 15;
    SDL_BlitSurface(numbers[(azurites/100)%10], NULL, screen, &numbersCoord); //hundred
    numbersCoord.x = 1110;
    numbersCoord.y = 15;
    SDL_BlitSurface(numbers[(azurites/10)%10], NULL, screen, &numbersCoord); //ten
    numbersCoord.x = 1150;
    numbersCoord.y = 15;
    SDL_BlitSurface(numbers[azurites%10], NULL, screen, &numbersCoord); //unit

    //display lives counter (drawing balls)
    SDL_Rect ballforlivesCoord;
    ballforlivesCoord.y = 25;
    for (i = 1 ; i <= lives ; i++)
    {
        ballforlivesCoord.x = 50 * i - 40;
        SDL_BlitSurface(balls[(loopCounter/2)%28], NULL, screen, &ballforlivesCoord);
    }

    if(stateBall == DEADSTATE)
    {

        if (loopCounter<6)//ball disappearing
        {
            ballforlivesCoord.x = 50 * (lives+1) - 40;
            SDL_BlitSurface(balls[loopCounter+28], NULL, screen, &ballforlivesCoord);
        }

    }

    // display the speed bar
    SDL_Rect barCoord;
    barCoord.x = 1363;
    barCoord.y = 10;
    int speedLoop = speed-10;

    for(i = 0; i < 25; i++){

        if(speedLoop > 0){
            barCoord.x += 12;
            if (i == 0)
                SDL_BlitSurface(speedImg[SPEEDBARMIN], NULL, screen, &barCoord);
            else if (i == 24)
                SDL_BlitSurface(speedImg[SPEEDBARMAX], NULL, screen, &barCoord);
            else
                SDL_BlitSurface(speedImg[SPEEDBAR], NULL, screen, &barCoord);

            speedLoop--;
        }else{
            barCoord.x += 12;
            SDL_BlitSurface(speedImg[SPEEDBARINVERT], NULL, screen, &barCoord);
        }

    }

    //display the shop bonus enabled

    if (loopCounter%200 > 100)
    {
        bool drawShop = FALSE;
        for (i = 0; i < 8; i++)
        {
            if (powersShop[i] == TRUE)
            {
                drawShop = TRUE;
            }
        }
        if (drawShop)
        {
            numbersCoord.x = 1231;
            numbersCoord.y = 0;
            SDL_BlitSurface(bonusShop[8], NULL, screen, &numbersCoord);
        }

        numbersCoord.x = 1493;
        numbersCoord.y = 25;
        if ( powersShop[MAGNET] == TRUE )
            SDL_BlitSurface(bonusShop[MAGNET], NULL, screen, &numbersCoord);
        if ( powersShop[MAGNETINF] == TRUE )
            SDL_BlitSurface(bonusShop[MAGNETINF], NULL, screen, &numbersCoord);
        numbersCoord.x = 1523;
        if ( powersShop[PADDLEINC] == TRUE )
            SDL_BlitSurface(bonusShop[PADDLEINC], NULL, screen, &numbersCoord);
        numbersCoord.x = 1553;
        if ( powersShop[CLONEBALL] == TRUE )
            SDL_BlitSurface(bonusShop[CLONEBALL], NULL, screen, &numbersCoord);
        if ( powersShop[CLONEBALLINF] == TRUE )
            SDL_BlitSurface(bonusShop[CLONEBALLINF], NULL, screen, &numbersCoord);
        numbersCoord.x = 1583;
        if ( powersShop[SPEEDMIN] == TRUE )
            SDL_BlitSurface(bonusShop[SPEEDMIN], NULL, screen, &numbersCoord);
        numbersCoord.x = 1613;
        if ( powersShop[REDBALL] == TRUE )
            SDL_BlitSurface(bonusShop[REDBALL], NULL, screen, &numbersCoord);

    }

    // display the pause panel if paused !
    if (pause == true)
    {
        bool endpause = false;
        while (!endpause)
        {
            SDL_Event evenement;
            while(SDL_PollEvent(&evenement))
            {
                switch(evenement.type)
                {
                    case SDL_KEYDOWN:
                        switch(evenement.key.keysym.sym)
                        {
                            case SDLK_p :
                                endpause = true;
                                SDL_EnableKeyRepeat(10,10);
                                break;
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

            //drawPausePanel
            planetCoord.x = (screen->w /2) - 250;
            planetCoord.y = (screen->h /2) - 250;
            SDL_BlitSurface(sprites[PAUSE], NULL, screen, &planetCoord);


            // finally, update the screen
            SDL_Flip(screen);
            SDL_Delay(25);

        }//endwhile
        playNoise(systemNoise, noises[HEARTBEAT]);
        SDL_BlitSurface(sprites[P3], NULL, screen, &planetCoord);
        SDL_Flip(screen);
        SDL_Delay(1000);
        SDL_BlitSurface(sprites[P2], NULL, screen, &planetCoord);
        SDL_Flip(screen);
        SDL_Delay(1000);
        SDL_BlitSurface(sprites[P1], NULL, screen, &planetCoord);
        SDL_Flip(screen);
        SDL_Delay(1000);
        playNoise(systemNoise, noises[BUZZ]);
        SDL_BlitSurface(sprites[GO], NULL, screen, &planetCoord);
        SDL_Flip(screen);
        SDL_Delay(500);


    }//endif

}//endfunction

void drawBall(SDL_Surface *screen, int map[NB_BLOCK_Y][NB_BLOCK_X][4], SDL_Surface *balls[40], SDL_Surface *ballsFire[27], float componentsBall[11], int componentsPaddle[6], int *offSetPaddle, int timeInit, int* lives, int* gameover, FMOD_SYSTEM *systemNoise, FMOD_SOUND *noises[13], int* resetCounter, int *impactPaddle, int loopCounter, SDL_Surface *cloud, SDL_Surface *shield, int *won){

    SDL_Rect ballCoord;

    float moveToX = 0;
    float moveToY = 0;

    /*WE DRAW ACCORDING TO THE STATE OF THE BALL : 0 for dead, 1 for alive, 2 for stuck, 3 for vortex, 4 for fireball */
    int stateball = componentsBall[STATE];
    switch(stateball)
    {
        case DEADSTATE : //dead mode (vortex on the paddle)
            // reminder : due to resetCounter mode, the loopCounter has already been set to zero
            if ( loopCounter >= 6 && loopCounter < 12 )//ball appearing after teleporting on the paddle
            {
                *offSetPaddle = componentsPaddle[HALFSIZE] - RADIUS;
                componentsBall[BALLX] = componentsPaddle[X] + *offSetPaddle;
                componentsBall[BALLY] = componentsPaddle[Y] - 30;

                ballCoord.x = componentsBall[BALLX];
                ballCoord.y = componentsBall[BALLY];
                SDL_BlitSurface(balls[loopCounter+27], NULL, screen, &ballCoord);
            }
            else if (loopCounter >= 12)
            {
                componentsBall[BALLX] = componentsPaddle[X] + *offSetPaddle;
                componentsBall[BALLY] = componentsPaddle[Y] - 30;

                playNoise(systemNoise, noises[READYNOISE]);
                componentsBall[DIRX] = 1;
                componentsBall[DIRY] = -1;
                componentsBall[ANGLE] = 45;
                componentsBall[STATE] = STUCKSTATE; //end of dead mode, switch to stuck mode
                ballCoord.x = componentsBall[BALLX];
                ballCoord.y = componentsBall[BALLY];
                SDL_BlitSurface(balls[(loopCounter/2)%28], NULL, screen, &ballCoord);
            }
            break;

        case ALIVESTATE : // alive mode
            int lap;
            for(lap = 0; lap < componentsBall[SPEED]; ++lap){

                // WE CHECK A POTENTIAL IMPACT
                checkCollision(map, screen, componentsBall, componentsPaddle, timeInit, lives, gameover, systemNoise, noises, resetCounter, impactPaddle, cloud, shield, won);
                if (*resetCounter == 1)
                    break;

                moveToX = componentsBall[BALLX] + ((((fabs(cos(componentsBall[ANGLE] * PI / 180)))*(componentsBall[DIRX]*componentsBall[SPEED])))/componentsBall[SPEED]);
                moveToY = componentsBall[BALLY] + ((((fabs(sin(componentsBall[ANGLE] * PI / 180)))*(componentsBall[DIRY]*componentsBall[SPEED])))/componentsBall[SPEED]);

                componentsBall[BALLX] = moveToX;
                componentsBall[BALLY] = moveToY;

            }

            ballCoord.x = componentsBall[BALLX];
            ballCoord.y = componentsBall[BALLY];

            if(componentsBall[RANK] == FIREBALLSTATE)
                SDL_BlitSurface(ballsFire[(loopCounter/2)%16], NULL, screen, &ballCoord);
            else if(componentsBall[RANK] == MASTER)
                SDL_BlitSurface(balls[(loopCounter/2)%28], NULL, screen, &ballCoord);
            else
                SDL_BlitSurface(balls[39], NULL, screen, &ballCoord);

            break;

        case STUCKSTATE : // stuck mode

            if(*offSetPaddle == NULL)
                *offSetPaddle = componentsBall[BALLX] - componentsPaddle[X];

            componentsBall[BALLX] = componentsPaddle[X] + (*offSetPaddle);
            componentsBall[BALLY] = componentsPaddle[Y] - 30;

            ballCoord.x = componentsBall[BALLX];
            ballCoord.y = componentsBall[BALLY];

            if(componentsBall[RANK] == FIREBALLSTATE)
                SDL_BlitSurface(ballsFire[(loopCounter/2)%16], NULL, screen, &ballCoord);
            else if(componentsBall[RANK] == MASTER)
                SDL_BlitSurface(balls[(loopCounter/2)%28], NULL, screen, &ballCoord);
            else
                SDL_BlitSurface(balls[39], NULL, screen, &ballCoord);


            break;

        case VORTEXSTATE : //vortex mode : ball teleporting from one point to another
            // reminder : due to resetCounter mode, the loopCounter has already been set to zero

            if (loopCounter<6) //ball disappearing
            {
                ballCoord.x = componentsBall[BALLX];
                ballCoord.y = componentsBall[BALLY];

                if(componentsBall[RANK] == FIREBALLSTATE)
                    SDL_BlitSurface(ballsFire[loopCounter+16], NULL, screen, &ballCoord);
                else
                    SDL_BlitSurface(balls[loopCounter+28], NULL, screen, &ballCoord);
            }
            else if (loopCounter<12) //ball appearing after teleportation
            {
                // remove the gate !
                int xvor = componentsBall[XHIT], yvor = componentsBall[YHIT];//converting float to int
                if(map[yvor][xvor][TYPE] == 5){
                    map[yvor][xvor][TYPE] = 0;
                }

                componentsBall[BALLX] = componentsBall[XHIT] * BLOCK_SIZE + 5 ;
                componentsBall[BALLY] = componentsBall[YHIT] * BLOCK_SIZE + 5;

                ballCoord.x = componentsBall[BALLX];
                ballCoord.y = componentsBall[BALLY];

                if(componentsBall[RANK] == FIREBALLSTATE)
                    SDL_BlitSurface(ballsFire[loopCounter+15], NULL, screen, &ballCoord);
                else
                    SDL_BlitSurface(balls[loopCounter+27], NULL, screen, &ballCoord);
            }
            else
            {
                componentsBall[STATE] = ALIVESTATE; //end of vortex mode, switch to alive mode
                ballCoord.x = componentsBall[BALLX];
                ballCoord.y = componentsBall[BALLY];
                if(componentsBall[RANK] == FIREBALLSTATE)
                    SDL_BlitSurface(ballsFire[(loopCounter/2)%16], NULL, screen, &ballCoord);
                else if(componentsBall[RANK] == MASTER)
                    SDL_BlitSurface(balls[(loopCounter/2)%28], NULL, screen, &ballCoord);
                else
                    SDL_BlitSurface(balls[39], NULL, screen, &ballCoord);
            }
            break;
    }
}

void drawPaddle(int map[NB_BLOCK_Y][NB_BLOCK_X][4], SDL_Surface *screen, int componentsPaddle[6], SDL_Surface *paddle, int rockets[300][3], SDL_Surface *rocket, SDL_Surface *explosion, int *impactPaddle, FMOD_SYSTEM *systemNoise, FMOD_SOUND *noises[13], int* won){

    SDL_Rect paddleCoord;

    // if the ball hit the paddle, little animation, paddle move top to bottom, and next bottom to top and stop at initial animation start point
    if(*impactPaddle != 0){

        if(*impactPaddle < 10 && *impactPaddle > 0){
            componentsPaddle[Y]++;
            *impactPaddle = (*impactPaddle + 1 >= 10) ? -1 : *impactPaddle + 1;

        }else{
            componentsPaddle[Y]--;
            *impactPaddle = (*impactPaddle - 1 <= -10) ? 0 : *impactPaddle - 1;
        }

    }

    paddleCoord.x = componentsPaddle[X];
    paddleCoord.y = componentsPaddle[Y];

    SDL_BlitSurface(paddle, NULL, screen, &paddleCoord);

    if(componentsPaddle[ROCKET] == ON){

        SDL_Rect rocketCoord;
        rocketCoord.x = componentsPaddle[X];
        rocketCoord.y = componentsPaddle[Y] - 10;

        SDL_BlitSurface(rocket, NULL, screen, &rocketCoord);

        rocketCoord.x = componentsPaddle[X] + 2*componentsPaddle[HALFSIZE] - 30;
        rocketCoord.y = componentsPaddle[Y] - 10;

        SDL_BlitSurface(rocket, NULL, screen, &rocketCoord);

    }

    drawRockets(map, screen, rockets, rocket, explosion, systemNoise, noises, won);

}

void drawBonus(SDL_Surface *screen, int componentsPaddle[6], float componentsBall[11], int powers[18][4], SDL_Surface *bonus[19], int activeBalls, FMOD_SYSTEM *systemNoise, FMOD_SOUND *noises[13]){

    int i;
    SDL_Rect bonusCoord;
    int xHit = componentsBall[XHIT], yHit = componentsBall[YHIT];

    checkBonus(screen, powers, componentsPaddle, systemNoise, noises);

    for(i = 0; i < NB_BLOCK_X*NB_BLOCK_Y; i++){

        if(powers[i][2] != NOBONUS && powers[i][3] == OFF && xHit == powers[i][X] && yHit == powers[i][Y]){
            powers[i][3] = FALLING;
            powers[i][X] = powers[i][X]*BLOCK_SIZE + 10;
            powers[i][Y] = powers[i][Y]*BLOCK_SIZE;
            componentsBall[XHIT] = -1;
            componentsBall[YHIT] = -1;
        }

        if(powers[i][3] == FALLING){
            bonusCoord.x = powers[i][X];
            bonusCoord.y = powers[i][Y];
            powers[i][Y] += 5/activeBalls;
            powers[i][Y] = (powers[i][Y] + 5/activeBalls == powers[i][Y]) ? powers[i][Y]+1 : powers[i][Y];
            SDL_BlitSurface(bonus[powers[i][2]], NULL, screen, &bonusCoord);
        }

    }

}

void drawRockets(int map[NB_BLOCK_Y][NB_BLOCK_X][4], SDL_Surface *screen, int rockets[300][3], SDL_Surface *rocket, SDL_Surface *explosion, FMOD_SYSTEM *systemNoise, FMOD_SOUND *noises[13], int* won){

    int i;
    SDL_Rect rocketCoord;

    for(i = 0; i < 200; i++){
        if(rockets[i][2] == FALLING){
            checkRockets(map, screen, rockets[i], explosion, won, systemNoise, noises);
            rockets[i][Y] -= 20;
            rocketCoord.x = rockets[i][X];
            rocketCoord.y = rockets[i][Y];
            SDL_BlitSurface(rocket, NULL, screen, &rocketCoord);
        }
    }

}


























