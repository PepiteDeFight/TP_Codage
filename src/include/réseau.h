/**
 * @file réseau.h
 * @brief Prototypes des fonctions de réseau
 * @author Meunier, Lemoult, Morisseau || L3 informatique Le mans
 * @version 1.0
 * @date Decembre 2021
 */

#ifndef _RESEAU_H
  #define _RESEAU_H

  #ifdef _WIN32
    #include <winsock2.h>
    #include <winsock.h>
    #include <windows.h>
  #else
    #include <netdb.h>
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <arpa/inet.h>
  #endif

  #include <unistd.h> /* close */
  typedef int SOCKET;
  #define SERVEURNAME "127.0.0.1" // adresse IP de mon serveur
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <errno.h>
  #define CLIENT 0
  #define SERVEUR 1


  SOCKET SocketCreation();

  int SocketConnexion(SOCKET, int);

  SOCKET SocketCreationConnexion(int);

  int SocketAttenteEmetteurRecepteur(SOCKET, SOCKET *, SOCKET *);

  SOCKET SocketClientAccept(SOCKET);

  int SocketEnvoyer(SOCKET, int *,int);

  int SocketRecevoir(SOCKET,int *,int);

  int SocketFermer(SOCKET);

#endif
