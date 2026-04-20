/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#include "stdio.h"
#include "string.h"

#include "screen.h"
#include "version.h"
#include "network.h"
#include "types.h"
#include "game.h"
#include "menu.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"

// Global objects
SDL_Surface *Screen;
NetAddr ConnectAddr;
// Time
Uint32 CurrentTime;
Uint32 PrevTime;

GameCore *Game;
MenuCore *Menu;

Mix_Music *Music;

void ClientMain(){
	// Initialization of objects
	Game = new GameCore(); 
	Menu = new MenuCore(); 

	MenuState state=m_online;
	// Initialization of SDL
	if (SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Failed to initializate SDL");
        exit(1);
	}	
	// Initialization of SDL_image
	int Flags = IMG_INIT_PNG;
	if ( !( IMG_Init(Flags) & Flags ) ) {
	    fprintf(stderr, "Failed to initializate SDL image");
        exit(1);
	}
	// Initialization of SDL_mixer
	if(Mix_OpenAudio(22050,AUDIO_S16,1,1024)) {
		fprintf(stderr, "Failed to initializate audio system");
        exit(1);
	}
	Music = Mix_LoadMUS("data/menu.xm");
	if (!Music) {
	    printf("Load failed: %s\n", Mix_GetError());
	}

	Mix_PlayMusic(Music, -1);
	// Loading data
	LoadSprites();
	// Creating window
	Screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
	// Cloning game version into caption
	char WindowCaption[86];
	strcpy(WindowCaption, "Teewars legacy milestone ");
	strcat(WindowCaption, TWLEGACY_MILESTONE);
	SDL_WM_SetCaption(WindowCaption, NULL);

	Game->Connect(inet_addr("127.0.0.1"), 5000);

	while (true){
		switch (state){
			case m_titlescreen:
				state = Menu->MainLoop();
				break;
			case m_online:
				state = Game->Loop();
				Game->NetworkLoop();
				break;
			case m_authors:
				state = Menu->AuthorsLoop();
				break;
			case m_exit:
				break;
		}
	}
	// Removing objects
	delete Game;
	delete Menu;
    SDL_Quit(); // Closing window

}