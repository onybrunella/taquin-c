/**
 * @file plateau.c
 * @author ONy Brunella ANDRIATSAHAVOJAONA
 * @brief Fonctions de gestion du plateau du taquin (initialisation, mélange, déplacement, vérification)
 */

 #include "taquin.h"
 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 
 /**
  * @brief Initialise le plateau en plaçant chaque pièce à sa position d'origine
  * 
  * @param p Pointeur vers le plateau
  */
 void InitialisationPlateau(Plateau *p){
     int i, j;
     for(i = 0; i < NB_LIG; i++){
         for(j = 0; j < NB_COL; j++){
             ((p->bloc)[i][j]).lig = i;
             ((p->bloc)[i][j]).col = j;
         }
     }
 }
 
 /**
  * @brief Trouve la position actuelle de la case vide
  * 
  * @param p Pointeur vers le plateau
  * @return Carre Coordonnées de la case vide
  */
 Carre TrouverCaseVide(Plateau *p){
     int i, j;
     Carre case_vide;
     for(i = 0; i < NB_LIG; i++){
         for(j = 0; j < NB_COL; j++){
             if (p->bloc[i][j].lig == NB_LIG - 1 && p->bloc[i][j].col == NB_COL - 1) {
                 case_vide.lig = i;
                 case_vide.col = j;
             }
         }
     }
     return case_vide;
 }
 
 /**
  * @brief Déplace la case vide dans une direction aléatoire (haut, bas, gauche, droite)
  * 
  * @param p Pointeur vers le plateau
  * @return Carre Nouvelle position de la case vide
  */
 Carre DeplacerCaseVide(Plateau *p){
     Carre case_vide = TrouverCaseVide(p);
     int lig = case_vide.lig;
     int col = case_vide.col;
 
     int direction = rand() % 4;
     int new_lig = lig;
     int new_col = col;
 
     switch (direction) {
         case 0:  /* Haut */
             if (lig > 0) new_lig = lig - 1;
             break;
         case 1:  /* Bas */
             if (lig < NB_LIG - 1) new_lig = lig + 1;
             break;
         case 2:  /* Gauche */
             if (col > 0) new_col = col - 1;
             break;
         case 3:  /* Droite */
             if (col < NB_COL - 1) new_col = col + 1;
             break;
     }
 
     if (new_lig != lig || new_col != col) {
         /* Échange de la case vide avec la case adjacente choisie */
         Carre temp = p->bloc[lig][col];
         p->bloc[lig][col] = p->bloc[new_lig][new_col];
         p->bloc[new_lig][new_col] = temp;
 
         case_vide.lig = new_lig;
         case_vide.col = new_col;
 
         printf("Case vide déplacée en : (%d, %d)\n", case_vide.lig, case_vide.col);
     }
 
     return case_vide;
 }
 
 /**
  * @brief Mélange le plateau en déplaçant la case vide de façon aléatoire plusieurs fois
  * 
  * @param p Pointeur vers le plateau
  * @param img Pointeur vers l'image à afficher
  */
 void MelangerPlateau(Plateau *p, MLV_Image *img){
     int i;
     for(i = 0; i < 120; i++){
         DeplacerCaseVide(p);
         AfficherPlateau(p, img);
         MLV_wait_milliseconds(20);
     }
 }
 
 /**
  * @brief Vérifie si le plateau est dans un état résolu
  * 
  * @param p Pointeur vers le plateau
  * @return int 1 si résolu, 0 sinon
  * @note Complexité en O(n²) avec n = NB_LIG
  */
 int estResolu(Plateau *p){
     int i, j;
     for(i = 0; i < NB_LIG; i++){
         for(j = 0; j < NB_COL; j++){
             if(p->bloc[i][j].lig != i || p->bloc[i][j].col != j){
                 return 0;
             }
         }
     }
     return 1;
 } 