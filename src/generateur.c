/**
 * @file generateur.c
 * @brief Réalisation des fonctions de génération de nombre pseudo-aléatoires
 * @author Meunier, Lemoult, Morisseau || L3 informatique Le mans
 * @version 1.0
 * @date Decembre 2021
 */
#include "include/generateur.h"

#define TAILLE_SEQUENCE puissance2(l)-1
#define TAILLE_RAND 10

/**
 * \fn void RandInit()
 * \brief La fonction initalise la sequence alétoire.
 */
void RandInit()
{
  seqRand=NULL;
  int VecteurInit[TAILLE_RAND]={1,1,1,1,1,1,1,1,1,1};
  int tabXOR[TAILLE_RAND]={0,0,1,1,1,1,1,1,1,1};
  seqRand=SequenceGenerer(VecteurInit,tabXOR,TAILLE_RAND);
}

/**
 * @fn void RandTerminer()
 * @brief La fonction libère et détruit le la sequence aléatoire.
 */
void RandTerminer()
{
  for(int i=0;i<puissance2(TAILLE_RAND)-1;i++)free(seqRand[i]);
  free(seqRand);
}

/**
 * @fn long RandGenerer()
 * @brief La fonction calcule un nombre pseudo-aléatoire. Si c'est la première fois n est défini grâce au temps (cf rapport).
 * @return Un nombre aléatoire.
 */
long RandGenerer(){
  static int n=0;
  //Si c'est la première fois qu'on déclare n alors on lui associe une valeur "pseudo aléatoire" qui est le temps depuis le 1er janvier 1970
  if(!n)
  {
    n=time(NULL);
  }
  n%=puissance2(TAILLE_RAND)-1;
  double val=0;
  for(int i=0;i<TAILLE_RAND;i++)
  {
    if(seqRand[n][i])val+=(314159265*puissance2(i));
  }
  n++;
  n%=puissance2(TAILLE_RAND)-1;
  return val<0?val*-1:val;
}

/**
 * @fn int XorApplique(int *tab, int *tabxor,int size)
 * @brief La fonction applique Xor sur tab pour créer une sequence.
 * @param tab La séquence actuelle.
 * @param tabxor C'est un tableau représentant le polynome générateur.
 * @param size La taille de la sequence.
 * @return La valeur du bit après avoir traversé tous les XOR.
 */
int XorApplique(int *tab, int *tabxor,int size)
{
  int resultat=tab[size-1];
  for(int i=size-2;i>=0;i--)
  {
    if(tabxor[i]){
      resultat=resultat^tab[i];
    }
  }
  return resultat;
}

/**
 * @fn void RecupererXOR(int *tab,int l)
 * @brief La fonction demande à l'utilisateur de saisir le polynome générateur.
 * @param tab Le tableau qui contient le polynome générateur .
 * @param l La longueur de la séquence
 */
void RecupererXOR(int *tab,int l)
{
  memset(tab,0,sizeof(int)*l);
  int i=0;
  do{
    printf("Saisir un polynome générateur (x2->2) (0 pour stop): ");
    scanf("%d",&i);
    if(i-1>=0 && i<=l)tab[i-1]=1;
  }while(i!=0);
  tab[i-1]=1;
}

/**
 * @fn int puissance2(int n)
 * @brief La fonction calcul 2 à la puissance n.
 * @param n Un nombre.
 * @return 2 à la puissance n.
 */
int puissance2(int n)
{
  int d=1;
  for(int i=0;i<n;i++)d*=2;
  return d;
}

/**
 * @fn void ajouter(int *tab1,int *tab2, int size,int n)
 * @brief La fonction ajoute une valeur au début d'un tableau.
 * @brief tab1 n'est pas modifié.
 * @param tab1 La séquence initiale
 * @param tab2 La séquence initiale décalé de 1 et n à la première place
 * @param size la taille des sequences
 * @param n Un nombre à ajouter au début de tab1

 */
void ajouter(int *tab1,int *tab2, int size,int n)
{
  size--;
  for(int i=size;i>0;i--)
  {
    tab2[i]=tab1[i-1];
  }
  tab2[0]=n;
}

/**
 * @fn int ** SequenceGenerer(int *VecteurInit,int *tabXOR,int l)
 * @brief La fonction génère un tableau avec toutes les séquences.
 * @param VecteurInit le vecteur d'initialisation.
 * @param tabXOR Le polynome générateur.
 * @param l La longueur de la séquence.
 * @return le tableau avec toutes les sequences generées.
 */
int ** SequenceGenerer(int *VecteurInit,int *tabXOR,int l)
{
  int resultat_XOR;
  /*Allocation de la memoire*/
  int ** tabfinal = malloc(sizeof(int *) * (TAILLE_SEQUENCE) ) ;

  for(int i = 0 ; i<TAILLE_SEQUENCE; i++)
    tabfinal[i] = malloc(sizeof(int) * l) ;

  /*Initialisation de tabfinal[0] séquence d'initialisation*/
  for(int i = 0 ; i<l ; i++) tabfinal[0][i] = VecteurInit[i] ;

  /*includeération de l'espace mémoire inutile*/
  //free(VecteurInit) ;

  /*Application des XOR*/
  for(int i = 0; i < TAILLE_SEQUENCE-1;i++)
  {
    resultat_XOR=XorApplique(tabfinal[i], tabXOR, l ) ;
    ajouter(tabfinal[i],tabfinal[i+1],l,resultat_XOR);
  }

  return tabfinal ;
}


/**
 * @fn void SequenceDetruire(int **sequence,int l)
 * @brief La fonction libère et détruit une liste de sequences donnée en paramètre.
 * @param sequence Liste de sequences à détruire.
 * @param l la longeur d'une sequence.
 */
void SequenceDetruire(int **sequence,int l)
{
  //libère les cases une par une
  for(int i=0;i<l;i++)free(sequence[i]);
  if(l)free(sequence);
  else free(*sequence);
}

/**
 * @fn void SequenceAfficher(int **seq,int l,int L)
 * @brief La fonction affiche la liste de sequences donnée en paramètre.
 * @param seq La liste de sequences à afficher.
 * @param l La longeur d'une séquence.
 * @param L Le nombre de séquences.
 */
void SequenceAfficher(int **seq,int l,int L)
{
  for(int i=0;i<l;i++)
  {
    printf("Valeur %d : ",i+1);
    for(int y=0;y<L;y++)
    {
      if(L>1)printf("%d ",seq[i][y]);
      else printf("%d ",(*seq)[i]);
    }
    printf("\n");
  }
}

/**
 * @fn int * CodeurGold(int ** sequence1, int ** sequence2, int c1, int c2, int l)
 * @brief La fonction fait le codage de gold.
 * @param sequence1 La première sequence.
 * @param sequence2 La deuxième sequence.
 * @param c1 La colonne de la sequence 1 pour l'encodage de gold.
 * @param c2 La colonne de la sequence 2 pour l'encodage de gold.
 * @param l La longueur.
 * @return La sequence encoder.
 */
//ATTENTION sequence1, sequene2 et le final ne sont pas free
int * CodeurGold(int ** sequence1, int ** sequence2, int c1, int c2, int l)
{
  /*Allocation de la memoire*/
  int * final = malloc(sizeof(int) * (TAILLE_SEQUENCE) );

  /*Application des XOR pour toutes les valeurs des colonnes c1(pour la sequence1) et c2(pour la sequence2)*/
  for(int i = 0 ; i < TAILLE_SEQUENCE; i++)
    final[i] = sequence1[i][c1]^sequence2[i][c2] ;

  return final ;
}

/**
 * @fn int Premiers(int n, int n2, int n3)
 * @brief La fonction regarde si les 3 paramètres sont premiers entre-eux.
 * @param n Un premier nombre.
 * @param n2 Un second.
 * @param n3 Un troisieme.
 * @return 1 si ils sont premiers sinon 0.
 */
//vérifie si n, n2, n3 sont premiers
int Premiers(int n, int n2, int n3)
{
  int nb_Diviseurs=0;
  for(int i=1;i<=n || i<=n2 || i<=n3;i++)
  {
    if(n%n2==0 || n%n3==0){printf(" %d est divisé par %d ou %d",n,n2,n3);return 0;}
    if(n2%n==0 || n2%n3==0){printf(" %d est divisé par %d ou %d",n2,n,n3);return 0;}
    if(n3%n2==0 || n3%n==0){printf(" %d est divisé par %d ou %d",n3,n2,n);return 0;}
    if(i<=n)if(n%i==0)nb_Diviseurs++;
    if(i<=n2)if(n2%i==0)nb_Diviseurs++;
    if(i<=n3)if(n3%i==0)nb_Diviseurs++;
  }
  return nb_Diviseurs==6;
}

/**
 * @fn int ** CodeurJPL(int *L, int L1, int L2, int L3, int **Sequence1, int **Sequence2, int **Sequence3)
 * @brief La fonction fait le codage JPL.
 * @param sequence1 la première sequence.
 * @param sequence2 la deuxième sequence.
 * @param sequence3 la deuxième sequence.
 * @param L1 la longueur de la sequence 1.
 * @param L2 la longueur de la sequence 2.
 * @param L3 la longuer de la sequence 3.
 * @param L la longueur
 * @return La sequence coder JPL
 */
int ** CodeurJPL(int *L, int L1, int L2, int L3, int **Sequence1, int **Sequence2, int **Sequence3)
{
  int **final;
  //Si ils sont tous premier alors on peut appliquer l'algorithme
  if(Premiers(L1,L2,L3));
  else return NULL;
  *L=L1+L2+L3;

  final=malloc(sizeof(int * )*(puissance2(L1)-1)*(puissance2(L2)-1)*(puissance2(L3)-1));
  for(int i=0;i<(puissance2(L1)-1)*(puissance2(L2)-1)*(puissance2(L3)-1);i++)
  {
    final[i]=calloc((*L),sizeof(int));
  }
  /***************TRAITEMENT******************/
  for(int i=0;i<(puissance2(L1)-1)*(puissance2(L2)-1)*(puissance2(L3)-1);i++)
  {
    for(int y=0;y<(*L);y++)
    {
      if(y<L1)             final[i][y]=Sequence1[i%(puissance2(L1)-1)][y];
      if(y>=L1 && y<L1+L2) final[i][y]=Sequence2[i%(puissance2(L2)-1)][y-L1];
      if(y>=L1+L2)         final[i][y]=Sequence3[i%(puissance2(L3)-1)][y-L1-L2];
    }
  }

  return final;
}
