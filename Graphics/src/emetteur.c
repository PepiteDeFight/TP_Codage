/**
 * @file emetteur.c
 * @brief Réalisation de l'entité emetteur avec interface graphique
 * @author Meunier, Lemoult, Morisseau || L3 informatique Le mans
 * @version 1.0
 * @date Decembre 2021
 */

#include "include/emetteur.h"
/**
 * @fn main
 * @brief Le programme joue le rôle d'emetteur, il récupère un message et l'envoie au canal pour l'ajout de bruit
 */
int main(){
  printf("Démarrage de l'émetteur\n");
  RandInit();
  nb_utilisateur=0;
  taille_message=0;
  SOCKET Emetteur = SocketCreationConnexion(CLIENT);
  //réception de nb_utilisateur
  do{
	SocketRecevoir(Emetteur,&nb_utilisateur,1);
  }while(nb_utilisateur<=0);
  //***************************
  //réception de taille_message
  //***************************
  do{
	   SocketRecevoir(Emetteur,&taille_message,1);
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
  SDL_Window* fenetre=SDL_CreateWindow("Emetteur Graphique" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 600 , 600 , SDL_WINDOW_SHOWN);
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
  int *signal=calloc(SignalSize(),sizeof(int));

  int **hadamard=HadamardCreer();//on génére la matrice de hadamard
  int *code;
  int *message;
  int upto5 = 1;
  for(int i=0;i<nb_utilisateur;i++)
  {
    message = MessageCreer();
    drawMessage(rendu,message);
    //Ajouter le signal sur la fenetre
    if(upto5<=5)
    {

      upto5++;
    }
    code = Encodage(i , hadamard, message ) ;
    free(message);

    addition(signal,code);
    free(code);
  }
  for(int i=nb_utilisateur;i<HadamardNbLigne();i++)
  {
    message = calloc(taille_message,sizeof(int));
    code = Encodage(i , hadamard, message ) ;
    free(message);
    addition(signal,code);
    free(code);
  }
  HadamardDetruire(hadamard);
  reduire(rendu);
  envoyer(rendu,EMETTEUR);
  SocketEnvoyer(Emetteur,signal,SignalSize());
  SDL_HideWindow(fenetre);

  //Fermeture des sockets
  SocketFermer(Emetteur);
  RandTerminer();

  //Femeture de la sdl
  SDL_DestroyRenderer(rendu);
  SDL_DestroyWindow(fenetre);
  SDL_Quit();
    return 0;
}
