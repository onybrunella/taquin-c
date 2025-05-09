
#include "taquin.h"
#include <stdio.h>
#include <stdlib.h>


/* afficher plateau avec image et libMLV */
void AfficherPlateau(Plateau *p, MLV_Image *img) {
    if (!img || !p) return;
    MLV_clear_window(MLV_COLOR_BLACK);
    int i, j;
    for (i = 0; i < NB_LIG; i++) {
        for (j = 0; j < NB_COL; j++) {
            /* Récupération des coordonnées de la pièce */
            /*int lig_originale = P->bloc[i][j].lig;
            int col_originale = P->bloc[i][j].col;*/
  
            int lig_originale = p->bloc[i][j].lig;
            int col_originale = p->bloc[i][j].col;
  
            /* Coordonnées d’origine dans l’image */
            int src_x = col_originale * TAILLE_CASE; /*(512/4)*/
            int src_y = lig_originale * TAILLE_CASE; /*(512/4)*/
            /* Coordonnées de destination dans la fenêtre */
            int dest_x = j * TAILLE_CASE;
            int dest_y = i * TAILLE_CASE;
  
            /* Ne pas afficher la dernière case (case vide) */
            /*if (!(i == NB_LIG - 1 && j == NB_COL - 1)) {*/
            if (!(lig_originale == NB_LIG - 1 && col_originale == NB_COL - 1)) {
                MLV_draw_partial_image(img, src_x, src_y, TAILLE_CASE, TAILLE_CASE, dest_x, dest_y);
            } else{
              printf("Case vide en : (%d, %d)\n", i, j);
            }
        }
    }
    MLV_actualise_window();
  }

/*fonction pour gerer clis de souris*/
void GererClicSouris(Plateau *p, MLV_Image *img){
    int x,y;
    /*attendre que l'user clique sur le bouton gauche de sa souris*/
    MLV_wait_mouse(&x, &y);
    int lig = y / TAILLE_CASE; /*récupère la coordonnée de la ligne*/
    int col = x / TAILLE_CASE; /*j'expliquerais mieux plus tard */
  
    Carre case_vide = TrouverCaseVide(p);
    int lig_case_vide = case_vide.lig;
    int col_case_vide = case_vide.col;
  
    /*if ((lig == lig_case_vide && abs(col - col_case_vide) == 1) || (col == col_case_vide && abs(lig - lig_case_vide) == 1)) {*/
    if ((lig == lig_case_vide && (col - col_case_vide == 1 || col - col_case_vide == -1)) ||  (col == col_case_vide && (lig - lig_case_vide == 1 || lig - lig_case_vide == -1))) {
      /*échanger les pièces */
      Carre temp = p->bloc[lig][col];  /*origine*/
      p->bloc[lig][col] = p->bloc[lig_case_vide][col_case_vide];  /*destination*/
      p->bloc[lig_case_vide][col_case_vide] = temp;   /*échange*/
    }
    AfficherPlateau(p, img);
  }

  void afficherVictoire() {
    MLV_draw_text(200, 200, "VOUS AVEZ GAGNÉ !!!!!!!!!", MLV_COLOR_RED2);
    MLV_actualise_window();
    MLV_wait_seconds(2);
  }