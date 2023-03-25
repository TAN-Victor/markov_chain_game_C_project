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

struct _zone {
    int numero; /* numéro de la zone */
    float* probas; /* tableau des proba de se déplacer vers chaque zone du jeu*/
};
typedef struct _zone zone;

struct _zones{
    zone* tab_zones; /* tableau des zones, de taille nb_zones */
    int nb_zones; /* nombre de zones */
};
typedef struct _zones zones;


/**
 * @brief initialise nb_zones à 10 et créer les zones du jeu 
 * 
 * @return renvoie un pointeur vers l'ensemble des zones du jeu 
 */
zones* nouvellesZones();


/**
 * @brief libère toutes les zones du jeu
 * 
 * @param pz une adresse vers un ensemble de zones valide
 */
void libereZones(zones* pz);


/**
 * @brief renvoie un pointeur vers la zone dont le numéro est n
 * 
 * @param n numéro de la zone compris entre 0 et nb_zones-1
 * @return zone* pointeur vers la zone de numéro n
 */
zone* trouveZone(int n);


/**
 * @brief modifie la probabilité de la zone en fonction du capital investi
 *        proba est augmenté/diminué de 0.1 par capital investi
 * @param n1 numéro de la zone de départ compris entre 0 et nb_zones-1
 * @param n2 numéro de la zone d'arrivée compris entre 0 et nb_zones-1
 * @param capital capital investi <= au capital de la joueuse 
 * @param action indique si on augmente (action = 1) ou retire (action = 0) de la probabilité
 */
void modifierZone(int n1, int n2, int capital, int action);


/**
 * @brief renvoie le numéro de la prochaine zone
 * 
 * @param nz numéro de la zone actuelle compris entre 
 * @return le numéro de la prochaine zone, -1 en cas d'erreur 
 */
int prochaineZone(int nz);

#endif