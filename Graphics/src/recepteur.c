/**
 * @file recepteur.c
 * @brief Réalisation de l'entité recepteur avec interface graphique
 * @author Meunier, Lemoult, Morisseau || L3 informatique Le mans
 * @version 1.0
 * @date Decembre 2021
 */

#include "include/recepteur.h"
extern int nb_utilisateur;
extern int taille_message;
int main(){
  printf("Démarrage du récepteur\n");
  RandInit();
  nb_utilisateur=0;
  taille_message=0;
  SOCKET Recepteur = SocketCreationConnexion(CLIENT);
  //réception de nb_utilisateur
  do{
	SocketRecevoir(Recepteur,&nb_utilisateur,1);
  }while(nb_utilisateur<=0);
  //**************************
  //réception de taille_message
  do{
	SocketRecevoir(Recepteur,&taille_message,1);
  }while(taille_message<=0);
  //**************************
  /***********************************/
  /*Création de l'interface graphique*/
  /***********************************/
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1) perror("Erreur démarage SDL");
  if( !(IMG_Init(IMG_INIT_PNG)) )perror("Erreur démarage IMG");
  if(TTF_Init() != 0)perror("Erreur démarage TTF");
  if(!Mix_Init(MIX_INIT_MP3))perror("Erreur démarage MIX");
  SDL_Surface *icon=IMG_Load(ICON_DESTINATION);
  SDL_Window* fenetre=SDL_CreateWindow("Recepteur Graphique" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 600 , 600 , SDL_WINDOW_HIDDEN);
  if(fenetre == NULL)
  {
    perror("Erreur creation fenetre");
  }
  SDL_SetWindowIcon(fenetre , icon);
  SDL_FreeSurface(icon);
  SDL_Renderer *rendu=SDL_CreateRenderer(fenetre,-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  SDL_SetRenderDrawColor(rendu,FOND_R,FOND_G,FOND_B,0);
  SDL_RenderClear(rendu);
  if(rendu == NULL)
  {
    perror("Erreur creation rendu");
  }
  /********************/
  /*Debut du programme*/
  /********************/
  int *signal=SignalCreer();
  SocketRecevoir(Recepteur,signal,SignalSize());
  //Signal reçu
  SDL_ShowWindow(fenetre);
  recevoir(rendu,RECEPTEUR);
  grandir(rendu);
  SDL_RenderFillRect(rendu,NULL);
  SDL_RenderPresent(rendu);

    //Les compteurs
    int k = 0;
    int sous_tot;

    //Buffer pour le calcul du message
    float f = (float) 1 / HadamardNbLigne();

    //Le message à retourner
    int *message = MessageCreer();

    int *sequence;
  for(int user=0;user<nb_utilisateur;user++)
  {
    //On récupère la séquence d'étalement de l'utilisateur
    sequence = SequenceInitialiser(user);

    //On parcours le signal
    for(int i = 0; i < SignalSize(); i+=HadamardNbLigne())
    {

      sous_tot = 0;

      //On prend 1 bit de message
      for(int j = 0; j < HadamardNbLigne(); j++){
        sous_tot += sequence[j] * signal[i+j];
      }

      //On ajoute le bit au message
      message[k++] = f * sous_tot;
    }


    free(sequence);
    drawMessage(rendu,message);
  }

  //libération du signal
  free(signal);

  //Fermeture des sockets
	SocketFermer(Recepteur);
  //Fermeture sdl
  // Destruction du renderer et de la fenêtre :
  SDL_DestroyRenderer(rendu);
  SDL_DestroyWindow(fenetre);
  SDL_Quit();
  RandTerminer();
    return 0;
}
