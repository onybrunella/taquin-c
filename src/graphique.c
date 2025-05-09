/**
 * @file graphique.c
 * @author Ony Brunella ANDRIATSAHAVOJAONA
 * @brief Fonctions d'affichage graphique du taquin à l'aide de la bibliothèque MLV
 *  */

 #include "taquin.h"
 #include <stdio.h>
 #include <stdlib.h>
 
 /**
  * @brief Affiche le plateau de jeu
  * 
  * @param p Pointeur vers le plateau
  * @param img Pointeur vers l'image
  */
 void AfficherPlateau(Plateau *p, MLV_Image *img) {
     if (!img || !p) return;
     MLV_clear_window(MLV_COLOR_BLACK);
     int i, j;
     for (i = 0; i < NB_LIG; i++) {
         for (j = 0; j < NB_COL; j++) {
             /* Récupération des coordonnées de la pièce */
             int lig_originale = p->bloc[i][j].lig;
             int col_originale = p->bloc[i][j].col;
             
             /* Coordonnées d'origine dans l'image */
             int src_x = col_originale * TAILLE_CASE;
             int src_y = lig_originale * TAILLE_CASE;
             
             /* Coordonnées de destination dans la fenêtre */
             int dest_x = j * TAILLE_CASE;
             int dest_y = i * TAILLE_CASE;
             
             /* Ne pas afficher la dernière case (case vide) */
             if (!(lig_originale == NB_LIG - 1 && col_originale == NB_COL - 1)) {
                 MLV_draw_partial_image(img, src_x, src_y, TAILLE_CASE, TAILLE_CASE, dest_x, dest_y);
             } else {
                 printf("Case vide en : (%d, %d)\n", i, j);
             }
         }
     }
     MLV_actualise_window();
 }
 
 /**
  * @brief Gère les clics de souris pour déplacer les pièces
  * 
  * @param p Pointeur vers le plateau
  * @param img Pointeur vers l'image
  */
 void GererClicSouris(Plateau *p, MLV_Image *img){
     int x, y;
     /* Attendre un clic de souris */
     MLV_wait_mouse(&x, &y);
     
     /* Convertir en indices de la grille */
     int lig = y / TAILLE_CASE;
     int col = x / TAILLE_CASE;
     
     /* Trouver la case vide */
     Carre case_vide = TrouverCaseVide(p);
     int lig_case_vide = case_vide.lig;
     int col_case_vide = case_vide.col;
     
     /* Vérifier si mouvement valide */
     if ((lig == lig_case_vide && (col - col_case_vide == 1 || col - col_case_vide == -1)) || 
         (col == col_case_vide && (lig - lig_case_vide == 1 || lig - lig_case_vide == -1))) {
         /* Échanger les pièces */
         Carre temp = p->bloc[lig][col];
         p->bloc[lig][col] = p->bloc[lig_case_vide][col_case_vide];
         p->bloc[lig_case_vide][col_case_vide] = temp;
     }
     
     /* Réafficher le plateau */
     AfficherPlateau(p, img);
 }
 
 /**
  * @brief Affiche un message de victoire
  */
 void afficherVictoire() {
     MLV_draw_text(200, 200, "VOUS AVEZ GAGNÉ !!!!!!!!!", MLV_COLOR_RED2);
     MLV_actualise_window();
     MLV_wait_seconds(2);
 }
 