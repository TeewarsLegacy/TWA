#include "screen.h"
#include "math.h"

// Global objects
extern SDL_Surface *Screen;

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
// Copyright
SDL_Surface *MenuCopyright;
// Menu background
SDL_Surface *MenuBackground;
// Arrow menu icon
SDL_Surface *MenuArrow;
// Server list bar
SDL_Surface *ServerlistBar;
// Cool 3D banner
SDL_Surface *Banner;
// Text tileset
SDL_Surface *TextTileset;
// Cursor
SDL_Surface *Cursor;

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
	MenuCopyright = LoadTexture("data/copyright.png");
	MenuBackground = LoadTexture("data/background.png");
	MenuArrow = LoadTexture("data/arrow.png");
	ServerlistBar = LoadTexture("data/serverlist_bar.png");
	Banner = LoadTexture("data/banner.png");
	TextTileset = LoadTexture("data/text.png");
	Cursor = LoadTexture("data/cursor.png");
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
	SDL_Rect dest; // Pos of surface
	dest.x = x;
	dest.y = y;

	// Drawing surface
	SDL_BlitSurface(surface, NULL, Screen, &dest);
}

/* Drawing surface, but with frame animation */
void DrawAnimationSurface(SDL_Surface *surface, int x, int y, int color, int numofframes, int frame){
	// Crop frame 
	SDL_Rect src;
	src.x = 0;
	src.y = (frame-1)*(surface->h/numofframes);
	src.w = surface->w;
	src.h = surface->h / numofframes;

	SDL_Rect point2;
	point2.x = x;
	point2.y = y-src.h;

	// Drawing surface
	SDL_BlitSurface(surface, &src, Screen, &point2);
}

/* Drawing player with color, and animation */
void DrawTee(int x, int y, PlayerState state, int color){
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
void DrawClouds(){
    for (int i=0; i<(800/128)+1; i++){
        int n;
        // Selection of sinus direction
        if (i%2 == 0){
            n = -1;
        }
        else{
            n = 1;
        }
        // Drawing surface
        DrawAnimationSurface(CloudsTileset, i*128, 60-sin(SDL_GetTicks()/500.0f)*5*n, SDL_MapRGBA(Screen->format, 255, 255, 255, 255), 2, 1+i%2);
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