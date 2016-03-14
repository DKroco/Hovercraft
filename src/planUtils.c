#include <stdlib.h>
#include <stdio.h>

#include "planUtils.h"

Coordonnees * init_coordonnees(int x, int y) {
	Coordonnees *c = malloc(1*sizeof(Coordonnees));
	c->x = x;
	c->y = y;
	return c;
}

Vecteur * init_vecteur(int x, int y) {
	Vecteur *v = malloc(1*sizeof(Vecteur));
	v->x = x;
	v->y = y;
	return v;
}