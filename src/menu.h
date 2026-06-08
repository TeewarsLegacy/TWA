/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#include "SDL/SDL.h"
#include "types.h"
#include "protocol.h"

#ifndef MENU_H
#define MENU_H

// Menu class define
class MenuCore{
public:
	MenuCore();
    void Refresh();
    void NetworkLoop();
	MenuState MainLoop();
	MenuState AuthorsLoop();
	MenuState HelpLoop();
	MenuState ServerlistLoop();
    MenuState SettingsLoop();
    MenuState MapDebuggerLoop();
private:
	SDL_Event Event;
    int BgAnimationCounter;
    int AuthorsAnimationCounter;
    int TitlescreenSelector = 0;
    int ServerSelector = 0;
    int ServerlistOptionSelector = 0;
    NMSPacket MasterserverPacket;
    NetAddr Masterserver;
    Map MapDebuggerMap;
    char MDCode[9] = {0};
    int XPos = 0, YPos = 0;
    bool ShowMap = false;
    bool ShowCenterPointer = true;
};

#endif