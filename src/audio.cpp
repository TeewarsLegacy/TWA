/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#include "audio.h"

extern Mix_Music *Music;
extern Mix_Chunk *Click;

/* Loading music and sounds */
void LoadSounds(){
	Music = Mix_LoadMUS("music/menu.xm");
	Click = Mix_LoadWAV("sounds/click.wav");
}

void PlaySound(int id){
	switch (id){
		case click:
			Mix_PlayChannel(-1, Click, 0);
			break;
	}
}

void PlayMusic(){
    Mix_PlayMusic(Music,-1);
}

void StopMusic(){
	Mix_PauseMusic();
}