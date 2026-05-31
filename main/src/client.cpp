/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#include "stdio.h"
#include "string.h"

#include "screen.h"
#include "version.h"
#include "network.h"
#include "types.h"
#include "game.h"
#include "menu.h"
#include "audio.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"

// Global objects
SDL_Surface *Screen;
// Time
Uint32 CurrentTime;
Uint32 PrevTime;

GameCore *Game;
MenuCore *Menu;

Mix_Music *Music;

int MouseX, MouseY;

int CSocket;

bool Connected = false;

GamePreferences Pref;

void LoadPreferences(){
	FILE *file_pointer;
	// Loading preferences file
    file_pointer = fopen("twl.pref", "r");

    if (file_pointer == NULL) {
		fprintf(stderr, "Save file is not detected");

        file_pointer = fopen("twl.pref", "w");
        // If we dont find settings file we write new
		fwrite(&Pref, sizeof(GamePreferences), 1, file_pointer);

    } else {
    	// Else we loading data from from this file
        fread(&Pref, sizeof(GamePreferences), 1, file_pointer);
    }

    // Closing file
    fclose(file_pointer);
}

void ClientMain(){
	// Initialization of objects
	Game = new GameCore(); 
	Menu = new MenuCore();

	// Loading settings
	LoadPreferences();

	MenuState state=m_titlescreen;
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
	// Network initialization
    NetInit();
    CSocket = NetUDPOpen(0);
    SetNONBlock(CSocket);
	// Loading data
	LoadSprites();
	// Creating window
	Screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
	// Cloning game version into caption
	char WindowCaption[86];
	strcpy(WindowCaption, "Teewars legacy milestone ");
	strcat(WindowCaption, TWLEGACY_MILESTONE);
	SDL_WM_SetCaption(WindowCaption, NULL);
	SDL_ShowCursor(SDL_DISABLE);
	// Playing music
	PlayMusic();

	// Mainloop
	while (true){
		// Updating cursor
        SDL_GetMouseState(&MouseX, &MouseY);
		switch (state){
			case m_titlescreen:
				state = Menu->MainLoop();
				break;
			case m_online:
				Game->NetworkLoop();
				state = Game->Loop();
				break;
			case m_authors:
				state = Menu->AuthorsLoop();
				break;
			case m_help:
				state = Menu->HelpLoop();
				break;
			case m_serverlist:
				Menu->NetworkLoop();
				state = Menu->ServerlistLoop();
				break;
			case m_exit:
				// Removing objects
				delete Game;
				delete Menu;
			    SDL_Quit(); // Closing window
		}

		SDL_Delay(16); // 60 fps
	}
}