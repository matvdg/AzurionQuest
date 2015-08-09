#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

// librairies
#include "glsdl.h"
#include <SDL/SDL_image.h>
#include <SDL/fmod.h>
#include <stdio.h>
#include <string.h>

// our files
#include "songs/songs.h"
#include "game/game.h"
#include "load/load.h"
#include "check/check.h"



int main ( int argc, char** argv ){

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_GLSDL ) < 0 )
    {
        printf( "Impossible d'ouvrir la SDL : %s\n", SDL_GetError() );
        return 1;
    }

    SDL_WM_SetIcon(SDL_LoadBMP("images/Assets/icon.bmp"), NULL); //icon of the game

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(1680, 1050, 32, SDL_HWSURFACE | SDL_FULLSCREEN | SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Impossible d'ouvrir le programme en plein ecran : %s\n", SDL_GetError());
        return 1;
    }

    // we create a sound system
    FMOD_SYSTEM *system = NULL;
    FMOD_SOUND *music = NULL;
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, NULL);


    // preload surfaces

    //backgrounds main menu
    int i = 0;
    int compteurboucle = 0;

    SDL_Surface *backgroundImg[9] = {NULL};

    SDL_Rect backgroundCoord;
    backgroundCoord.x = 0;
    backgroundCoord.y = 0;

    loadBackgrounds(backgroundImg);


    /*   INTRO ANIMATION   */
    loadIntro(screen, system, music);

    //buttons
    SDL_Surface *buttons[10] = {NULL};
    loadButtons(buttons);

    SDL_Rect buttonsCoord;
    buttonsCoord.x = 0;
    buttonsCoord.y = 0;

    int buttonAction[4] = {NULL}, stateMute = OFF;
    int mouseX = 0, mouseY = 0;

    //bonusShop
    bool powersShop[8] = {FALSE};


    //numbers
    SDL_Surface *numbers[10] = {NULL};
    loadNumbers(numbers);
    SDL_Rect numbersCoord;

    int menu = 0;
    int hlevel,hworld,hcoins;
    int world = 0, level = 0, azurites = 0, difficulty = 0;

    /* LOAD BACKUP */
    loadBackUp(&world, &level, &azurites, &difficulty);

    //INIT GAME
    if (world==0)
    {
        loadStory(screen, system, music);
        world = 1;
        saveBackUp(world, level, azurites, difficulty);
    }

    /* MENU SOUND */
    playSound(system, music, "sounds/endlerzik.mp3", -1);


    /* MOUSE AND KEYBOARD CONFIGURATION */
    SDL_ShowCursor(SDL_ENABLE);
    SDL_WarpMouse(screen->w/2, screen->h/2);
    SDL_EnableKeyRepeat(10,10);


    // program main loop
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

                            case SDLK_a : //hidden xxx level !
                                stopSound(system);
                                playSound(system, music, "soundtracks/JoeCocker.mp3", -1);
                                hlevel = 9;
                                hworld = 9;
                                hcoins = 69;
                                play(screen, &hworld, &hlevel, &hcoins, &difficulty, powersShop);
                                stopSound(system);
                                playSound(system, music, "sounds/endlerzik.mp3", -1);
                                SDL_EnableKeyRepeat(10,10);
                                SDL_ShowCursor(SDL_ENABLE);
                                break;

                            case SDLK_p : //hidden pirates level !
                                stopSound(system);
                                playSound(system, music, "soundtracks/pirates.mp3", -1);
                                hlevel = 8;
                                hworld = 8;
                                hcoins = 0;
                                play(screen, &hworld, &hlevel, &hcoins, &difficulty, powersShop);
                                stopSound(system);
                                playSound(system, music, "sounds/endlerzik.mp3", -1);
                                SDL_EnableKeyRepeat(10,10);
                                SDL_ShowCursor(SDL_ENABLE);
                                break;


                             default:
                                continue;
                                break;
                        }
                    break;

                //mouse pressed
                case SDL_MOUSEBUTTONDOWN:

                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        mouseX = event.button.x;
                        mouseY = event.button.y;
                        if (menu == 0)
                        {
                            checkButton(mouseX,mouseY,PRESSED,buttonAction);
                        }
                    }
                    break;

                //mouse released
                case SDL_MOUSEBUTTONUP:

                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        mouseX = event.button.x;
                        mouseY = event.button.y;
                        if (menu == 0)
                        {
                            checkButton(mouseX,mouseY,RELEASED,buttonAction);
                        }
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

        if(menu == 0)
        {

            /* we draw the home's buttons */
            SDL_BlitSurface(backgroundImg[(compteurboucle%9)], NULL, screen, &backgroundCoord); // draw backgroundImage

            /* WE BLIT MUTE TEXT */
            buttonsCoord.x = 50;
            buttonsCoord.y = 0;
            (stateMute == ON) ? SDL_BlitSurface(buttons[MUTEINVERT], NULL, screen, &buttonsCoord) : SDL_BlitSurface(buttons[MUTE], NULL, screen, &buttonsCoord);

            //mute
            buttonsCoord.x = 50;
            buttonsCoord.y = 50;
            (stateMute == ON) ? SDL_BlitSurface(buttons[SWITCHOFF], NULL, screen, &buttonsCoord) : SDL_BlitSurface(buttons[SWITCHON], NULL, screen, &buttonsCoord);

            //play
            buttonsCoord.y = screen->h - 150;
            (buttonAction[PLAY] == PRESSED) ? SDL_BlitSurface(buttons[PLAYINVERT], NULL, screen, &buttonsCoord) : SDL_BlitSurface(buttons[PLAY], NULL, screen, &buttonsCoord);

            //garagebay
            buttonsCoord.x = 600;
            (buttonAction[GARAGE] == PRESSED) ? SDL_BlitSurface(buttons[GARAGEINVERT], NULL, screen, &buttonsCoord) : SDL_BlitSurface(buttons[GARAGE], NULL, screen, &buttonsCoord);

            //quit
            buttonsCoord.x = 1150;
            (buttonAction[QUIT] == PRESSED) ? SDL_BlitSurface(buttons[QUITINVERT], NULL, screen, &buttonsCoord) : SDL_BlitSurface(buttons[QUIT], NULL, screen, &buttonsCoord);


            /* we execute the buttons ! */
            if (buttonAction[MUTE] == SWITCHED) //mute
            {
                if(stateMute == ON){ // we active sound
                    pauseSound(system);
                    playSound(system, music, "sounds/buttonmute.mp3", 0);
                }else{ // we desactive sound
                    pauseSound(system);
                }
                stateMute = (stateMute == ON) ? OFF : ON;
                buttonAction[MUTE] = NONE;
            }
            else if (buttonAction[PLAY] == RELEASED) //play
            {
                menu = 1;
                buttonAction[PLAY] = NONE;
            }
            else if (buttonAction[GARAGE] == RELEASED) //garagebay
            {
                menu = 2;
                stopSound(system);
                playSound(system, music, "sounds/buttongarage.mp3", 0);
                playSound(system, music, "sounds/garagebay.mp3", 0);
                buttonAction[GARAGE] = NONE;
            }
            else if (buttonAction[QUIT] == RELEASED)  //quit
            {
                done = true;
                buttonAction[QUIT] = NONE;
            }
        }


        if(menu == 1) //start the game !
        {
            stopSound(system);
            playSound(system, music, "sounds/buttonplay.mp3", 0);
            shufflemusic(system, music);
            loadGame(screen, powersShop);
            loadBackUp(&world, &level,&azurites, &difficulty);
            menu = 0;
            stopSound(system);
            playSound(system, music, "soundtrack s/endlerzik.mp3", -1);
            SDL_ShowCursor(SDL_ENABLE);
        }

        if(menu == 2) //GarageBay
        {
            loadGarage(screen, &menu, &done, numbers, &world, &level, &difficulty, &azurites, system, music, powersShop);
        }


        // DRAWING ENDS HERE

        // finally, update the screen
        SDL_Flip(screen);
        SDL_Delay(100); //set the speed of the background animations
        compteurboucle++;

    } // end main loop


    // free loaded
    SDL_FreeSurface(*backgroundImg);
    SDL_FreeSurface(screen);

    closeSound(system, music);
    SDL_Quit();

    return EXIT_SUCCESS;
}

