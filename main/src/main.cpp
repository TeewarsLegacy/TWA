/* copyright (c) 2007 magnus auvinen, see LICENSE file for more info */
/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#include <string.h>
#include <stdlib.h>

extern void ClientMain();
extern void ServerMain(int Port);

int main(int argc, char *argv[])
{
	bool IsSrv = false;
    int Port = 80;

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
    }

    if (IsSrv) {
        ServerMain(Port);
    } else {
        ClientMain();
    }
}