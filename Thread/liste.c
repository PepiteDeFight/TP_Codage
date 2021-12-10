#include "liste.h"

int listeVide(TDA_LISTE liste)
{
  return liste->suivant == NULL;
}

TDA_LISTE listeDernier(TDA_LISTE liste)
{
  if(listeVide(liste)) return NULL;

  TDA_LISTE parcour = liste->suivant;
  while(parcour->suivant != NULL){
    parcour = parcour->suivant;
  }
  return parcour;
}

TDA_LISTE listePremier(TDA_LISTE liste)
{
  if(listeVide(liste)) return NULL;
  return liste->suivant;
}

TDA_LISTE listeCreer()
{
  TDA_LISTE liste = malloc(sizeof(TDA_LISTE)) ;
  liste->suivant = NULL;
  return liste ;
}

void listeDetruire(TDA_LISTE liste)
{
  while(! listeVide(liste)){
    listeRetirer(liste, listePremier(liste)->indice);
  }
  free(liste);
}

pthread_t listeAcceder(TDA_LISTE liste, int position)
{
  int i;
  if(listeVide(liste))return NULL;
  TDA_LISTE cellule = liste->suivant;
  for(i = 0; cellule->indice != position; i++){
    if(!cellule->suivant)return NULL;
    cellule = cellule -> suivant;
  }
  return cellule->t;
}

int listeAjouter(TDA_LISTE liste, pthread_t p)
{
  TDA_LISTE cellule = malloc(sizeof(TDA_LISTE));
  if(cellule==NULL)return -1;
  cellule->t = p;
  if(listeVide(liste))cellule->indice=0;
  else cellule->indice=listeDernier(liste)->indice+1;
  cellule->suivant = NULL;

  listeDernier(liste)->suivant = cellule;
  return 0;
}

void listeRetirer(TDA_LISTE liste,int indice)
{
  if(!listeVide(liste)){
    TDA_LISTE buffer,courrant = listePremier(liste);
    while(courrant->suivant->indice!=indice) courrant = buffer->suivant;
    buffer=courrant->suivant;
    courrant->suivant=buffer->suivant;
    free(buffer);
  }
}
