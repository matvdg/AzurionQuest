#include "../check/check.h"
#include "../load/load.h"

void checkButton(int mouseX,int mouseY,int position,int buttonAction[4]){

    if ( mouseX > 50 && mouseX < 150 && mouseY > 50 && mouseY < 90 && position == RELEASED) //mute button
    {
        buttonAction[MUTE] = SWITCHED;
    }
    else if ( mouseX > 50 && mouseX < 550 && mouseY > 900 && mouseY < 1000 ) //play button
    {
        buttonAction[PLAY] = position;
    }
    else if  ( mouseX > 600 && mouseX < 1100 && mouseY > 900 && mouseY < 1000 ) // garage button
    {
        buttonAction[GARAGE] = position;
    }
    else if ( mouseX > 1150 && mouseX < 1650 && mouseY > 900 && mouseY < 1000 ) // quit button
    {
        buttonAction[QUIT] = position;
    }
    else
    {
        buttonAction[MUTE] = NONE;
        buttonAction[PLAY] = NONE;
        buttonAction[GARAGE] = NONE;
        buttonAction[QUIT] = NONE;
    }

};

void checkButtonGarage(int mouseX,int mouseY,int position,int buttonActionGarage[11]){

    if ( mouseX > 890 && mouseX < 940 && mouseY > 330 && mouseY < 380 ) //left button
    {
        buttonActionGarage[LEFT] = position;
    }
    else if ( mouseX > 1020 && mouseX < 1070 && mouseY > 330 && mouseY < 380 ) // right button
    {
        buttonActionGarage[RIGHT] = position;
    }
    else if ( mouseX > 50 && mouseX < 150 && mouseY > 930 && mouseY < 1030 ) // home button
    {
        buttonActionGarage[HOME] = position;
    }
    else if ( mouseX > 180 && mouseX < 280 && mouseY > 930 && mouseY < 1030 ) // reset button
    {
        buttonActionGarage[RESET] = position;
    }
    else if ( mouseX > 1500 && mouseX < 1600 && mouseY > 930 && mouseY < 1030 ) // esc button
    {
        buttonActionGarage[ESC] = position;
    }
    else if ( mouseX > 310 && mouseX < 410 && mouseY > 930 && mouseY < 1030 ) // playintro button
    {
        buttonActionGarage[PLAYINTRO] = position;
    }

    else if ( mouseX > 180 && mouseX < 280 && mouseY > 730 && mouseY < 830 ) // replay button
    {
        buttonActionGarage[REPLAY] = position;
    }
    else if ( mouseX > 110 && mouseX < 160 && mouseY > 560 && mouseY < 610 ) // leftworld button
    {
        buttonActionGarage[LEFTWORLD] = position;
    }
    else if ( mouseX > 300 && mouseX < 350 && mouseY > 560 && mouseY < 610 ) // rightworld button
    {
        buttonActionGarage[RIGHTWORLD] = position;
    }
    else if ( mouseX > 110 && mouseX < 160 && mouseY > 660 && mouseY < 710 ) // leftlevel button
    {
        buttonActionGarage[LEFTLEVEL] = position;
    }
    else if ( mouseX > 300 && mouseX < 350 && mouseY > 660 && mouseY < 710 ) // rightlevel button
    {
        buttonActionGarage[RIGHTLEVEL] = position;
    }
    else
    {
        buttonActionGarage[LEFT] = NONE;
        buttonActionGarage[RIGHT] = NONE;
        buttonActionGarage[HOME] = NONE;
        buttonActionGarage[ESC] = NONE;
        buttonActionGarage[RESET] = NONE;
        buttonActionGarage[REPLAY] = NONE;
        buttonActionGarage[LEFTWORLD] = NONE;
        buttonActionGarage[RIGHTWORLD] = NONE;
        buttonActionGarage[LEFTLEVEL] = NONE;
        buttonActionGarage[RIGHTLEVEL] = NONE;
        buttonActionGarage[PLAYINTRO] = NONE;
    }

}

void checkReset(SDL_Surface *screen, int* azurites, int *world, int *level,int *worldReplay, int *levelReplay, int *difficulty, FMOD_SYSTEM *system, FMOD_SOUND *music){

    SDL_Surface *reset = {NULL};
    SDL_Rect resetCoord;
    resetCoord.x = 0;
    resetCoord.y = 0;

    reset = loadImageOptimised("images/Assets/other/reset.jpg");

    playSound(system, music, "sounds/buzz.mp3", -1);

    bool endReset = false;

    while (!endReset)
    {
        SDL_Event event;
        SDL_BlitSurface(reset, NULL, screen, &resetCoord);
        SDL_Flip(screen);

        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                //mouse pressed
                case SDL_MOUSEBUTTONDOWN:

                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        if (event.button.x > 600 && event.button.x < 820 && event.button.y > 665 && event.button.y < 772)
                        {
                            endReset = true;
                            stopSound(system);
                        }
                        else if (event.button.x > 945 && event.button.x < 1170 && event.button.y > 665 && event.button.y < 772)
                        {
                            *world = 1;
                            *level = 1;
                            *difficulty = 1;
                            *worldReplay = 1;
                            *levelReplay = 1;
                            saveBackUp(*world, *level, *azurites, *difficulty);
                            stopSound(system);
                            playSound(system, music, "sounds/reset.mp3", 0);
                            endReset = true;
                        }
                    }
                    break;

                 default:
                    continue;
                    break;

            } // end switch
        }//endPollEvent
    }//endReset Loop
}//end

void checkCollision(int map[NB_BLOCK_Y][NB_BLOCK_X][4], SDL_Surface *screen, float componentsBall[11], int componentsPaddle[6], int timeInit, int* lives, int* gameover, FMOD_SYSTEM *systemNoise, FMOD_SOUND *noises[13], int* resetCounter, int* impactPaddle, SDL_Surface *cloud, SDL_Surface *shield, int* won){

    if(!checkBorder(map, screen, componentsBall, lives, gameover, systemNoise, noises, resetCounter)){

        if(componentsBall[RANK] == MASTER || componentsBall[RANK] == CLONE){
            if(!checkBrick_V41(map, screen, componentsBall, systemNoise, noises, resetCounter, cloud, shield, won)){
                checkPaddle_V2(componentsBall, componentsPaddle, timeInit, systemNoise, noises, impactPaddle);
            }
        }else if(componentsBall[RANK] == FIREBALLSTATE){
            if(!checkBrick_FireMode_V41(map, screen, componentsBall, systemNoise, noises, resetCounter, cloud, shield, won)){
                checkPaddle_V2(componentsBall, componentsPaddle, timeInit, systemNoise, noises, impactPaddle);
            }
        }

    }

}

bool checkBorder(int map[NB_BLOCK_Y][NB_BLOCK_X][4], SDL_Surface *screen, float componentsBall[11], int* lives, int* gameover, FMOD_SYSTEM *systemNoise, FMOD_SOUND *noises[13], int* resetCounter){

    float angleBall[2][2] = {NULL};
    angleBall[TL][X] = componentsBall[BALLX];
    angleBall[TL][Y] = componentsBall[BALLY];
    angleBall[TR][X] = componentsBall[BALLX] + 40;
    angleBall[TR][Y] = componentsBall[BALLY];

    // BORDERS
    bool collision = (componentsBall[BALLY] >= ( screen->h - 40 )) ? true : false; //to avoid useless multiple collisions testing

    //Collision TOP OF THE SCREEN
    if( angleBall[TR][Y] <= 90 )
    {
        componentsBall[DIRY] = -componentsBall[DIRY];
        collision = true;
    }


    // Collision BOTTOM OF THE SCREEN = death
    else if (componentsBall[BALLY] >= ( screen->h ))
    {
        if(componentsBall[RANK] == MASTER || componentsBall[RANK] == FIREBALLSTATE){
            *lives = *lives - 1;
            *resetCounter = 1;
            componentsBall[STATE] = DEADSTATE; //dead state !
            componentsBall[RANK] = MASTER; //for the fireball which becomes normal again after death (FIREBALLSTATE)
            if (*lives==-1)
            {
                *gameover = 1;
                playNoise(systemNoise, noises[GAMEOVERNOISE]);
            }
            else {playNoise(systemNoise, noises[DIENOISE]);}
        }else{
            componentsBall[STATE] = INACTIVE; //for the clones
            playNoise(systemNoise, noises[DIENOISE]);
        }
    }

    //Collision RIGHT & LEFT
    else if(angleBall[TR][X] >= screen->w || angleBall[TL][X] <= 0)
    {
        componentsBall[DIRX] = -componentsBall[DIRX];
        collision = true;
    }

    return collision;

}

bool checkBrick_V41(int map[NB_BLOCK_Y][NB_BLOCK_X][4], SDL_Surface *screen, float componentsBall[11], FMOD_SYSTEM *systemNoise, FMOD_SOUND *noises[13], int* resetCounter, SDL_Surface *cloud, SDL_Surface *shield, int *won){

    // COLLISION ENGINE V4.1 : IMPACT-DESTROYER => THE BEST EVER !
    bool collision = false;

    int yMapHit = 0;
    int xMapHit = 0;

    int DirX = componentsBall[DIRX];
    int DirY = componentsBall[DIRY];

    int impactPoints[2][2] = {{0,0}};
    int centerBall[2] = {componentsBall[BALLX] + RADIUS, componentsBall[BALLY] + RADIUS};

    // FRONT COLLISION FIRST
    switch(DirX){

        case 1 :

            switch(DirY){

                case 1 :

                    impactPoints[0][X] = centerBall[X] + RADIUS*cos(-componentsBall[ANGLE] * (PI / 180));
                    impactPoints[0][Y] = centerBall[Y] - RADIUS*sin(-componentsBall[ANGLE] * (PI / 180));

                    break;
                case -1 :

                    impactPoints[0][X] = centerBall[X] + RADIUS*cos(componentsBall[ANGLE] * (PI / 180));
                    impactPoints[0][Y] = centerBall[Y] - RADIUS*sin(componentsBall[ANGLE] * (PI / 180));

                    break;
                default :

                    break;

            }

            break;
        case -1 :

            switch(DirY){

                case 1 :

                    impactPoints[0][X] = centerBall[X] + RADIUS*cos((PI+(componentsBall[ANGLE] * PI / 180)));
                    impactPoints[0][Y] = centerBall[Y] - RADIUS*sin((PI+(componentsBall[ANGLE] * PI / 180)));

                    break;
                case -1 :

                    impactPoints[0][X] = centerBall[X] + RADIUS*cos((PI-(componentsBall[ANGLE] * PI / 180)));
                    impactPoints[0][Y] = centerBall[Y] - RADIUS*sin((PI-(componentsBall[ANGLE] * PI / 180)));

                    break;
                default :

                    break;

            }

            break;
        default :

            break;
    }

    if(map[impactPoints[0][Y]/BLOCK_SIZE][impactPoints[0][X]/BLOCK_SIZE][TYPE] != VIDE){


        xMapHit = impactPoints[0][X]/BLOCK_SIZE;
        yMapHit = impactPoints[0][Y]/BLOCK_SIZE;

        if(map[yMapHit][xMapHit][TYPE] != TELEPORT){
            switch (DirX){
                case 1 :
                    switch(DirY){
                        case 1 :
                            if( fabs(impactPoints[0][X] - ((impactPoints[0][X]/BLOCK_SIZE)*BLOCK_SIZE)) > fabs(impactPoints[0][Y] - ((impactPoints[0][Y]/BLOCK_SIZE)*BLOCK_SIZE)) )
                                componentsBall[DIRY] = -componentsBall[DIRY];
                            else
                                componentsBall[DIRX] = -componentsBall[DIRX];
                            break;

                        case -1 :
                            if( fabs(impactPoints[0][X] - ((impactPoints[0][X]/BLOCK_SIZE)*BLOCK_SIZE)) > fabs(impactPoints[0][Y] - (((impactPoints[0][Y]/BLOCK_SIZE)*BLOCK_SIZE))+ BLOCK_SIZE ) )
                                componentsBall[DIRY] = -componentsBall[DIRY];
                            else
                                componentsBall[DIRX] = -componentsBall[DIRX];
                            break;
                    }
                    break;
                case -1 :
                    switch(DirY){
                        case 1 :
                            if( fabs(impactPoints[0][X] - (((impactPoints[0][X]/BLOCK_SIZE)*BLOCK_SIZE))+ BLOCK_SIZE ) > fabs(impactPoints[0][Y] - ((impactPoints[0][Y]/BLOCK_SIZE)*BLOCK_SIZE)) )
                                componentsBall[DIRY] = -componentsBall[DIRY];
                            else
                                componentsBall[DIRX] = -componentsBall[DIRX];
                            break;
                        case -1 :
                            if( fabs(impactPoints[0][X] - (((impactPoints[0][X]/BLOCK_SIZE)*BLOCK_SIZE))+ BLOCK_SIZE) > fabs(impactPoints[0][Y] - (((impactPoints[0][Y]/BLOCK_SIZE)*BLOCK_SIZE))+ BLOCK_SIZE) )
                                componentsBall[DIRY] = -componentsBall[DIRY];
                            else
                                componentsBall[DIRX] = -componentsBall[DIRX];
                            break;
                    }
                    break;
            }
        }

        collision = true;

    }

    // LATERAL COLLISIONS

    int k;
    if(!collision){

        for(k = 2; k <= 20; k++){

            switch(DirX){
                case 1 :
                    switch(DirY){
                        case 1 :

                            impactPoints[1][X] = centerBall[X] + RADIUS*cos((-componentsBall[ANGLE] * PI / 180) + (PI / k));
                            impactPoints[1][Y] = centerBall[Y] - RADIUS*sin((-componentsBall[ANGLE] * PI / 180) + (PI / k));

                            break;
                        case -1 :

                            impactPoints[1][X] = centerBall[X] + RADIUS*cos((componentsBall[ANGLE] * PI / 180) + (PI / k));
                            impactPoints[1][Y] = centerBall[Y] - RADIUS*sin((componentsBall[ANGLE] * PI / 180) + (PI / k));

                            break;
                    }
                    break;
                case -1 :
                    switch(DirY){
                        case 1 :

                            impactPoints[1][X] = centerBall[X] + RADIUS*cos(((PI+(componentsBall[ANGLE] * PI / 180)) + (PI / k)));
                            impactPoints[1][Y] = centerBall[Y] - RADIUS*sin(((PI+(componentsBall[ANGLE] * PI / 180)) + (PI / k)));

                            break;
                        case -1 :

                            impactPoints[1][X] = centerBall[X] + RADIUS*cos(((PI-(componentsBall[ANGLE] * PI / 180)) + (PI / k)));
                            impactPoints[1][Y] = centerBall[Y] - RADIUS*sin(((PI-(componentsBall[ANGLE] * PI / 180)) + (PI / k)));

                            break;
                    }
                    break;
            }


            if(map[impactPoints[1][Y]/BLOCK_SIZE][impactPoints[1][X]/BLOCK_SIZE][TYPE] != VIDE){

                xMapHit = impactPoints[1][X]/BLOCK_SIZE;
                yMapHit = impactPoints[1][Y]/BLOCK_SIZE;

                if(map[yMapHit][xMapHit][TYPE] != TELEPORT){
                    if( (componentsBall[DIRX] == 1 && componentsBall[DIRY] == 1) || (componentsBall[DIRX] == -1 && componentsBall[DIRY] == -1) )
                        componentsBall[DIRX] = -componentsBall[DIRX];
                    else
                        componentsBall[DIRY] = -componentsBall[DIRY];
                }


                collision = true;
                break;
            }

        }

    }

    if(!collision){

        for(k = 2; k <= 20; k++){

            switch(DirX){
                case 1 :
                    switch(DirY){
                        case 1 :

                            impactPoints[1][X] = centerBall[X] + RADIUS*cos((-componentsBall[ANGLE] * PI / 180) - (PI / k));
                            impactPoints[1][Y] = centerBall[Y] - RADIUS*sin((-componentsBall[ANGLE] * PI / 180) - (PI / k));

                            break;
                        case -1 :

                            impactPoints[1][X] = centerBall[X] + RADIUS*cos((componentsBall[ANGLE] * PI / 180) - (PI / k));
                            impactPoints[1][Y] = centerBall[Y] - RADIUS*sin((componentsBall[ANGLE] * PI / 180) - (PI / k));

                            break;
                    }
                    break;
                case -1 :
                    switch(DirY){
                        case 1 :

                            impactPoints[1][X] = centerBall[X] + RADIUS*cos(((PI+(componentsBall[ANGLE] * PI / 180)) - (PI / k)));
                            impactPoints[1][Y] = centerBall[Y] - RADIUS*sin(((PI+(componentsBall[ANGLE] * PI / 180)) - (PI / k)));

                            break;
                        case -1 :

                            impactPoints[1][X] = centerBall[X] + RADIUS*cos(((PI-(componentsBall[ANGLE] * PI / 180)) - (PI / k)));
                            impactPoints[1][Y] = centerBall[Y] - RADIUS*sin(((PI-(componentsBall[ANGLE] * PI / 180)) - (PI / k)));

                            break;
                    }
                    break;
            }

            if(map[impactPoints[1][Y]/BLOCK_SIZE][impactPoints[1][X]/BLOCK_SIZE][TYPE] != VIDE){

                xMapHit = impactPoints[1][X]/BLOCK_SIZE;
                yMapHit = impactPoints[1][Y]/BLOCK_SIZE;

                if(map[yMapHit][xMapHit][TYPE] != TELEPORT){
                    if( (componentsBall[DIRX] == 1 && componentsBall[DIRY] == 1) || (componentsBall[DIRX] == -1 && componentsBall[DIRY] == -1) )
                        componentsBall[DIRY] = -componentsBall[DIRY];
                    else
                        componentsBall[DIRX] = -componentsBall[DIRX];
                }

                collision = true;
                break;

            }

        }

    }


    // Vortex collision
    if(map[yMapHit][xMapHit][TYPE] == TELEPORT){

        *resetCounter = 1;
        componentsBall[STATE] = VORTEXSTATE; //vortex state !

        int i = 0, j = 0;
        //we parse the map in order to find the vortex gate !
        for (i = 0; i < NB_BLOCK_Y; i++){

            for (j = 0; j < NB_BLOCK_X; j++){

                if ( map[i][j][TYPE] == TELEPORT && (i != yMapHit || j != xMapHit))
                {
                    componentsBall[YHIT] = i;
                    componentsBall[XHIT] = j;
                }

            }

        }

        map[yMapHit][xMapHit][TYPE] = VIDE; // remove the gate !
        playNoise(systemNoise, noises[VORTEXNOISE]);

    }

    // GEMSTONE OF AZURION (LEVEL 9 ONLY)
    else if(map[yMapHit][xMapHit][TYPE] == AZURIONPART )
    {
        map[yMapHit][xMapHit][TYPE] == VIDE;
        playNoise(systemNoise, noises[GEMSTONENOISE]);
        * won = 1;

    }

    // Metal collision
    else if(map[yMapHit][xMapHit][TYPE] == METAL )
    {

        SDL_Rect shieldCoord;
        // we blit the shield over the metal !
        shieldCoord.x = xMapHit*BLOCK_SIZE;
        shieldCoord.y = yMapHit*BLOCK_SIZE;
        SDL_BlitSurface(shield, NULL, screen, &shieldCoord);

        playNoise(systemNoise, noises[METALBOUNCE]);

        // if we hit many times an indestructible brick, we are maybe blocked ?
        componentsBall[LAST_IMPACT_TIME] = (componentsBall[LAST_IMPACT_TIME] == 0) ? SDL_GetTicks() : componentsBall[LAST_IMPACT_TIME];
        if( (SDL_GetTicks() - componentsBall[LAST_IMPACT_TIME]) > 8000 ){
            componentsBall[ANGLE] = ((componentsBall[ANGLE]-5) < 45) ? componentsBall[ANGLE]+5 : componentsBall[ANGLE]-5;
            componentsBall[LAST_IMPACT_TIME] = SDL_GetTicks();
        }

    }

    // Changing the type of brick
    else if(map[yMapHit][xMapHit][TYPE] != VIDE && map[yMapHit][xMapHit][TYPE] != METAL){
        if(map[yMapHit][xMapHit][TYPE] == GREENBOX)
        {
            //draw colapsing clouds
            SDL_Rect cloudCoord;
            cloudCoord.x = xMapHit*BLOCK_SIZE;
            cloudCoord.y = yMapHit*BLOCK_SIZE;
            SDL_BlitSurface(cloud, NULL, screen, &cloudCoord);
        }

        map[yMapHit][xMapHit][TYPE]--;

        if(componentsBall[RANK] == FIREBALLSTATE || map[yMapHit][xMapHit][TYPE] == VIDE){
            componentsBall[YHIT] = yMapHit;
            componentsBall[XHIT] = xMapHit;
        }

        componentsBall[LAST_IMPACT_TIME] = 0;

        playNoise(systemNoise, noises[BOUNCE]);

    }

    return collision;

}

bool checkBrick_FireMode_V41(int map[NB_BLOCK_Y][NB_BLOCK_X][4], SDL_Surface *screen, float componentsBall[11], FMOD_SYSTEM *systemNoise, FMOD_SOUND *noises[13], int* resetCounter, SDL_Surface *cloud, SDL_Surface *shield, int *won){

    // COLLISION ENGINE V4.1 : IMPACT-DESTROYER => THE BEST EVER !
    bool collision = false;

    int yMapHit = 0;
    int xMapHit = 0;

    int DirX = componentsBall[DIRX];
    int DirY = componentsBall[DIRY];

    int impactPoints[2][2] = {{0,0}};
    int centerBall[2] = {componentsBall[BALLX] + RADIUS, componentsBall[BALLY] + RADIUS};

    // FRONT COLLISION FIRST
    switch(DirX){

        case 1 :

            switch(DirY){

                case 1 :

                    impactPoints[0][X] = centerBall[X] + RADIUS*cos(-componentsBall[ANGLE] * (PI / 180));
                    impactPoints[0][Y] = centerBall[Y] - RADIUS*sin(-componentsBall[ANGLE] * (PI / 180));

                    break;
                case -1 :

                    impactPoints[0][X] = centerBall[X] + RADIUS*cos(componentsBall[ANGLE] * (PI / 180));
                    impactPoints[0][Y] = centerBall[Y] - RADIUS*sin(componentsBall[ANGLE] * (PI / 180));

                    break;
                default :

                    break;

            }

            break;
        case -1 :

            switch(DirY){

                case 1 :

                    impactPoints[0][X] = centerBall[X] + RADIUS*cos((PI+(componentsBall[ANGLE] * PI / 180)));
                    impactPoints[0][Y] = centerBall[Y] - RADIUS*sin((PI+(componentsBall[ANGLE] * PI / 180)));

                    break;
                case -1 :

                    impactPoints[0][X] = centerBall[X] + RADIUS*cos((PI-(componentsBall[ANGLE] * PI / 180)));
                    impactPoints[0][Y] = centerBall[Y] - RADIUS*sin((PI-(componentsBall[ANGLE] * PI / 180)));

                    break;
                default :

                    break;

            }

            break;
        default :

            break;
    }

    if(map[impactPoints[0][Y]/BLOCK_SIZE][impactPoints[0][X]/BLOCK_SIZE][TYPE] != VIDE){


        xMapHit = impactPoints[0][X]/BLOCK_SIZE;
        yMapHit = impactPoints[0][Y]/BLOCK_SIZE;

        if(map[yMapHit][xMapHit][TYPE] == METAL){
            switch (DirX){
                case 1 :
                    switch(DirY){
                        case 1 :
                            if( fabs(impactPoints[0][X] - ((impactPoints[0][X]/BLOCK_SIZE)*BLOCK_SIZE)) > fabs(impactPoints[0][Y] - ((impactPoints[0][Y]/BLOCK_SIZE)*BLOCK_SIZE)) )
                                componentsBall[DIRY] = -componentsBall[DIRY];
                            else
                                componentsBall[DIRX] = -componentsBall[DIRX];
                            break;

                        case -1 :
                            if( fabs(impactPoints[0][X] - ((impactPoints[0][X]/BLOCK_SIZE)*BLOCK_SIZE)) > fabs(impactPoints[0][Y] - (((impactPoints[0][Y]/BLOCK_SIZE)*BLOCK_SIZE))+ BLOCK_SIZE ) )
                                componentsBall[DIRY] = -componentsBall[DIRY];
                            else
                                componentsBall[DIRX] = -componentsBall[DIRX];
                            break;
                    }
                    break;
                case -1 :
                    switch(DirY){
                        case 1 :
                            if( fabs(impactPoints[0][X] - (((impactPoints[0][X]/BLOCK_SIZE)*BLOCK_SIZE))+ BLOCK_SIZE ) > fabs(impactPoints[0][Y] - ((impactPoints[0][Y]/BLOCK_SIZE)*BLOCK_SIZE)) )
                                componentsBall[DIRY] = -componentsBall[DIRY];
                            else
                                componentsBall[DIRX] = -componentsBall[DIRX];
                            break;
                        case -1 :
                            if( fabs(impactPoints[0][X] - (((impactPoints[0][X]/BLOCK_SIZE)*BLOCK_SIZE))+ BLOCK_SIZE) > fabs(impactPoints[0][Y] - (((impactPoints[0][Y]/BLOCK_SIZE)*BLOCK_SIZE))+ BLOCK_SIZE) )
                                componentsBall[DIRY] = -componentsBall[DIRY];
                            else
                                componentsBall[DIRX] = -componentsBall[DIRX];
                            break;
                    }
                    break;
            }

        }

        collision = true;

    }

    // LATERAL COLLISIONS

    int k;
    if(!collision){

        for(k = 2; k <= 20; k++){

            switch(DirX){
                case 1 :
                    switch(DirY){
                        case 1 :

                            impactPoints[1][X] = centerBall[X] + RADIUS*cos((-componentsBall[ANGLE] * PI / 180) + (PI / k));
                            impactPoints[1][Y] = centerBall[Y] - RADIUS*sin((-componentsBall[ANGLE] * PI / 180) + (PI / k));

                            break;
                        case -1 :

                            impactPoints[1][X] = centerBall[X] + RADIUS*cos((componentsBall[ANGLE] * PI / 180) + (PI / k));
                            impactPoints[1][Y] = centerBall[Y] - RADIUS*sin((componentsBall[ANGLE] * PI / 180) + (PI / k));

                            break;
                    }
                    break;
                case -1 :
                    switch(DirY){
                        case 1 :

                            impactPoints[1][X] = centerBall[X] + RADIUS*cos(((PI+(componentsBall[ANGLE] * PI / 180)) + (PI / k)));
                            impactPoints[1][Y] = centerBall[Y] - RADIUS*sin(((PI+(componentsBall[ANGLE] * PI / 180)) + (PI / k)));

                            break;
                        case -1 :

                            impactPoints[1][X] = centerBall[X] + RADIUS*cos(((PI-(componentsBall[ANGLE] * PI / 180)) + (PI / k)));
                            impactPoints[1][Y] = centerBall[Y] - RADIUS*sin(((PI-(componentsBall[ANGLE] * PI / 180)) + (PI / k)));

                            break;
                    }
                    break;
            }


            if(map[impactPoints[1][Y]/BLOCK_SIZE][impactPoints[1][X]/BLOCK_SIZE][TYPE] != VIDE){

                xMapHit = impactPoints[1][X]/BLOCK_SIZE;
                yMapHit = impactPoints[1][Y]/BLOCK_SIZE;

                if(map[yMapHit][xMapHit][TYPE] == METAL){
                    if( (componentsBall[DIRX] == 1 && componentsBall[DIRY] == 1) || (componentsBall[DIRX] == -1 && componentsBall[DIRY] == -1) )
                        componentsBall[DIRX] = -componentsBall[DIRX];
                    else
                        componentsBall[DIRY] = -componentsBall[DIRY];
                }

                collision = true;
                break;

            }

        }

    }

    if(!collision){

        for(k = 2; k <= 20; k++){

            switch(DirX){
                case 1 :
                    switch(DirY){
                        case 1 :

                            impactPoints[1][X] = centerBall[X] + RADIUS*cos((-componentsBall[ANGLE] * PI / 180) - (PI / k));
                            impactPoints[1][Y] = centerBall[Y] - RADIUS*sin((-componentsBall[ANGLE] * PI / 180) - (PI / k));

                            break;
                        case -1 :

                            impactPoints[1][X] = centerBall[X] + RADIUS*cos((componentsBall[ANGLE] * PI / 180) - (PI / k));
                            impactPoints[1][Y] = centerBall[Y] - RADIUS*sin((componentsBall[ANGLE] * PI / 180) - (PI / k));

                            break;
                    }
                    break;
                case -1 :
                    switch(DirY){
                        case 1 :

                            impactPoints[1][X] = centerBall[X] + RADIUS*cos(((PI+(componentsBall[ANGLE] * PI / 180)) - (PI / k)));
                            impactPoints[1][Y] = centerBall[Y] - RADIUS*sin(((PI+(componentsBall[ANGLE] * PI / 180)) - (PI / k)));

                            break;
                        case -1 :

                            impactPoints[1][X] = centerBall[X] + RADIUS*cos(((PI-(componentsBall[ANGLE] * PI / 180)) - (PI / k)));
                            impactPoints[1][Y] = centerBall[Y] - RADIUS*sin(((PI-(componentsBall[ANGLE] * PI / 180)) - (PI / k)));

                            break;
                    }
                    break;
            }

            if(map[impactPoints[1][Y]/BLOCK_SIZE][impactPoints[1][X]/BLOCK_SIZE][TYPE] != VIDE){

                xMapHit = impactPoints[1][X]/BLOCK_SIZE;
                yMapHit = impactPoints[1][Y]/BLOCK_SIZE;

                if(map[yMapHit][xMapHit][TYPE] == METAL){
                    if( (componentsBall[DIRX] == 1 && componentsBall[DIRY] == 1) || (componentsBall[DIRX] == -1 && componentsBall[DIRY] == -1) )
                        componentsBall[DIRY] = -componentsBall[DIRY];
                    else
                        componentsBall[DIRX] = -componentsBall[DIRX];
                }

                collision = true;
                break;

            }

        }

    }


    // Vortex collision
    if(map[yMapHit][xMapHit][TYPE] == TELEPORT){

        *resetCounter = 1;
        componentsBall[STATE] = VORTEXSTATE; //vortex state !

        int i = 0, j = 0;
        //we parse the map in order to find the vortex gate !
        for (i = 0; i < NB_BLOCK_Y; i++){

            for (j = 0; j < NB_BLOCK_X; j++){

                if ( map[i][j][TYPE] == TELEPORT && (i != yMapHit || j != xMapHit))
                {
                    componentsBall[YHIT] = i;
                    componentsBall[XHIT] = j;
                }

            }

        }


        map[yMapHit][xMapHit][TYPE] = VIDE; // remove the gate !
        playNoise(systemNoise, noises[VORTEXNOISE]);

    }

    // GEMSTONE OF AZURION (LEVEL 9 ONLY)
    else if(map[yMapHit][xMapHit][TYPE] == AZURIONPART )
    {
        map[yMapHit][xMapHit][TYPE] == VIDE;
        playNoise(systemNoise, noises[GEMSTONENOISE]);
        * won = 1;

    }

    // Metal collision
    else if(map[yMapHit][xMapHit][TYPE] == METAL)
    {

        SDL_Rect shieldCoord;
        // we blit the shield over the metal !
        shieldCoord.x = xMapHit*BLOCK_SIZE;
        shieldCoord.y = yMapHit*BLOCK_SIZE;
        SDL_BlitSurface(shield, NULL, screen, &shieldCoord);

        playNoise(systemNoise, noises[METALBOUNCE]);

        // if we hit many times an indestructible brick, we are maybe blocked ?
        componentsBall[LAST_IMPACT_TIME] = (componentsBall[LAST_IMPACT_TIME] == 0) ? SDL_GetTicks() : componentsBall[LAST_IMPACT_TIME];
        if( (SDL_GetTicks() - componentsBall[LAST_IMPACT_TIME]) > 8000 ){
            componentsBall[ANGLE] = ((componentsBall[ANGLE]-5) < 45) ? componentsBall[ANGLE]+5 : componentsBall[ANGLE]-5;
            componentsBall[LAST_IMPACT_TIME] = SDL_GetTicks();
        }

    }

    // Changing the type of brick
    else if(map[yMapHit][xMapHit][TYPE] != VIDE && map[yMapHit][xMapHit][TYPE] != METAL){

        //draw colapsing clouds
        SDL_Rect cloudCoord;
        cloudCoord.x = xMapHit*BLOCK_SIZE;
        cloudCoord.y = yMapHit*BLOCK_SIZE;
        SDL_BlitSurface(cloud, NULL, screen, &cloudCoord);

        map[yMapHit][xMapHit][TYPE] = VIDE;

        componentsBall[YHIT] = yMapHit;
        componentsBall[XHIT] = xMapHit;

        componentsBall[LAST_IMPACT_TIME] = 0;

        playNoise(systemNoise, noises[BOUNCE]);

    }

    return collision;

}

void checkPaddle_V2(float componentsBall[11], int componentsPaddle[6], int timeInit, FMOD_SYSTEM *systemNoise, FMOD_SOUND *noises[13], int* impactPaddle){

    float angleBall[2][2] = {NULL};
    angleBall[BL][X] = componentsBall[BALLX];
    angleBall[BL][Y] = componentsBall[BALLY] + 40;
    angleBall[BR][X] = componentsBall[BALLX] + 40;
    angleBall[BR][Y] = componentsBall[BALLY] + 40;

    int DirX = componentsBall[DIRX];
    int DirY = componentsBall[DIRY];

     //PADDLE

    if(componentsBall[STATE] == ALIVESTATE){

        if ( ( SDL_GetTicks() - timeInit ) >= 300 ){

            // Check Collision
            if(
                (
                    (
                        angleBall[BR][X] >= componentsPaddle[X]
                        &&
                        angleBall[BR][X] <= (componentsPaddle[X] + (componentsPaddle[HALFSIZE]*2))
                    )
                    ||
                    (
                        angleBall[BL][X] >= componentsPaddle[X]
                        &&
                        angleBall[BL][X] <= (componentsPaddle[X] + (componentsPaddle[HALFSIZE]*2))
                    )
                 )
                 &&
                    angleBall[BR][Y] >= componentsPaddle[Y] + 10
                 &&
                    angleBall[BR][Y] <= ( componentsPaddle[Y] + 15 )
            )
            {

                if(*impactPaddle == 0)
                    *impactPaddle = 1;

                playNoise(systemNoise, noises[PADDLEBOUNCE]);

                if (componentsPaddle[MODE] == WAITINGSTUCK)
                    componentsBall[STATE] = STUCKSTATE;

                if(DirX == 1)
                {

                    if( ( angleBall[BL][X] + RADIUS ) <= (componentsPaddle[X] + componentsPaddle[HALFSIZE]) ){
                        componentsBall[DIRX] = -componentsBall[DIRX];
                        componentsBall[DIRY] = -componentsBall[DIRY];
                        componentsBall[ANGLE] = ( ( 30 * ( angleBall[BR][X] - componentsPaddle[X] ) ) / componentsPaddle[HALFSIZE] ) + 30;
                    }else{
                        componentsBall[ANGLE] = ( ( -30 * ( angleBall[BL][X] - componentsPaddle[X] - componentsPaddle[HALFSIZE] ) ) / componentsPaddle[HALFSIZE] ) + 60;
                        componentsBall[DIRY] = -componentsBall[DIRY];
                    }

                }
                else
                {

                    if( ( angleBall[BR][X] - RADIUS ) >= (componentsPaddle[X] + componentsPaddle[HALFSIZE]) ){
                        componentsBall[DIRX] = -componentsBall[DIRX];
                        componentsBall[DIRY] = -componentsBall[DIRY];
                        componentsBall[ANGLE] = ( ( -30 * ( angleBall[BL][X] - componentsPaddle[X] - componentsPaddle[HALFSIZE] ) ) / componentsPaddle[HALFSIZE] ) + 60;
                    }else{
                        componentsBall[ANGLE] = ( ( 30 * ( angleBall[BR][X] - componentsPaddle[X] ) ) / componentsPaddle[HALFSIZE] ) + 30;
                        componentsBall[DIRY] = -componentsBall[DIRY];
                    }

                }

            }

        }

    }

}

void checkEndGame(int map[NB_BLOCK_Y][NB_BLOCK_X][4], int *won, FMOD_SYSTEM *systemNoise, FMOD_SOUND *noises[13]){

    int i = 0, j = 0, stillBricks = 0;

    for (i = 0; i < NB_BLOCK_Y; i++){

        for (j = 0; j < NB_BLOCK_X; j++){

            if(map[i][j][TYPE] == GREENBOX || map[i][j][TYPE] == BLUEBOX || map[i][j][TYPE] == REDBOX )
                stillBricks++;

        }


    }
    if (stillBricks==0)
        playNoise(systemNoise, noises[VICTORYNOISE]);

    *won = (stillBricks == 0) ? 1 : 0;

}

void checkBonus(SDL_Surface *screen, int powers[18][4], int componentsPaddle[6], FMOD_SYSTEM *systemNoise, FMOD_SOUND *noises[13]){

    int i, j;

    for(i = 0; i < NB_BLOCK_X*NB_BLOCK_Y; i++){


        // collision with bottom screen
        if(powers[i][Y] >= screen->h)
        {
            powers[i][3] = OFF;
        }

        // collision with paddle
        else if(
            (
                (
                    powers[i][X] + 30 >= componentsPaddle[X]
                    &&
                    powers[i][X] + 30 <= (componentsPaddle[X] + (componentsPaddle[HALFSIZE]*2))
                )

             )
             &&
                powers[i][Y] + 30 >= componentsPaddle[Y] + 10
             &&
                powers[i][3] == FALLING
        )
        {
            powers[i][3] = ON;
            powers[i][X] = 0;
            powers[i][Y] = 0;

            playNoise(systemNoise, noises[BONUSNOISE]);

            // if we active an INCPAD or DECPAD, we've to inactive invert bonus (DECPAD => inactive INCPAD) (INCPAD => inactive DECPAD)
            if(powers[i][2] == DECPAD){
                for(j = 0; j < NB_BLOCK_X*NB_BLOCK_Y; j++){
                    if(powers[j][2] == INCPAD && powers[j][3] == ON)
                        powers[j][3] = OFF;
                }
            }else if(powers[i][2] == INCPAD){
                for(j = 0; j < NB_BLOCK_X*NB_BLOCK_Y; j++){
                    if(powers[j][2] == DECPAD && powers[j][3] == ON)
                        powers[j][3] = OFF;
                }
            }

        }

    }

}

void checkRockets(int map[NB_BLOCK_Y][NB_BLOCK_X][4], SDL_Surface *screen, int rockets[3], SDL_Surface *explosion, int *won, FMOD_SYSTEM *systemNoise, FMOD_SOUND *noises[13]){

    if(map[rockets[Y]/BLOCK_SIZE][rockets[X]/BLOCK_SIZE][TYPE] != VIDE && map[rockets[Y]/BLOCK_SIZE][rockets[X]/BLOCK_SIZE][TYPE] != TELEPORT){

        // GEMSTONE OF AZURION (LEVEL 9 ONLY)
        if(map[rockets[Y]/BLOCK_SIZE][rockets[X]/BLOCK_SIZE][TYPE] == AZURIONPART )
        {
            map[rockets[Y]/BLOCK_SIZE][rockets[X]/BLOCK_SIZE][TYPE] = VIDE;
            playNoise(systemNoise, noises[GEMSTONENOISE]);
            * won = 1;
            rockets[2] = OFF;

        }
        else
        {
            map[rockets[Y]/BLOCK_SIZE][rockets[X]/BLOCK_SIZE][TYPE] = VIDE;
            rockets[2] = OFF;
            playNoise(systemNoise, noises[LASERNOISE]);
        }


        SDL_Rect explosionCoord;
        explosionCoord.x = rockets[X];
        explosionCoord.y = rockets[Y];
        SDL_BlitSurface(explosion, NULL, screen, &explosionCoord);

    }else if(rockets[Y] <= 100){
        rockets[2] = OFF;
    }

}
