/**
 * @file hadamard.h
 * @brief Prototypes des fonctions de Hadamard
 * @author Meunier, Lemoult, Morisseau || L3 informatique Le mans
 * @version 1.0
 * @date Decembre 2021
 */

#ifndef HADAMARD_H
 #define HADAMARD_H

 #include <stdio.h>
 #include <stdlib.h>

 //Renvoie la première puissance de 2 supérieur ou égale au nombre d'utilisateurs
 int HadamardNbLigne();

 //Transforme la matrice hadamard de N en matrice hadamard de N+1
 void HadamardAppliqueN(int**, int);

 //Crée une matrice Hadamard de la première taille possible qui puisse contenir le nombre d'utilisateur
 int ** HadamardCreer();

 //Détruit la matrice Hadamard passé en paramètre
 void HadamardDetruire(int **);

 //Affiche une matrice passé en paramètre
 void Hadamard_Afficher(int **);

#endif
