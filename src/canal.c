/**
 * @file canal.c
 * @brief Réalisation de l'entité canal
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
  printf("Démarrage du canal\n");
  RandInit();
  nb_utilisateur=atoi(argv[1]);
  taille_message=atoi(argv[2]);
  //Création des sockets
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
  /********************/
  /*Debut du programme*/
  /********************/
  int *signal=SignalCreer();
  while(getchar()!='\n');
  printf("=========================\n");
  printf("TRANSMISSION DU MESSAGE  \n");
  printf("EN COURS ...  \n");

  for(int i=0;i<TIMESLEEP;i++)
  {
    printf("%d ...\n",TIMESLEEP-i);
    sleep(1);
  }
  SocketRecevoir(Emetteur,signal,SignalSize());
  printf("Message reçu : \n");
  SignalAfficher(signal);
  printf("Ajout d'un bruit : \n");
  SignalAjouterBruit(signal);
  printf("---> OK\n");
  printf("Affichage :\n");
  SignalAfficher(signal);
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
  SocketEnvoyer(Recepteur,signal,SignalSize());
  printf("---> OK\n");
  printf("Terminer ?\n");
  while(getchar()!='\n');
  RandTerminer();
  //Fermeture des sockets
  SocketFermer(Canal);
  SocketFermer(Emetteur);
  SocketFermer(Recepteur);
  return 0;
}
