/**
 * @file zones.h
 * @author Noah Kwa Moutome
 * @brief interface des zones
 * @date 2023-03-10
 * 
 * @necessities 
 * 
 */
#ifndef ZONE_H
#define ZONE_H

#include "structures.h"


struct _zone{
    int numero; /* numéro de la zone, compris entre 0 et NB_DE_ZONES-1 */
    int est_autorise; /* vaut 0 si tous les personnages sont autorisés, 1 si uniquement ceux de joueuse 1, 2 si ceux de joueuse 2*/
};
typedef struct _zone* zone;

struct _zones{
    zone* tab_zones; /* tableau des zones, de taille nb_zones */
    matrice_probas matrice; /* matrice des probabilités de se déplacer entre les zones */
};
typedef struct _zones* zones;


/**
 * @brief initialise nb_zones à 10 et créer les zones du jeu 
 * 
 * @return renvoie un pointeur vers l'ensemble des zones du jeu 
 */
zones nouvellesZones();


/**
 * @brief libère toutes les zones du jeu
 * 
 * @param pz une adresse vers un ensemble de zones valide
 */
void libereZones(zones pz);


/**
 * @brief renvoie un pointeur vers la zone dont le numéro est n
 * 
 * @param n numéro de la zone compris entre 0 et nb_zones-1
 * @return zone la zone numéro n
 */
zone trouveZone(zones z, int n);


/**
 * @brief modifie la probabilité de la zone en fonction du capital investi
 *        proba est augmenté/diminué de 0.1 par capital investi
 * @param n1 numéro de la zone de départ compris entre 0 et nb_zones-1
 * @param n2 numéro de la zone d'arrivée compris entre 0 et nb_zones-1
 * @param capital capital investi <= au capital de la joueuse 
 * @param action indique si on augmente (action = 1) ou retire (action = 0) de la probabilité
 */
void modifierZone(zones z, int n1, int n2, int capital, int action);


/**
 * @brief renvoie le numéro de la prochaine zone
 * 
 * @param nz numéro de la zone actuelle compris entre 
 * @return le numéro de la prochaine zone, -1 en cas d'erreur 
 */
int prochaineZone(zones z, int nz);

/* ------------------------------------------------------------------ */
/* Getters and Setters */

/**
 * @brief renvoie le numéro de la zone z
 * 
 * @param z zone 
 * @return int numéro de la zone
 */
int getNumero(zone z);

/**
 * @brief met à jour le numéro de la zone
 * 
 * @param z la zone à modifier
 * @param n le nouveau numéro
 */
void setNumero(zone z, int n);

/**
 * @brief renvoie un entier correspondant au type de joueurs autorisés sur la zone
 * 
 * @param z la zone en question
 * @return int 
 */
int getEstAutorise(zone z);

/**
 * @brief met à jour l'entier est_autorise
 * 
 * @param z la zone à modifier
 * @param n le type de perso autorisés
 */
void setEstAutorise(zone z, int n);

/**
 * @brief renvoie la liste des zones du jeu
 * 
 * @param z les zones du jeu
 * @return zone* 
 */
zone* getTabZones(zones z);

/**
 * @brief renvoie la matrice des probabilités de se déplacer entre les zones
 * 
 * @param z les zones du jeu
 * @return matrice_probas 
 */
matrice_probas getMatrice(zones z);

/**
 * @brief met à jour la matrice des probabilités de se déplacer entre les zones
 * 
 * @param z les zones du jeu
 * @param m la nouvelle matrice
 */
void setMatrice(zones z, matrice_probas m);

/**
 * @brief ajoute une zone au jeu
 * 
 * @param z les zones du jeu
 */
void addZone(zones z);

#endif
