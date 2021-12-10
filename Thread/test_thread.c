#include <stdio.h>

#include <pthread.h>

#include <errno.h>

#include "main.h"

#include <stdlib.h>

#define AGENT 0
#define AP 1

#define VAL_DEFAULT 0
#define VAL_START 1
#define VAL_DESTROY 2
#define VAL_QUIT 3
#define VAL_PAUSE 4
#define VAL_RUN 5
#define VAL_IGNORE 6
#define ERREUR -1

TDA_LISTE liste;

int Create(pthread_t *thread_agents,int nb, void *(*routine) (void *),int *arg)
{
  if(pthread_create(*thread_agents, NULL, routine, arg) == EAGAIN) perror("Erreur Création Thread");

  return listeAjouter(liste, *thread_agents);
}

int Invoke(int indice)
{
  if(listeVide(liste))return ERREUR;
  TDA_LISTE current=listeAcceder(liste,indice);
  if(current == NULL)return ERREUR;/*Thread inexistant*/
  current->etat=VAL_START
  return 0;
}

int Destroy(int indice)
{
  if(listeVide(liste))return ERREUR;
  TDA_LISTE current=listeAcceder(liste,indice);
  if(current == NULL)return ERREUR;/*Thread inexistant*/
  current->etat=VAL_DESTROY;
  return listeRetirer(indice);
}

int Quit(int indice)
{
  if(listeVide(liste))return ERREUR;
  TDA_LISTE current=listeAcceder(liste,indice);
  if(current == NULL)return ERREUR;/*Thread inexistant*/
  if (current->etat != VAL_IGNORE){
    current->etat=VAL_QUIT;
    return listeRetirer(indice);
  }
  return 0;
}

int Suspend(int indice)
{
  if(listeVide(liste))return ERREUR;
  TDA_LISTE current=listeAcceder(liste,indice);
  if(current == NULL)return ERREUR;/*Thread inexistant*/
  current->etat=VAL_PAUSE;
}

int Resume(int indice)
{
  if(listeVide(liste))return ERREUR;
  TDA_LISTE current=listeAcceder(liste,indice);
  if(current == NULL)return ERREUR;/*Thread inexistant*/
  current->etat=VAL_RUN;
}


void menu() {
  printf("\n====================================");
  printf("\n\t 1 # Creation Agent");
  printf("\n\t 2 # Invoque Agent");
  printf("\n\t 3 # Destrution Agent");
  printf("\n\t 4 # Fin Agent");
  printf("\n\t 5 # Fin AP");
  printf("\n====================================\n");
}

void * mainAgent(void *arg) {
  /* code */
  return NULL;
}

int main() {
  int nbAgent = 0;
  int saisie = 0;
  pthread_t *thread_agents;
  int encours=0;

  void * arg[PTHREAD_THREAD_MAX];

  while (saisie != -1) {
    menu();
    scanf("%d", & saisie);

    switch (saisie) {
    case 1: //Création Agent
      printf("Création de l'agent n°%d\n\n", nbAgent);
      if (create( & thread_agent[nbAgent++], NULL, & mainAgent, NULL) == EAGAIN) perror("PB thread");
      break;

    case 2:
      ;
      break; //Invocation Agent
    case 3:
      ;
      break; //destruction Agent
    case 4:
      ;
      break; //Fin Agent
    case 5:
      saisie = -1;
      break;
    }
  }

  pthread_join(thread_agent[1], NULL);
  return 0;
}
