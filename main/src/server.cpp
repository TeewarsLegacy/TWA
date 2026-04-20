/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#include "stdio.h"

// Defines
#define GROUND_CONTROL_SPEED 10.0f
#define GROUND_FRICTION 0.5f
#define GROUND_JUMP_IMPULSE 11.5f
#define GRAVITY 0.5
#define HOOK_LENGTH 380.0f
#define HOOK_FIRE_SPEED 80.0f
#define HOOK_DRAG_ACCEL 3.0f
#define HOOK_DRAG_SPEED 15.0f

#include "SDL/SDL.h"
#include "stdio.h"
#include "map.h"
#include "network.h"
#include "protocol.h"

NetAddr Client;
NPacket SPacket;
char buffer[MAX_PACKET_SIZE] = "\0";
int SSocket;
unsigned int ServerPort = 80;

void SendPacket(){
	NetUDPSend(SSocket, &Client, &SPacket, sizeof(SPacket));
}

void ServerMain(int Port){
	ServerPort = Port;
	// Creating server
	NetInit();
	SSocket = NetUDPOpen(ServerPort);
	printf("Server listening on port %d\n",ServerPort);
	LoadMap(&SPacket.current_map, "dm1");
	while (true){
        int size = NetUDPRecv(SSocket, &Client, buffer, MAX_PACKET_SIZE);
        if (size > 0)
		{
		    buffer[size] = '\0';printf("Got: %s\n", buffer);

		    if (strcmp(buffer, "Connected") == 0)
		    {
		        printf("Player connected\n");
		        SendPacket();
		    }
		}
		SDL_Delay(16);
	}
}