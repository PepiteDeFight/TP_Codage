/**
 * @file réseau.c
 * @brief Réalisation des fonctions de réseau (sockets)
 * @author Meunier, Lemoult, Morisseau || L3 informatique Le mans
 * @version 1.0
 * @date Decembre 2021
 */

#include "include/réseau.h"

/**
 * @fn SOCKET SocketCreation()
 * @brief La fonction créer un socket.
 * @return La socket.
 */
SOCKET SocketCreation()
{
  SOCKET S = socket(AF_INET, SOCK_STREAM, 0);
  return S;
}

/**
 * @fn int SocketConnexion(SOCKET S, int mode)
 * @brief La fonction fait la connexion au socket.
 * @param S un socket.
 * @param mode le mode de connexion au socket.
 * @return Un entier d'erreur.
 */
int SocketConnexion(SOCKET S, int mode)
{
  struct sockaddr_in addr;
	addr.sin_addr.s_addr = inet_addr(SERVEURNAME);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(30000);
  addr.sin_addr.s_addr=htonl(INADDR_ANY);
  switch(mode)
  {
    case CLIENT : connect(S,(const struct sockaddr *)&addr,sizeof(addr));
                  break;
    case SERVEUR :bind(S,(const struct sockaddr *)&addr,sizeof(addr));
                  break;
  }
  return 0;
}

/**
 * @fn SOCKET SocketCreationConnexion(int mode)
 * @brief La fonction est 2 en 1, elle créer et connecte un socket.
 * @param mode Serveur (1) Client (0).
 * @return La socket.
 */
SOCKET SocketCreationConnexion(int mode)
{
    SOCKET socket=SocketCreation();
    SocketConnexion(socket,mode);
    return socket;
}

/**
 * @fn int SocketAttenteEmetteurRecepteur(SOCKET Cannal, SOCKET *Emetteur, SOCKET *Recepteur)
 * @brief La fonction permet au canal d'attendre que l'emetteur et le recepteur se connectent.
 * @param Cannal La socket du cannal.
 * @param Emetteur La socket de l'Emetteur.
 * @param Recepteur La socket du recepteur.
 * @return 0.
 */
int SocketAttenteEmetteurRecepteur(SOCKET Cannal, SOCKET *Emetteur, SOCKET *Recepteur)
{
  listen(Cannal,2);
	struct sockaddr_in addr_Emetteur;
	struct sockaddr_in addr_Recepteur;
	socklen_t csize = sizeof(addr_Emetteur);
	printf("Attente de l'emmeteur : \n");
	*Emetteur = accept(Cannal, (struct sockaddr * )&addr_Emetteur, &csize);
	printf("Attente du recepteur : \n");
	*Recepteur = accept(Cannal, (struct sockaddr * )&addr_Recepteur, &csize);
  return 0;
}

/**
 * @fn SOCKET SocketClientAccept(SOCKET Cannal)
 * @brief La fonction attend qu'un client se connecte.
 * @param cannal La socket du cannal.
 * @return Un socket connecté.
 */
SOCKET SocketClientAccept(SOCKET Cannal)
{
  listen(Cannal,1);
	struct sockaddr_in Addr;
	socklen_t csize = sizeof(Addr);
	printf("Attente du Client : \n");
  return accept(Cannal, (struct sockaddr * )&Addr, &csize);
}

/**
 * @fn SOCKET SocketClientAccept(SOCKET Cannal)
 * @brief La fonction effectue l'envoie d'un message sur une socket.
 * @param S La socket sur laquel envoyer le message.
 * @param message Le message à envoyer.
 * @param size La taille du tableau message.
 * @return Un socket.
 */
int SocketEnvoyer(SOCKET S, int *message,int size)
{
  for(int i=0;i<size;i++)
  {
    send(S,&(message[i]),sizeof(int),0);
  }
  return 0;
}

/**
 * @fn int SocketRecevoir(SOCKET S,int *message,int size)
 * @brief La fonction récupère l'information transmis par réseau.
 * @param S Une socket.
 * @param message Le message reçus.
 * @param size La taille du tableau message.
 * @return 0.
 */
int SocketRecevoir(SOCKET S,int *message,int size)
{
  for(int i=0;i<size;i++)
  {
    recv(S,&(message[i]),sizeof(int),0);
  }
  return 0;
}
/**

 * @fn int SocketFermer(SOCKET S)
 * @brief La fonction effectue la fermeture d'un socket donné en paramètre.
 * @param S La socket à fermer.
 * @return 0.
 */
int SocketFermer(SOCKET S)
{
  if(shutdown(S,SHUT_RDWR)<0)perror("Erreur : Shutdown");
  if(close(S)<0)perror("Erreur : close");
  return 0;
}
