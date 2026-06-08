/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#include "SDL/SDL_mixer.h"

#ifndef AUDIO_H
#define AUDIO_H

enum{
	click = 1
};

void LoadSounds();
void PlaySound(int id);
void PlayMusic();
void StopMusic();

#endif