/* copyright (c) 2007 magnus auvinen, see LICENSE file for more info */
/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#include <string.h>
#include <stdlib.h>
#include "network.h"
#include <SDL.h>

extern void ClientMain();
extern void ServerMain(int Port, char *Map, char *Name);

NetAddr MasterserverAddr;

extern "C" int main(int argc, char *argv[])
{
    MasterserverAddr.ip = inet_addr("127.0.0.1");
    MasterserverAddr.port = 6000;

	bool IsSrv = false;
    int Port = 5000;
    char *Map="dm1";
    char *SName="Unnamed server";

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-s") == 0) {
            IsSrv = true;
        }
        else if (strcmp(argv[i], "-p") == 0) {
            if (i + 1 < argc) {
                Port = atoi(argv[i + 1]);
                i++;
            }
        }
        else if (strcmp(argv[i], "-m") == 0) {
            Map = argv[i + 1];
        }
        else if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            SName = argv[++i];
        }
    }

    if (IsSrv) {
        ServerMain(Port, Map, SName);
    } else {
        ClientMain();
    }

    return 0;
}
