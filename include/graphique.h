#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H

#include <MLV/MLV_all.h>
#include "plateau.h"
#include <time.h>

void afficher_plateau(Plateau *plateau, MLV_Image *image);
void gerer_clic_souris(Plateau *plateau, MLV_Image *image);
void formater_temps(time_t debut, time_t fin, char *buffer);
void afficher_timer(time_t debut);
void afficher_victoire(time_t debut);
#endif