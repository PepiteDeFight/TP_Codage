/**
 * @file recepteur.c
 * @brief Réalisation de l'entité recepteur
 * @author Meunier, Lemoult, Morisseau || L3 informatique Le mans
 * @version 1.0
 * @date Decembre 2021
 */

#include "include/recepteur.h"

extern int nb_utilisateur;
extern int taille_message;

/**
 * @fn main
 * @brief Le programme joue le rôle du récepteur, il récupère un message du canal
 */
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
  /********************/
  /*Debut du programme*/
  /********************/
  int *signal=SignalCreer();
  printf("=========================\n");
  printf("RECEPTION DU MESSAGE  \n");
  printf("EN COURS ...  \n");
  printf("=========================\n");
  SocketRecevoir(Recepteur,signal,SignalSize());
  printf("Message reçu !\n");
  printf("Affichage du signal reçu: \n");
  SignalAfficher(signal);
  printf("Décodage du signal reçu: \n");
  DecodageSimple(signal);
  printf("---> OK\n");
  printf("Terminer ?\n");
  while(getchar()!='\n');
  //Fermeture des sockets
	SocketFermer(Recepteur);
  RandTerminer();
  return 0;
}
