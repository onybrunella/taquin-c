# modification du Makefile pour le tp7 en s'inspirant du Makfile de ce lien : http://www-igm.univ-mlv.fr/~boussica/mlv/api/French/html/outils_compilation.html

# nom de l'exécutable
TARGET = taquin

# Répertoires
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# liste des fichiers sources
SRC = $(SRC_DIR)/main.c \
      $(SRC_DIR)/plateau.c \
      $(SRC_DIR)/graphique.c 
	  
# Liste des fichiers objets (dérivée des sources)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Compilateur
CC = gcc
CFLAGS = -Wall -ansi -I$(INCLUDE_DIR) `pkg-config --cflags MLV`
LDFLAGS =  `pkg-config --libs MLV`

# Règle par défaut
all: $(TARGET)

# Création du répertoire de build dans le cas où il n'existe pas
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Règle de création de l'exécutable
$(TARGET): $(BUILD_DIR) $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LDFLAGS)

# Règle de compilation des fichiers sources en objets
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

# Nettoyage
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
