/**
* @file graphique.c
 * @author Ony Brunella ANDRIATSAHAVOJAONA
 * @brief Fonctions d'affichage graphique du taquin à l'aide de la bibliothèque MLV
 */

#include "../include/graphique.h"

void afficher_plateau(Plateau *p, MLV_Image *img) {
    if (!img || !p) return;
    MLV_clear_window(MLV_COLOR_BLACK);
    /*afficher l'img originale à droite*/
    MLV_Image* img_reduite = MLV_copy_image(img);
    int taille_img_reduite = TAILLE_IMAGE / 2;
    MLV_resize_image(img_reduite, taille_img_reduite, taille_img_reduite);

    int zone_x = TAILLE_IMAGE + IMAGE_GAP;
    int zone_y = 0;
    int zone_largeur = TAILLE_IMAGE;
    int zone_hauteur = TAILLE_IMAGE;

    int x_img = zone_x + (zone_largeur - taille_img_reduite) / 2;
    int y_img = zone_y + (zone_hauteur - taille_img_reduite) / 2;

    MLV_draw_image(img_reduite, x_img, y_img);

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

void gerer_clic_souris(Plateau *p, MLV_Image *img){
    int x, y;
    MLV_get_mouse_position(&x, &y);

    /* Vérifie si le bouton gauche est pressé */
    if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) != MLV_PRESSED) {
        return;
    }

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
    MLV_wait_milliseconds(100);
}

void formater_temps(time_t debut, time_t fin, char *buffer) {
    int secondes = (int)difftime(fin, debut);
    int minutes = secondes / 60;
    int reste_secondes = secondes % 60;
    sprintf(buffer, "%02d:%02d", minutes, reste_secondes);
}

void afficher_timer(time_t debut) {
    char temps[10];
    formater_temps(debut, time(NULL), temps);

    MLV_draw_filled_rectangle(TAILLE_IMAGE + IMAGE_GAP, 10, 200, 30, MLV_COLOR_BLACK);
    MLV_draw_text(TAILLE_IMAGE + IMAGE_GAP, 10, temps, MLV_COLOR_WHITE);
}

void afficher_victoire(time_t debut) {
    char temps[10];
    char message[100];
    formater_temps(debut, time(NULL), temps);
    sprintf(message, "VOUS AVEZ GAGNÉ !!!\nTemps: %s", temps);

    MLV_draw_filled_rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
                            MLV_rgba(0, 0, 0, 128));

    MLV_draw_adapted_text_box(
        (WINDOW_WIDTH / 2), (WINDOW_HEIGHT / 3),
        message,
        40,
        MLV_rgba(0, 255, 0, 255),
        MLV_rgba(0, 0, 0, 200),
        MLV_rgba(0, 255, 0, 255),
        MLV_TEXT_CENTER
    );

    MLV_actualise_window();
    MLV_wait_seconds(3);
}