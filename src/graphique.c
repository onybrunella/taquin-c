/**
* @file graphique.c
 * @author Ony Brunella ANDRIATSAHAVOJAONA
 * @brief Fonctions d'affichage graphique du taquin à l'aide de la bibliothèque MLV
 */

#include "../include/taquin.h"

/**
 * Affiche le plateau de jeu
 */
void afficher_plateau(Plateau *p, MLV_Image *img) {
    if (!img || !p) return;
    MLV_clear_window(MLV_COLOR_BLACK);
    int i, j;
    for (i = 0; i < NB_LIG; i++) {
        for (j = 0; j < NB_COL; j++) {
            int lig_originale = p->bloc[i][j].lig;
            int col_originale = p->bloc[i][j].col;

            int src_x = col_originale * TAILLE_CASE;
            int src_y = lig_originale * TAILLE_CASE;

            int dest_x = j * TAILLE_CASE;
            int dest_y = i * TAILLE_CASE;

            /*n'affiche pas la case vide*/
            if (!(lig_originale == NB_LIG - 1 && col_originale == NB_COL - 1)) {
                MLV_draw_partial_image(img, src_x, src_y, TAILLE_CASE, TAILLE_CASE, dest_x, dest_y);
            }
        }
    }
    MLV_actualise_window();
}

/**
 * Gère les clics de souris pour déplacer les pièces
 */
void gerer_clic_souris(Plateau *p, MLV_Image *img){
    int x, y;
    MLV_wait_mouse(&x, &y);

    int lig = y / TAILLE_CASE;
    int col = x / TAILLE_CASE;

    Carre case_vide = trouver_case_vide(p);
    int lig_case_vide = case_vide.lig;
    int col_case_vide = case_vide.col;

    if ((lig == lig_case_vide && (col - col_case_vide == 1 || col - col_case_vide == -1)) ||
        (col == col_case_vide && (lig - lig_case_vide == 1 || lig - lig_case_vide == -1))) {
        Carre temp = p->bloc[lig][col];
        p->bloc[lig][col] = p->bloc[lig_case_vide][col_case_vide];
        p->bloc[lig_case_vide][col_case_vide] = temp;
        }

    afficher_plateau(p, img);
}

/**
 * Affiche un message de victoire
 */
void afficher_victoire() {
    MLV_draw_text(200, 200, "VOUS AVEZ GAGNÉ !!!!!!!!!", MLV_COLOR_RED2);
    MLV_actualise_window();
    MLV_wait_seconds(2);
}
