/**
 * @file test_Generateur.c
 * @brief Ficher de test pour contrôler les fonctions de génération
 * @author Meunier, Lemoult, Morisseau || L3 informatique Le mans
 * @version 1.0
 * @date Decembre 2021
 */
#include "../include/generateur.h"
#define N 124
/*
 * @fn main
 * @brief Le programme teste les fonctions de génération de séquences pseudo-aléatoire ainsi que les codage JPL et gold.
 */
int main()
{
  int vecteur_init[N];
  for(int i=0;i<N;i++)vecteur_init[i]=1;
  int tabXOR[N]={0};
  int l1,l2,l3,l4,l;

  printf("Saisir la taille de la première séquence (mat1) -->JPL: ");
  scanf("%d",&l1);
  RecupererXOR(tabXOR,l1);
  printf("Generation de la matrice (mat1):");
  int **mat1=SequenceGenerer(vecteur_init,tabXOR,l1);
  printf("OK\n");
  printf("Affichage de mat1 :\n");
  SequenceAfficher(mat1,puissance2(l1)-1,l1);
  printf("OK\n");

  printf("Saisir la taille de la deuxième séquence (mat2) -->JPL: ");
  scanf("%d",&l2);
  RecupererXOR(tabXOR,l2);
  printf("Generation de la matrice (mat2):");
  int **mat2=SequenceGenerer(vecteur_init,tabXOR,l2);
  printf("OK\n");
  printf("Affichage de mat2 :\n");
  SequenceAfficher(mat2,puissance2(l2)-1,l2);
  printf("OK\n");

  printf("Saisir la taille de la troisième séquence (mat3) -->JPL: ");
  scanf("%d",&l3);
  RecupererXOR(tabXOR,l3);
  printf("Generation de la matrice (mat3):");
  int **mat3=SequenceGenerer(vecteur_init,tabXOR,l3);
  printf("OK\n");
  printf("Affichage de mat3 :\n");
  SequenceAfficher(mat3,puissance2(l3)-1,l3);
  printf("OK\n");

  printf("La taille de la troisième séquence (mat4) -->GOLD vaut celle de mat3.\n");
  l4=l3;
  RecupererXOR(tabXOR,l4);
  printf("Generation de la matrice (mat4):");
  int **mat4=SequenceGenerer(vecteur_init,tabXOR,l4);
  printf("OK\n");
  printf("Affichage de mat4 :\n");
  SequenceAfficher(mat4,puissance2(l4)-1,l4);
  printf("OK\n");

  printf("Generation de la matrice finaleGOLD avec le codeur GOLD: ");
  int *finalGOLD=CodeurGold(mat3,mat4,1,1,l4);
  printf("OK\n");
  printf("Affichage de la matrice finalGOLD (Résultat du codeur GOLD) :\n");
  SequenceAfficher(&finalGOLD,puissance2(l4)-1,1);

  printf("Generation de la matrice finale avec le codeur JPL: ");
  int **final=CodeurJPL(&l,l1,l2,l3,mat1,mat2,mat3);
  if(final == NULL) printf("KO\n");
  else printf("OK\n");
  if(final != NULL) printf("Affichage de la matrice final (Résultat du codeur JPL) :\n");
  if(final != NULL) SequenceAfficher(final,(puissance2(l1)-1)*(puissance2(l2)-1)*(puissance2(l3)-1),l);

  printf("Destruction de mat1 : ");
  SequenceDetruire(mat1,puissance2(l1)-1);
  printf("OK\n");
  printf("Destruction de mat2 : ");
  SequenceDetruire(mat2,puissance2(l2)-1);
  printf("OK\n");
  printf("Destruction de mat3 : ");
  SequenceDetruire(mat3,puissance2(l3)-1);
  printf("OK\n");
  printf("Destruction de mat4 : ");
  SequenceDetruire(mat4,puissance2(l4)-1);
  printf("OK\n");
  if(final != NULL)printf("Destruction de final : ");
  if(final != NULL)SequenceDetruire(final,(puissance2(l1)-1)*(puissance2(l2)-1)*(puissance2(l3)-1));
  if(final != NULL)printf("OK\n");
  printf("Destruction de finalGOLD : ");
  SequenceDetruire(&finalGOLD,0);
  printf("OK\n");
  return 0;
}
