/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#include "SDL/SDL_mixer.h"

#ifndef AUDIO_H
#define AUDIO_H

enum{
	click = 1
};

enum{
	menu_music = 1,
	ingame1_music = 2
};

void LoadSounds();
void PlaySound(int id);
void PlayMusic(int id);
void StopMusic();

#endif