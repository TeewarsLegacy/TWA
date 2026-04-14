/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#ifndef MAP_H
#define MAP_H

#include "protocol.h"

void LoadMap(Map *object, const char* map_name); // Parser of maps
void SendMap(Map object, char* string); // Transform map into string
void SaveMap(Map object, const char* map_name); // Saving map (Helpfull for editor)

#endif