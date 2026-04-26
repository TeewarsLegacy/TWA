/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#include "game.h"
#include "screen.h"
#include "protocol.h"
#include "map.h"
#include "stdio.h"

// Global objects
extern SDL_Surface *Screen;
extern bool Connected;
extern int CSocket;

int xpos = 0;
int ypos = 0;

GameCore::GameCore(){
	return;
}

void GameCore::Connect(unsigned int ip, unsigned short port){
    // Creating connection
    Connected=true;
    Server.ip = ip;
    Server.port = port;
    NetUDPSend(CSocket, &Server, "Connected", strlen("Connected"));
}

void GameCore::NetworkLoop(){
    int size = NetUDPRecv(CSocket, &Server, &CPacket, sizeof(CPacket));
}

MenuState GameCore::Loop(){
	SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 120,120,255)); // Cleaning screen

    while (SDL_PollEvent(&Event)){
        switch (Event.type) { // Listening events
            case SDL_KEYDOWN:
                switch (Event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        Connected=false;
                        return m_titlescreen;
                    case SDLK_LEFT:
                        xpos++;
                        break;
                    case SDLK_RIGHT:
                        xpos--;
                        break;
                    case SDLK_UP:
                        ypos++; 
                        break;
                    case SDLK_DOWN:
                        ypos--;
                        break;
                }
                break;
            case SDL_QUIT:
                return m_exit;
        }
    }
    DrawMap(xpos, ypos, &CPacket.current_map);
    DrawClouds();
	SDL_Flip(Screen);
	return m_online;
}