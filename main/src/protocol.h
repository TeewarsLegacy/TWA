/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#ifndef PROTOCOL_H
#define PROTOCOL_H

/* Network input struct */
struct Input{
	int left;
	int right;
	int angle;
	int jump;
	int fire;
	int hook;
	int activeweapon;
};

/* Vertex of vertex map system, also this is like float, but 1 is 32/32 */
struct MapVertex{
	int x,y;
	bool last;
};

/* Map object like pickup and etc */
struct MapObject{
	int x,y;
	int type;
};

/* Map structure */
struct Map{
	// Count of objects
	int vertices_n;
	int objects_n;
	MapVertex vertices[1024];
	MapObject objects[64];
};

/* Server info struct */
struct ServerInfo{
	// Also, here is fixed count of max players (8)
	int players;
	char name[64];
	int have_password;
	char password[16];
};

enum{
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