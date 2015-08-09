#include "../songs/songs.h"

void shufflemusic(FMOD_SYSTEM *system,FMOD_SOUND *music){
    srand(time(NULL));
    int shuffle = rand()%19;
    char musicStr[3], musicPathStr[30] = "soundtracks/";
    sprintf(musicStr, "%d", shuffle);
    strcat(musicPathStr, musicStr);
    strcat(musicPathStr, ".mp3");
    playSound(system,music, musicPathStr, -1);
}

void initNoises(FMOD_SYSTEM *systemNoise, FMOD_SOUND *noises[13]){
    FMOD_System_CreateSound(systemNoise, "sounds/bounce.mp3", FMOD_CREATESAMPLE, 0, &noises[BOUNCE]);
    FMOD_System_CreateSound(systemNoise, "sounds/metalbounce.mp3", FMOD_CREATESAMPLE, 0, &noises[METALBOUNCE]);
    FMOD_System_CreateSound(systemNoise, "sounds/paddle.mp3", FMOD_CREATESAMPLE, 0, &noises[PADDLEBOUNCE]);
    FMOD_System_CreateSound(systemNoise, "sounds/die.mp3", FMOD_CREATESAMPLE, 0, &noises[DIENOISE]);
    FMOD_System_CreateSound(systemNoise, "sounds/gameover.mp3", FMOD_CREATESAMPLE, 0, &noises[GAMEOVERNOISE]);
    FMOD_System_CreateSound(systemNoise, "sounds/laser.mp3", FMOD_CREATESAMPLE, 0, &noises[LASERNOISE]);
    FMOD_System_CreateSound(systemNoise, "sounds/vortex.mp3", FMOD_CREATESAMPLE, 0, &noises[VORTEXNOISE]);
    FMOD_System_CreateSound(systemNoise, "sounds/victory.mp3", FMOD_CREATESAMPLE, 0, &noises[VICTORYNOISE]);
    FMOD_System_CreateSound(systemNoise, "sounds/ready.mp3", FMOD_CREATESAMPLE, 0, &noises[READYNOISE]);
    FMOD_System_CreateSound(systemNoise, "sounds/gemstonenoise.mp3", FMOD_CREATESAMPLE, 0, &noises[GEMSTONENOISE]);
    FMOD_System_CreateSound(systemNoise, "sounds/bonus.mp3", FMOD_CREATESAMPLE, 0, &noises[BONUSNOISE]);
    FMOD_System_CreateSound(systemNoise, "sounds/heartbeat.mp3", FMOD_CREATESAMPLE, 0, &noises[HEARTBEAT]);
    FMOD_System_CreateSound(systemNoise, "sounds/buzz.mp3", FMOD_CREATESAMPLE, 0, &noises[BUZZ]);
}

void playNoise(FMOD_SYSTEM *system, FMOD_SOUND *noise){

    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, noise, 0, NULL);

}

void playSound(FMOD_SYSTEM *system, FMOD_SOUND *music, char *musicName, int loop){

    FMOD_System_CreateSound(system, musicName, FMOD_SOFTWARE | FMOD_LOOP_NORMAL | FMOD_2D | FMOD_CREATESTREAM, 0, &music);
    FMOD_Sound_SetLoopCount(music, loop);
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, music, 0, NULL);

}

void pauseSound(FMOD_SYSTEM *system){

    // free music
    FMOD_CHANNELGROUP *canal;
    FMOD_BOOL etat;
    FMOD_System_GetMasterChannelGroup(system,&canal);
    FMOD_ChannelGroup_GetPaused(canal, &etat);
    if (etat) // if the music is paused
        FMOD_ChannelGroup_SetPaused(canal,0); // we remove the pause
    else //otherwise, it's playing
        FMOD_ChannelGroup_SetPaused(canal,1); // we set the pause

}

void stopSound(FMOD_SYSTEM *system){

    // free music
    FMOD_CHANNELGROUP *canal;
    FMOD_System_GetMasterChannelGroup(system,&canal);
    FMOD_ChannelGroup_Stop(canal);
}

void closeSound(FMOD_SYSTEM *system, FMOD_SOUND *music){

    // free music
    FMOD_Sound_Release(music);
    FMOD_System_Close(system);
    FMOD_System_Release(system);

}
