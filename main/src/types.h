/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */

#ifndef TYPES_H
#define TYPES_H

/* Menu state */
enum MenuState{
	m_titlescreen=0,
	m_serverlist, // Servers list
	m_authors, // Game authors screen
	m_help,
	m_online, // Nothing, because player ingame
	m_pausemenu, // Pause menu
	m_exit // Exit from game
};

/* Player state */
enum PlayerState{
	walk_left = 0,
	walk_right,
	idle_left,
	idle_right,
	fall_left,
	fall_right
};

/* Game settings structure */
struct GamePreferences{
	char name[32] = "Nameless tee";
	char clan[32] = "No clan";
	int volume=0;
	bool fullscreen=false;
};

#endif
