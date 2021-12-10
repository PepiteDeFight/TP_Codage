/**
 * @file graphics.h
 * @brief Inclusion des fichiers nécéssaires pour l'interface graphique
 * @author Meunier, Lemoult, Morisseau || L3 informatique Le mans
 * @version 1.0
 * @date Decembre 2021
 */
#ifndef GRAPHICS_H
    #define GRAPHICS_H

    //Includes sdl
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
    #include <SDL_mixer.h>

    //Includes nécéssaires au fonctions
    #include "../../../src/include/encodage.h"
    #include <math.h>

    //definition des macros
    //liens vers les images nécéssaires
    #define ICON_DESTINATION "../img/icon.png"
    #define PERSONNAGES_DESTINATION "../img/personnages.png"
    #define PACKAGE_DESTINATION "../img/package.png"
    #define FOND_DESTINATION "../img/fond_bruitage.png"
    #define POLICE_DESTINATION "src/Elastic Stretch.ttf"
    #define TAILLE_POLICE 25
    #define X 0
    #define Y 2
    #define H 3
    #define L 1
    #define FOND_R 211
    #define FOND_G 233
    #define FOND_B 255
    #define EMETTEUR 0
    #define CANAL 1
    #define RECEPTEUR 2
    #define FILTRE 5
    #define NB_COLONNES ((int)sqrt(max)+1)
    #define NB_LIGNES hauteur
    #define TAILLE_CASE TableauMax.h







    //Prototypes des différentes fonctions
    void drawMessage(SDL_Renderer *,int *);
    void reduire(SDL_Renderer *);
    void grandir(SDL_Renderer *rendu);
    void envoyer(SDL_Renderer *,int );
    void recevoir(SDL_Renderer *,int );
    void changerCouleur(SDL_Renderer *,int);
    void bruiter(SDL_Renderer *, int *);


#endif
