/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#include "menu.h"
#include "screen.h"
#include "audio.h"
#include "game.h"
#include "network.h"
#include "stdio.h"
#include "cmath"

// Global objects
extern SDL_Surface *Screen;
extern GameCore *Game;
extern void CloseClient();
extern bool Connected;

MenuCore::MenuCore(){
    BgAnimationCounter = 0;
    AuthorsAnimationCounter = 0;
    PlayMusic();
	return;
}

MenuState MenuCore::MainLoop(){
	SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 0,0,0)); // Cleaning screen

	SDL_PollEvent(&Event);
    switch (Event.type) { // Listening events
        case SDL_KEYDOWN:
            switch (Event.key.keysym.sym){
                // Selector
                case SDLK_UP:
                    if (Selector == 0){
                        Selector = 4;
                    }
                    Selector --;
                    break;
                case SDLK_DOWN:
                    if (Selector == 4){
                        Selector = 0;
                    }
                    Selector ++;
                    break;
                case SDLK_RETURN:
                case SDLK_SPACE:
                case SDLK_KP_ENTER:
                    switch (Selector){
                        case 0:
                            if (Connected == false){
                                Game->Connect(inet_addr("127.0.0.1"), 5000);
                            }
                            return m_online;
                        case 1:
                            return m_authors;
                        case 2:
                            return m_help;
                        case 4:
                            return m_exit;
                    }
                    break;
            }
            break;
        case SDL_QUIT:
        	CloseClient();
            exit(0);
    }
    // Drawing background tiles
    for (int y=0; y < round(600/MenuBackground->h)*2; y++){
        for (int x=0; x < round(800/MenuBackground->w)*3; x++){
            DrawSurface(MenuBackground, BgAnimationCounter+MenuBackground->w*x,MenuBackground->h*y,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
        }
    }
    // Drawing menu and copyright
    DrawSurface(MenuFrame, 25,140,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawSurface(MenuCopyright, 0,550,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawSurface(Banner, 535,383,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawString(120,250,"PLAY",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawString(120,285,"ABOUT",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawString(120,320,"HELP",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawString(120,355,"SETTINGS",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawString(120,390,"EXIT",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    // Drawing logo
    DrawAnimatedString(120,120,"TEEWARS LEGACY",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    BgAnimationCounter-=5;
    if (BgAnimationCounter <= -MenuBackground->w){
        BgAnimationCounter = 0;
    }
	SDL_Flip(Screen);
	SDL_Delay(16); // 60 fps
	return m_titlescreen;
}


MenuState MenuCore::AuthorsLoop(){
    SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 0,0,0)); // Cleaning screen

    SDL_PollEvent(&Event);
    switch (Event.type) { // Listening events
        case SDL_KEYDOWN:
            return m_titlescreen;
            break;
        case SDL_QUIT:
            SDL_Quit();
            exit(0);
    }
    // Drawing background tiles
    for (int y=0; y < round(600/MenuBackground->h)*2; y++){
        for (int x=0; x < round(800/MenuBackground->w)*3; x++){
            DrawSurface(MenuBackground, BgAnimationCounter+MenuBackground->w*x,MenuBackground->h*y,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
        }
    }
    // Drawing message
    DrawString(120,568,"PRESS ANY KEY TO EXIT",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    SDL_Flip(Screen);
    SDL_Delay(16); // 60 fps
    return m_authors;
}

MenuState MenuCore::HelpLoop(){
    SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 0,0,0)); // Cleaning screen

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
    // Drawing background tiles
    for (int y=0; y < round(600/MenuBackground->h)*2; y++){
        for (int x=0; x < round(800/MenuBackground->w)*3; x++){
            DrawSurface(MenuBackground, BgAnimationCounter+MenuBackground->w*x,MenuBackground->h*y,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
        }
    }
    // Drawing info 
    // TODO: Add more info about game
    DrawString(0,50,"USE A AND D KEYS FOR MOVE",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawString(0,100,"USE SPACE FOR JUMPING",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawString(0,150,"USE LEFT MOUSE BUTTON",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawString(0,182,"FOR SHOOTING",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawString(0,232,"USE RIGHT MOUSE BUTTON",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawString(0,264,"FOR HOOK",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    BgAnimationCounter-=5;
    if (BgAnimationCounter <= -MenuBackground->w){
        BgAnimationCounter = 0;
    }
    SDL_Flip(Screen);
    SDL_Delay(16); // 60 fps
    return m_help;
}