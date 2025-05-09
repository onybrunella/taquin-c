#ifndef PLATEAU_H
#define PLATEAU_H

#include <MLV/MLV_all.h>

#define NB_COL 4
#define NB_LIG 4

#define TAILLE_IMAGE 512  /* Taille de l’image (512x512 pixels) */
#define TAILLE_CASE (TAILLE_IMAGE / NB_LIG)  /* Taille d’une case (128x128 pixels) */

typedef struct carre{
  int lig;
  int col;
} Carre;

typedef struct plateau{
  Carre bloc[NB_COL][NB_LIG];
} Plateau;


/* Initialise le plateau avec les coordonnées de chaque bloc */
void InitialisationPlateau(Plateau *plateau);

void AfficherPlateau(Plateau *P, MLV_Image *image);

Carre TrouverCaseVide(Plateau *p);

Carre DeplacerCaseVide(Plateau *p);

void MelangerPlateau(Plateau *plateau, MLV_Image *img);

void GererClicSouris(Plateau *plateau, MLV_Image *img);
int estResolu(Plateau *p);
void afficherVictoire();

#endif
