/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#include "map.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"

/* Parser of maps */
void LoadMap(Map *object, const char* map_name){
	FILE *file_pointer;
	// Editing path and loading
	char path[256] = "maps/";
	strcat(path, map_name);
	strcat(path, ".twlm");
	file_pointer = fopen(path, "r"); 
	if (!file_pointer) {
		fprintf(stderr, "Failed to open map %s", path);
		return;
	}
	// Parsing
	char character;
	char line_buffer[64];
    int line_number = 0;
    int n_vertex = 0;
    int n_objects = 0;
    int n_decorations = 0;
    bool is_object = false;
    bool is_decoration = false;
    // Reading lines
	while (fgets(line_buffer, sizeof(line_buffer), file_pointer)) {
        printf("Line: %s", line_buffer);
        // Checking is this object or not
        if (line_buffer[0] != ';'){ // If it tip we skip check
            if (strncmp(line_buffer, "point", 5) == 0) {
                is_object = false;
                is_decoration = false;
            }
            if (strncmp(line_buffer, "object", 6) == 0) {
                is_object = true;
                is_decoration = false;
                // Selection of object type
                if (strncmp(line_buffer + 7, "SPAWN" , 5) == 0){
                    object->objects[n_objects].type = SPAWN;
                }
                if (strncmp(line_buffer + 7, "WEAPON_GUN" , 10) == 0){
                    object->objects[n_objects].type = WEAPON_GUN;
                }
                if (strncmp(line_buffer + 7, "WEAPON_SHOTGUN" , 14) == 0){
                    object->objects[n_objects].type = WEAPON_SHOTGUN;
                }
                if (strncmp(line_buffer + 7, "WEAPON_RIFLE" , 12) == 0){
                    object->objects[n_objects].type = WEAPON_RIFLE;
                }
                if (strncmp(line_buffer + 7, "WEAPON_GRENADE" , 14) == 0){
                    object->objects[n_objects].type = WEAPON_GRENADE;
                }
                if (strncmp(line_buffer + 7, "ARMOR_1" , 7) == 0){
                    object->objects[n_objects].type = ARMOR_1;
                }
                if (strncmp(line_buffer + 7, "ARMOR_5" , 7) == 0){
                    object->objects[n_objects].type = ARMOR_5;
                }
                if (strncmp(line_buffer + 7, "ARMOR_10" , 8) == 0){
                    object->objects[n_objects].type = ARMOR_10;
                }
                if (strncmp(line_buffer + 7, "HEALTH_1" , 8) == 0){
                    object->objects[n_objects].type = HEALTH_1;
                }
                if (strncmp(line_buffer + 7, "HEALTH_5" , 8) == 0){
                    object->objects[n_objects].type = HEALTH_5;
                }
                if (strncmp(line_buffer + 7, "HEALTH_10" , 9) == 0){
                    object->objects[n_objects].type = HEALTH_10;
                }
            }
            if (strncmp(line_buffer, "deco", 4) == 0) {
                is_object = false;
                is_decoration = true;
                // Selection of decoration type
                object->decorations[n_decorations].type = atof(line_buffer + 4);
            }
            // Parsing position of it
            if (line_buffer[0] == 'x') {
                // If it object writing into object massive, else writing into vertices
                if (is_object == true){
                    object->objects[n_objects].x = round(atof(line_buffer + 1)*32);
                }
                else if (is_decoration == true){
                    object->decorations[n_decorations].x = round(atof(line_buffer + 1)*32);
                }
                else{
                    object->vertices[n_vertex].x = round(atof(line_buffer + 1)*32);
                }
            }
            if (line_buffer[0] == 'y') {
                // Same, but adding into counters
                if (is_object == true){
                    object->objects[n_objects].y = round(atof(line_buffer + 1)*32);
                    n_objects++;
                }
                else if (is_decoration == true){
                    object->decorations[n_decorations].y = round(atof(line_buffer + 1)*32);
                    n_decorations++;
                }
                else{
                    object->vertices[n_vertex].y = round(atof(line_buffer + 1)*32);
                    n_vertex++;
                }
            }
            if (strncmp(line_buffer, "break", 5) == 0) {
                object->vertices[n_vertex-1].last = true;
            }
        }
        line_number++;
    }
    // Cloning info about vertices into object
    object->vertices_n = n_vertex;
    object->objects_n = n_objects;
    object->decorations_n = n_decorations;
    fclose(file_pointer);
}