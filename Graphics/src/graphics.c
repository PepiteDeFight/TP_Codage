/**
 * @file graphics.c
 * @brief Réalisation des fonctions de graphismes pour l'interface graphique SDL
 * @author Meunier, Lemoult, Morisseau || L3 informatique Le mans
 * @version 1.0
 * @date Decembre 2021
 */
#include "include/graphics.h"


int rectPersonnages[5][4]=
{
  //X,L,Y,H
  {257,405,200,1286},{860,607,200,1286},{1558,474,200,1286},{2299,416,200,1286},{2929,446,200,1286}
};

SDL_Color couleurNoire={0,0,0};

/*
 * @fn void coordPoint(int *x, int *y,float angle,int centre, int rayon)
 * @brief La fonction renvoie les coordonnées d'un point sur le cercle de centre passé en paramètres, de rayon passé en paramètres et de l'angle également passé en paramètres
 *
 * @param x La coordonnée x
 * @param y La coordonnée y
 * @param angle l'angle du point par rapport au centre
 * @param centre les coordonnées du centre du cercle
 * @param rayon le rayon du cercle
 */
void coordPoint(int *x, int *y,float angle,int centre, int rayon)
{
  angle*=0.0174533;//conversion en radians
  *x=centre+rayon*cos(angle);
  *y=centre+rayon*sin(angle);
}

/*
 * @fn void drawMessage(SDL_Renderer *rendu, int *Message)
 * @brief La fonction affiche un personnage aléatoire avec un message passé en paramètres
 *
 * @param rendu Le rendu de la fenêtre
 * @param Message Le message (suite de 0 ou de 1).
 */
void drawMessage(SDL_Renderer *rendu, int *Message)
{
  static int angle=0;
  angle+=360/nb_utilisateur;
  angle%=360;
  char text[taille_message+1];
  for(int i=0;i<taille_message;i++)
  {
    if(Message[i]==1)text[i]='1';
    else text[i]='0';
  }
  text[taille_message]=0;
  if(Message==NULL)perror("Erreur drawMessage --> Message null");
  TTF_Font *police=TTF_OpenFont(POLICE_DESTINATION,80);
  SDL_Surface *texte=TTF_RenderText_Solid(police,text,couleurNoire);
  SDL_Surface *personnages=IMG_Load(PERSONNAGES_DESTINATION);
  if(personnages==NULL)perror("Erreur images personnages --> non existante");
  SDL_Texture *texture=SDL_CreateTextureFromSurface(rendu,personnages);
  SDL_Rect SourceRect, DestRect;



  int rand=(RandGenerer()%5);//on choisi un personnage aléatoirement
  //on recupère les coordonnées du personnage n (position) dans la texture avec tous les personnages
  SourceRect.x=rectPersonnages[rand][X];
  SourceRect.y=rectPersonnages[rand][Y];
  SourceRect.w=rectPersonnages[rand][L];
  SourceRect.h=rectPersonnages[rand][H];
  //on calcul la position, sur la fenêtre, du personnage n
  coordPoint(&DestRect.x,&DestRect.y,angle,300,250);
  DestRect.x-=40;
  DestRect.y-=75;
  DestRect.h=150;
  DestRect.w=80;
  SDL_RenderCopy(rendu,texture,&SourceRect,&DestRect);
  SDL_Texture *texture2=SDL_CreateTextureFromSurface(rendu,texte);
  coordPoint(&DestRect.x,&DestRect.y,angle,250,100);
  DestRect.h=25;
  DestRect.w=100;
  SDL_RenderCopyEx(rendu,texture2,NULL,&DestRect,angle,NULL,SDL_FLIP_NONE);
  SDL_RenderPresent(rendu);
  SDL_Delay((int)(5000/nb_utilisateur));

  SDL_FreeSurface(personnages);
  SDL_DestroyTexture(texture);
  TTF_CloseFont(police);
  SDL_FreeSurface(texte);
  SDL_DestroyTexture(texture2);
}

/*
 * @fn void reduire(SDL_Renderer *rendu)
 * @brief La fonction affiche une image "package" et la fait réduire donnant l'illusion d'une compression
 *
 * @param rendu Le rendu de la fenêtre
 */
void reduire(SDL_Renderer *rendu)
{
  SDL_Rect dest={0,0,600,600};
  SDL_Surface *surface=IMG_Load(PACKAGE_DESTINATION);
  SDL_Texture *text=SDL_CreateTextureFromSurface(rendu,surface);
  SDL_SetRenderDrawColor(rendu,FOND_R,FOND_G,FOND_B,0);
  for(int i=10;i>0;i--)
  {
    SDL_RenderFillRect(rendu,NULL);
    dest.x=dest.y=(10-i)*30;
    dest.h=dest.w=60*i;
    SDL_RenderCopy(rendu,text,NULL,&dest);
    SDL_RenderPresent(rendu);
    SDL_Delay(400);
  }
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(text);
}

/*
 * @fn void grandir(SDL_Renderer *rendu)
 * @brief La fonction inverse de reduire.
 *
 * @param rendu Le rendu de la fenêtre
 */
void grandir(SDL_Renderer *rendu)
{
  SDL_Rect dest={0,0,600,600};
  SDL_Surface *surface=IMG_Load(PACKAGE_DESTINATION);
  SDL_Texture *text=SDL_CreateTextureFromSurface(rendu,surface);
  for(int i=0;i<10;i++)
  {
    SDL_RenderClear(rendu);
    SDL_SetRenderDrawColor(rendu,FOND_R,FOND_G,FOND_B,0);
    dest.x=dest.y=(10-i)*30;
    dest.h=dest.w=60*i;
    SDL_RenderCopy(rendu,text,NULL,&dest);
    SDL_RenderPresent(rendu);
    SDL_Delay(400);
  }
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(text);
}

/*
 * @fn void envoyer(SDL_Renderer *rendu,int qui)
 * @brief La fonction affiche l'image compressée (voir reduire()) du centre vers la gauche donnant l'illusion d'un déplacement/transfert.
 *
 * @param rendu Le rendu de la fenêtre.
 * @param qui L'appelant de la fonction.
 */
void envoyer(SDL_Renderer *rendu,int qui)
{
  SDL_Surface *surface=IMG_Load(PACKAGE_DESTINATION);
  SDL_Texture *text=SDL_CreateTextureFromSurface(rendu,surface);
  TTF_Font *police=TTF_OpenFont(POLICE_DESTINATION,TAILLE_POLICE);
  SDL_Surface *texte;
  SDL_Texture *texteFinal;
  SDL_Rect destTexte={200,100,200,50};
  //l'image centrale fait à la fin x=270,y=270,w=60,h=60
  SDL_Rect destimg={270,270,60,60};
  switch(qui)
  {
    case EMETTEUR : texte=TTF_RenderText_Blended(police,"Emetteur",couleurNoire);break;
    case CANAL : texte=TTF_RenderText_Blended(police,"Canal",couleurNoire);break;
    default : texte=TTF_RenderText_Blended(police,"",couleurNoire);break;
  }
  texteFinal=SDL_CreateTextureFromSurface(rendu,texte);
  for(int i=0;i<=11;i++)
  {
    SDL_RenderClear(rendu);
    SDL_SetRenderDrawColor(rendu,FOND_R,FOND_G,FOND_B,0);
    destimg.x-=27;
    SDL_RenderCopy(rendu,text,NULL,&destimg);
    SDL_RenderCopy(rendu,texteFinal,NULL,&destTexte);
    SDL_RenderPresent(rendu);
    SDL_Delay(200);
  }

  SDL_FreeSurface(surface);
  SDL_DestroyTexture(text);
  SDL_DestroyTexture(texteFinal);
  SDL_FreeSurface(texte);
  TTF_CloseFont(police);
}

/*
 * @fn void recevoir(SDL_Renderer *rendu,int qui)
 * @brief La fonction fait l'inverse de la fonction envoyer.
 *
 * @param rendu Le rendu de la fenêtre.
 * @param qui L'appelant de la fonction.
 */
void recevoir(SDL_Renderer *rendu,int qui)
{
  SDL_Surface *surface=IMG_Load(PACKAGE_DESTINATION);
  SDL_Texture *text=SDL_CreateTextureFromSurface(rendu,surface);
  TTF_Font *police=TTF_OpenFont(POLICE_DESTINATION,TAILLE_POLICE);
  SDL_Surface *texte;
  SDL_Texture *texteFinal;
  SDL_Rect destTexte={200,100,200,50};
  //l'image centrale fait à la fin x=270,y=270,w=60,h=60
  SDL_Rect destimg={600,270,60,60};
  switch(qui)
  {
    case EMETTEUR : texte=TTF_RenderText_Blended(police,"Emetteur",couleurNoire);break;
    case CANAL : texte=TTF_RenderText_Blended(police,"Canal",couleurNoire);break;
    case RECEPTEUR : texte=TTF_RenderText_Blended(police,"Recepteur",couleurNoire);break;
    default : texte=TTF_RenderText_Blended(police,"",couleurNoire);break;
  }
  texteFinal=SDL_CreateTextureFromSurface(rendu,texte);
  for(int i=0;i<=11;i++)
  {
    SDL_RenderClear(rendu);
    SDL_SetRenderDrawColor(rendu,FOND_R,FOND_G,FOND_B,0);
    destimg.x-=27;
    SDL_RenderCopy(rendu,text,NULL,&destimg);
    SDL_RenderCopy(rendu,texteFinal,NULL,&destTexte);
    SDL_RenderPresent(rendu);
    SDL_Delay(200);
  }
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(text);
  SDL_DestroyTexture(texteFinal);
  SDL_FreeSurface(texte);
  TTF_CloseFont(police);
}

/*
 * @fn void changerCouleur(SDL_Renderer *rendu,int val)
 * @brief La fonction change la couleur en fonction de la valeur passée en paramètres.
 *
 * @param rendu Le rendu de la fenêtre.
 * @param val La valeur déterminante.
 */
void changerCouleur(SDL_Renderer *rendu,int val)
{
    val*=FILTRE;//application d'un filtre pour "grossir" la valeur du signal
    val=(val+125)%255;
    SDL_SetRenderDrawColor(rendu,val,val,val,0);
}



/*
 * @fn int valeur(int x,int y,int tcase,int caseMax)
 * @brief La fonction renvoie les coordonnées du tableau signal en fonction de l'endroit où on a appuyer sur la fenêtre.
 *
 * @param x La coordonnées x d'évenement appuyer.
 * @param y La coordonnées y d'évenement appuyer.
 * @param tcase La taille d'une case de l'affichage du signal.
 * @param caseMax Le nombre de case maximum par ligne, c'est également le nombre de colonnes.
 * @return La nième case du tableau signal
 */
int valeur(int x,int y,int tcase,int caseMax)
{
  //on sait que on commence en 100 100
  //offset
  x-=100;
  y-=100;
  int compteurx=0,compteury=0;
  for(compteurx=0,compteury=0;x>tcase || y>tcase;)
  {
    if(x>tcase)
    {
      compteurx++;
      x-=tcase;
    }
    if(y>tcase)
    {
      compteury++;
      y-=tcase;
    }
  }
  if((caseMax*compteury+compteurx)>=SignalSize())return -1;
  return caseMax*compteury+compteurx;
}


/*
 * @fn void bruiter(SDL_Renderer *rendu, int *signal)
 * @brief La fonction permet de graphiquement rajouter du bruit au signal depuis le canal.
 *
 * @param rendu Le rendu de la fenêtre.
 * @param signal Le signal à transmetre.
 */
void bruiter(SDL_Renderer *rendu, int *signal)
{
  SDL_Surface *fond=IMG_Load(FOND_DESTINATION);
  SDL_Texture *text=SDL_CreateTextureFromSurface(rendu,fond);
  SDL_RenderCopy(rendu,text,NULL,NULL);
  SDL_RenderPresent(rendu);
  SDL_FreeSurface(fond);
  int longueur=0,hauteur=0;
  SDL_Rect TableauMax={95,95,410,410};
  SDL_SetRenderDrawColor(rendu,0,0,0,0);
  int max=SignalSize();
  TableauMax.h=(int)(400/NB_COLONNES);
  TableauMax.w=TableauMax.h;
  TableauMax.x=100;
  TableauMax.y=100;
  for(hauteur=0;hauteur<sqrt(max) && hauteur*NB_COLONNES<max;hauteur++)
  {
    for(longueur=0;longueur<NB_COLONNES && (hauteur*NB_COLONNES+longueur)<max;longueur++)
    {
      changerCouleur(rendu,signal[(int)(hauteur*(sqrt(max))+longueur)]);
      SDL_RenderFillRect(rendu,&TableauMax);
      SDL_SetRenderDrawColor(rendu,0,0,0,0);
      SDL_RenderDrawRect(rendu,&TableauMax);

      TableauMax.x+=TableauMax.w;
    }
    TableauMax.x=100;
    TableauMax.y+=TableauMax.h;
  }
  SDL_RenderPresent(rendu);
  int val,compteur;
  SDL_Event event;
  SDL_bool continuer=SDL_TRUE;
  while(continuer)
  {
    while(SDL_PollEvent(&event))
      switch(event.type)
      {
        case SDL_QUIT:
          continuer=SDL_FALSE;
        case SDL_MOUSEBUTTONDOWN:
          if(event.button.x >100 && event.button.y >100 && event.button.x<100+NB_COLONNES*TAILLE_CASE && event.button.y<100+NB_LIGNES*TAILLE_CASE)
          {
            switch(event.button.button)
            {
              case SDL_BUTTON_LEFT://diminuer le signal
                  val=valeur(event.button.x,event.button.y,TAILLE_CASE,NB_COLONNES);
                  if(val>=0)signal[val]-=5;

                break;
                case SDL_BUTTON_RIGHT://augmenter le signal
                val=valeur(event.button.x,event.button.y,TAILLE_CASE,NB_COLONNES);
                if(val>=0)signal[val]+=5;
                break;
            }
            if(val<0)break;
            compteur=0;
            changerCouleur(rendu,signal[val]);
            TableauMax.x=100+((val%NB_COLONNES))*TAILLE_CASE;
            while(val>=NB_COLONNES){val-=NB_COLONNES;compteur++;}
            TableauMax.y=100+compteur*TAILLE_CASE;


            SDL_RenderFillRect(rendu,&TableauMax);
            SDL_SetRenderDrawColor(rendu,0,0,0,0);
            SDL_RenderDrawRect(rendu,&TableauMax);
            SDL_RenderPresent(rendu);
          }
          break;

        case SDL_KEYDOWN:
          if(event.key.keysym.sym == SDLK_RETURN)continuer=SDL_FALSE;
          break;
      }
  }
  SDL_DestroyTexture(text);
}
