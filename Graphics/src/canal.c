/**
 * @file canal.c
 * @brief Réalisation de l'entité canal en version graphique
 * @author Meunier, Lemoult, Morisseau || L3 informatique Le mans
 * @version 1.0
 * @date Decembre 2021
 */

#include "include/canal.h"

/*
 * @fn main
 * @brief Le programme joue le role de canal, il permet de récuperer un signal, de rajouter du bruit et de l'envoyer au destinataire. Ainsi ce programme joue le rôle de passerelle entre deux clients
 */
int main(int argc, char *argv[]){
  if(argc != 3 || !atoi(argv[1]) || !atoi(argv[2]))
  {
    printf("Erreur lors du lancement de canal\n");
    printf("Si vous avez lancez ./tp1.sh :\n");
    printf("\tProblème à ce niveau\n");
    printf("Si vous avez lancez ./canal :\n");
    printf("\tIl faut prendre en compte les 2 paramètres obligatoires :\n");
    printf("\t\t./canal nb_utilisateur>0 taille_message>0\n");
    printf("Terminé\n");
    return -1;
  }
  //printf("Démarrage du canal\n");
  nb_utilisateur=atoi(argv[1]);
  taille_message=atoi(argv[2]);
  /********************/
  /*Création du réseau*/
  /********************/
  SOCKET Canal = SocketCreationConnexion(SERVEUR);
  SOCKET Emetteur, Recepteur;
  /***********************/
  //Connexion des sockets clientes (Emetteur et Recepteur)
  SocketAttenteEmetteurRecepteur(Canal,&Emetteur,&Recepteur);
  //Envoie des informations nécessaires en brut
  SocketEnvoyer(Emetteur,&nb_utilisateur,1);
  SocketEnvoyer(Recepteur,&nb_utilisateur,1);
  SocketEnvoyer(Emetteur,&taille_message,1);
  SocketEnvoyer(Recepteur,&taille_message,1);
  //***********************************

  /***********************************/
  /*Création de l'interface graphique*/
  /***********************************/
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1) perror("Erreur démarage SDL");
  if( !(IMG_Init(IMG_INIT_PNG)) )perror("Erreur démarage IMG");
  if(TTF_Init() != 0)perror("Erreur démarage TTF");
  if(!Mix_Init(MIX_INIT_MP3))perror("Erreur démarage MIX");
  SDL_Surface *icon=IMG_Load(ICON_DESTINATION);
  SDL_Window* fenetre=SDL_CreateWindow("Canal Graphique" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 600 , 600 , SDL_WINDOW_HIDDEN);
  if(fenetre == NULL)
  {
    perror("Erreur creation fenetre");
  }
  SDL_SetWindowIcon(fenetre , icon);
  SDL_FreeSurface(icon);
  SDL_Renderer *rendu=SDL_CreateRenderer(fenetre,-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  SDL_SetRenderDrawColor(rendu,FOND_R,FOND_G,FOND_B,0);
  SDL_RenderClear(rendu);
  SDL_RenderPresent(rendu);
  if(rendu == NULL)
  {
    perror("Erreur creation rendu");
  }
  //***********************************
  /********************/
  /*Debut du programme*/
  /********************/


  int *signal=SignalCreer();
  SocketRecevoir(Emetteur,signal,SignalSize());
  //Signal reçu
  SDL_ShowWindow(fenetre);
  recevoir(rendu,CANAL);
  grandir(rendu);

  /*************************************/
  /*Modification signal --> ajout bruit*/
  /*************************************/
  bruiter(rendu,signal);

  /*************************************/
  reduire(rendu);
  envoyer(rendu,CANAL);
  SDL_HideWindow(fenetre);
  SocketEnvoyer(Recepteur,signal,SignalSize());

  //Fermeture des sockets
  SocketFermer(Canal);
  SocketFermer(Emetteur);
  SocketFermer(Recepteur);
  free(signal);
  //Fermeture sdl
  // Destruction du renderer et de la fenêtre :
  SDL_DestroyRenderer(rendu);
  SDL_DestroyWindow(fenetre);
  SDL_Quit();
  return 0;
}
