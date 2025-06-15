# Jeu du Taquin

### Ony Brunella ANDRIATSAHAVOJAONA


## Lancement du jeu

1. **Compiler le projet**
   ```bash
   make
   ```

2. **Lancer le jeu**  

   - Avec l'image par défaut (sun.png)
      ```bash
      ./taquin data/earth.png
      ```
   => Pour changer l'image par défaut, modifiez DEFAULT_IMAGE_PATH dans src/main.c :
    ```c
    #define DEFAULT_IMAGE_PATH "data/votre_image.png"
    ```

   - Avec une image personnalisée
      ```bash
      ./taquin data/votre_image.png
      ```
      Exemple :
      ```bash
        ./taquin data/earth.png
        ```
   
**Remarque :**
-> Vous pouvez remplacer `data/earth.png` par le chemin de votre propre image.
Cependant, l'image utilisée doit être au format 512×512 pixels et placée dans le dossier `data`.
