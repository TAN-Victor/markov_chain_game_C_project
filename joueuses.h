#ifndef JOUEUSES_H
#define JOUEUSES_H
#include "personnages.h"
//#include "cartes.h"


typedef struct joueuse
{
    int capital;
    personnage[5] membres;
    cartes[] main_du_joueur; /*une liste contenant les cartes de la joueuse*/
    int id; /*on identifie une joueuse par un numéro unique*/
};

/*
  @requires: nothing
  @assigns: nothing
  @ensures: renvoie un pointeur vers une joueuse :
            - on initialise le capital à 5
            - on initialise les 5 membres du joueurs
            - on initialise la main_du_joueur avec 5 cartes aléatoires
            - on associe à la joeuse une clée unique (1 ou 2)-> cette clef permet de savoir qui est le joueur n°1
*/
joueuse* creation_joueuse();


/*
  @requires: j est un pointeur de 
  @assigns: j
  @ensures: libère l'espace mémoire de la joueuse j
*/
void free_joueuse(joueuse* j);


/*
  @requires:
  @assigns:
  @ensures: renvoie la clef de la joeuse dont c'est le tour
*/
int tour_joueuse();


/*
  @requires:
  @assigns:
  @ensures:
*/
personnage* membre_ecole(joueuse* j);


/*
  @requires: j est un pointeur vers une joueuse valide
  @assigns: nothing
  @ensures: renvoie le nombre de membres de la joueuse j
*/
int nb_membre_ecole(joueuse* j);


/*
  @requires:
  @assigns:
  @ensures:
*/
int tous_manges(joueuse* j);


/*
  @requires:
  @assigns:
  @ensures:
*/
void reinitialise_capital(joueuse* j);


/*
  @requires: j est un pointeur vers une joueuse valide et capital<joueuse.capital
  @assigns: j.capital
  @ensures: on retire le capital
*/
void utilise_capital(joueuse* j, int capital);

/*
  @requires: j est un pointeur vers une joueuse valide et c est carte que possède j
  @assigns: j.main_du_joueur
  @ensures: c est retirée de la main_du_joueur et on applique les effets de c
*/
void utilise_carte(joueuse* j, carte c);

#endif