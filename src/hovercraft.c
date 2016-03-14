#include <stdlib.h>
#include <stdio.h>

#include "hovercraft.h"

Hovercraft * init_hovercraft(Coordonnees *pos) {
	Hovercraft *hc = malloc(1*sizeof(Hovercraft));
	hc->pos = pos;
	hc->vitesse = init_vecteur(0, 0);
	hc->acceleration = init_vecteur(0, 0);
	return hc;
}