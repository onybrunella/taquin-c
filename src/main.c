/**
* @file main.c
 * @author Ony Brunella ANDRIATSAHAVOJAONA
 */

#include <time.h>
#include "../include/graphique.h"
#include "../include/plateau.h"

#define DEFAULT_IMAGE_PATH "data/sun.png"

int main(int argc, char *argv[]) {
    MLV_Image *image, *resized_image;
    Plateau plateau;
    const char *image_path = DEFAULT_IMAGE_PATH;

    MLV_create_window("Jeu de Taquin", "Taquin", WINDOW_WIDTH, WINDOW_HEIGHT);

    if (argc >= 2) {
        image_path = argv[1];
    }

    image = MLV_load_image(image_path);
    if (!image) {
        fprintf(stderr, "Erreur : Impossible de charger l'image !!!!!!\n");
        return 1;
    }

    resized_image = MLV_create_image(TAILLE_IMAGE, TAILLE_IMAGE);
    MLV_resize_image_with_proportions(image, TAILLE_IMAGE, TAILLE_IMAGE);
    MLV_draw_image_on_image(image, resized_image, 0, 0);

    MLV_free_image(image);

    srand(time(NULL));
    initialiser_plateau(&plateau);
    melanger_plateau(&plateau, resized_image);

    time_t debut = time(NULL);

    while (!est_resolu(&plateau)) {
        if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) {
            gerer_clic_souris(&plateau, resized_image);
        }
        afficher_plateau(&plateau, resized_image);
        afficher_timer(debut);
        MLV_actualise_window();
        MLV_wait_milliseconds(16);
    }

    afficher_victoire(debut);
    MLV_free_image(resized_image);
    MLV_free_window();

    return 0;
}