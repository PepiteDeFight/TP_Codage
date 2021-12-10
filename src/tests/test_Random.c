/**
 * @file test_Random.c
 * @brief Ficher de test pour contrôler les fonctions de génération de nombre pseudo-aléatoires
 * @author Meunier, Lemoult, Morisseau || L3 informatique Le mans
 * @version 1.0
 * @date Decembre 2021
 */
#include "../include/generateur.h"
/*
 * @fn main
 * @brief Le programme teste les fonctions de génération de nombre pseudo-aléatoires.
 */
int main()
{
  int i=0;
  printf("Initialisation du générateur pseudo aléatoire : ");
  RandInit();
  printf("OK\n");
  printf("Saisir un nombre : ");
  scanf("%d",&i);
  printf("OK\n");
  while(i-->0)printf("%3d : %ld \n",i+1,RandGenerer());
  RandTerminer();
  return 0;
}
