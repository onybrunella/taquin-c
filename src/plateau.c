/**
 * @file plateau.c
 * @author Ony Brunella ANDRIATSAHAVOJAONA
 * @brief Fonctions de gestion du plateau du taquin (initialisation, mélange, déplacement, vérification)
 */

#include "../include/plateau.h"
#include "../include/graphique.h"

void initialiser_plateau(Plateau *p) {
    int i, j;
    for (i = 0; i < NB_LIG; i++) {
        for (j = 0; j < NB_COL; j++) {
            p->bloc[i][j].lig = i;
            p->bloc[i][j].col = j;
        }
    }
}

Carre trouver_case_vide(Plateau *p) {
    int i, j;
    Carre case_vide;
    for (i = 0; i < NB_LIG; i++) {
        for (j = 0; j < NB_COL; j++) {
            if (p->bloc[i][j].lig == NB_LIG - 1 && p->bloc[i][j].col == NB_COL - 1) {
                case_vide.lig = i;
                case_vide.col = j;
            }
        }
    }
    return case_vide;
}

Carre deplacer_case_vide(Plateau *p) {
    Carre case_vide = trouver_case_vide(p);
    int lig = case_vide.lig;
    int col = case_vide.col;

    int direction = rand() % 4;
    int new_lig = lig;
    int new_col = col;

    switch (direction) {
        case 0:
            if (lig > 0) new_lig = lig - 1;
            break;
        case 1:
            if (lig < NB_LIG - 1) new_lig = lig + 1;
            break;
        case 2:
            if (col > 0) new_col = col - 1;
            break;
        case 3:
            if (col < NB_COL - 1) new_col = col + 1;
            break;
    }

    if (new_lig != lig || new_col != col) {
        Carre temp = p->bloc[lig][col];
        p->bloc[lig][col] = p->bloc[new_lig][new_col];
        p->bloc[new_lig][new_col] = temp;
        case_vide.lig = new_lig;
        case_vide.col = new_col;

        printf("Case vide déplacée en : (%d, %d)\n", case_vide.lig, case_vide.col);
    }

    return case_vide;
}

void melanger_plateau(Plateau *p, MLV_Image *img) {
    int i;
    for (i = 0; i < 10; i++) {
        deplacer_case_vide(p);
        afficher_plateau(p, img);
        MLV_wait_milliseconds(20);
    }
}

int est_resolu(Plateau *p) {
    int i, j;
    for (i = 0; i < NB_LIG; i++) {
        for (j = 0; j < NB_COL; j++) {
            if (p->bloc[i][j].lig != i || p->bloc[i][j].col != j) {
                return 0;
            }
        }
    }
    return 1;
}
