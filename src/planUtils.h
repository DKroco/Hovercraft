#ifndef PLANUTILS_H
#define PLANUTILS_H

typedef struct {
	int x;
	int y;
} Coordonnees;

typedef Coordonnees Vecteur;

Coordonnees * init_coordonnees(int x, int y);
Vecteur * init_vecteur(int x, int y);

#endif