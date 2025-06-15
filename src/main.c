/**
* @file main.c
 * @author Ony Brunella ANDRIATSAHAVOJAONA
 */
/*
#include <time.h>
#include "../include/graphique.h"
#include "../include/plateau.h"

#define DEFAULT_IMAGE_PATH "data/earth.png"

int main(int argc, char *argv[]) {

    MLV_Image *image;
    Plateau plateau;
    const char *image_path = DEFAULT_IMAGE_PATH;

    MLV_create_window("Jeu de Taquin", "Taquin", TAILLE_IMAGE, TAILLE_IMAGE);

    if (argc >= 2) {
        image_path = argv[1];
    }

    image = MLV_load_image(image_path);
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
}*/
/**
* @file main.c
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

    while (!est_resolu(&plateau)) {
        gerer_clic_souris(&plateau, resized_image);
    }

    afficher_victoire();
    MLV_free_image(resized_image);
    MLV_free_window();

    return 0;
}