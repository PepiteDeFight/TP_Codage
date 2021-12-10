############################
# Makefile Codage
############################

#####Developpeurs#####
#   Rodrigue Meunier
#   Mathis Morisseau
#   Nicolas Lemoult
######################

############
#Directories
############
bin_graphics_dir= $(graphics_dir)/bin
top_dir= .
graphics_dir=Graphics

############
#Macros
############
CC=gcc
CCC=gcc -c
FLAGS=-Wall -g -lm
MODULES=obj/réseau.o obj/encodage.o obj/hadamard.o obj/generateur.o

FLAGSRM=-r -f
############
#Executables
############

bin/emetteur : $(MODULES) src/emetteur.c src/include/emetteur.h
		$(CC) $(MODULES) src/emetteur.c -o bin/emetteur $(FLAGS)

bin/recepteur : $(MODULES) src/recepteur.c src/include/recepteur.h
		$(CC) $(MODULES) src/recepteur.c -o bin/recepteur $(FLAGS)

bin/canal : $(MODULES) src/canal.c src/include/canal.h
		$(CC) $(MODULES) src/canal.c -o bin/canal $(FLAGS)


############
#Tests
############
bin/tests/test_Encodage : obj/hadamard.o obj/encodage.o obj/generateur.o src/tests/test_Encodage.c
		$(CC) obj/hadamard.o obj/encodage.o obj/generateur.o src/tests/test_Encodage.c -o bin/tests/test_Encodage $(FLAGS)

bin/tests/test_HDBnAri : obj/generateur.o obj/hadamard.o obj/encodage.o src/tests/test_HDBnAri.c
		$(CC) obj/generateur.o obj/hadamard.o obj/encodage.o src/tests/test_HDBnAri.c -o bin/tests/test_HDBnAri $(FLAGS)

bin/tests/test_Hadamard : obj/hadamard.o src/tests/test_Hadamard.c
		$(CC) obj/hadamard.o src/tests/test_Hadamard.c -o bin/tests/test_Hadamard $(FLAGS)

bin/tests/test_Generateur : obj/generateur.o src/tests/test_Generateur.c
		$(CC) obj/generateur.o src/tests/test_Generateur.c -o bin/tests/test_Generateur $(FLAGS)

bin/tests/test_Random : obj/generateur.o src/tests/test_Generateur.c
		$(CC) obj/generateur.o src/tests/test_Random.c -o bin/tests/test_Random $(FLAGS)

bin/tests/test_Client : obj/réseau.o src/tests/test_Réseau_Client.c
		$(CC) obj/réseau.o src/tests/test_Réseau_Client.c -o bin/tests/test_Client $(FLAGS)

bin/tests/test_Serveur : obj/réseau.o src/tests/test_Réseau_Serveur.c
		$(CC) obj/réseau.o src/tests/test_Réseau_Serveur.c -o bin/tests/test_Serveur $(FLAGS)

############
#Modules
############

modules : obj/hadamard.o obj/encodage.o obj/generateur.o obj/réseau.o

obj/hadamard.o : src/hadamard.c src/include/hadamard.h
		$(CCC) src/hadamard.c -o obj/hadamard.o $(FLAGS)

obj/encodage.o : src/encodage.c src/include/encodage.h
		$(CCC) src/encodage.c -o obj/encodage.o $(FLAGS)

obj/generateur.o : src/generateur.c src/include/generateur.h
		$(CCC) src/generateur.c -o obj/generateur.o $(FLAGS)

obj/réseau.o : src/réseau.c src/include/réseau.h
		$(CCC) src/réseau.c -o obj/réseau.o $(FLAGS)

############
#Commandes
############

all : build bin/emetteur bin/recepteur bin/canal

clean :
		rm $(FLAGSRM) obj
		rm $(FLAGSRM) bin
		rm $(bin_graphics_dir)/canal
		rm $(bin_graphics_dir)/emetteur
		rm $(bin_graphics_dir)/recepteur

build :
		mkdir -p obj;
		mkdir -p bin;
		mkdir -p bin/tests;

graphic :
	cd $(graphics_dir); make all; cd $(top_dir)

right :
		chmod 766 $(top_dir) -R

tests : build bin/tests/test_Encodage	bin/tests/test_HDBnAri bin/tests/test_Hadamard bin/tests/test_Generateur bin/tests/test_Client bin/tests/test_Serveur bin/tests/test_Random

docs :
		cd Doxygen;	rm $(FLAGSRM) html; doxygen config;

install_SDL:
		sudo apt install libsdl2-2.0-0 libsdl2-gfx-1.0-0 libsdl2-image-2.0-0 libsdl2-mixer-2.0-0 libsdl2-net-2.0-0 libsdl2-ttf-2.0-0 libsdl2-gfx-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-net-dev libsdl2-ttf-dev libsdl2-dev

infos :
		@echo "	all 	  		: Création de emetteur, recepteur et canal.";
		@echo "	graphic			: Création de emetteur, recepteur et canal en version grapghique.";
		@echo "	tests	  		: Création des tests.";
		@echo "	modules  		: Création des modules.";
		@echo "	build				: Créer les dossiers.";
		@echo "	right				: Applique les droits nécessaires pour le lancement du projet.";
		@echo "	install_SDL	: Installe la SDL si non présente.";
		@echo "	docs				: Générer la documentation Doxygen.";
		@echo "	clean				: Supprimer les fichiers temporaires";
