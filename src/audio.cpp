/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#include "audio.h"

extern Mix_Music *MenuMusic;
extern Mix_Music *Ingame1Music;
extern Mix_Chunk *Click;

/* Loading music and sounds */
void LoadSounds(){
	MenuMusic = Mix_LoadMUS("music/menu.xm");
	Ingame1Music = Mix_LoadMUS("music/g1.xm");
	Click = Mix_LoadWAV("sounds/click.wav");
}

void PlaySound(int id){
	switch (id){
		case click:
			Mix_PlayChannel(-1, Click, 0);
			break;
	}
}

void PlayMusic(int id){
	switch (id){
		case menu_music:
			Mix_PlayMusic(MenuMusic,-1);
			break;
		case ingame1_music:
			Mix_PlayMusic(Ingame1Music,-1);
			break;
	}
    
}

void StopMusic(){
	Mix_PauseMusic();
}