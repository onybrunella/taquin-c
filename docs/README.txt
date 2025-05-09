Pour commencer, version simple en faisant un découpage de 4 par 4 de l'image par la case noire en bas de l'image à droite

Ce **TP en langage C** consiste à programmer un **jeu de taquin** avec une interface graphique en utilisant la **LibMLV**. Voici les principales étapes pour mener à bien ce projet :

---

### 🔹 **1. Comprendre le fonctionnement du jeu de taquin**
Le taquin est un puzzle constitué de **15 pièces numérotées de 1 à 15** sur une grille **4x4**, avec une **case vide** permettant de faire glisser les pièces adjacentes.
Le but est de remettre les pièces dans l'ordre en effectuant des déplacements.

---

### 🔹 **2. Chargement et découpage de l’image**
- **Choisir une image** de **512x512 pixels** (formats acceptés : PNG, JPG, GIF).
- **Découper l’image en 16 carrés** (4x4).
- **Créer une structure de données** pour représenter chaque carré et sa position initiale.

  ```c
  #define NB_COL 4
  #define NB_LIG 4

  typedef struct carre {
      int lig;  // Ligne de la pièce dans l’état final
      int col;  // Colonne de la pièce dans l’état final
  } Carre;

  typedef struct plateau {
      Carre bloc[NB_LIG][NB_COL];  // Matrice de 4x4
  } Plateau;
  ```

- **Initialiser le plateau** pour qu’il représente l’état final.

  ```c
  void InitialisationPlateau(Plateau *P) {
      int i, j;
      for (i = 0; i < NB_LIG; i++) {
          for (j = 0; j < NB_COL; j++) {
              P->bloc[i][j].lig = i;
              P->bloc[i][j].col = j;
          }
      }
  }
  ```

---

### 🔹 **3. Mélange du plateau**
- **Mélanger les pièces de manière valide** :
  ⚠️ **Attention !** On ne peut pas mélanger les pièces de manière totalement aléatoire, car toutes les configurations ne sont pas résolubles.
- **Solution suggérée** : Appliquer **120 déplacements aléatoires valides** à partir de l'état final.

  ```c
  // Fonction pour générer un mouvement aléatoire parmi les mouvements possibles
  void MelangerPlateau(Plateau *P) {
      for (int i = 0; i < 120; i++) {
          // Déplacer aléatoirement la case vide (mouvements autorisés)
      }
  }
  ```

---

### 🔹 **4. Affichage avec la bibliothèque LibMLV**
La **LibMLV** est utilisée pour gérer l’interface graphique :
- **Créer une fenêtre** : `MLV_create_window()`
- **Charger l’image** : `MLV_load_image()`
- **Dessiner l’image découpée** : `MLV_draw_image_part()`
- **Gérer les déplacements avec la souris** : `MLV_wait_mouse()`
- **Actualiser la fenêtre** : `MLV_actualise_window()`

Exemple de création de fenêtre :
```c
MLV_create_window("Taquin", "Jeu de Taquin", 512, 512);
```

---

### 🔹 **5. Interaction avec le joueur**
- **Détecter les clics de la souris** : `MLV_wait_mouse(&x, &y);`
- **Déterminer si un mouvement est possible**
- **Échanger la case vide avec une case voisine**
- **Vérifier si le puzzle est résolu**
- **Afficher un message de victoire et le temps écoulé**

