/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#include <string.h>

extern void client_main();
extern void server_main();

int main(int argc, char *argv[])
{
	// Checking arguments
	for (int i = 1; i<argc; i++){
		if (strcmp(argv[i], "-s") == 0){
			server_main();
			return 0;
		}
	}
	// If no arguments we launch client
	client_main();
	return 0;
}