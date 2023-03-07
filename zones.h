struct zones{
    int tab_zones[10]; /* la case i représente la zone i */
    float tab_proba[10]; /* la case i contient la proba d'aller sur la case i */
};
typedef struct zones zones;

struct zone;
typedef struct zone zone;

/*
@requires: nothing
@assigns: nothing
@ensures: renvoie un pointeur vers l'ensemble des zones du jeu
*/
zones* newZones();

/*
@requires: une adresse vers un ensemble de zone valide pz
@assigns: la case mémoire pointée par pz
@ensures: libère toutes les zones du jeu
*/
void freeZones(zones* pz);

/*
@requires: un entier n compris entre 0 et 9
@assigns: nothing
@ensures: renvoie un pointeur vers la zone numéro n
*/
zone* getZone(int n);

/*
@requires: une adresse vers un ensemble de zones valide pz
@assigns: les cases mémoires de tab_proba de la case pointée par pz
@ensures: met à jour le tableau en fonction de l'argument action passé en paramètre (voir joueuse.h)
*/
void applyDecisions(zones* pz /* insérer une action en paramètre ici*/);

/*
@requires: un entier n compris entre 0 et 9
@assigns: nothing
@ensures: renvoie un pointeur vers la zone successeur de la zone numéro n en fonction des proba présentent dans ens_zone
*/
zone* nextZone(zones ens_zones, int n);