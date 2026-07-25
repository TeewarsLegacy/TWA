/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
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

extern NetAddr MasterserverAddr;

ServerInfo SInfo;
NetAddr Client;
NPacket SPacket;
char buffer[MAX_PACKET_SIZE] = "\0";
int SSocket;
unsigned int ServerPort;

void SendPacket(){
	NetUDPSend(SSocket, &Client, &SPacket, sizeof(SPacket));
}

void ServerMain(int Port, char *Map, char *Name){

	// Configuration of server
	ServerPort = Port;
	// Creating server
	NetInit();
	SSocket = NetUDPOpen(ServerPort);
	printf("Server with name '%s' listening on port %d\n", Name ,ServerPort);
	// Sending info about server for masterserver
	SInfo.players_count = 0;
	SInfo.have_password = 0;
	strcpy(SInfo.name, Name);
    NetUDPSend(SSocket, &MasterserverAddr, &SInfo, sizeof(SInfo));
	// Loading map
	LoadMap(&SPacket.current_map, Map);
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
