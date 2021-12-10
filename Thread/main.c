#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include "main.h"
#include <stdlib.h>

#define create phtread_create
void *mainAgent(void * inutile)
{
  printf("\tSALUT\n") ;
  pthread_exit(NULL);
}

void menu()
{
    printf("\n====================================") ;
    printf("\n\t 1 # Creation Agent") ;
    printf("\n\t 2 # Invoque Agent") ;
    printf("\n\t 3 # Destrution Agent") ;
    printf("\n\t 4 # Fin Agent") ;
    printf("\n\t 5 # Fin AP") ;
    printf("\n====================================\n") ;
    printf("N'OUBLIE PAS, LE BINAIRE, C'EST DEUX ETATS !\nTU PEUX CHOISIR \n>") ;
}

int main(){
  int nbAgent = 0;
  int saisie = 0;
  //pthread_t thread_agent[NB_AGENT] ;

  //void * arg[PTHREAD_THREAD_MAX] ;

  while(saisie != -1)
  {
    menu() ;
    scanf("%d",&saisie) ;

    switch(saisie)
    {
      case 1 : //Création Agent
        printf("Création de l'agent n°%d\n\n", nbAgent);
        //if (create(&thread_agent[nbAgent++], NULL , &mainAgent, NULL) == EAGAIN) perror("PB thread");
        break;


      case 2 : ;break; //Invocation Agent
      case 3 : ;break; //destruction Agent
      case 4 : ;break; //Fin Agent
      case 5 : saisie = -1 ; break ;
    }
  }

  //pthread_join(thread_agent[1],NULL) ;
  return 0;
}
