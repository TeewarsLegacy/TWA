/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#include "game.h"
#include "screen.h"
#include "protocol.h"
#include "map.h"
#include "stdio.h"

// Global objects
extern SDL_Surface *Screen;
extern bool Connected;
extern void CloseClient();
NPacket CPacket;

int xpos = 0;
int ypos = 0;

GameCore::GameCore(){
	return;
}

void GameCore::Connect(unsigned int ip, unsigned short port){
    // Creating connection
    Connected=true;
    NetInit();
    Socket = NetUDPOpen(0);
    SetNONBlock(Socket);
    Server.ip = ip;
    Server.port = port;
    NetUDPSend(Socket, &Server, "Connected", strlen("Connected"));
}

void GameCore::NetworkLoop(){
    int size = NetUDPRecv(Socket, &Server, &CPacket, sizeof(CPacket));
}

MenuState GameCore::Loop(){

	SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 120,120,255)); // Cleaning screen

	SDL_PollEvent(&Event);
    switch (Event.type) { // Listening events
        case SDL_KEYDOWN:
            switch (Event.key.keysym.sym){
                case SDLK_ESCAPE:
                    NetClose(Socket);
                    Connected=false;
                    return m_titlescreen;
                default:
                    printf("The %s key was pressed!\n",SDL_GetKeyName(Event.key.keysym.sym));
                    break;
            }
        case SDL_QUIT:
        	CloseClient();
            exit(0);
    }
    xpos-=2;
    ypos--;
    DrawMap(xpos, ypos, &CPacket.current_map);
    DrawClouds();
	SDL_Flip(Screen);

	SDL_Delay(16); // 60 fps
	return m_online;
}