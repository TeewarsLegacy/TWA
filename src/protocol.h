/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#ifndef PROTOCOL_H
#define PROTOCOL_H

#define MAX_PLAYERS 8

#include "types.h"
#include "network.h"

/* Network input struct */
struct NInput{
	// For all of these value from 0 to 1 (boolean)
	int left=0;
	int right=0;
	float angle=0;
	int jump=0;
	int fire=0;
	int hook=0;
	int active_weapon=0; // only 0-3 value
};

/* Network player appearance struct */
struct NPlayerAppearance{
	int skin_id;
	int body_color; // Now not using
	int legs_color; // also
};

/* Network player entity */
struct NPlayer{
	int id;
	char name[32];
	int x;
	int y;
	float angle;
	int active_weapon;
	int current_state;
	NPlayerAppearance appearance;
	NetAddr addr;
};
/* Vertex of vertex map system, also this is like float, but 1 is 32/32 */
struct MapVertex{
	int x,y;
	bool last; // TODO: Transform bool into int
};

/* Map object like pickup and etc */
struct MapObject{
	int x,y;
	int type;
};

/* Map decoration like tree, grass and etc */
struct MapDeco{
	int x,y;
	int type;
};

/* Map structure */
struct Map{
	// Count of objects
	int vertices_n;
	int objects_n;
	int decorations_n;
	MapVertex vertices[1024];
	MapObject objects[64];
	MapDeco decorations[128];
};

/* Network packet object */
struct NPacket{
	NPlayer players[MAX_PLAYERS];
	Map current_map; // TODO: Move map into map packet
};

/* Server info struct */
struct ServerInfo{
	// Also, here is fixed count of max players (8)
	int players_count;
	char name[19]="\0";
	int have_password=0;
	NetAddr addr;
};

/* Master server packet object */
struct NMSPacket{
	int servers_count=0;
	ServerInfo servers[1024];
};


enum{ //  Weapons
	GUN=0,
	SHOTGUN,
	RIFLE,
	GRENADE
};

enum{ // Skins
	SKIN_DEFAULT=0,
	SKIN_BLUEKITTY,
	SKIN_BLUESTRIPES,
	SKIN_BROWNBEAR,
	SKIN_PINKY,
	SKIN_REDBOPP,
	SKIN_CAMMOSTRIPES,
	SKIN_COALA,
	SKIN_LIMEKITTY,
	SKIN_CAMMO,
	SKIN_REDSTRIPE,
	SKIN_SADDO,
	SKIN_TOPTRI,
	SKIN_TWINBOP,
	SKIN_TWINTRI,
	SKIN_WARPAINT,
	SKIN_NINJA
};

enum{ // Game objects
	ITEM_NULL = 0,
	SPAWN,
	WEAPON_GUN,
	WEAPON_SHOTGUN,
	WEAPON_RIFLE,
	WEAPON_GRENADE,
	ARMOR_1,
	ARMOR_5,
	ARMOR_10,
	HEALTH_1,
	HEALTH_5,
	HEALTH_10
};

#endif