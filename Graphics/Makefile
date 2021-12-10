############################
# Makefile Codage partie Graphique
############################

#####Developpeurs#####
#   Rodrigue Meunier
#   Mathis Morisseau
#   Nicolas Lemoult
######################

############
#Fichiers sources
############
bin_dir= bin
top_dir = ..
graphics_dir= ./Graphics
src_dir= src
obj_dir= obj

############
#Macros
############
CC=gcc
CCC=gcc -c
SDL_FLAGS= $(FLAGS) `sdl2-config --cflags` `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer
FLAGS= -Wall -g -lm
MODULES=$(top_dir)/obj/réseau.o $(top_dir)/obj/encodage.o $(top_dir)/obj/hadamard.o $(top_dir)/obj/generateur.o $(obj_dir)/graphics.o

############
#Executables
############
$(bin_dir)/emetteur : $(MODULES) $(src_dir)/emetteur.c $(src_dir)/include/emetteur.h
		$(CC) $(MODULES) $(src_dir)/emetteur.c -o $(bin_dir)/emetteur $(SDL_FLAGS)

$(bin_dir)/recepteur : $(MODULES) $(src_dir)/recepteur.c $(src_dir)/include/recepteur.h
		$(CC) $(MODULES) $(src_dir)/recepteur.c -o $(bin_dir)/recepteur $(SDL_FLAGS)

$(bin_dir)/canal : $(MODULES) $(src_dir)/canal.c $(src_dir)/include/canal.h
		$(CC) $(MODULES) $(src_dir)/canal.c -o $(bin_dir)/canal $(SDL_FLAGS)

############
#Modules
############
make_module:
		cd $(top_dir);make -f Makefile modules;cd $(graphics_dir)
		$(CCC) $(src_dir)/graphics.c -o $(obj_dir)/graphics.o $(SDL_FLAGS)

############
#Commandes
############

all : build make_module $(bin_dir)/emetteur $(bin_dir)/recepteur $(bin_dir)/canal

clean :
		cd $(top_dir);make -f Makefile clean;cd $(graphics_dir)
		rm -r -f $(obj_dir)

build :
		cd $(top_dir);make -f Makefile build;cd $(graphics_dir)
		mkdir -p $(obj_dir)

right:
		cd $(top_dir);make right;cd $(graphics_dir)
