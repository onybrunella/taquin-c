#ifndef PLATEAU_H
#define PLATEAU_H

#include <MLV/MLV_all.h>

#define NB_COL 4
#define NB_LIG 4

#define TAILLE_IMAGE 512
#define TAILLE_CASE (TAILLE_IMAGE / NB_LIG)

typedef struct carre {
    int lig;
    int col;
} Carre;

typedef struct plateau {
    Carre bloc[NB_COL][NB_LIG];
} Plateau;

void initialiser_plateau(Plateau *plateau);
Carre trouver_case_vide(Plateau *plateau);
Carre deplacer_case_vide(Plateau *plateau);
void melanger_plateau(Plateau *plateau, MLV_Image *img);
int est_resolu(Plateau *plateau);

#endif