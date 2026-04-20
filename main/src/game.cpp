/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#include "game.h"
#include "screen.h"
#include "protocol.h"
#include "map.h"
#include "stdio.h"

// Global objects
extern SDL_Surface *Screen;
NPacket CPacket;

int xpos = 0;
int ypos = 0;

GameCore::GameCore(){
	return;
}

void GameCore::Connect(unsigned int ip, unsigned short port){
    // Creating connection
    NetInit();
    Socket = NetUDPOpen(0);
    SetNONBlock(Socket);
    inet_pton(AF_INET, "127.0.0.1", &Server.ip);
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
            printf("The %s key was pressed!\n",
                   SDL_GetKeyName(Event.key.keysym.sym));
            break;
        case SDL_QUIT:
        	SDL_Quit();
            exit(0);
    }
    xpos-=2;
    ypos--;
    DrawMap(xpos, ypos, &CPacket.current_map,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawSurface(MenuFrame, 0,0,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawClouds();
    DrawString(0,400,"ZABIDEN1234567890",SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
	SDL_Flip(Screen);

	SDL_Delay(16); // 60 fps
	return m_online;
}