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
    bool is_object = false;
    // Reading lines
	while (fgets(line_buffer, sizeof(line_buffer), file_pointer)) {
        printf("Line: %s", line_buffer);
        // Checking is this object or not
        if (line_buffer[0] != ';'){ // If it tip we skip check
            if (strncmp(line_buffer, "point", 5) == 0) {
                is_object = false;
            }
            if (strncmp(line_buffer, "object", 6) == 0) {
                is_object = true;
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
            // Parsing position of it
            if (line_buffer[0] == 'x') {
                // If it object writing into object massive, else writing into vertices
                if (is_object == true){
                    object->objects[n_objects].x = round(atof(line_buffer + 1)*32);
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

    // Debug output
    for (int i = 0; i < n_vertex; i ++){
    	printf("Vertex %d on pos %d %d\n", i, object->vertices[i].x, object->vertices[i].y);
    }
    fclose(file_pointer);
}