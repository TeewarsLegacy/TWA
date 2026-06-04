/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#include "game.h"
#include "screen.h"
#include "protocol.h"
#include "map.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"

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
	SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 105,138,214)); // Cleaning screen

    while (SDL_PollEvent(&Event)){
        switch (Event.type) { // Listening events
            case SDL_KEYDOWN:
                switch (Event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        Connected=false;
                        return m_titlescreen;
        			case SDLK_SPACE:
        			case SDLK_UP:
        				CInput.jump = 1;
        				break;
        			}
        		break;
        	case SDL_KEYUP:
        		switch (Event.key.keysym.sym){
        			case SDLK_SPACE:
        			case SDLK_UP:
        				CInput.jump = 0;
        				break;
        			}
        		break;
        	case SDL_MOUSEBUTTONDOWN:
			    if (Event.button.button == SDL_BUTTON_LEFT) {
			        CInput.fire = 1;
			    }
			    if (Event.button.button == SDL_BUTTON_RIGHT) {
			        CInput.hook = 1;
			    }
			    break;

			case SDL_MOUSEBUTTONUP:
			    if (Event.button.button == SDL_BUTTON_LEFT) {
			        CInput.fire = 0;
			    }
			    if (Event.button.button == SDL_BUTTON_RIGHT) {
			        CInput.hook = 0;
			    }
			    break;
            case SDL_QUIT:
                return m_exit;
        }
    }
    // Smooth control
    Uint8* CurrentKeyStates = SDL_GetKeyState(NULL);    

	if (CurrentKeyStates[SDLK_LEFT] || CurrentKeyStates[SDLK_a]) {
	    xpos++;
		CInput.left = 1;
	}
	else{
		CInput.left = 0;
	}
	if (CurrentKeyStates[SDLK_RIGHT] || CurrentKeyStates[SDLK_d]) {
	    xpos--;
		CInput.right = 1;
	}
	else{
		CInput.right = 0;
	}
	if (CurrentKeyStates[SDLK_UP]) {
	    ypos++;
	}
	if (CurrentKeyStates[SDLK_DOWN]) {
	    ypos--;
	}
    DrawBackground(xpos/2, ypos-150);
    DrawMap(xpos, ypos, &CPacket.current_map);
    // Debug hud
   /*char buf[64];
	sprintf(buf, "LEFT %d", CInput.left);
	DrawString(0, 50, buf, SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
	sprintf(buf, "RIGHT %d", CInput.right);
    DrawString(0,100,buf,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
	sprintf(buf, "ANGLE %d", CInput.angle);
    DrawString(0,150,buf,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
	sprintf(buf, "JUMP %d", CInput.jump);
    DrawString(0,200,buf,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
	sprintf(buf, "FIRE %d", CInput.fire);
    DrawString(0,250,buf,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
	sprintf(buf, "HOOK %d", CInput.hook);
    DrawString(0,300,buf,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
	sprintf(buf, "ACTIVE_WEAPON %d", CInput.active_weapon);
    DrawString(0,350,buf,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));*/

    DrawCursor();
    
	SDL_Flip(Screen);
	return m_online;
}