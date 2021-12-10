/**
 * @file test_HDBnAri.c
 * @brief Ficher de test pour contrôler les fonctions de codage HDBn et Arithmétique
 * @author Meunier, Lemoult, Morisseau || L3 informatique Le mans
 * @version 1.0
 * @date Decembre 2021
 */
#include "../include/encodage.h"

void viderBuffer()
{
  char c=1;
  while((c=getchar()) != '\n');
}
/*
 * @fn main
 * @brief Le programme teste les fonctions de codage/décodage hdbn et arithmétique.
 */
int main(){
  //Valeur du TD1 pour tester
  int taille_signal = 23;
  int seq[taille_signal];

  //Signal du TD1
  seq[0] = 1;
  seq[1] = 0;
  seq[2] = 0;
  seq[3] = 1;
  seq[4] = 0;
  seq[5] = 1;
  seq[6] = 0;
  seq[7] = 0;
  seq[8] = 0;
  seq[9] = 0;
  seq[10] = 0;
  seq[11] = 0;
  seq[12] = 1;
  seq[13] = 1;
  seq[14] = 0;
  seq[15] = 0;
  seq[16] = 0;
  seq[17] = 0;
  seq[18] = 1;
  seq[19] = 1;
  seq[20] = 1;
  seq[21] = 0;
  seq[22] = 0;

  //On demande à l'utilisateur n
  int n=2;
  printf("Saisir n :");
  do{
    scanf("%d",&n);
  }while(n<=0);

  //Signal original
  printf("Signal original : ");
  hdbAfficher(seq, taille_signal);

  //Codage en Hdbn
  int *code = hdbCoder(seq, taille_signal, n);
  printf("Signal codé :     ");
  hdbAfficher(code, taille_signal);

  //Décodage en Hdbn
  int * signal_recu = hdbDecoder(code, taille_signal, n);
  printf("Signal décodé :   ");
  hdbAfficher(signal_recu, taille_signal);

  free(code);
  free(signal_recu);

  /*********************/
  /*Codage Arithmétique*/
  /*********************/
  viderBuffer();
  char chaine[N];
  int compteurLettresDiff=0;
  float chaineCodee=0;
  float *Intervalles[2];
  char *LettresRestantes=malloc(sizeof(char)*1);
  char *message;
  float ProbabilitesLettres[37];
  /*  Tableau des probablilités:
   *  -[0;25] => Lettres
   *  -[26;34] => Chiffres (1->9)
   *  -[35] => Reste
   *  -[36] => Balise (BALISE)
   *  -Total : 0->36 = 37
   */

  memset(ProbabilitesLettres,0,sizeof(float)*37);
  memset(chaine,0,sizeof(char)*N);

  printf("\t====LECTURE====\nLecture : ");
  ChaineLire(chaine);
  ChaineMajer(chaine);
  if(DEBUG)printf("Message = ");
  ChaineAfficher(chaine);

  printf("\n\t====ENCODAGE====\n");
  chaineCodee=ArithCoder(chaine,ProbabilitesLettres,Intervalles,LettresRestantes,&compteurLettresDiff);
  memset(chaine,0,sizeof(char)*N);
  printf("x = %.10f",chaineCodee);

  printf("\n\t====DECODAGE====\n");
  message=ArithDecoder(chaineCodee,ProbabilitesLettres,Intervalles,LettresRestantes,compteurLettresDiff);
  printf("Message = %s",message);
  free(message);
  free(LettresRestantes);
  free(Intervalles[BORNEINF]);
  free(Intervalles[BORNESUP]);
}
