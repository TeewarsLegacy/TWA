/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#include "menu.h"
#include "screen.h"
#include "audio.h"
#include "game.h"
#include "network.h"
#include "types.h"
#include "stdio.h"
#include "string.h"
#include "map.h"
#include "cmath"

// Global objects
extern SDL_Surface *Screen;
extern GameCore *Game;
extern bool Connected;
extern int CSocket;
extern NetAddr MasterserverAddr;
extern GamePreferences Pref;

MenuCore::MenuCore(){
    BgAnimationCounter = 0;
    AuthorsAnimationCounter = 0;
	return;
}

void MenuCore::Refresh(){
    // Reseting packet
    MasterserverPacket.servers_count = 0;
    ServerSelector = 0;

    // After this sending to masterserver
    NetUDPSend(CSocket, &MasterserverAddr, "Refresh", strlen("Refresh"));
}

void MenuCore::NetworkLoop(){
    int size = NetUDPRecv(CSocket, &MasterserverAddr, &MasterserverPacket, sizeof(MasterserverPacket));
}

MenuState MenuCore::MainLoop(){
	SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 0,0,0)); // Cleaning screen

	while (SDL_PollEvent(&Event)){
        switch (Event.type) { // Listening events
            case SDL_KEYDOWN:
            	PlayAudio(click);
                // Adding symbols to buffer, and if this buffer = "mapdebug" we open secret page
                for (int i = 0; i < 7; i++)
                    MDCode[i] = MDCode[i + 1];
                MDCode[7] = Event.key.keysym.unicode&0x7F;
                MDCode[8] = '\0';
                printf("Code: %s\n", MDCode);
                if (strcmp(MDCode, "mapdebug") == 0){
                    LoadMap(&MapDebuggerMap, "empty");
                    return m_mapdebugger;
                }
                switch (Event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        return m_exit;
                    // Selector
                    case SDLK_UP:
                        TitlescreenSelector--;
                        if (TitlescreenSelector < 0) TitlescreenSelector = 4;
                        break;

                    case SDLK_DOWN:
                        TitlescreenSelector++;
                        if (TitlescreenSelector > 4) TitlescreenSelector = 0;
                        break;
                    case SDLK_RETURN:
                    case SDLK_SPACE:
                    case SDLK_KP_ENTER:
                        switch (TitlescreenSelector){
                            case 0:
                                Refresh();
                                //if (Connected == false){
                                //    Game->Connect(inet_addr("127.0.0.1"), 5000);
                                //}
                                return m_serverlist;
                            case 1:
                                return m_authors;
                            case 2:
                                return m_help;
                            case 3:
                                return m_settings;
                            case 4:
                                return m_exit;
                        }
                        break;
                }
                break;
            case SDL_QUIT:
                return m_exit;
        }
    }

    // Drawing background tiles
    for (int y=0; y < round(600/MenuBackground->h)*2; y++){
        for (int x=0; x < round(800/MenuBackground->w)*3; x++){
            DrawSurface(MenuBackground, BgAnimationCounter+MenuBackground->w*x,MenuBackground->h*y,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
        }
    }
    // Drawing menu and copyright
    DrawSurface(MenuFrame, 800/2-700/2,140,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawSurface(MenuCopyright, 0,530,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawSurface(Banner, 350,218,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    // Options
    switch (TitlescreenSelector){
        case 0:
            DrawStringWithUnderline(120,250,"PLAY",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            DrawString(120,285,"ABOUT",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            DrawString(120,320,"HELP",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            DrawString(120,355,"SETTINGS",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            DrawString(120,390,"EXIT",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            break;
        case 1:
            DrawString(120,250,"PLAY",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            DrawStringWithUnderline(120,285,"ABOUT",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            DrawString(120,320,"HELP",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            DrawString(120,355,"SETTINGS",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            DrawString(120,390,"EXIT",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            break;
        case 2:
            DrawString(120,250,"PLAY",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            DrawString(120,285,"ABOUT",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            DrawStringWithUnderline(120,320,"HELP",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            DrawString(120,355,"SETTINGS",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            DrawString(120,390,"EXIT",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            break;
        case 3:
            DrawString(120,250,"PLAY",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            DrawString(120,285,"ABOUT",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            DrawString(120,320,"HELP",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            DrawStringWithUnderline(120,355,"SETTINGS",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            DrawString(120,390,"EXIT",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            break;
        case 4:
            DrawString(120,250,"PLAY",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            DrawString(120,285,"ABOUT",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            DrawString(120,320,"HELP",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            DrawString(120,355,"SETTINGS",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            DrawStringWithUnderline(120,390,"EXIT",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            break;

    }

    // Drawing logo
    DrawAnimatedString(800/2-(32*14)/2,120,"TEEWARS LEGACY",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    BgAnimationCounter-=5;
    if (BgAnimationCounter <= -MenuBackground->w){
        BgAnimationCounter = 0;
    }

    DrawCursor();

	SDL_Flip(Screen);
	return m_titlescreen;
}


MenuState MenuCore::ServerlistLoop(){
    SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 0,0,0)); // Cleaning screen

    while (SDL_PollEvent(&Event)){
        switch (Event.type) { // Listening events
            case SDL_KEYDOWN:
            	PlayAudio(click);
                switch (Event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        NetClose(CSocket);
                        return m_titlescreen;
                    // Server selector
                    case SDLK_UP:
                        if (ServerSelector > 0) ServerSelector--;
                        break;

                    case SDLK_DOWN:
                        if (ServerSelector < MasterserverPacket.servers_count-1) ServerSelector++;
                        break;

                    case SDLK_LEFT:
                        if (ServerlistOptionSelector > 0) ServerlistOptionSelector--;
                        break;

                    case SDLK_RIGHT:
                        if (ServerlistOptionSelector < 2) ServerlistOptionSelector++;
                        break;
                    case SDLK_RETURN:
                    case SDLK_SPACE:
                    case SDLK_KP_ENTER:
                        switch (ServerlistOptionSelector){
                            printf("ENTER PRESSED, option=%d\n", ServerlistOptionSelector);
                            case 0:
                                Refresh();
                                break;
                            case 1:
                                if (Connected == false){
                                    Game->Connect(MasterserverPacket.servers[ServerSelector].addr.ip, MasterserverPacket.servers[ServerSelector].addr.port);
                                }
                                return m_online;
                            case 2:
                                return m_titlescreen;
                        }
                        break;
                }
                break;
            case SDL_QUIT:
                return m_exit;
        }
    }

    // Drawing background tiles
    for (int y=0; y < round(600/MenuBackground->h)*2; y++){
        for (int x=0; x < round(800/MenuBackground->w)*3; x++){
            DrawSurface(MenuBackground, BgAnimationCounter+MenuBackground->w*x,MenuBackground->h*y,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
        }
    }
    // Drawing servers frame and serverlist if we got servers
    if (MasterserverPacket.servers_count > 0){
        DrawSurface(ServerlistFrame, 0,32,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
        for (int i = 0; i < 5; i++){
            DrawSurface(MenuArrow, 650,108,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            DrawSurface(ServerlistBar, 77,108+i*50,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            DrawCompressedString(180,108+44+i*50,MasterserverPacket.servers[i+ServerSelector].name,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            DrawCompressedString(77,108+44+i*50,"999",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            DrawCompressedString(566,108+44+i*50,"8",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
        }
    }
    else{ // else we draw message
        DrawSurface(MenuFrame, 0,32,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
        DrawString(70, 208,"SERVERS NOT FOUND",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
        DrawString(65, 272,"TRY PRESS REFRESH BUTTON",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    }

    // Options (also can be optimised)
    switch (ServerlistOptionSelector){
        case 0:
            DrawStringWithUnderline(50, 500,"REFRESH",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            DrawString(250, 500,"CONNECT",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            DrawString(450, 500,"EXIT",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            break;
        case 1:
            DrawString(50, 500,"REFRESH",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            DrawStringWithUnderline(250, 500,"CONNECT",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            DrawString(450, 500,"EXIT",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            break;
        case 2:
            DrawString(50, 500,"REFRESH",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            DrawString(250, 500,"CONNECT",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            DrawStringWithUnderline(450, 500,"EXIT",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
            break;

    }

    BgAnimationCounter-=5;
    if (BgAnimationCounter <= -MenuBackground->w){
        BgAnimationCounter = 0;
    }

    DrawCursor();

    SDL_Flip(Screen);
    return m_serverlist;
}

MenuState MenuCore::AuthorsLoop(){
    SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 0,0,0)); // Cleaning screen

    while (SDL_PollEvent(&Event)){
        switch (Event.type) { // Listening events
            case SDL_KEYDOWN:
            	PlayAudio(click);
                return m_titlescreen;
                break;
            case SDL_QUIT:
                return m_exit;
        }
    }
    // Drawing background tiles
    for (int y=0; y < round(600/MenuBackground->h)*2; y++){
        for (int x=0; x < round(800/MenuBackground->w)*3; x++){
            DrawSurface(MenuBackground, BgAnimationCounter+MenuBackground->w*x,MenuBackground->h*y,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
        }
    }
    // Drawing message
    DrawString(120,568,"PRESS ANY KEY TO EXIT",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));

    DrawCursor();

    SDL_Flip(Screen);
    return m_authors;
}

MenuState MenuCore::HelpLoop(){
    SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 0,0,0)); // Cleaning screen

    while (SDL_PollEvent(&Event)){
        switch (Event.type) { // Listening events
            case SDL_KEYDOWN:
            	PlayAudio(click);
                return m_titlescreen;
            case SDL_QUIT:
                return m_exit;
        }
    }
    // Drawing background tiles
    for (int y=0; y < round(600/MenuBackground->h)*2; y++){
        for (int x=0; x < round(800/MenuBackground->w)*3; x++){
            DrawSurface(MenuBackground, BgAnimationCounter+MenuBackground->w*x,MenuBackground->h*y,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
        }
    }
    // Drawing info with different icons
    DrawString(0,50,"USE A AND D KEYS TO MOVE",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    //DrawTee(24*24 + TeeTilesetLeft->w/2,50, walk_left, 0, gun, SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawString(0,100,"USE SPACE FOR JUMPING",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    //DrawTee(21*24 + TeeTilesetLeft->w/2,100, fall_left, 0, gun, SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawString(0,150,"USE LEFT MOUSE BUTTON TO SHOOT",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawAnimationSurface(WeaponsTilesetRight, 30*24 + WeaponsTilesetRight->w/3,150, SDL_MapRGBA(Screen->format, 255, 255, 255, 255), 4, shotgun);
    DrawString(0,200,"USE RIGHT MOUSE BUTTON TO HOOK",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawString(0,250,"USE MOUSE WHEEL OR FOLOWING KEYS",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawString(0,280,"TO SELECT WEAPONS",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));

    // Drawing info about weapons
    DrawStringWithUnderline(10,330,"1",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawAnimationSurface(WeaponsTilesetRight, 32 - WeaponsTilesetRight->w/2,370, SDL_MapRGBA(Screen->format, 255, 255, 255, 255), 4, gun);
    DrawStringWithUnderline(60,330,"2",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawAnimationSurface(WeaponsTilesetRight, 32+50 - WeaponsTilesetRight->w/2,370, SDL_MapRGBA(Screen->format, 255, 255, 255, 255), 4, shotgun);
    DrawStringWithUnderline(110,330,"3",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawAnimationSurface(WeaponsTilesetRight, 32+100 - WeaponsTilesetRight->w/2,370, SDL_MapRGBA(Screen->format, 255, 255, 255, 255), 4, grenade);
    DrawStringWithUnderline(160,330,"4",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawAnimationSurface(WeaponsTilesetRight, 32+150 - WeaponsTilesetRight->w/2,370, SDL_MapRGBA(Screen->format, 255, 255, 255, 255), 4, rifle);

    BgAnimationCounter-=5;
    if (BgAnimationCounter <= -MenuBackground->w){
        BgAnimationCounter = 0;
    }

    DrawCursor();

    // Drawing message
    DrawString(120,568,"PRESS ANY KEY TO EXIT",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));

    SDL_Flip(Screen);
    return m_help;
}

MenuState MenuCore::SettingsLoop(){
    SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 0,0,0)); // Cleaning screen

    while (SDL_PollEvent(&Event)){
        switch (Event.type) { // Listening events
            case SDL_KEYDOWN:
            	PlayAudio(click);
                return m_titlescreen;
                break;
            case SDL_QUIT:
                return m_exit;
        }
    }
    // Drawing background tiles
    for (int y=0; y < round(600/MenuBackground->h)*2; y++){
        for (int x=0; x < round(800/MenuBackground->w)*3; x++){
            DrawSurface(MenuBackground, BgAnimationCounter+MenuBackground->w*x,MenuBackground->h*y,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
        }
    }
    // Drawing frame, sliders, checkboxes, settings icons and etc
    DrawSurface(SettingsFrame, 0, 0, SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawSurface(SettingsIcons, 32, 50, SDL_MapRGBA(Screen->format, 255, 255, 255, 255));

    DrawCheckbox(0,40,Pref.fullscreen);

    BgAnimationCounter-=5;
    if (BgAnimationCounter <= -MenuBackground->w){
        BgAnimationCounter = 0;
    }

    DrawCursor();

    SDL_Flip(Screen);
    return m_settings;
}

MenuState MenuCore::MapDebuggerLoop(){
    SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 105,138,214)); // Cleaning screen

    while (SDL_PollEvent(&Event)){
        switch (Event.type) { // Listening events
            case SDL_KEYDOWN:
                switch (Event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        return m_titlescreen;
                    case SDLK_F5:
                    	ShowMap = false;
                        LoadMap(&MapDebuggerMap, "empty");
                        ShowMap = true;
                        break;
                    case SDLK_F6:
                    	if (ShowCenterPointer == true){
                    		ShowCenterPointer = false;
                    	}
                    	else{
                    		ShowCenterPointer = true;
                    	}
                    	break;
                    }
                break;
            case SDL_QUIT:
                return m_exit;
        }
    }
    // Smooth control
    Uint8* CurrentKeyStates = SDL_GetKeyState(NULL);

    if (CurrentKeyStates[SDLK_LEFT] || CurrentKeyStates[SDLK_a]) {
        XPos++;
    }
    if (CurrentKeyStates[SDLK_RIGHT] || CurrentKeyStates[SDLK_d]) {
        XPos--;
    }
    if (CurrentKeyStates[SDLK_UP]) {
        YPos++;
    }
    if (CurrentKeyStates[SDLK_DOWN]) {
        YPos--;
    }
    DrawBackground(XPos/2, YPos-150);
    if (ShowMap == true){
    	DrawMap(XPos + 400, YPos + 300, &MapDebuggerMap);
    }
    // Debug hud
    DrawString(0,50,"MAP DEBUGGER",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawString(0,100,"USE F5 TO UPDATE MAP",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawString(0,150,"USE F6 TO HIDE CENTER POINTER",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "X %d", -XPos);
    DrawString(0,200,buffer,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    snprintf(buffer, sizeof(buffer), "Y %d", -YPos);
    DrawString(0,250,buffer,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));

    if (ShowCenterPointer == true){
	    // Center pointer
	    DrawSurface(Cursor, 400-50/2, 300-50/2, SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    }

    SDL_Flip(Screen);
    return m_mapdebugger;
}
