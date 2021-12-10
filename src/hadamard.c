/**
 * @file hadamard.c
 * @brief Réalisation des fonctions de Hadamard
 * @author Meunier, Lemoult, Morisseau || L3 informatique Le mans
 * @version 1.0
 * @date Decembre 2021
 */
#include "include/hadamard.h"

extern int nb_utilisateur;

/* Les macros permettent de déterminer la case à recopier dans la matrice hadamard de N+1
 * On obtient cette relation en imaginant couper la matrice hadamard de N+1 en quatre et en ramenant chaque coordonnés à une position de hadamard de N
 * Si i ou j est plus petit que la moitié de la matrice, on prend i ou j, sinon, on prend i ou j - la moitié de la taille de la matrice
 */

#define MACRO_I (i -taille_actu) < 0 ? i : i - taille_actu
#define MACRO_J (j -taille_actu) < 0 ? j : j - taille_actu




/**
 * @fn int HadamardNbLigne()
 * @brief Calcul de la première puissance de 2 supérieur ou égale au nombre d'utilisateurs.
 *
 * @return Le nombre de ligne de la matrice Hadamard en fonction du nombre d'utilisateurs.
 */
int HadamardNbLigne(){
  int i;
  for(i = 1; i < nb_utilisateur; i*=2);
  return i;
}

/**
 * @fn void HadamardAppliqueN(int** hadamard, int taille_actu)
 * @brief Modifie la matrice hadamard de N en matrice hadamard de N+1.
 *
 * @param hadamard Matrice hadamard à augmenter.
 * @param taille_actu La taille de la matrice hadamard actuelle (avant augmentation).
 */
void HadamardAppliqueN(int** hadamard, int taille_actu){
  int i, j; // i et j vont parcourir la matrice hadamard de N+1

  //On parcours toute la matrice hadamard de N+1
  for(i=0; ( i < taille_actu *2); i++){
    for(j=0; (j < taille_actu *2); j++){

      //On change la matrice uniquement si on ne se trouve pas dans la matrice hadamard de N
      if( ! (i < taille_actu && j < taille_actu) ){

        //Quand on ne doit pas inverser la matrice hadamard de N
        if( ! (i >= taille_actu && j >= taille_actu) ) hadamard[i][j] = hadamard[MACRO_I][MACRO_J];
        //Quand on doit inverser la matrice hadamard de N
        else hadamard[i][j] = -hadamard[MACRO_I][MACRO_J];
      }
    }
  }
}

/**
 * @fn int **HadamardCreer()
 * @brief Créer une matrice Hadamard de la première taille possible qui peut contenir le nombre d'utilisateur.
 *
 * @return La matrice de hadamard.
 */
int **HadamardCreer(){

  //On sauvegarde la taille de Hadamard
  int taille_matrice = HadamardNbLigne();

  //Compteur de la taille de la matrice actuelle
  int taille_actu = 1;

  //Création de la matrice de Hadamard de taille 1
  int **hadamard;
  hadamard = malloc(sizeof(int*)*taille_matrice);
  for(int i = 0; i < taille_matrice; i++){
    hadamard[i]= malloc(sizeof(int)*taille_matrice);
  }
  hadamard[0][0] = 1;

  //Tant que la matrice de Hadamard c'est pas assez grande, on prend la matrice de Hadamard à N+1
  while(taille_actu < nb_utilisateur){

    //On double la taille de la matrice (et donc le nombre d'utilisateur max)
    HadamardAppliqueN(hadamard, taille_actu);
    taille_actu *= 2;
  }
  return hadamard;
}

/**
 * @fn void HadamardDetruire(int **hadamard)
 * @brief Détruit la matrice Hadamard passée en paramètre.
 * @param hadamard La matrice à détruire.
*/
void HadamardDetruire(int **hadamard){
  int taille_matrice = HadamardNbLigne();

  //Destruction de la mémoire dynamique
  for(int i = 0; i < taille_matrice; i++) free(hadamard[i]);
  free(hadamard);
}


/**
 * @fn void Hadamard_Afficher(int **mat)
 * @brief Affiche une matrice passée en paramètre.
 *
 * @param mat La matrice à afficher.
 */
void Hadamard_Afficher(int **mat){
  int n, m;
  for(n = 0; n < HadamardNbLigne(); n++){
    for(m = 0; m < HadamardNbLigne(); m++){
      printf("%2d ", mat[n][m]);
    }
    printf("\n");
  }
}
