/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#include "game.h"
#include "screen.h"
#include "map.h"

#include "stdio.h"

// Global objects
extern SDL_Surface *Screen;

GameCore::GameCore(){
    LoadMap(&object, "dm1");
	return;
}

MenuState GameCore::Loop(){
	SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 120,120,255)); // Cleaning screen

	SDL_PollEvent(&Event);
    switch (Event.type) { // Listening events
        case SDL_KEYDOWN:
            printf("The %s key was pressed!\n",
                   SDL_GetKeyName(Event.key.keysym.sym));
            break;
        case SDL_QUIT:
        	SDL_Quit();
            exit(0);
    }
    DrawMap(20, 0, &object,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawSurface(MenuFrame, 0,0,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawClouds();
    DrawString(0,400,"ZABIDEN1234567890",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
	SDL_Flip(Screen);
	SDL_Delay(16); // 60 fps
	return online;
}
