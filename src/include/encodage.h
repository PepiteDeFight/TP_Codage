/**
 * @file encodage.h
 * @brief Prototypes des fonctions de codage et de décodage
 * @author Meunier, Lemoult, Morisseau || L3 informatique Le mans
 * @version 1.0
 * @date Decembre 2021
 */

#ifndef ENCODAGE_H
   #define ENCODAGE_H

   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #include <time.h>
   #include "hadamard.h"
   #include "generateur.h"
   int nb_utilisateur;
   int taille_message;
   typedef enum booleen{FAUX = -1, VRAI = 1} bool;
   #define BORNEINF 0
   #define BORNESUP 1
   #define CHAINE_VIDE 1
   #define DEBUG 1
   #define N 512
   #define BALISE '#'
   #define CARACTERESPE '@'
   #define MARKER_EMPLACEMENT 27
   #define PROBABILITE Intervalles[BORNESUP][indice]-Intervalles[BORNEINF][indice]
   #define TIMESLEEP 5

   #define BRUIT_FORT 1
   #define BRUIT_MOYEN 2
   #define BRUIT_FAIBLE 3
   #define BRUIT_CHOISI BRUIT_FAIBLE

   // la fonction recoit un utilisateur de 0 à nb_utilisateur - 1 , le tableau de hadamard qui correspond et le message à coder pour renvoyer le message codé
  int * Encodage(int, int **, int *);

  void DecodageSimple(int *);

  //code est la matrice envoyé elle est la somme de tous les message de taille (taille_message)
  int * Decodage(int *, int);

  int * SequenceInitialiser(int);

  void addition(int *,int *);

  int *SignalCreer();

  int *SignalGenerer(int);

  void SignalAjouterBruit(int *);

  int SignalSize();

  void SignalAfficher(int *);

  int *MessageCreer();

  void MessageAfficher(int *);

  void MessageDetruire(int *);

  int * hdbCoder(int *, int, int);

  int * hdbDecoder(int *, int, int);

  void hdbAfficher(int *, int);

  int ChaineTraiter(char [N],float [37],float *[2],char *);

  float ArithCoder(char [N],float [37],float *[2],char *,int *);

  char * ArithDecoder(float,float [37],float *[2],char *,int);

  void AppliqueArith(float,float,float *, float *);

  void ChaineMajer(char [N]);

  void ChaineAfficher(char [N]);

  void ChaineLire(char [N]);

  void IntervallesAfficher(float *[2],char *,int);

#endif
