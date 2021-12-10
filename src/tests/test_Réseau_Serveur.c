/**
 * @file test_Réseau_Serveur.c
 * @brief Ficher de test pour contrôler les fonctions de réseau en particulier celles pour le serveur
 * @author Meunier, Lemoult, Morisseau || L3 informatique Le mans
 * @version 1.0
 * @date Decembre 2021
 */
#include "../include/réseau.h"
#define N 124
/*
 * @fn main
 * @brief Le programme teste les fonctions de réseau en particulier celles pour le serveur.
 */
int main(){
  printf("Démarrage du Serveur\n");
  printf("Saisis juste un '\\n' pour arrêter\n");
  SOCKET Serveur = SocketCreationConnexion(SERVEUR);
  SOCKET Client = SocketClientAccept(Serveur);
  printf("Client Connecté\n");
  /*****************************/
  int buffer[N]={1};
  while(buffer[0]!='\n')
  {
    printf("[CLIENT]:");
    SocketRecevoir(Client,buffer,N);
    for(int i=0;i<N;i++)printf("%c",buffer[i]);
  }
  /*****************************/
	SocketFermer(Serveur);
  SocketFermer(Client);
  return 0;
}
