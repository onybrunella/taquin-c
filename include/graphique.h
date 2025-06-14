#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H

#include <MLV/MLV_all.h>
#include "plateau.h"

void afficher_plateau(Plateau *plateau, MLV_Image *image);
void gerer_clic_souris(Plateau *plateau, MLV_Image *image);
void afficher_victoire();

#endif