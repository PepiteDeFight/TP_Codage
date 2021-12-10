/**
 * @file test_Hadamard.c
 * @brief Ficher de test pour contrôler les fonctions de Hadamard
 * @author Meunier, Lemoult, Morisseau || L3 informatique Le mans
 * @version 1.0
 * @date Decembre 2021
 */
#include "../include/hadamard.h"
int nb_utilisateur;
/*
 * @fn main
 * @brief Le programme teste les fonctions de génération de matrice de hadamard.
 */
int main()
{
  //On affiche le nombre d'utilisateur séléctionné
  printf("\n\nSaisir le nombre d'utilisateur : \n");
  scanf("%d",&nb_utilisateur);

  //On crée la matrice Hadamard la plus petite possible qui peut contenir tout les utilisateurs
  int** hadamard = HadamardCreer();

  //On affiche la matrice de hadamard séléctionnée
  printf("Matrice de Hadamard séléctionnée : \n\n");
  Hadamard_Afficher(hadamard);

  HadamardDetruire(hadamard);
}
