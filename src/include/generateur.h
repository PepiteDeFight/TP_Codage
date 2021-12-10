/**
 * @file generateur.h
 * @brief Prototypes des fonctions de génerations de séquences pseudo aléatoires
 * @author Meunier, Lemoult, Morisseau || L3 informatique Le mans
 * @version 1.0
 * @date Decembre 2021
 */

#ifndef _GENERATEUR_H
  #define _GENERATEUR_H
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <time.h>
  #define DEFAULT 1
  int **seqRand;

  void RandInit();

  void RandTerminer();

  long RandGenerer();

  void ajouter(int *,int *, int,int);

  int puissance2(int);

  int XorApplique(int *, int *,int);

  void RecupererXOR(int *,int);

  int ** SequenceGenerer(int *,int *,int);

  void SequenceDetruire(int **, int);

  void SequenceAfficher(int **,int,int);

  int * CodeurGold(int **, int **, int, int, int);

  int ** CodeurJPL(int *, int, int, int, int **, int **, int **);

  int Premiers(int, int, int);

#endif
