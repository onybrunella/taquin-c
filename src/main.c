#include <stdio.h>
#include <time.h>
#include "taquin.h"

int main(int argc, char *argv[]) {

    MLV_Image *image;
    Plateau plateau;

    MLV_create_window("Jeu de Taquin", "Taquin", TAILLE_IMAGE, TAILLE_IMAGE);
    /*image = MLV_load_image("data/earth.png");*/
    if (argc < 2) {
      fprintf(stderr, "Usage : %s <image>\n", argv[0]);
      MLV_free_window();
      return 1;
  }
    image = MLV_load_image(argv[1]);
    if(!image){
        fprintf(stderr, "Erreur : Impossible de charger l'image !!!!!!\n");
        return 1;
    }
  

    /* Vérification de la taille de l'image (pour l'instant il faut qu'elle soit de taille 512*512) */
    if(MLV_get_image_width(image) != TAILLE_IMAGE || MLV_get_image_height(image) != TAILLE_IMAGE){
        fprintf(stderr, "Erreur : L'image doit être de taille %d x %d pixels\n", TAILLE_IMAGE, TAILLE_IMAGE);
        MLV_free_image(image);
        MLV_free_window();
        return 1;
    }


    MLV_resize_image(image, TAILLE_IMAGE, TAILLE_IMAGE);
    printf("%d\n",TAILLE_CASE);

    srand(time(NULL)); 

    InitialisationPlateau(&plateau);

   /*Carre case_vide = TrouverCaseVide(&plateau);
  printf("case vide: lig = %d, col = %d \n", casevide.lig, casevide.col);*/


    /*AfficherPlateau(&plateau, image);*/



      MelangerPlateau(&plateau, image);

      while (!estResolu(&plateau)) {
        GererClicSouris(&plateau, image);
      }

      afficherVictoire();    

  /*MLV_wait_mouse(NULL, NULL);*/
    MLV_free_image(image);
    MLV_free_window();
    
    return 0;
}
