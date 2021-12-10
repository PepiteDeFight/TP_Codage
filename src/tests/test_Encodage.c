/**
 * @file test_Encodage.c
 * @brief Ficher de test pour contrôler les fonctions d'encodage
 * @author Meunier, Lemoult, Morisseau || L3 informatique Le mans
 * @version 1.0
 * @date Decembre 2021
 */

#include "../include/encodage.h"
/*
 * @fn main
 * @brief Le programme teste les fonctions d'encodage.
 */
int main(){
  RandInit();
  int * message;
  printf("Saisir le nombre d'utilisateur : ");
  scanf("%d",&nb_utilisateur);
  printf(" ---> OK\n");
  printf("Saisir la taille du message : ");
  scanf("%d",&taille_message);
  printf(" ---> OK\n");

  /**********************************************************/
  /*                         CODAGE                         */
  /**********************************************************/
  printf("=======================PARTIE CODAGE=======================\n");
  int * signal=SignalGenerer(DEBUG);
  printf("Signal générer : \n");
  SignalAfficher(signal);
  /**********************************************************/
  /*                        DECODAGE                        */
  /**********************************************************/
  printf("=======================PARTIE DECODAGE=======================\n");
  //Affichage du signal
  printf("Signal reçu : \n");
  SignalAfficher(signal);

  //Affichage message de tt les utilisateurs
  for(int i = 0; i < nb_utilisateur; i++){
    printf("\nMessage de l'utilisateur %d : ", i+1);

    message = Decodage(signal, i);
    MessageAfficher(message);

    free(message);
  }
  free(signal);
  RandTerminer();
  return 0;
}
