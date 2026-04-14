/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */
#include "stdio.h"

#define GROUND_CONTROL_SPEED 10.0f
#define GROUND_FRICTION 0.5f
#define GROUND_JUMP_IMPULSE 11.5f
#define GRAVITY 0.5
#define HOOK_LENGTH 380.0f
#define HOOK_FIRE_SPEED 80.0f
#define HOOK_DRAG_ACCEL 3.0f
#define HOOK_DRAG_SPEED 15.0f

#include "map.h"

void server_main(){
	Map object;
	LoadMap(&object, "dm1");
}