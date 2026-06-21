/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */

#include "screen.h"
#include "math.h"

// Global objects
extern SDL_Surface *Screen;
extern int MouseX, MouseY;

// Tees tileset
SDL_Surface *TeeTilesetLeft;
SDL_Surface *TeeTilesetRight;
// Weapons tileset
SDL_Surface *WeaponsTilesetLeft;
SDL_Surface *WeaponsTilesetRight;
// Armor and health icons tileset
SDL_Surface *HealthTileset;
SDL_Surface *ArmorTileset;
// Clouds tileset
SDL_Surface *CloudsTileset;
// Menu frame
SDL_Surface *MenuFrame;
// Server list frame
SDL_Surface *ServerlistFrame;
// Settings frame
SDL_Surface *SettingsFrame;
// Copyright
SDL_Surface *MenuCopyright;
// Menu background
SDL_Surface *MenuBackground;
// Arrow menu icon
SDL_Surface *MenuArrow;
// Server list bar
SDL_Surface *ServerlistBar;
// Settings icons
SDL_Surface *SettingsIcons;
// Checkbox
SDL_Surface *Checkbox;
// Cool 3D banner
SDL_Surface *Banner;
// Text tileset
SDL_Surface *TextTileset;
// Mouse cursor
SDL_Surface *Cursor;
// Map decorations
SDL_Surface *DecorationsTileset;
// Mountians
SDL_Surface *Mountians;

char TextFromTileset[37] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

/* Load sprites into pointers */
void LoadSprites(){
	TeeTilesetLeft = LoadTexture("data/tees_left.png");
	TeeTilesetRight = LoadTexture("data/tees_right.png");
	WeaponsTilesetLeft = LoadTexture("data/weapons_left.png");
	WeaponsTilesetRight = LoadTexture("data/weapons_right.png");
	HealthTileset = LoadTexture("data/health.png");
	ArmorTileset = LoadTexture("data/armor.png");
	CloudsTileset = LoadTexture("data/clouds.png");
	MenuFrame = LoadTexture("data/menu_frame.png");
	ServerlistFrame = LoadTexture("data/serverlist_frame.png");
	SettingsFrame = LoadTexture("data/settings_frame.png");
	MenuCopyright = LoadTexture("data/copyright.png");
	MenuBackground = LoadTexture("data/background.png");
	MenuArrow = LoadTexture("data/arrow.png");
	ServerlistBar = LoadTexture("data/serverlist_bar.png");
	Banner = LoadTexture("data/banner.png");
	TextTileset = LoadTexture("data/text.png");
	Cursor = LoadTexture("data/cursor.png");
	DecorationsTileset = LoadTexture("data/decorations.png");
	Mountians = LoadTexture("data/mountians.png");
	SettingsIcons = LoadTexture("data/settings_icons.png");
	Checkbox = LoadTexture("data/checkbox.png");
}

/* Draw rectange with size and color */
void DrawRectangle(int x, int y, int w, int h, int color){
	SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    // Fill rect with color
    SDL_FillRect(Screen, &rect, color);
}

/* Load texture into surface */
SDL_Surface* LoadTexture(char *path){
	return IMG_Load(path); // Loading image into surface pointer
}

/* Draw surface with size and color */
void DrawSurface(SDL_Surface *surface, int x, int y, int color){

	SDL_Rect dest; // Position of surface
	dest.x = x;
	dest.y = y;

	// Drawing surface
	SDL_BlitSurface(surface, NULL, Screen, &dest);
}

/* Drawing surface, but with frame animation */
void DrawAnimationSurface(SDL_Surface *surface, int x, int y, int color, int numofframes, int frame, int angle) {
    // Calculating sprite height
    int frame_h = surface->h / numofframes;
    
    SDL_Surface* single_frame = SDL_CreateRGBSurface(
        SDL_SWSURFACE, surface->w, frame_h, surface->format->BitsPerPixel,
        surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask
    );

    Uint32 old_flags = surface->flags & SDL_SRCALPHA;
    if (old_flags) {
        SDL_SetAlpha(surface, 0, 0);
    }

    if (surface->flags & SDL_SRCCOLORKEY) {
        SDL_SetColorKey(single_frame, SDL_SRCCOLORKEY, surface->format->colorkey);
    }
    
    SDL_Rect src;
    src.x = 0;
    src.y = (frame - 1) * frame_h;
    src.w = surface->w;
    src.h = frame_h;
    
    // Copy the single frame from the sheet onto our temp surface
    SDL_BlitSurface(surface, &src, single_frame, NULL);

    // Restore original alpha flags back to asset tileset
    if (old_flags) {
        SDL_SetAlpha(surface, SDL_SRCALPHA, surface->format->alpha);
    }

    // Rotating isolated surface
    SDL_Surface* rotated_frame = rotozoomSurface(single_frame, angle, 1.0, 1);

	if (surface->flags & SDL_SRCCOLORKEY) {
        SDL_SetColorKey(rotated_frame, SDL_SRCCOLORKEY, surface->format->colorkey);
    } else if (old_flags && rotated_frame) {
        SDL_SetAlpha(rotated_frame, SDL_SRCALPHA, surface->format->alpha);
    }

    SDL_Rect dest;
    dest.x = x - (rotated_frame->w - single_frame->w) / 2;
    dest.y = y - src.h - (rotated_frame->h - single_frame->h) / 2;

    // Drawing surface
    SDL_BlitSurface(rotated_frame, NULL, Screen, &dest);

    // Removing those buffers
    SDL_FreeSurface(single_frame);
    SDL_FreeSurface(rotated_frame);
}


/* Drawing player with color, and animation */
void DrawTee(int x, int y, int state, float angle, int weapon_type, int color){
	switch (state){
		case walk_left:
			DrawAnimationSurface(TeeTilesetLeft, x, y, color, 4, tee_walk1);
			break;
		case walk_right:
			DrawAnimationSurface(TeeTilesetRight, x, y, color, 4, tee_walk1);
			break;
		case idle_left:
			DrawAnimationSurface(TeeTilesetLeft, x, y, color, 4, tee_idle);
			break;
		case idle_right:
			DrawAnimationSurface(TeeTilesetRight, x, y, color, 4, tee_idle);
			break;
		case fall_left:
			DrawAnimationSurface(TeeTilesetLeft, x, y, color, 4, tee_jump);
			break;
		case fall_right:
			DrawAnimationSurface(TeeTilesetRight, x, y, color, 4, tee_jump);
			break;
	}
	if (angle >= 180){
		DrawAnimationSurface(WeaponsTilesetRight, x, y, SDL_MapRGBA(Screen->format, 255, 255, 255, 255), 4, gun, angle+90);
	}
	else{
		DrawAnimationSurface(WeaponsTilesetLeft, x, y, SDL_MapRGBA(Screen->format, 255, 255, 255, 255), 4, gun, angle+90);
	}

	
}
/* Draw map with game objects (like pickups and etc) */
void DrawMap(int x, int y, Map *object){
	Sint16 vx[1024];
    Sint16 vy[1024];

    int count = 0;
    // Drawing map polygon with outline
    for (int i = 0; i < object->vertices_n; i++)
    {
        vx[count] = object->vertices[i].x + x;
        vy[count] = object->vertices[i].y + y;
        count++;

        // if this last polygon we draw polygon
        if (object->vertices[i].last == true || i == object->vertices_n - 1)
        {
            if (count >= 3)
            {
                filledPolygonRGBA(Screen,
                                  vx, vy,
                                  count,
                                  100, 70, 20, 255);
                polygonRGBA(Screen,
                            vx, vy,
                            count,
                            0, 0, 0, 255);
            }

            count = 0; // reseting counter
        }
    }
    // Draw objects with different sprites
	for(int i=0;i<object->decorations_n;i++){
		switch (object->decorations[i].type){
			case 1:
				DrawAnimationSurface(DecorationsTileset, object->decorations[i].x + x, object->decorations[i].y + y, SDL_MapRGBA(Screen->format, 255, 255, 255, 255),4,1);
				break;
			case 2:
				DrawAnimationSurface(DecorationsTileset, object->decorations[i].x + x, object->decorations[i].y + y, SDL_MapRGBA(Screen->format, 255, 255, 255, 255),4,2);
				break;
			case 3:
				DrawAnimationSurface(DecorationsTileset, object->decorations[i].x + x, object->decorations[i].y + y, SDL_MapRGBA(Screen->format, 255, 255, 255, 255),4,3);
				break;
			case 4:
				DrawAnimationSurface(DecorationsTileset, object->decorations[i].x + x, object->decorations[i].y + y, SDL_MapRGBA(Screen->format, 255, 255, 255, 255),4,4);
				break;
		}
	}
	// Draw objects with different sprites
	for(int i=0;i<object->objects_n;i++){
		switch (object->objects[i].type){
			case SPAWN:
				break;
			case WEAPON_GUN:
				DrawAnimationSurface(WeaponsTilesetRight, object->objects[i].x + x + sin(SDL_GetTicks()/500.0f)*5, object->objects[i].y + y + sin(SDL_GetTicks()/250.0f)*5, SDL_MapRGBA(Screen->format, 255, 255, 255, 255),4,gun);
				break;
			case WEAPON_SHOTGUN:
				DrawAnimationSurface(WeaponsTilesetRight, object->objects[i].x + x + sin(SDL_GetTicks()/500.0f)*5, object->objects[i].y + y + sin(SDL_GetTicks()/250.0f)*5, SDL_MapRGBA(Screen->format, 255, 255, 255, 255),4,shotgun);
				break;
			case WEAPON_RIFLE:
				DrawAnimationSurface(WeaponsTilesetRight, object->objects[i].x + x + sin(SDL_GetTicks()/500.0f)*5, object->objects[i].y + y + sin(SDL_GetTicks()/250.0f)*5, SDL_MapRGBA(Screen->format, 255, 255, 255, 255),4,rifle);
				break;
			case WEAPON_GRENADE:
				DrawAnimationSurface(WeaponsTilesetRight, object->objects[i].x + x + sin(SDL_GetTicks()/500.0f)*5, object->objects[i].y + y + sin(SDL_GetTicks()/250.0f)*5, SDL_MapRGBA(Screen->format, 255, 255, 255, 255),4,grenade);
				break;
			case ARMOR_1:
				DrawAnimationSurface(ArmorTileset, object->objects[i].x + x + sin(SDL_GetTicks()/500.0f)*5, object->objects[i].y + y + sin(SDL_GetTicks()/250.0f)*5, SDL_MapRGBA(Screen->format, 255, 255, 255, 255),3,1);
				break;
			case ARMOR_5:
				DrawAnimationSurface(ArmorTileset, object->objects[i].x + x + sin(SDL_GetTicks()/500.0f)*5, object->objects[i].y + y + sin(SDL_GetTicks()/250.0f)*5, SDL_MapRGBA(Screen->format, 255, 255, 255, 255),3,2);
				break;
			case ARMOR_10:
				DrawAnimationSurface(ArmorTileset, object->objects[i].x + x + sin(SDL_GetTicks()/500.0f)*5, object->objects[i].y + y + sin(SDL_GetTicks()/250.0f)*5, SDL_MapRGBA(Screen->format, 255, 255, 255, 255),3,3);
				break;
			case HEALTH_1:
				DrawAnimationSurface(HealthTileset, object->objects[i].x + x + sin(SDL_GetTicks()/500.0f)*5, object->objects[i].y + y + sin(SDL_GetTicks()/250.0f)*5, SDL_MapRGBA(Screen->format, 255, 255, 255, 255),3,1);
				break;
			case HEALTH_5:
				DrawAnimationSurface(HealthTileset, object->objects[i].x + x + sin(SDL_GetTicks()/500.0f)*5, object->objects[i].y + y + sin(SDL_GetTicks()/250.0f)*5, SDL_MapRGBA(Screen->format, 255, 255, 255, 255),3,2);
				break;
			case HEALTH_10:
				DrawAnimationSurface(HealthTileset, object->objects[i].x + x + sin(SDL_GetTicks()/500.0f)*5, object->objects[i].y + y + sin(SDL_GetTicks()/250.0f)*5, SDL_MapRGBA(Screen->format, 255, 255, 255, 255),3,3);
				break;
		}
	}
}

/* Drawing fully animated clouds */
void DrawBackground(int offsetx, int offsety){
	// Drawing mountians
	DrawSurface(Mountians, 0, 200, SDL_MapRGBA(Screen->format, 255, 255, 255, 255));

    // Very buggy cloud code
	int Distance = 300;
    int worldWidth = 1600;
    for (int i = 0; i < worldWidth / Distance + 3; i++)
    {
        int baseX = i * Distance;

        float x1 = baseX - offsetx * 0.6f;
        float y1 = 140 + sin((SDL_GetTicks() / 800.0f) + i * 2) * 6 + offsety;

        if (x1 < -200) x1 += worldWidth;
        if (x1 > worldWidth) x1 -= worldWidth;

        DrawAnimationSurface(
            CloudsTileset,
            x1, y1,
            SDL_MapRGBA(Screen->format, 255, 255, 255, 255),
            2,
            1
        );

        DrawAnimationSurface(
            CloudsTileset,
            x1 - worldWidth, y1,
            SDL_MapRGBA(Screen->format, 255, 255, 255, 255),
            2,
            1
        );
    }
}

/* Drawing text using text atlas */
void DrawString(int x, int y, char *string, int color){
    for(int n = 0; n < strlen(string); n++){
    	for (int i = 0; i < strlen(TextFromTileset); i++){
    		if (TextFromTileset[i] == string[n]){
				DrawAnimationSurface(TextTileset, x + n * 24, y, color, 36, i+1);
    		}
    	}
    }
}

void DrawCompressedString(int x, int y, char *string, int color){
	for(int n = 0; n < strlen(string); n++){
    	for (int i = 0; i < strlen(TextFromTileset); i++){
    		if (TextFromTileset[i] == string[n]){
				DrawAnimationSurface(TextTileset, x + n * 20, y, color, 36, i+1);
    		}
    	}
    }
}

/* Drawing text using text atlas with cool effect */
void DrawAnimatedString(int x, int y, char *string, int color){
    for(int n = 0; n < strlen(string); n++){
    	for (int i = 0; i < strlen(TextFromTileset); i++){
    		if (TextFromTileset[i] == string[n]){
				DrawAnimationSurface(TextTileset, x + n * 32, y + sin((SDL_GetTicks()/500.0)+n*0.1)*15, color, 36, i+1);
    		}
    	}
    }
}

/* Drawing text using text atlas with underline */
void DrawStringWithUnderline(int x, int y, char *string, int color){
	// Underline
    DrawRectangle(x+2+4, y+2, 24*strlen(string), 4, SDL_MapRGBA(Screen->format, 0, 0, 0, 255));  // Shadow for underline
    DrawRectangle(x+4, y, 24*strlen(string), 4, color);
    // Text
    for(int n = 0; n < strlen(string); n++){
    	for (int i = 0; i < strlen(TextFromTileset); i++){
    		if (TextFromTileset[i] == string[n]){
				DrawAnimationSurface(TextTileset, x + n * 24, y, color, 36, i+1);
    		}
    	}
    }
}

/* Drawing cursor  */
void DrawCursor(){
	DrawSurface(Cursor, MouseX-50/2,MouseY-50/2,SDL_MapRGBA(Screen->format, 255, 255, 255, 255));
}

/* Drawing checkbox */
void DrawCheckbox(int x, int y, bool active){
	int selection;
	if (active == true){
		selection = 2;
	}
	else{
		selection = 1;
	}

	DrawAnimationSurface(Checkbox, x, y, SDL_MapRGBA(Screen->format, 0, 0, 0, 255), 2, selection);
}