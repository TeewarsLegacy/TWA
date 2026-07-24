/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_gfxPrimitives.h"
#include "SDL/SDL_rotozoom.h"

#include "protocol.h"
#include "types.h"

#ifndef SCREEN_H
#define SCREEN_H

// Sprites global pointers
// Tees tileset (TODO: REMOVE THIS AND ADD 1 LEGS TILESET)
extern SDL_Surface *TeeTilesetLeft;
extern SDL_Surface *TeeTilesetRight;
// Tees tilesets
extern SDL_Surface *TeeBodiesTileset;
extern SDL_Surface *TeeLegsTileset;  // This have 3 frames
extern SDL_Surface *TeeEye;
// Weapons tileset
extern SDL_Surface *WeaponsTilesetLeft;
extern SDL_Surface *WeaponsTilesetRight;
// Armor and health icons tileset
extern SDL_Surface *HealthTileset;
extern SDL_Surface *ArmorTileset;
// Clouds tileset
extern SDL_Surface *CloudsTileset;
// Menu frame
extern SDL_Surface *MenuFrame;
// Server list frame
extern SDL_Surface *ServerlistFrame;
// Settings frame
extern SDL_Surface *SettingsFrame;
// Copyright
extern SDL_Surface *MenuCopyright;
// Menu background
extern SDL_Surface *MenuBackground;
// Arrow menu icon
extern SDL_Surface *MenuArrow;
// Server list bar
extern SDL_Surface *ServerlistBar;
// Settings icons
extern SDL_Surface *SettingsIcons;
// Checkbox
extern SDL_Surface *Checkbox;
// Cool 3D banner
extern SDL_Surface *Banner;
// Text tileset
extern SDL_Surface *TextTileset; // This have 36 frames
// Mouse cursor
extern SDL_Surface *Cursor;
// Map decorations
extern SDL_Surface *DecorationsTileset;
// Mountians
extern SDL_Surface *Mountians;

enum{ // Weapons tileset (TODO: REMOVE THIS AND START USE WEAPONS NAMES FROM PROTOCOL)
	gun=1,
	rifle,
	shotgun,
	grenade
};

enum{ // Health tileset
	health1=1,
	health5,
	health10
};

enum{ // Armor tileset
	armor1=1,
	armor5,
	armor10
};

// GFX important functions
void LoadSprites(); // Load sprites into pointers
void DrawRectangle(int x, int y, int w, int h, int color); // Draw rectange with size and color
SDL_Surface* LoadTexture(char *path); // Load texture into surface
void DrawSurface(SDL_Surface *surface, int x, int y, int color); // Draw surface with size and color
void DrawAnimationSurface(SDL_Surface *surface, int x, int y, int color, int numofframes, int frame, int angle=0); // Drawing surface, but with frame animation (Can be helpfull in animations)
// Game GFX functions
void DrawTee(int x, int y, int state, NPlayerAppearance appearance, float angle, int weapon_type, int color); // Drawing player with animation
void DrawMap(int x, int y, Map *object); // Draw map with game objects (like pickups and etc)
void DrawBackground(int offsetx, int offsety); // Drawing clouds and mountians with paralax
int StringLength(); // Return length of string in pixels
void DrawString(int x, int y, char *string, int color); // Drawing text using text atlas
void DrawCompressedString(int x, int y, char *string, int color); // Drawing compressed text using text atlas
void DrawAnimatedString(int x, int y, char *string, int color); // Drawing text using text atlas with cool effect
void DrawStringWithUnderline(int x, int y, char *string, int color); // Drawing text using text atlas with underline
void DrawCursor(); // Drawing cursor
void DrawCheckbox(int x, int y, bool active); // Drawing checkbox
#endif