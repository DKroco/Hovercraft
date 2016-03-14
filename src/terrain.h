#ifndef TERRAIN_H
#define TERRAIN_H

#include "planUtils.h"

typedef struct {
	Coordonnees pos;
	int rayon;
} Checkpoint;

typedef struct {
	int nbCheckpoints;
	struct Checkpoint[] Checkpoints;
} Terrain;

#endif