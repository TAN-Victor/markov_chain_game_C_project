/*
@requires:
@assigns:
@ensures:
*/

#include "zones.h"

struct personnage {
    int type; /* 0 pour monstre et 1 ou 2 pour membre d'école*/
    int status; /* 0 si mort, 1 si en vie */
    zone current_zone; /* zone courrante sur laquelle se trouve le personnage*/
};

/*
@requires: nothing
@assigns: nothing
@ensures: renvoie un pointeur vers un personnages de type:
        - monstre si n = 0
        - membre d'école de joueuse 1 si n = 1
        - membre d'école de jouese 2 si n = 2,
    le place sur la zone z passée en argument
    et initialise son statut sur vivant (ie 1)
*/
personnage* newPersonnage(int n, zone z);

/*
@requires: une adresse vers un personnage valide pp
@assigns: la valeur de la case mémoire pointée par le pointeur passé en argument
@ensures: libère l'espace occupé par la case mémoire pointée par pp 
*/
void freePersonnage(personnage* pp);

/*
@requires: une adresse vers un personnage valide pp, une zone existante z
@assigns: la case mémoire pointée par pp
@ensures: le personnage pointé par pp se trouve maintenant sur la zone z
*/
void moveTo(personnage* pp, zone z);

/*
@requires: une adresse vers un personnage valide pp
@assigns: nothing
@ensures: renvoie la zone dans laquelle se trouve le personnage pointé par pp
*/
zone getZone(personnage* pp);

/*
@requires: une adresse vers un personnage valide pp
@assigns: la case mémoire pointée par pp
@ensures: met à jour le statut du personnage pointé par pp
*/
void gotEaten(personnage* pp);