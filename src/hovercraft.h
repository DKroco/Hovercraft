#ifndef HOVERCRAFT_H
#define HOVERCRAFT_H

#include "planUtils.h"

typedef struct {
	Coordonnees *pos;
	Vecteur *vitesse;
	Vecteur *acceleration;
} Hovercraft;

Hovercraft * init_hovercraft(Coordonnees *pos);

#endif