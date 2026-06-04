/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#include "audio.h"

extern Mix_Music *Music;

void PlayMusic(){
    Mix_PlayMusic(Music,-1);
}

void StopMusic(){
	Mix_PauseMusic();
}