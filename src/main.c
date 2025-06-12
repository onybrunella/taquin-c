/**
* @file main.c
 * @author Ony Brunella ANDRIATSAHAVOJAONA
 */

#include <stdio.h>
#include <time.h>
#include "../include/taquin.h"

int main(int argc, char *argv[]) {

    MLV_Image *image;
    Plateau plateau;

    MLV_create_window("Jeu de Taquin", "Taquin", TAILLE_IMAGE, TAILLE_IMAGE);

    if (argc < 2) {
        fprintf(stderr, "Usage : %s <image>\n", argv[0]);
        MLV_free_window();
        return 1;
    }
    image = MLV_load_image(argv[1]);
    if (!image) {
        fprintf(stderr, "Erreur : Impossible de charger l'image !!!!!!\n");
        return 1;
    }

    if (MLV_get_image_width(image) != TAILLE_IMAGE || MLV_get_image_height(image) != TAILLE_IMAGE) {
        fprintf(stderr, "Erreur : L'image doit être de taille %d x %d pixels\n", TAILLE_IMAGE, TAILLE_IMAGE);
        MLV_free_image(image);
        MLV_free_window();
        return 1;
    }

    MLV_resize_image(image, TAILLE_IMAGE, TAILLE_IMAGE);

    srand(time(NULL));

    initialiser_plateau(&plateau);

    melanger_plateau(&plateau, image);

    while (!est_resolu(&plateau)) {
        gerer_clic_souris(&plateau, image);
    }

    afficher_victoire();

    MLV_free_image(image);
    MLV_free_window();

    return 0;
}
