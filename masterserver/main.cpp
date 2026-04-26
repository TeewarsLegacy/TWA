/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#include "stdio.h"
#include "protocol.h"
// Windows delay library
#ifdef _WIN32
    #include <windows.h>
#else
	// Linux delay library
    #include <unistd.h>
#endif

#include <ctype.h>

NetAddr Client;
NMSPacket SPacket;
ServerInfo SIbuffer;
char buffer[MAX_PACKET_SIZE] = "\0";
int SSocket;

void SendPacket(){
	NetUDPSend(SSocket, &Client, &SPacket, sizeof(SPacket));
}

int main(){
	// Creating server
	NetInit();
	SSocket = NetUDPOpen(6000);
	printf("Masterserver listening on port %d\n",6000);
	while (true){
        int size = NetUDPRecv(SSocket, &Client, buffer, MAX_PACKET_SIZE);
        if (size > 0)
		{
		    if (size == sizeof(ServerInfo))
		    {
		    	memcpy(&SIbuffer, buffer, sizeof(ServerInfo));
		    	// Cloning info about address
		    	SIbuffer.addr.ip = Client.ip;
		    	SIbuffer.addr.port = Client.port;

		    	// Buffer for output
		    	struct in_addr addr;
				addr.s_addr = SIbuffer.addr.ip;
		    	printf("SERVER NAME | %s | SERVER ID | %d | SERVER IP | %s | SERVER PORT | %d | \n", SIbuffer.name, SPacket.servers_count, inet_ntoa(addr), SIbuffer.addr.port);

		    	memcpy(&SPacket.servers[SPacket.servers_count], &SIbuffer, sizeof(ServerInfo));
		    	// Transforming small letters into big (Because TWL gfx system supports only capital letters)
		    	for (int i = 0; SPacket.servers[SPacket.servers_count].name[i]; i++)
				{
				    SPacket.servers[SPacket.servers_count].name[i] = toupper((unsigned char)SPacket.servers[SPacket.servers_count].name[i]);
				}
		        SPacket.servers_count++;
		    }
			else
			{
			    buffer[size] = '\0';

			    if (strcmp(buffer, "Refresh") == 0)
			    {
			        SendPacket();
			    }
			}
		}
		#ifdef _WIN32
			Sleep(16);
		#else
			usleep(16000);
		#endif
	}
	return 0;
}
