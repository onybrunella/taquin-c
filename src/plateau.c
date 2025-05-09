#include "taquin.h"
#include <stdio.h>
#include <stdlib.h>


#include <time.h>

/* fonction pour initialiser le plateau avant mélange */
void InitialisationPlateau(Plateau *p){
  int i, j;
  for(i=0;i<NB_LIG;i++){
    for(j=0;j<NB_COL;j++){
    ((p->bloc)[i][j]).lig=i;
    ((p->bloc)[i][j]).col=j;
    }
  }
}

/*fonction pour trouver case vide*/
Carre TrouverCaseVide(Plateau *p){
  int i,j;
  Carre case_vide;
  for(i=0; i<NB_LIG;i++){
    for(j=0;j<NB_COL;j++){
      if (p->bloc[i][j].lig == NB_LIG - 1 && p->bloc[i][j].col == NB_COL - 1) {
      case_vide.lig = i;
      case_vide.col = j;
      }
    }
  }
  return case_vide;
}

/*fFonctoon pour déplacer la case vide dans le plateau*/
Carre DeplacerCaseVide(Plateau *p){
  /*if (!p) {
    fprintf(stderr, "Erreur : plateau null\n");
    return;
  }*/
  Carre case_vide=TrouverCaseVide(p);
  int lig=case_vide.lig;
  int col=case_vide.col;

  int direction = rand() % 4; /**/
  int new_lig=lig;
  int new_col=col;
  switch (direction) {
    case 0:  /* Haut */
        if (lig > 0) {
            new_lig = lig -1;
        }
        break;
    case 1: /* Bas */
        if (lig < NB_LIG - 1) {
            new_lig = lig+1;
        }
        break;
    case 2: /* Gauche */
        if (col > 0) {
            new_col=col-1;
        }
        break;
    case 3: /* Droite */
        if (col < NB_COL - 1) {
            new_col=col+1;
        }
        break;
}

    if (new_lig != lig || new_col != col) {
    /*   Carre temp = p->bloc[new_lig][new_col];
      p->bloc[new_lig][new_col]= p-> bloc[lig][col];
      p->bloc[lig][col]=temp;*/

      Carre temp = p->bloc[lig][col];
      p->bloc[lig][col] = p->bloc[new_lig][new_col];
      p->bloc[new_lig][new_col] = temp;

    case_vide.lig=new_lig;
      case_vide.col=new_col;
          printf("Case vide déplacée en : (%d, %d)\n", case_vide.lig, case_vide.col);

    }
    return case_vide;
}


/* fonction pour mélanger le plateau */
void MelangerPlateau(Plateau *p, MLV_Image *img){
  int i;
  for(i=0;i<120;i++){
    DeplacerCaseVide(p);
   /* MLV_actualise_window();*/
   AfficherPlateau(p, img);
   MLV_wait_milliseconds(20); 
  }
}

/*fonction qui regarde si le plateau est résolu ou pas*/
/*il parcoure le plateau est vérifiesi chaque pièce  est à sa place d'orine.*/
/**
 * @brief Vérifie si le puzzle est résolu
 * @param p Plateau à analyser
 * @return 1 si résolu, 0 sinon
 * @note Complexité O(n²) où n = NB_LIG
 */
int estResolu(Plateau *p){
  int i, j;
  for(i=0;i<NB_LIG;i++){
    for(j=0;j<NB_COL;j++){
      if(p->bloc[i][j].lig != i || p->bloc[i][j].col !=j){
        return 0;
      }

    }
  }
  return 1;
}

