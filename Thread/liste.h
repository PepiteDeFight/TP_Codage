#ifndef _LISTE_

#include <pthread.h>
#include <stdlib.h>

typedef struct cel
{
  struct cel *suivant ;
  int etat;
  int indice;
  pthread_t * t ;
} *TDA_LISTE ;


int listeVide(TDA_LISTE liste);

TDA_LISTE listeDernier(TDA_LISTE liste);

TDA_LISTE listeCreer();

void listeDetruire(TDA_LISTE liste);

pthread_t listeAcceder(TDA_LISTE liste, int position);

int listeAjouter(TDA_LISTE liste, pthread_t p);

int listeRetirer(TDA_LISTE liste);


#endif
