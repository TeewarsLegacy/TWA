/* copyright (c) 2026 mykyta polishyk, see LICENSE file for more info */

#ifndef COLLISION_H
#define COLLISION_H

enum{
	SOLID=0,
	NOT_SOLID
};

void ColInit(Map object);
int ColIsSolid(int x, int y);
bool ColIntersectLine(int x0, int y0, int x1, int y1, int *outx, int *outy);

#endif
