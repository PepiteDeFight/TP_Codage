

# Bienvenue !

Voici le README permettant de comprendre ce qu'est ce projet. Ce projet se décompose en plusieurs parties avec des fichiers de tests, un readme, un fichier shell pour exécuter correctement le programme et un makefile. Pour rappel l'objectif de ce TP est de simuler de la 3G à travers 3 entités qui sont l'**Emetteur**, le **Canal** et le **Récepteur**. L'Emetteur est une entité qui gère plusieurs utilisateurs, canal sert d'intermédiaire pour ajouter un bruit et récepteur permet de décoder les messages reçus.


## Fichier

L'ensemble des fichiers sources sont disponibles dans le fichier src à la racine du projet.
Lorsque vous compiler (cf Création) vous obtiendrez 2 nouveaux fichiers qui sont ./bin et ./obj .
Ils contiennent les exécutables et les objets de compilation.

![Organisation des fichiers](img/Organisation.png?raw=true "Title")


# Création des différents modules

## Création des exécutables

Pour générer les exécutables, il vous suffit de taper la commande suivante :

    make all

## Création des tests
Pour générer les tests il vous suffit de taper la commande suivante :

    make tests

## Création des exécutables graphiques
Pour générer les exécutables graphiques, il vous suffit de taper la commande suivante :

    make graphics

 Vous pouvez aussi vous déplacer dans le dossier Graphics et faire un :

    make all

Il est important d'avoir sur sa machine la SDL (pour linux) :

    make install_SDL

## Générer la documentation (Doxygen)

Pour visualiser de façon clair, une documentation Doxygen peut être générer via :

    make docs


## Makefile

Pour plus d'informations quant aux commandes disponible :

    make infos

## Supprimer les fichiers

Vous pouvez supprimer les fichiers pour recompiler par exemple :

    make clean

## Les droits

Pour exécuter le programme schell il faut les droits nécessaires :

    make right

# Exécuter

## Lancer la simulation
Après avoir générer les exécutables, vous pouvez démarrer la simulation en tapant la commande :

    ./lancerSimulation.sh

## Lancer la simulation graphiquement
Après avoir générer les exécutables graphiques, vous pouvez démarrer la simulation en déplaçant votre répertoire courant dans Graphics et en tapant la commande :

    ./lancerSimulation.sh

## Tester les programmes
Après avoir générer les tests, vous pouvez tester les différentes fonctions réaliser dans ce projet, ils se situent ici :

    ./bin/tests/
   Vous pouvez ensuite choisir quel(s) fichier(s) vous souhaitez tester.



 - [Hadamard](test___hadamard_8c.html)
 - [Encodage Décodage avec Hadamard](test___encodage_8c.html)
 - [Générateur de JPL et GOLD](test___generateur_8c.html)
 - [Codage HDBn et Arithmétique](test___h_d_bn_ari_8c.html)
 - [Générateur de nombre pseudo-aléatoires](test___random_8c.html)
 - Réseau [Client](test___r_xC3_xA9seau___client_8c.html) et [Serveur](test___r_xC3_xA9seau___serveur_8c.html)

# Divers

-   Makefile intégré
-   Développé en C
-   Documentation Doxygen
-   Version avec SDL

> “Le binaire, c'est deux états.” F.Carlier


# Licence
Tous les fichiers de PDF sont sous aucune licence, les images, fichiers sources peuvent être modifiés mais auquel cas nous ne garantissons pas l'exécution correcte. Nous réservons aucun droits sur le projet vous pouvez le modifier comme bon vous semble.

**Créer, partager et surtout coder !**
