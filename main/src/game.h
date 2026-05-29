/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#include "SDL/SDL.h"
#include "types.h"
#include "network.h"
#include "protocol.h"

#ifndef GAME_H
#define GAME_H

// Game class define
class GameCore{
public:
	GameCore();
	void Connect(unsigned int ip, unsigned short port);
	void NetworkLoop();
	MenuState Loop();
private:
	SDL_Event Event;
    NetAddr Server;
	NPacket CPacket;
	NInput CInput;
};

#endif