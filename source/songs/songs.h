#ifndef SONGS_H_INCLUDED
#define SONGS_H_INCLUDED

#include "../init/init.h"

void playNoise(FMOD_SYSTEM *system, FMOD_SOUND *noise);
void playSound(FMOD_SYSTEM *system, FMOD_SOUND *music, char *musicName, int loop);
void closeSound(FMOD_SYSTEM *system, FMOD_SOUND *music);
void pauseSound(FMOD_SYSTEM *system);
void stopSound(FMOD_SYSTEM *system);
void initNoises(FMOD_SYSTEM *systemNoise, FMOD_SOUND *noises[13]);
void shufflemusic(FMOD_SYSTEM *system, FMOD_SOUND *music);

#endif // SONGS_H_INCLUDED
