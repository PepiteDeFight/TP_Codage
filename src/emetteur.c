/**
 * @file emetteur.c
 * @brief Réalisation de l'entité emetteur
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
  /********************/
  /*Debut du programme*/
  /********************/
  int *signal=SignalGenerer(0);
  printf("Affichage du signal émit: \n");
  SignalAfficher(signal);
  printf("OK : \n");
  printf("Transmission ?\n");
  while(getchar()!='\n');
  printf("=========================\n");
  printf("TRANSMISSION DU MESSAGE  \n");
  printf("EN COURS ...  \n");

  for(int i=0;i<TIMESLEEP;i++)
  {
    printf("%d ...\n",TIMESLEEP-i);
    sleep(1);
  }
  printf("\n=========================\n");
  SocketEnvoyer(Emetteur,signal,SignalSize());
  printf("---> OK\n");
  printf("Terminer ?\n");
  while(getchar()!='\n');
  //Fermeture des sockets
  SocketFermer(Emetteur);
  RandTerminer();
  return 0;
}
