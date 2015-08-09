#include "../load/load.h"

void loadBackgrounds(SDL_Surface *backgroundImg[9]){

    int i;
    for (i = 0; i < 9; i++)
    {
        char ichar[2];
        sprintf(ichar, "%d", i);
        char bgimgStr[100] = "images/Backgrounds/background";
        strcat(bgimgStr, ichar);
        strcat(bgimgStr, ".jpg");
        backgroundImg[i] = loadImageOptimised(bgimgStr);
    }

}

void loadStory(SDL_Surface *screen, FMOD_SYSTEM *system, FMOD_SOUND *music){

    int i;
    SDL_ShowCursor(SDL_DISABLE);
    SDL_WarpMouse(screen->w/2, screen->h/2);

    SDL_Surface *intro = {NULL};
    SDL_Rect frameCoord;
    frameCoord.x = 0;
    frameCoord.y = 0;

    SDL_Surface *frames[7] = {NULL};

    for(i = 0; i < 7; i++){
        //story BlackCrew
        char pathImage[100] = "images/Cinematics/story/";
        char imageRank[2] = "";

        sprintf(imageRank, "%d", i);
        strcat(pathImage, imageRank);
        strcat(pathImage, ".jpg");
        frames[i] = loadImageOptimised(pathImage);
    }

    playSound(system, music, "soundtracks/story.mp3", 0);

    for(i = 0; i < 5; i++){
        SDL_BlitSurface(frames[i], NULL, screen, &frameCoord);
        SDL_Flip(screen);
        SDL_Delay(14000);
    }
    SDL_BlitSurface(frames[5], NULL, screen, &frameCoord);
    SDL_Flip(screen);
    SDL_Delay(1000);
    SDL_BlitSurface(frames[6], NULL, screen, &frameCoord);
    SDL_Flip(screen);
    SDL_Delay(1000);
    /* MOUSE AND KEYBOARD CONFIGURATION */
    SDL_ShowCursor(SDL_ENABLE);
    SDL_WarpMouse(screen->w/2, screen->h/2);
    SDL_EnableKeyRepeat(10,10);



}

void loadIntro(SDL_Surface *screen, FMOD_SYSTEM *system, FMOD_SOUND *music){

    int i;
    SDL_ShowCursor(SDL_DISABLE);
    SDL_WarpMouse(screen->w/2, screen->h/2);

    SDL_Surface *intro = {NULL};
    SDL_Rect frameCoord;
    frameCoord.x = 0;
    frameCoord.y = 0;

    SDL_Surface *frames[26] = {NULL};

    for(i = 0; i < 26; i++){
        //intro BlackCrew
        char pathImage[100] = "images/Cinematics/logo/";
        char imageRank[2] = "";

        sprintf(imageRank, "%d", i);
        strcat(pathImage, imageRank);
        strcat(pathImage, ".jpeg");
        frames[i] = loadImageOptimised(pathImage);
    }

    playSound(system, music, "sounds/intro.mp3", 0);

    for(i = 0; i < 26; i++){
        SDL_BlitSurface(frames[i], NULL, screen, &frameCoord);
        SDL_Flip(screen);
        SDL_Delay(30);
    }

    SDL_Delay(5000);

}

void loadBonus(SDL_Surface *bonus[19]){

    bonus[INCPAD] = IMG_Load("images/Powers/incpaddle.png");
    bonus[DECPAD] = IMG_Load("images/Powers/decpaddle.png");
    bonus[INCSPEED] = IMG_Load("images/Powers/incspeed.png");
    bonus[DECSPEED] = IMG_Load("images/Powers/decspeed.png");
    bonus[MAGNETBALL] = IMG_Load("images/Powers/magnetball.png");
    bonus[DOUBLEBALL] = IMG_Load("images/Powers/doubleball.png");
    bonus[FIREBALL] = IMG_Load("images/Powers/fireball.png");
    bonus[LASER] = IMG_Load("images/Powers/laser.png");
    bonus[DEATH] = IMG_Load("images/Powers/death.png");
    bonus[LIFE] = IMG_Load("images/Powers/life.png");
    bonus[AZURITE2] = IMG_Load("images/Powers/azurite2.png");
    bonus[AZURITE3] = IMG_Load("images/Powers/azurite3.png");
    bonus[AZURITE4] = IMG_Load("images/Powers/azurite4.png");
    bonus[AZURITE5] = IMG_Load("images/Powers/azurite5.png");
    bonus[AZURITE6] = IMG_Load("images/Powers/azurite6.png");
    bonus[AZURITE7] = IMG_Load("images/Powers/azurite7.png");
    bonus[AZURITE8] = IMG_Load("images/Powers/azurite8.png");
    bonus[AZURITE9] = IMG_Load("images/Powers/azurite9.png");

}

void loadButtons(SDL_Surface *buttons[10]){

    buttons[PLAY] = IMG_Load("images/Assets/buttons/play.png");
    buttons[PLAYINVERT] = IMG_Load("images/Assets/buttons/playinvert.png");
    buttons[QUIT] = IMG_Load("images/Assets/buttons/quit.png");
    buttons[QUITINVERT] = IMG_Load("images/Assets/buttons/quitinvert.png");
    buttons[GARAGE] = IMG_Load("images/Assets/buttons/garage.png");
    buttons[GARAGEINVERT] = IMG_Load("images/Assets/buttons/garageinvert.png");
    buttons[MUTE] = IMG_Load("images/Assets/buttons/mute.png");
    buttons[MUTEINVERT] = IMG_Load("images/Assets/buttons/muteinvert.png");
    buttons[SWITCHON] = IMG_Load("images/Assets/buttons/switchon.png");
    buttons[SWITCHOFF] = IMG_Load("images/Assets/buttons/switchoff.png");

}

void loadButtonsGarage(SDL_Surface *buttonsGarage[23]){

    buttonsGarage[LEFT] = IMG_Load("images/Assets/buttons/left.png");
    buttonsGarage[LEFTINVERT] = IMG_Load("images/Assets/buttons/leftinvert.png");
    buttonsGarage[RIGHT] = IMG_Load("images/Assets/buttons/right.png");
    buttonsGarage[RIGHTINVERT] = IMG_Load("images/Assets/buttons/rightinvert.png");
    buttonsGarage[HOME] = IMG_Load("images/Assets/buttons/home.png");
    buttonsGarage[HOMEINVERT] = IMG_Load("images/Assets/buttons/homeinvert.png");
    buttonsGarage[ESC] = IMG_Load("images/Assets/buttons/esc.png");
    buttonsGarage[ESCINVERT] = IMG_Load("images/Assets/buttons/escinvert.png");
    buttonsGarage[RESET] = IMG_Load("images/Assets/buttons/reset.png");
    buttonsGarage[RESETINVERT] = IMG_Load("images/Assets/buttons/resetinvert.png");
    buttonsGarage[REPLAY] = IMG_Load("images/Assets/buttons/replay.png");
    buttonsGarage[REPLAYINVERT] = IMG_Load("images/Assets/buttons/replayinvert.png");
    buttonsGarage[LEFTWORLD] = IMG_Load("images/Assets/buttons/left.png");
    buttonsGarage[LEFTWORLDINVERT] = IMG_Load("images/Assets/buttons/leftinvert.png");
    buttonsGarage[RIGHTWORLD] = IMG_Load("images/Assets/buttons/right.png");
    buttonsGarage[RIGHTWORLDINVERT] = IMG_Load("images/Assets/buttons/rightinvert.png");
    buttonsGarage[LEFTLEVEL] = IMG_Load("images/Assets/buttons/left.png");
    buttonsGarage[LEFTLEVELINVERT] = IMG_Load("images/Assets/buttons/leftinvert.png");
    buttonsGarage[RIGHTLEVEL] = IMG_Load("images/Assets/buttons/right.png");
    buttonsGarage[RIGHTLEVELINVERT] = IMG_Load("images/Assets/buttons/rightinvert.png");
    buttonsGarage[PLAYINTRO] = IMG_Load("images/Assets/buttons/intro.png");
    buttonsGarage[PLAYINTROINVERT] = IMG_Load("images/Assets/buttons/introinvert.png");
    buttonsGarage[BOUGHT] = IMG_Load("images/Shop/bought.png");
}

void loadGarage(SDL_Surface *screen, int *menu, bool *done, SDL_Surface *numbers[10], int *world, int *level, int *difficulty, int *azurites, FMOD_SYSTEM *system, FMOD_SOUND *music, bool powersShop[8]){

    /* LOAD BUTTONS */
    SDL_Surface *buttonsGarage[23] = {NULL};
    loadButtonsGarage(buttonsGarage);


    int worldReplay = *world, levelReplay = *level;
    int buttonActionGarage[11] = {NULL};
    int mouseX = 0, mouseY = 0;
    int i;


    /* GARAGE BAY BACKGROUND */
    SDL_Surface *garagebay;
    garagebay = loadImageOptimised("images/Backgrounds/garagebay.jpg");


    SDL_Rect backgroundCoord;
    backgroundCoord.x = 0;
    backgroundCoord.y = 0;

    SDL_Rect numbersCoord;
    SDL_Rect buttonsCoord;

    /* GARAGE LOOP */
    bool over = false;
    while (!over)
    {

        /* we draw the background */
        SDL_BlitSurface(garagebay, NULL, screen, &backgroundCoord);

        /* display difficulty */
        numbersCoord.x = 960;
        numbersCoord.y = 330;
        SDL_BlitSurface(numbers[*difficulty], NULL, screen, &numbersCoord);

        /* display world & level */
        numbersCoord.x = 1320;
        SDL_BlitSurface(numbers[*world], NULL, screen, &numbersCoord);
        numbersCoord.x = 1505;
        SDL_BlitSurface(numbers[*level], NULL, screen, &numbersCoord);

        /* display replay */
        numbersCoord.x = 210;
        numbersCoord.y = 560;
        SDL_BlitSurface(numbers[worldReplay], NULL, screen, &numbersCoord);
        numbersCoord.y = 660;
        SDL_BlitSurface(numbers[levelReplay], NULL, screen, &numbersCoord);

        // display azurites coins
        numbersCoord.x = 140;
        numbersCoord.y = 30;
        SDL_BlitSurface(numbers[(*azurites/1000)%10], NULL, screen, &numbersCoord); //thousand
        numbersCoord.x = 180;
        SDL_BlitSurface(numbers[(*azurites/100)%10], NULL, screen, &numbersCoord); //hundred
        numbersCoord.x = 220;
        SDL_BlitSurface(numbers[(*azurites/10)%10], NULL, screen, &numbersCoord); //ten
        numbersCoord.x = 260;
        SDL_BlitSurface(numbers[*azurites%10], NULL, screen, &numbersCoord); //unit



        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                // exit if the window is closed
                case SDL_QUIT:
                    *done = true;
                    break;

                //mouse pressed
                case SDL_MOUSEBUTTONDOWN:

                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        mouseX = event.button.x;
                        mouseY = event.button.y;
                        checkButtonGarage(mouseX,mouseY,PRESSED,buttonActionGarage);
                    }
                    break;

                //mouse released
                case SDL_MOUSEBUTTONUP:

                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        mouseX = event.button.x;
                        mouseY = event.button.y;
                        checkButtonGarage(mouseX,mouseY,RELEASED,buttonActionGarage);
                    }
                    break;

                 default:
                    continue;
                    break;
            }
        }


        /* we draw the buttonsGarage */

        //left
        buttonsCoord.x = 890;
        buttonsCoord.y = 330;
        (buttonActionGarage[LEFT] == PRESSED) ? SDL_BlitSurface(buttonsGarage[LEFTINVERT], NULL, screen, &buttonsCoord) : SDL_BlitSurface(buttonsGarage[LEFT], NULL, screen, &buttonsCoord);

        //right
        buttonsCoord.x = 1020;
        (buttonActionGarage[RIGHT] == PRESSED) ? SDL_BlitSurface(buttonsGarage[RIGHTINVERT], NULL, screen, &buttonsCoord) : SDL_BlitSurface(buttonsGarage[RIGHT], NULL, screen, &buttonsCoord);

        //left replay world
        buttonsCoord.x = 110;
        buttonsCoord.y = 560;
        (buttonActionGarage[LEFTWORLD] == PRESSED) ? SDL_BlitSurface(buttonsGarage[LEFTWORLDINVERT], NULL, screen, &buttonsCoord) : SDL_BlitSurface(buttonsGarage[LEFTWORLD], NULL, screen, &buttonsCoord);

        //right replay world
        buttonsCoord.x = 300;
        (buttonActionGarage[RIGHTWORLD] == PRESSED) ? SDL_BlitSurface(buttonsGarage[RIGHTWORLDINVERT], NULL, screen, &buttonsCoord) : SDL_BlitSurface(buttonsGarage[RIGHTWORLD], NULL, screen, &buttonsCoord);

         //left replay level
        buttonsCoord.x = 110;
        buttonsCoord.y = 660;
        (buttonActionGarage[LEFTLEVEL] == PRESSED) ? SDL_BlitSurface(buttonsGarage[LEFTLEVELINVERT], NULL, screen, &buttonsCoord) : SDL_BlitSurface(buttonsGarage[LEFTLEVEL], NULL, screen, &buttonsCoord);

         // right replay level
        buttonsCoord.x = 300;
        (buttonActionGarage[RIGHTLEVEL] == PRESSED) ? SDL_BlitSurface(buttonsGarage[RIGHTLEVELINVERT], NULL, screen, &buttonsCoord) : SDL_BlitSurface(buttonsGarage[RIGHTLEVEL], NULL, screen, &buttonsCoord);

        // replay
        buttonsCoord.x = 180;
        buttonsCoord.y = 730;
        (buttonActionGarage[REPLAY] == PRESSED) ? SDL_BlitSurface(buttonsGarage[REPLAYINVERT], NULL, screen, &buttonsCoord) : SDL_BlitSurface(buttonsGarage[REPLAY], NULL, screen, &buttonsCoord);

        // playintro
        buttonsCoord.x = 310;
        buttonsCoord.y = screen->h - 150;
        (buttonActionGarage[PLAYINTRO] == PRESSED) ? SDL_BlitSurface(buttonsGarage[PLAYINTROINVERT], NULL, screen, &buttonsCoord) : SDL_BlitSurface(buttonsGarage[PLAYINTRO], NULL, screen, &buttonsCoord);

        //home
        buttonsCoord.x = 50;
        (buttonActionGarage[HOME] == PRESSED) ? SDL_BlitSurface(buttonsGarage[HOMEINVERT], NULL, screen, &buttonsCoord) : SDL_BlitSurface(buttonsGarage[HOME], NULL, screen, &buttonsCoord);

        //reset
        buttonsCoord.x = 180;
        (buttonActionGarage[RESET] == PRESSED) ? SDL_BlitSurface(buttonsGarage[RESETINVERT], NULL, screen, &buttonsCoord) : SDL_BlitSurface(buttonsGarage[RESET], NULL, screen, &buttonsCoord);

        //esc
        buttonsCoord.x = 1500;
        (buttonActionGarage[ESC] == PRESSED) ? SDL_BlitSurface(buttonsGarage[ESCINVERT], NULL,  screen, &buttonsCoord) : SDL_BlitSurface(buttonsGarage[ESC], NULL, screen, &buttonsCoord);


        /* we execute the buttonsGarage ! */
        if (buttonActionGarage[LEFT] == RELEASED) //left - decrease difficulty
        {
            playSound(system, music, "sounds/buttonmute.mp3", 0);
            *difficulty = (*difficulty < 2) ? 1 : *difficulty - 1;
            saveBackUp(*world, *level, *azurites, *difficulty);

            buttonActionGarage[LEFT] = NONE;
        }

        else if (buttonActionGarage[RIGHT] == RELEASED)  //right + increase difficulty
        {
            playSound(system, music, "sounds/buttonmute.mp3", 0);
            *difficulty = (*difficulty > 4) ? 5 : *difficulty + 1;
            saveBackUp(*world, *level, *azurites, *difficulty);

            buttonActionGarage[RIGHT] = NONE;
        }

        else if (buttonActionGarage[HOME] == RELEASED)  //home
        {
            stopSound(system);
            playSound(system, music, "sounds/buttongarage.mp3", 0);
            playSound(system, music, "sounds/endlerzik.mp3", -1);
            *menu = 0;
            over = true;
            buttonActionGarage[HOME] = NONE;
        }

        else if (buttonActionGarage[ESC] == RELEASED)  //esc
        {
            *done = true;
            over = true;
            buttonActionGarage[ESC] = NONE;
        }
        else if (buttonActionGarage[PLAYINTRO] == RELEASED)  //playintro
        {
            playSound(system, music, "sounds/buttongarage.mp3", 0);
            stopSound(system);
            loadStory(screen, system, music);
            buttonActionGarage[PLAYINTRO] = NONE;
        }
        else if (buttonActionGarage[RESET] == RELEASED)  //reset the game !
        {
            checkReset(screen, azurites, world, level, &worldReplay, &levelReplay, difficulty, system, music);
            buttonActionGarage[RESET] = NONE;
        }
        else if (buttonActionGarage[LEFTWORLD] == RELEASED)  //leftworld
        {
            worldReplay = (worldReplay < 2) ? 1 : worldReplay - 1;
            playSound(system, music, "sounds/buttonmute.mp3", 0);
            buttonActionGarage[LEFTWORLD] = NONE;
        }
        else if (buttonActionGarage[RIGHTWORLD] == RELEASED)  //rightworld
        {
            worldReplay = (worldReplay < *world) ? worldReplay + 1 : *world;
            levelReplay = (worldReplay == *world && levelReplay > *level) ? *level : levelReplay;
            playSound(system, music, "sounds/buttonmute.mp3", 0);
            buttonActionGarage[RIGHTWORLD] = NONE;
        }
        else if (buttonActionGarage[LEFTLEVEL] == RELEASED)  //leftlevel
        {
            levelReplay = (levelReplay < 2) ? 1 : levelReplay - 1;
            playSound(system, music, "sounds/buttonmute.mp3", 0);
            buttonActionGarage[LEFTLEVEL] = NONE;
        }
        else if (buttonActionGarage[RIGHTLEVEL] == RELEASED)  //rightlevel
        {
            levelReplay = (worldReplay == *world) ? (levelReplay < *level) ? levelReplay + 1 : *level : (levelReplay > 8) ? 9 : levelReplay + 1;
            playSound(system, music, "sounds/buttonmute.mp3", 0);
            buttonActionGarage[RIGHTLEVEL] = NONE;
        }
        else if (buttonActionGarage[REPLAY] == RELEASED)  //replay
        {
            playSound(system, music, "sounds/buttonplay.mp3", 0);
            stopSound(system);
            shufflemusic(system, music);
            buttonActionGarage[REPLAY] = NONE;
            play(screen, &worldReplay, &levelReplay, azurites, difficulty, powersShop);
            stopSound(system);
            playSound(system, music, "soundtracks/endlerzik.mp3", -1);
            SDL_EnableKeyRepeat(10,10);
            SDL_ShowCursor(SDL_ENABLE);
        }


        /* we buy elements from the shop*/
        //MAGNET, MAGNETINF, HEART, PADDLEINC, CLONEBALL, CLONEBALLINF, SPEEDMIN, REDBALL, BONUSSHOP


        if ( mouseX > 65 && mouseX < 430 && mouseY > 195 && mouseY < 250 )
        {
            if (powersShop[MAGNET] == false)
            {
                if (*azurites < 50)
                {
                    playSound(system, music, "sounds/notenough.mp3", 0);
                    mouseX = 0;
                    mouseY = 0;
                }
                else
                {
                    playSound(system, music, "sounds/bought.mp3", 0);
                    powersShop[MAGNET] = true;
                    *azurites = *azurites - 50;
                    saveBackUp(*world, *level, *azurites, *difficulty);
                }


            }
        }

       if (powersShop[MAGNET] == true)
       {
            buttonsCoord.x = 80;
            buttonsCoord.y = 195;
            SDL_BlitSurface(buttonsGarage[BOUGHT], NULL, screen, &buttonsCoord);
       }

       if ( mouseX > 65 && mouseX < 430 && mouseY > 250 && mouseY < 310 )
        {
            if (powersShop[MAGNETINF] == false)
            {
                if (*azurites < 80)
                {
                    playSound(system, music, "sounds/notenough.mp3", 0);
                    mouseX = 0;
                    mouseY = 0;
                }
                else
                {
                    playSound(system, music, "sounds/bought.mp3", 0);
                    powersShop[MAGNETINF] = true;
                    *azurites = *azurites - 80;
                    saveBackUp(*world, *level, *azurites, *difficulty);
                }


            }
        }

       if (powersShop[MAGNETINF] == true)
       {
            buttonsCoord.x = 80;
            buttonsCoord.y = 255;
            SDL_BlitSurface(buttonsGarage[BOUGHT], NULL, screen, &buttonsCoord);
       }

       if ( mouseX > 65 && mouseX < 430 && mouseY > 310 && mouseY < 375 )
        {
            if (powersShop[HEART] == false)
            {
                if (*azurites < 40)
                {
                    playSound(system, music, "sounds/notenough.mp3", 0);
                    mouseX = 0;
                    mouseY = 0;
                }
                else
                {
                    playSound(system, music, "sounds/bought.mp3", 0);
                    powersShop[HEART] = true;
                    *azurites = *azurites - 40;
                    saveBackUp(*world, *level, *azurites, *difficulty);
                }


            }
        }

       if (powersShop[HEART] == true)
       {
            buttonsCoord.x = 80;
            buttonsCoord.y = 315;
            SDL_BlitSurface(buttonsGarage[BOUGHT], NULL, screen, &buttonsCoord);
       }

       if ( mouseX > 65 && mouseX < 430 && mouseY > 375 && mouseY < 430 )
        {
            if (powersShop[PADDLEINC] == false)
            {
                if (*azurites < 70)
                {
                    playSound(system, music, "sounds/notenough.mp3", 0);
                    mouseX = 0;
                    mouseY = 0;
                }
                else
                {
                    playSound(system, music, "sounds/bought.mp3", 0);
                    powersShop[PADDLEINC] = true;
                    *azurites = *azurites - 70;
                    saveBackUp(*world, *level, *azurites, *difficulty);
                }


            }
        }

       if (powersShop[PADDLEINC] == true)
       {
            buttonsCoord.x = 80;
            buttonsCoord.y = 375;
            SDL_BlitSurface(buttonsGarage[BOUGHT], NULL, screen, &buttonsCoord);
       }

       if ( mouseX > 430 && mouseX < 780 && mouseY > 195 && mouseY < 250 )
        {
            if (powersShop[CLONEBALL] == false)
            {
                if (*azurites < 150)
                {
                    playSound(system, music, "sounds/notenough.mp3", 0);
                    mouseX = 0;
                    mouseY = 0;
                }
                else
                {
                    playSound(system, music, "sounds/bought.mp3", 0);
                    powersShop[CLONEBALL] = true;
                    *azurites = *azurites - 150;
                    saveBackUp(*world, *level, *azurites, *difficulty);
                }


            }
        }

       if (powersShop[CLONEBALL] == true)
       {
            buttonsCoord.x = 433;
            buttonsCoord.y = 195;
            SDL_BlitSurface(buttonsGarage[BOUGHT], NULL, screen, &buttonsCoord);
       }

       if ( mouseX > 430 && mouseX < 780 && mouseY > 250 && mouseY < 310 )
        {
            if (powersShop[CLONEBALLINF] == false)
            {
                if (*azurites < 200)
                {
                    playSound(system, music, "sounds/notenough.mp3", 0);
                    mouseX = 0;
                    mouseY = 0;
                }
                else
                {
                    playSound(system, music, "sounds/bought.mp3", 0);
                    powersShop[CLONEBALLINF] = true;
                    *azurites = *azurites - 200;
                    saveBackUp(*world, *level, *azurites, *difficulty);
                }


            }
        }

       if (powersShop[CLONEBALLINF] == true)
       {
            buttonsCoord.x = 433;
            buttonsCoord.y = 255;
            SDL_BlitSurface(buttonsGarage[BOUGHT], NULL, screen, &buttonsCoord);
       }

       if ( mouseX > 430 && mouseX < 780 && mouseY > 310 && mouseY < 375 )
        {
            if (powersShop[SPEEDMIN] == false)
            {
                if (*azurites < 120)
                {
                    playSound(system, music, "sounds/notenough.mp3", 0);
                    mouseX = 0;
                    mouseY = 0;
                }
                else
                {
                    playSound(system, music, "sounds/bought.mp3", 0);
                    powersShop[SPEEDMIN] = true;
                    *azurites = *azurites - 120;
                    saveBackUp(*world, *level, *azurites, *difficulty);
                }


            }
        }

       if (powersShop[SPEEDMIN] == true)
       {
            buttonsCoord.x = 433;
            buttonsCoord.y = 315;
            SDL_BlitSurface(buttonsGarage[BOUGHT], NULL, screen, &buttonsCoord);
       }

       if ( mouseX > 430 && mouseX < 780 && mouseY > 375 && mouseY < 430 )
        {
            if (powersShop[REDBALL] == false)
            {
                if (*azurites < 100)
                {
                    playSound(system, music, "sounds/notenough.mp3", 0);
                    mouseX = 0;
                    mouseY = 0;
                }
                else
                {
                    playSound(system, music, "sounds/bought.mp3", 0);
                    powersShop[REDBALL] = true;
                    *azurites = *azurites - 100;
                    saveBackUp(*world, *level, *azurites, *difficulty);
                }


            }
        }

       if (powersShop[REDBALL] == true)
       {
            buttonsCoord.x = 433;
            buttonsCoord.y = 375;
            SDL_BlitSurface(buttonsGarage[BOUGHT], NULL, screen, &buttonsCoord);
       }



        SDL_Flip(screen);

    }

}

void loadGame(SDL_Surface *screen, bool powersShop[8]){

    int world, level, azurites, difficulty;

    loadBackUp(&world, &level, &azurites, &difficulty);
    play(screen, &world, &level, &azurites, &difficulty, powersShop);
    saveBackUp(world, level, azurites, difficulty);

}

void loadBackUp(int *world, int *level, int *azurites, int* difficulty){

    int t, h, d, u;

    FILE* file = NULL;
    file = fopen("player/backup.txt", "r");

    fscanf(file, "%d", world);
    fscanf(file, "%d", level);
    fscanf(file, "%d", difficulty);
    fscanf(file, "%d", &t);
    fscanf(file, "%d", &h);
    fscanf(file, "%d", &d);
    fscanf(file, "%d", &u);

    fclose(file);

    *azurites = u + 10*d + 100*h + 1000*t;

}

void saveBackUp(int world, int level, int azurites, int difficulty){

    FILE* file = NULL;
    file = fopen("player/backup.txt", "w");

    fprintf(file, "%d", world);
    fprintf(file, " ");
    fprintf(file, "%d", level);
    fprintf(file, " ");
    fprintf(file, "%d", difficulty);
    fprintf(file, " ");

    int t = azurites/1000, h = (azurites - t*1000)/100, d = (azurites - t*1000 - h*100)/10, u = (azurites - t*1000 - h*100 - d*10);
    fprintf(file, "%d", t);
    fprintf(file, " ");
    fprintf(file, "%d", h);
    fprintf(file, " ");
    fprintf(file, "%d", d);
    fprintf(file, " ");
    fprintf(file, "%d", u);
    fprintf(file, " ");

    fclose(file);

}

void loadSprites(SDL_Surface *sprites[31], SDL_Surface *speedImg[4], SDL_Surface *bonusShop[9], int world){

    char worldStringFormat[10];
    sprintf(worldStringFormat, "%d", world);

    char background[100] = "images/Planets/";
    strcat(background, worldStringFormat);
    strcat(background, ".jpg");

    char intro[100] = "images/Cinematics/intro/";
    strcat(intro, worldStringFormat);
    strcat(intro, ".jpg");

    char conclusion[100] = "images/Cinematics/win/";
    strcat(conclusion, worldStringFormat);
    strcat(conclusion, ".jpg");

    char locationBoxes[4][100] = {
        "images/Bricks/",
        "images/Bricks/",
        "images/Bricks/",
        "images/Bricks/"
    };

    strcat(locationBoxes[0], worldStringFormat);
    strcat(locationBoxes[0], "/greenbox.png");
    strcat(locationBoxes[1], worldStringFormat);
    strcat(locationBoxes[1], "/bluebox.png");
    strcat(locationBoxes[2], worldStringFormat);
    strcat(locationBoxes[2], "/redbox.png");
    strcat(locationBoxes[3], worldStringFormat);
    strcat(locationBoxes[3], "/metal.png");

    sprites[GREENBOX] = loadImageOptimised(locationBoxes[0]);
    sprites[BLUEBOX] = loadImageOptimised(locationBoxes[1]);
    sprites[REDBOX] = loadImageOptimised(locationBoxes[2]);
    sprites[METAL] = loadImageOptimised(locationBoxes[3]);
    if (world == 8)
    {
        sprites[GREENBOX] = IMG_Load("images/Bricks/8/greenbox.png");
        sprites[BLUEBOX] = IMG_Load("images/Bricks/8/bluebox.png");
        sprites[REDBOX] = IMG_Load("images/Bricks/8/redbox.png");
        sprites[METAL] = IMG_Load("images/Bricks/8/metal.png");
    }
    sprites[TELEPORT] = loadImageOptimised("images/Bricks/metalshield.png"); // cheat : keep TELEPORT ENUM due to use in renderMap() as an int, but we don't use it as a sprite (V1-9), used for metalshield  to avoid unused space
    sprites[AZURIONPART] = loadImageOptimised("images/Bricks/azurionpart.png");
    sprites[V1] = loadImageOptimised("images/Bricks/vortex/1.png");
    sprites[V2] = loadImageOptimised("images/Bricks/vortex/2.png");
    sprites[V3] = loadImageOptimised("images/Bricks/vortex/3.png");
    sprites[V4] = loadImageOptimised("images/Bricks/vortex/4.png");
    sprites[V5] = loadImageOptimised("images/Bricks/vortex/5.png");
    sprites[V6] = loadImageOptimised("images/Bricks/vortex/6.png");
    sprites[V7] = loadImageOptimised("images/Bricks/vortex/7.png");
    sprites[V8] = loadImageOptimised("images/Bricks/vortex/8.png");
    sprites[V9] = loadImageOptimised("images/Bricks/vortex/9.png");
    sprites[CLOUD] = IMG_Load("images/Bricks/cloud.png");
    sprites[BACKGROUND] = loadImageOptimised(background);
    sprites[INTRO] = loadImageOptimised(intro);
    sprites[CONCLUSION] = loadImageOptimised(conclusion);
    sprites[SMALLPADDLE] = IMG_Load("images/Assets/paddle/paddlesmall.png");
    sprites[MEDIUMPADDLE] = IMG_Load("images/Assets/paddle/paddlemedium.png");
    sprites[LARGEPADDLE] = IMG_Load("images/Assets/paddle/paddlelarge.png");
    sprites[GAMEOVER] = IMG_Load("images/Assets/other/gameover.png");
    sprites[WON] = IMG_Load("images/Assets/other/won.png");
    sprites[PAUSE] = IMG_Load("images/Assets/other/pause.png");
    sprites[P1] = IMG_Load("images/Assets/other/1.png");
    sprites[P2] = IMG_Load("images/Assets/other/2.png");
    sprites[P3] = IMG_Load("images/Assets/other/3.png");
    sprites[GO] = IMG_Load("images/Assets/other/4.png");
    sprites[EXPLOSION] = IMG_Load("images/Bricks/explosion.png");

    speedImg[SPEEDBAR] = loadImageOptimised("images/Assets/speed/speed.png");
    speedImg[SPEEDBARINVERT] = loadImageOptimised("images/Assets/speed/speedinvert.png");
    speedImg[SPEEDBARMIN] = loadImageOptimised("images/Assets/speed/speedmin.png");
    speedImg[SPEEDBARMAX] = loadImageOptimised("images/Assets/speed/speedmax.png");

    bonusShop[MAGNET] = IMG_Load("images/Shop/0.png");
    bonusShop[MAGNETINF] = IMG_Load("images/Shop/1.png");
    bonusShop[HEART] = IMG_Load("images/Shop/2.png");
    bonusShop[PADDLEINC] = IMG_Load("images/Shop/3.png");
    bonusShop[CLONEBALL] = IMG_Load("images/Shop/4.png");
    bonusShop[CLONEBALLINF] = IMG_Load("images/Shop/5.png");
    bonusShop[SPEEDMIN] = IMG_Load("images/Shop/6.png");
    bonusShop[REDBALL] = IMG_Load("images/Shop/7.png");
    bonusShop[BONUSSHOP] = IMG_Load("images/Shop/shopbonus.png");

}

void loadEnd(SDL_Surface *screen){
    SDL_Surface *theend[4];
    SDL_Rect endCoord;
    endCoord.x = 0;
    endCoord.y = 0;
    int i=0;
    for (i=0 ; i<4 ; i++)
    {
        char ichar[3];
        sprintf(ichar, "%d", i);
        char nbimgStr[50] = "images/Cinematics/end/";
        strcat(nbimgStr, ichar);
        strcat(nbimgStr, ".jpg");
        theend[i] = loadImageOptimised(nbimgStr);
        SDL_BlitSurface(theend[i], NULL, screen, &endCoord);
        SDL_Flip(screen);
        SDL_Delay(5000); //TIME FOR EACH END IMAGE
    }

}

void loadNumbers(SDL_Surface *numbers[10]){
    int i=0;
    for (i=0 ; i<=9 ; i++)
    {
        char ichar[3];
        sprintf(ichar, "%d", i);
        char nbimgStr[50] = "images/Numbers/";
        strcat(nbimgStr, ichar);
        strcat(nbimgStr, ".png");
        numbers[i] = IMG_Load(nbimgStr);
    }
}

void loadBalls(SDL_Surface *balls[40]){

    int i=0;
    for (i=0 ; i<40 ; i++)
    {
        char ichar[3];
        sprintf(ichar, "%d", i);
        char ballimgStr[50] = "images/Assets/iceball/";
        strcat(ballimgStr, ichar);
        strcat(ballimgStr, ".png");
        balls[i] = IMG_Load(ballimgStr);
    }
}

void loadBallsFire(SDL_Surface *ballsFire[27]){

    int i=0;
    for (i=0 ; i<27 ; i++)
    {
        char ichar[3];
        sprintf(ichar, "%d", i);
        char ballimgStr[50] = "images/Assets/fireball/";
        strcat(ballimgStr, ichar);
        strcat(ballimgStr, ".png");
        ballsFire[i] = IMG_Load(ballimgStr);
    }
}

void loadMap(int map[NB_BLOCK_Y][NB_BLOCK_X][4], int powers[18][4], int world, int lvl){

    FILE* file = NULL;
    int i = 0, j = 0;
    char worldStr[10], lvlStr[10];
    sprintf(worldStr, "%d", world);
    sprintf(lvlStr, "%d", lvl);
    char mapName[100] = "maps/map_w";
    strcat(mapName, worldStr);
    strcat(mapName, "_l");
    strcat(mapName, lvlStr);
    strcat(mapName, ".txt");
    file = fopen(mapName, "r");

    fseek (file, 0, SEEK_SET);

    int indexPower = 0;

    for (i = 0; i < NB_BLOCK_Y; i++){
        for (j = 0; j < NB_BLOCK_X; j++){

            fscanf(file, "%d", &map[i][j][TYPE]);
            fscanf(file, "%d", &map[i][j][POWER]);
            fscanf(file, "%d", &map[i][j][AZURITE]);

            if(map[i][j][POWER] > 0){
                powers[indexPower][X] = j;
                powers[indexPower][Y] = i;
                powers[indexPower][2] = map[i][j][POWER];
                powers[indexPower][3] = OFF;
                indexPower++;
            }

            if(map[i][j][AZURITE] > 0){
                powers[indexPower][X] = j;
                powers[indexPower][Y] = i;
                powers[indexPower][2] = map[i][j][AZURITE]+9;
                powers[indexPower][3] = OFF;
                indexPower++;
            }

        }
    }

    fclose(file);


}

SDL_Surface* loadImageOptimised(const char* spritePath){
    SDL_Color transparencyColour = {0, 0, 0, 0};

    SDL_Surface* pSurface = IMG_Load(spritePath);
    if ( pSurface != NULL )
    {
        // Nous optimisons la texture pour correspondre avec le format de l'écran
        SDL_Surface* pOptimisedSurface = SDL_DisplayFormat(pSurface);
        if ( pOptimisedSurface != NULL )
        {
            // Nous libérons la mémoire associée à l'ancienne surface
            SDL_FreeSurface(pSurface);

            // Nous définissons une couleur de transparence
            Uint32 colorkey = SDL_MapRGB(pOptimisedSurface->format, transparencyColour.r, transparencyColour.g, transparencyColour.b);
            if ( SDL_SetColorKey(pOptimisedSurface, SDL_RLEACCEL, colorkey ) == -1 )
            {
                fprintf(stderr,"Fail to set transparency in '%s'\n",spritePath);
            }

            // Nous remplaçons notre pointeur final par le pointeur sur la surface optimisée
            pSurface = pOptimisedSurface;
        }
        else
        {
            fprintf(stderr,"Fail to optimise sprite '%s'\n",spritePath);
        }
    }
    else
    {
        fprintf(stderr,"Fail to load sprite '%s'\n",spritePath);
    }

    return pSurface;
}
