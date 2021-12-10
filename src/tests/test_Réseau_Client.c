/**
 * @file test_Réseau_Client.c
 * @brief Ficher de test pour contrôler les fonctions de réseau en particulier celles pour le client
 * @author Meunier, Lemoult, Morisseau || L3 informatique Le mans
 * @version 1.0
 * @date Decembre 2021
 */
#include "../include/réseau.h"
#define N 124
/*
 * @fn main
 * @brief Le programme teste les fonctions de réseau en particulier celles pour le client.
 */
int main(){
  printf("Démarrage du Client\n");
  SOCKET Client = SocketCreationConnexion(CLIENT);
  /*****************************/
  char c=1;
  int compteur;
  int buffer[N]={1};
  while(buffer[0]!='\n')
  {
    memset(buffer,0,sizeof(int)*N);
    printf("[VOUS]:");
    c=1;
    compteur=0;
    do
    {
      c=getchar();
      buffer[compteur++]=c;
    }while(c!='\n');
    SocketEnvoyer(Client,buffer,N);
  }
  /*****************************/
  SocketFermer(Client);
    return 0;
}
