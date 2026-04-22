/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#include "game.h"
#include "screen.h"
#include "protocol.h"
#include "map.h"
#include "stdio.h"

// Global objects
extern SDL_Surface *Screen;
extern bool Connected;
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

    while (SDL_PollEvent(&Event)){
        switch (Event.type) { // Listening events
            case SDL_KEYDOWN:
                switch (Event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        Connected=false;
                        NetClose(Socket);
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
    DrawSurface(MenuFrame, 800/2-700/2,140,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
    DrawString(800/2-32*10/2,400, "CONNECTING", SDL_MapRGB(Screen->format, 255,255,255));
    DrawMap(xpos, ypos, &CPacket.current_map);
    DrawClouds();
	SDL_Flip(Screen);
	return m_online;
}