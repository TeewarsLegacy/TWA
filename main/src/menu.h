/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#include "SDL/SDL.h"
#include "types.h"

#ifndef MENU_H
#define MENU_H

// Menu class define
class MenuCore{
public:
	MenuCore();
	MenuState MainLoop();
	MenuState AuthorsLoop();
	MenuState HelpLoop();
	MenuState ServerlistLoop();
private:
	SDL_Event Event;
    int BgAnimationCounter;
    int AuthorsAnimationCounter;
    int Selector = 0;
};

#endif