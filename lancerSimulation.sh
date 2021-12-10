#!/bin/sh
nb_Utilisateur=0
taille_message=0
while [ $nb_Utilisateur -lt 1 ]
do
  printf "Saisir le nombre d'utilisateur : \n"
  read nb_Utilisateur
done
while [ $taille_message -lt 1 ]
do
  printf "Saisir la taille des messages : \n"
  read taille_message
done
gnome-terminal -- bash -c "./bin/canal $nb_Utilisateur $taille_message"
gnome-terminal -- bash -c "./bin/emetteur"
gnome-terminal -- bash -c "./bin/recepteur"
