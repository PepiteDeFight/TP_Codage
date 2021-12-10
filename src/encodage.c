/**
 * @file encodage.c
 * @brief Contient les fonctions d'encodage et de décodage de Hadamard, HDBn et Arithmétique
 * @author Meunier, Lemoult, Morisseau || L3 informatique Le mans
 * @version 1.0
 * @date Decembre 2021
 */
#include "include/encodage.h"
#include <math.h>

/******************************/

/*      Codage De Hadmard     */

/******************************/


/*
 * @fn int * Encodage(int user, int **hadamard, int * message)
 * @brief La fonction recoit un utilisateur de 0 à nb_utilisateur - 1 , le tableau de hadamard qui correspond et le message à coder pour renvoyer le message codé
 *
 * @param user Utilisateur que l'on veut Encoder
 * @param hadamard Matrice de Hadamard correspondante au nombre d'utilisateur
 * @param message Message complet avec tous les signaux sommés
 * @return Le signal de l'utilisateur (user)
 */
int * Encodage(int user, int **hadamard, int * message)
{
  int * code = calloc(SignalSize(),sizeof(int) ) ;
  int i , j ; // i taille = code, j = taille message

  if( !(user >= 0 && user < nb_utilisateur ) ) // vérifie la validité de l'utilisateur
    return code ;


  for( j = 0 ; j < taille_message ; j++ )// encodage de l'information
    for( i = 0 ; i < ( HadamardNbLigne() ) ; i++ )
      if(message[j]==0)code[i + (j*HadamardNbLigne())]=-hadamard[user][i];
      else code[i + (j*HadamardNbLigne())]=hadamard[user][i];
  for(int i=0;i<SignalSize();i++)if(!code[i])code[i]=-1;
  return code ;
}


/**
 * @fn void DecodageSimple(int *signal)
 * @brief La fonction execute simplement le décodage et affiche chaque message reçu
 * @param signal un signal à décoder
 */
void DecodageSimple(int *signal)
{
  int *message;
  printf("Affichage des messages reçu :\n");
  for(int i=0;i<nb_utilisateur;i++)
  {
    printf("Utilisateur %d à transmit : ",i+1);
    message=Decodage(signal,i);
    MessageAfficher(message);
    printf("\n");
    free(message);
  }
  free(signal);
}




/**
 * @fn int * Decodage(int * signal, int utilisateur)
 * @brief La fonction reçoit un signal et son numéro d'utilisateur pour décrypter le messgae du signal
 * @param signal un signal à décoder
 * @param utilisateur le numéro d'utilisateur correspondant au signal
 * @return Le message décodé
 */
int * Decodage(int * signal, int utilisateur)
{

  //Les compteurs
  int i, j, k = 0;
  int sous_tot;

  //Buffer pour le calcul du message
  float f = (float) 1 / HadamardNbLigne();

  //Le message à retourner
  int *message = MessageCreer();

  //On récupère la séquence d'étalement de l'utilisateur
  int *sequence = SequenceInitialiser(utilisateur);

  //On parcours le signal
  for(i = 0; i < SignalSize(); i+=HadamardNbLigne()){

    sous_tot = 0;

    //On prend 1 bit de message
    for(j = 0; j < HadamardNbLigne(); j++){
      sous_tot += sequence[j] * signal[i+j];
    }

    //On ajoute le bit au message
    message[k++] = f * sous_tot;
  }

  free(sequence);
  return message;
}


/**
 * @fn void addition(int *final,int *code)
 * @brief La fonction prend deux tableaux et les sommes
 * @param final le tableau final de la taille de sortie
 * @param code un signal codé
 */
void addition(int *final,int *code)
{
  for(int i=0;i<SignalSize();i++)final[i]+=code[i];
}

/**
 * @fn int * SequenceInitialiser(int utilisateur)
 * @brief La fonction initialise une sequence
 * @param utilisateur le numéro d'utilisateur
 * @return retourne une sequence
 */
int * SequenceInitialiser(int utilisateur)
{
  int ** hadamard = HadamardCreer();

  int *sequence = malloc(sizeof(int) * HadamardNbLigne());
  int i;

  for(i = 0; i < HadamardNbLigne(); i++){
    sequence[i] = hadamard[utilisateur][i];
  }
  HadamardDetruire(hadamard);
  return sequence;
}


/**
 * @fn int *SignalCreer()
 * @brief La fonction alloue la mémoire nécessaire pour un signal
 * @return retourne le signal
 */
int *SignalCreer()
{
  return malloc(sizeof(int)*SignalSize());
}



/**
 * @fn int *SignalCreer()
 * @brief La fonction génère un signal de 0
 * @param debug Affichage des procédures
 * @return retourne le signal
 */
int *SignalGenerer(int debug)
{
  int **hadamard=HadamardCreer();
  int *code;
  int *message;
  int *final=calloc(SignalSize(),sizeof(int));
  for(int i=0;i<nb_utilisateur;i++)
  {
    printf("Je suis l'utilisateur %d\n",i+1);
    if(debug)printf("Création du message : \n");
    message = MessageCreer();
    printf("\tMessage : ");
    MessageAfficher(message);
    printf("OK\n");
    if(debug)printf("Encodage du message : ");
    code = Encodage(i , hadamard, message ) ;
    free(message);
    if(debug)printf("OK\n");
    if(debug)printf("Affichage : \n");
    if(debug)SignalAfficher(code);
    if(debug)printf("Addition du message codé :");
    addition(final,code);
    if(debug)printf("OK \n");
    free(code);
  }
  for(int i=nb_utilisateur;i<HadamardNbLigne();i++)
  {
    message = calloc(taille_message,sizeof(int));
    code = Encodage(i , hadamard, message ) ;
    free(message);
    addition(final,code);
    free(code);
  }
  HadamardDetruire(hadamard);
  return final;
}


/**
 * @fn void SignalAjouterBruit(int *signal)
 * @brief La fonction ajoute du bruit à un signal passé en paramètre.
 * @param signal un signal
 */
void SignalAjouterBruit(int *signal)
{
  int max;
  switch(BRUIT_CHOISI)
  {
    case BRUIT_FAIBLE:max=RandGenerer()%(int)(SignalSize()*0.33);break;
    case BRUIT_MOYEN:max=RandGenerer()%(int)(SignalSize()*0.66);break;
    case BRUIT_FORT:max=RandGenerer()%(int)(SignalSize()*0.99);break;
  }
  //on génére un nombre aléatoire pas trop grand (n)
  for(int n=max;n>0;n--)
  {
    //Modulo 3 donne un chiffre dans l'intervalle [0,1,2].
    //L'utilisation de -1 permet de passer cet intervalle en [-1,0,1]
    signal[RandGenerer()%SignalSize()]+=(RandGenerer()%3)-1;
  }
  return;
}

/**
 * @fn int SignalSize()
 * @brief La fonction donne la taille d'un signal.
 * @return retourne la taille d'un signal
 */
int SignalSize()
{
  return taille_message*HadamardNbLigne();
}

/**
 * @fn void SignalAfficher(int *signal)
 * @brief La fonction affiche le signal passé en paramètre.
 * @param signal le signal à afficher
 */
void SignalAfficher(int *signal)
{
  for(int i = 0 ; i < SignalSize() ; i++)printf("valeur %2d : %2d \n",i, signal[i]) ;
}


/**
 * @fn int *MessageCreer()
 * @brief La fonction génère un message aléatoirement avec la fonction de génération du TP2.
 * @return retourne le message
 */
int *MessageCreer()
{
  int *message=calloc(taille_message,sizeof(int) );
  for(int i=0;i<taille_message;i++)
  //message[i]=rand()%2;
  //Utilisation de notre propre fonction de génération de nombre
  message[i]=RandGenerer()%2;
  return message;
}


/**
 * @fn void MessageAfficher(int *message)
 * @brief La fonction affiche le message passé en paramètre.
 * @param message un message à afficher
 */
void MessageAfficher(int *message)
{
  int i;
  for(i = 0; i < taille_message; i++){
    if(message[i]==1)printf("1 ");
    else printf("0 ");
  }
  printf("\n");
}

/**
 * @fn void MessageDetruire(int *a)
 * @brief La fonction détruit un message.
 * @param a le messgae à détruire
 */
void MessageDetruire(int *a)
{
  free(a);
}


/******************************/

/*         Codage HDBn        */

/******************************/



/**
 * @fn int * hdbCoder(int * sequence, int taille_seq, int n)
 * @brief La fonction code une séquence avec un codeur hdbn.
 * @param sequence une séquence à coder
 * @param taille_seq la taille de la séquence
 * @param n Le n de hdbN
* @return La séquence codée
 */
int * hdbCoder(int * sequence, int taille_seq, int n){

  //Création du signal à renvoyer
  int *code = malloc(sizeof(int)* taille_seq);

  //Le premier viol est négatif et le premier 1 est positif
  bool dernier_viol = FAUX;
  bool dernier_un = FAUX;

  int i, j;
  int compteur_zero = 0;

  //On parcours tout le signal bit par bit
  for(i = 0; i < taille_seq; i++){

    //Si le bit est 1
    if(sequence[i] == VRAI){
      compteur_zero = 0;

      //Le 1 est positif car le dernier 1 était négatif
      if(dernier_un == FAUX){
        code[i] = 1;
        dernier_un = VRAI;
      }

      //Le 1 est négatif car le dernier 1 était positif
      else{
        code[i] = -1;
        dernier_un = FAUX;
      }
    }

    //Si le bit est 0
    else{
      compteur_zero ++;

      //Si il n'y pas trop de 0 d'affilé
      if(compteur_zero <= n){
        code[i] = 0;
      }

      //Si il y a trop de 0 d'affilé
      else{

        if(dernier_viol == VRAI){

          //Code erreur si dernier viol positif et dernier 1 positif
          if(dernier_un == VRAI){
            code[i-n] = -1;
            for(j = 1; j < n; j++) code[i-j] = 0;
            code[i] = -1;
            dernier_un = FAUX;
          }

          //Code erreur si dernier viol positif et dernier 1 négatif
          else{
            code[i-n] = 0;
            for(j = 1; j < n; j++) code[i-j] = 0;
            code[i] = -1;
            dernier_un = FAUX;
          }

        dernier_viol = FAUX;
        }

        else{

          //Code erreur si dernier viol négatif et dernier 1 positif
          if(dernier_un == VRAI){
            code[i-n] = 0;
            for(j = 1; j < n; j++) code[i-j] = 0;
            code[i] = 1;
            dernier_un = VRAI;
          }

          //Code erreur si dernier viol négatif et dernier 1 négatif
          else{
            code[i-n] = 1;
            for(j = 1; j < n; j++) code[i-j] = 0;
            code[i] = 1;
            dernier_un = VRAI;
          }

          dernier_viol = VRAI;
        }

      compteur_zero = 0;
      }
    }
  }
  //On renvoie le résultat
  return code;
}





/**
 * @fn int * hdbDecoder(int * code, int taille_seq, int n)
 * @brief La fonction décode une séquence codée avec un codeur hdbn.
 * @param code une séquence codée
 * @param taille_seq la taille de la séquence
 * @param n Le n de hdbN
 * @return La séquence décodée
 */
int * hdbDecoder(int * code, int taille_seq, int n)
{

  //Création du signal à renvoyer
  int *seq = malloc(sizeof(int)* taille_seq);

  //Le premier 1 est positif
  bool dernier_un = FAUX;

  int i, j;

  //On parcours tout le signal bit par bit
  for(i = 0; i < taille_seq; i++){

    //Si le bit est à 0
    if(code[i] == 0){
      seq[i] = 0;
    }


    else{
      if(code[i] == 1){

        //Si les deux dernier 1 sont bien différent
        if(dernier_un == FAUX){
          dernier_un = VRAI;
          seq[i] = 1;
        }

        //Si les deux dernier 1 sont identiques (erreur)
        else{
          for(j = 0; j <= n; j++){
            seq[i-j] = 0;
          }
        }
      }
      else{

        //Si les deux dernier 1 sont bien différent
        if(dernier_un == VRAI){
          dernier_un = FAUX;
          seq[i] = 1;
        }

        //Si les deux dernier 1 sont identiques (erreur)
        else{
          for(j = 0; j <= n; j++){
            seq[i-j] = 0;
          }
        }
      }
    }
  }
  //On renvoie le résultat
  return seq;
}

/**
 * @fn void hdbAfficher(int *signal, int taille_signal)
 * @brief La fonction affiche un signal de taille passée en paramêtre.
 * @param taille_signal la tialle du signal
 */
void hdbAfficher(int *signal, int taille_signal)
{
  int i;
  for(i = 0; i < taille_signal; i++){
    printf("%3d ", signal[i]);
  }
  printf("\n");
}


/******************************/

/*    Codage Arithmétique     */

/******************************/

/**
 * @fn void ProbaAfficher(float ProbabilitesLettres[37])
 * @brief La fonction affiche le tableau des probabilités.
 * @param ProbabilitesLettres le tableau en question
 */
void ProbaAfficher(float ProbabilitesLettres[37])
{
  for(int i=0;i<26;i++)
    if(DEBUG)printf("La lettre %c vaut %f\n",i+'a',ProbabilitesLettres[i]);
  for(int i=0;i<9;i++)
      if(DEBUG)printf("La lettre %c vaut %f\n",i+'1',ProbabilitesLettres[i+26]);
  if(DEBUG)printf("Le reste vallent %f\n",ProbabilitesLettres[35]);
  if(DEBUG)printf("La balise # vaut %f\n",ProbabilitesLettres[36]);
}

/**
 * @fn void IntervallesAfficher(float *Intervalles[2],char *LettresRestantes,int compteur)
 * @brief La fonction affiche l'intervalle de chaque lettre.
 * @param Intervalles[2] le tableau des intervalles
 * @param LettresRestantes tableau de lettres présentent dans le message
 * @param compteur le nombre de lettres
 */
void IntervallesAfficher(float *Intervalles[2],char *LettresRestantes,int compteur)
{
  for(int i=0;i<compteur;i++)if(DEBUG)printf("%c : [%f;%f[\n",LettresRestantes[i],Intervalles[BORNEINF][i],Intervalles[BORNESUP][i]);
}

/**
 * @fn void ChaineMajer(char chaine[N])
 * @brief La fonction met en majuscule les lettres d'un tableau de taille N.
 * @param chaine[N] le tableau en question
 */
void ChaineMajer(char chaine[N])
{
  for(int i=0;chaine[i]!=BALISE;i++)if(chaine[i]>='a' && chaine[i]<='z')chaine[i]=chaine[i]-'a'+'A';
}

/**
 * @fn void ChaineLire(char chaine[N])
 * @brief La fonction recupère dans l'entrée standard.
 * @param chaine[N] le tableau qui récupère les caractères
 */
void ChaineLire(char chaine[N])
{
  int compteur=0;
  char c=1;
  while(c!='\n')
  {
    c=getchar();
    chaine[compteur++]=c;
  }
  chaine[compteur-1]=BALISE;
}
/**
 * @fn void ChaineAfficher(char chaine[N])
 * @brief La fonction affiche la chaine récupèrée avec la fonction ChaineLire.
 * @param chaine[N] le tableau des caractères.
 */
void ChaineAfficher(char chaine[N])
{
    for(int i=0;chaine[i]!=BALISE;i++)if(DEBUG)printf("%c",chaine[i]);
}

/**
 * @fn int ChaineTraiter(char chaine[N],float ProbabilitesLettres[37],float *Intervalles[2],char *LettresRestantes)
 * @brief La fonction traite une chaine c'est-à-dire, elle compte les occurances de chaque lettre, les classes et calcule leur probabilité.
 * @param chaine[N] le tableau des caractères.
 * @param ProbabilitesLettres[37] le tableau des probabilités.
 * @param Intervalles[2] le tableau des intervalles.
 * @param LettresRestantes tableau contenant les lettres, en 1 seul exemplaire, présentes dans la chaine .
 * @return Le nombre de lettres différentes.
 */
int ChaineTraiter(char chaine[N],float ProbabilitesLettres[37],float *Intervalles[2],char *LettresRestantes)
{
  int compteur;
  int i=0,y=0;
  int compteurDifferentes=0;
  for(compteur=0;chaine[compteur]!=BALISE;compteur++)
  {
    if(chaine[compteur]>='A' && chaine[compteur]<='Z') ProbabilitesLettres[chaine[compteur]-'A']++;
    else if(chaine[compteur]>='1' && chaine[compteur]<='9') ProbabilitesLettres[chaine[compteur]-'1'+26]++;
    else if(chaine[compteur]!=BALISE)
    {
      ProbabilitesLettres[35]++;
      //Certains caractères spéciaux vallent 2 char pour y remerdier on les comptes comme 2
    }
  }
  compteur++;
  if(DEBUG)printf("Il y a %d lettres \n",compteur);
  //On rajoute la balise
  ProbabilitesLettres[36]=1;
  //********************
  if(DEBUG)printf("Le tableau de probablilités Contient maintenant pour chaque caractère son nombre d'occurance\n");
  for(int i=0;i<37;i++)
    if(ProbabilitesLettres[i]!=0)
    {
      ProbabilitesLettres[i]/=compteur;
      compteurDifferentes++;
      LettresRestantes=realloc(LettresRestantes,sizeof(char)*compteurDifferentes);
      if(i<26)LettresRestantes[compteurDifferentes-1]=i+'A';
      if(i>=26 && i<35)LettresRestantes[compteurDifferentes-1]='1'+i-26;
      if(i == 35)LettresRestantes[compteurDifferentes-1]=CARACTERESPE;
      if(i == 36)LettresRestantes[compteurDifferentes-1]=BALISE;
    }
  if(DEBUG)printf("Compteur diff : %d\n",compteurDifferentes);
  ProbaAfficher(ProbabilitesLettres);
  Intervalles[BORNEINF]=malloc(sizeof(float)*compteurDifferentes);
  Intervalles[BORNESUP]=malloc(sizeof(float)*compteurDifferentes);

  //On remplit les intervalles
  //On cherche d'abord la première lettre pour initialiser le tableau
  //i représente l'indice de recherche des Lettres
  //y représente l'indice d'incrémentation du tableau Intervalles => y ne doit pas dépasser le nombre max de lettres (compteurDifferentes)

  for(i=0;i<37;i++)
  {
    if(ProbabilitesLettres[i]>0)
    {
      Intervalles[BORNEINF][y]=0;
      Intervalles[BORNESUP][y]=ProbabilitesLettres[i];
      y++;
      i++;
      compteur=i;
      break;
    }
  }
  //Maintenant on traite le reste
  for(i=compteur;i<37;i++)
  {
    if(ProbabilitesLettres[i]>0)
    {
      Intervalles[BORNEINF][y]=Intervalles[BORNESUP][y-1];
      Intervalles[BORNESUP][y]=Intervalles[BORNESUP][y-1]+ProbabilitesLettres[i];
      y++;
    }
  }

  IntervallesAfficher(Intervalles,LettresRestantes,compteurDifferentes);
  return compteurDifferentes;
}


/**
 * @fn void AppliqueArith(float binfLettre,float bsupLettre,float *binf, float *bsup)
 * @brief La fonction applique sur un intervalle le calcul de la prochaine intervalle.
 * @param binfLettre Borne inférieure de la lettre à coder.
 * @param bsupLettre Borne supérieure de la lettre à coder.
 * @param binf Borne inférieure finale.
 * @param bsup Borne supérieure finale.
 */
void AppliqueArith(float binfLettre,float bsupLettre,float *binf, float *bsup)
{
  float TInterval = (*bsup)-(*binf);
  //On calcul dabord bsup car elle a besoin de l'ancienne binf
  *bsup=*binf+TInterval*bsupLettre;
  *binf=*binf+TInterval*binfLettre;
}

/**
 * @fn char * ArithDecoder(float BorneADecoder,float ProbabilitesLettres[37],float *Intervalles[2],char *LettresRestantes,int compteurDifferentes)
 * @brief La fonction décode un message codé avec le codeur arithmétique.
 * @param BorneADecoder Borne inférieure à décoder .
 * @param ProbabilitesLettres[37] le tableau des probabilités.
 * @param Intervalles[2] le tableau des intervalles.
 * @param LettresRestantes tableau contenant les lettres, en 1 seul exemplaire, présentes dans la chaine .
 * @param compteurDifferentes Le nombre de lettres différentes.
 * @return Une chaine de caractères représentant le message décodé.
 */
char * ArithDecoder(float BorneADecoder,float ProbabilitesLettres[37],float *Intervalles[2],char *LettresRestantes,int compteurDifferentes)
{
  //nombre du mot = (nombre du mot – borne inférieure de la lettre) / probabilité de la lettre
  int indice=0;
  int compteur=0;
    char *chaine=malloc(sizeof(char));
    do{
      if(DEBUG)printf("Valeur de la borne : %.10f \n",BorneADecoder);
      for(indice=0;!(BorneADecoder>=Intervalles[BORNEINF][indice] && BorneADecoder<Intervalles[BORNESUP][indice]);indice++);
      if(DEBUG)printf("La lettre est %c \n",LettresRestantes[indice]);
      //Indice correspond à la lettre à décoder
      compteur++;
      chaine=realloc(chaine,compteur*sizeof(char));
      chaine[compteur-1]=LettresRestantes[indice];
      BorneADecoder=(BorneADecoder-Intervalles[BORNEINF][indice])/(PROBABILITE);
      getchar();
    }while(!(BorneADecoder>=Intervalles[BORNEINF][compteurDifferentes-1] && BorneADecoder<Intervalles[BORNESUP][compteurDifferentes-1]));
    compteur++;
    chaine=realloc(chaine,compteur*sizeof(char));
    chaine[compteur-1]='\n';
    return chaine;
}

/**
 * @fn float ArithCoder(char chaine[N],float ProbabilitesLettres[37],float *Intervalles[2],char *LettresRestantes,int *compteur)
 * @brief La fonction applique le codage arithmétique sur une chaine de caractères passée en paramètre.
 * @param chaine[N] le tableau des caractères à coder.
 * @param ProbabilitesLettres[37] le tableau des probabilités.
 * @param LettresRestantes tableau contenant les lettres, en 1 seul exemplaire, présentes dans la chaine .
 * @param compteur Le nombre de lettres différentes.
 */
float ArithCoder(char chaine[N],float ProbabilitesLettres[37],float *Intervalles[2],char *LettresRestantes,int *compteur)
{
  *compteur = ChaineTraiter(chaine,ProbabilitesLettres,Intervalles,LettresRestantes);
  int indice=0;
  float BorneInf=0,BorneSup=1;
  //On code même la balise
  for(int i=0;chaine[i-1]!=BALISE;i++)
  {
    for(indice=0;LettresRestantes[indice]!=chaine[i];indice++);
    if(DEBUG)printf("Itération n°%d : %.10f et %.10f [%f;%f]\n",i,BorneInf,BorneSup,Intervalles[BORNEINF][indice],Intervalles[BORNESUP][indice]);
    //indice correspond à l'indice de la lettre i (chaine) dans le tableau des intervalles
    AppliqueArith(Intervalles[BORNEINF][indice],Intervalles[BORNESUP][indice],&BorneInf,&BorneSup);
  }
  return BorneInf;
}
