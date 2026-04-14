/* copyright (c) 2007 magnus auvinen, see LICENSE file for more info */
/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#include <string.h>

extern void ClientMain();
extern void ServerMain();

int main(int argc, char *argv[])
{
	// Checking arguments
	for (int i = 1; i<argc; i++){
		if (strcmp(argv[i], "-s") == 0){
			ServerMain();
			return 0;
		}
	}
	// If no arguments we launch client
	ClientMain();
	return 0;
}