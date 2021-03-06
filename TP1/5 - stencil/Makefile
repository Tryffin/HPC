#o###########################################################################o#
#|                           Auto Makefile                                   |#
#|                              (by Adrien CASSAGNE)                         |#
#o###########################################################################o#

# Configuration ###############################################################
#------------------------------------------------------------------------------
# executable name
PROG_NAME = stencil
# files extension
EXT = cpp

# Compiling options ###########################################################
#------------------------------------------------------------------------------
# compiler choice
CC = g++
# compiling options
CFLAGS = -O3 -march=native -Wall -std=c++11# -ftree-vectorizer-verbose=1
# compiling options (debug mode)
DCFLAGS = -g -O0
# compiling flags
LDFLAGS = -fopenmp
# librairie link
LIBS = -lm

# DO NOT TOUCH ANYTHING AFTER THIS LINE

# Dossiers ####################################################################
#------------------------------------------------------------------------------
# dossier des fichiers sources
SRC_DIR  = src
# dossier des fichiers binaires 
BIN_DIR  = bin
# dossier des fichiers objets
OBJ_DIR  = obj
# dossier des fichiers objets de debug
OBJD_DIR = objd
# dossier des fichier de documentations
DOC_DIR  = doc
# dossier de sauvegarde des fichiers sources
SAVE_DIR = save

# Liste des fichiers ##########################################################
#------------------------------------------------------------------------------
# fichiers sources
SRC = $(wildcard $(SRC_DIR)/*.$(EXT) $(SRC_DIR)/tools/*.$(EXT))
# fichiers d'entêtes
HEAD = $(wildcard $(SRC_DIR)/*.h)
# fichiers objets
OBJ  = $(subst $(SRC_DIR), $(OBJ_DIR), $(SRC:.$(EXT)=.o))
OBJD = $(subst $(SRC_DIR), $(OBJD_DIR), $(SRC:.$(EXT)=.o))

# Date actuelle ###############################################################
#------------------------------------------------------------------------------
DATE = $(shell date "+%Y-%m-%d_%H:%M:%S")

# Exécutables #################################################################
#------------------------------------------------------------------------------
EXE  =  $(BIN_DIR)/$(PROG_NAME)
EXED =  $(BIN_DIR)/$(PROG_NAME)_debug

# Cibles ######################################################################
#------------------------------------------------------------------------------
# cible principale
all : standard

.PHONY: standard debug
standard : ofolders $(EXE)
debug : ofolders $(EXED)

#------------------------------------------------------------------------------
# Compilation classique -------------------------------------------------------
#------------------------------------------------------------------------------
# création de l'exécutable à partir des objets (linkage)
$(EXE) : $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

# transforme les sources en objet (binaire) quand il y a des .h
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.$(EXT) $(SRC_DIR)/%.h
	$(CC) $(LDFLAGS) $(CFLAGS) -c $< -o $@ 

# transfome les sources en objet (binaire) quand il n'y a pas de .h
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.$(EXT)
	$(CC) $(LDFLAGS) $(CFLAGS) -c $< -o $@

#------------------------------------------------------------------------------
# Compilation debug -----------------------------------------------------------
#------------------------------------------------------------------------------
# création de l'exécutable à partir des objets (linkage)
$(EXED) : $(OBJD)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

# transforme les sources en objet (binaire) quand il y a des .h
$(OBJD_DIR)/%.o : $(SRC_DIR)/%.$(EXT) $(SRC_DIR)/%.h
	$(CC) $(LDFLAGS) $(DCFLAGS) -c $< -o $@ 
	
# transfome les sources en objet (binaire) quand il n'y a pas de .h
$(OBJD_DIR)/%.o : $(SRC_DIR)/%.$(EXT)
	$(CC) $(LDFLAGS) $(DCFLAGS) -c $< -o $@

# Autres cibles ###############################################################
#------------------------------------------------------------------------------
.PHONY: clean mrproper folders archive save

#------------------------------------------------------------------------------
# Suppression des fichiers objets ---------------------------------------------
#------------------------------------------------------------------------------
clean :
	rm -rf $(OBJ_DIR)/* $(OBJD_DIR)/*

#------------------------------------------------------------------------------
# suppression de tous les fichiers générés par le Makefile --------------------
#------------------------------------------------------------------------------
mrproper : clean
	rm -rf $(BIN_DIR)/*
	rm -f $(PROG_NAME).tar.gz
	
#------------------------------------------------------------------------------
# Création des dossiers de travail pour le projet -----------------------------
#------------------------------------------------------------------------------
folders:
	mkdir $(SRC_DIR) $(BIN_DIR) $(OBJ_DIR) $(OBJD_DIR) $(DOC_DIR) $(SAVE_DIR)

#------------------------------------------------------------------------------
# création d'une archive du projet --------------------------------------------
#------------------------------------------------------------------------------
archive: mrproper
	tar czvf $(PROG_NAME).tar.gz Makefile $(BIN_DIR)/ $(SRC_DIR)/ $(OBJ_DIR)/ \
                                          $(OBJD_DIR)/ $(DOC_DIR)/            \
                                          --exclude .svn

#------------------------------------------------------------------------------
# Sauvegarde des fichiers sources dans le dossier "save" ----------------------
#------------------------------------------------------------------------------
save:
	mkdir $(SAVE_DIR)/$(DATE)
	cp -R $(SRC_DIR)/* $(SAVE_DIR)/$(DATE)/

# Script permettant de reproduire l'arborescence de src dans obj ##############
#------------------------------------------------------------------------------
NUM_LINE = $(shell ls -l $(OBJ_DIR)/ | wc -l)
ofolders:
ifeq ($(NUM_LINE),1)
	@find $(SRC_DIR) -not -path '*/.*/*' -not -name '.*' -type d -exec mkdir \
                                                             $(OBJ_DIR)/\{\} \;
	@mv $(OBJ_DIR)/$(SRC_DIR)/* $(OBJ_DIR)/ || true
	@rmdir $(OBJ_DIR)/$(SRC_DIR)
	@find $(SRC_DIR) -not -path '*/.*/*' -not -name '.*' -type d -exec mkdir \
                                                            $(OBJD_DIR)/\{\} \;
	@mv $(OBJD_DIR)/$(SRC_DIR)/* $(OBJD_DIR)/ || true
	@rmdir $(OBJD_DIR)/$(SRC_DIR)
endif
