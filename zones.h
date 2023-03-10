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
    float proba; /* proba de se déplacer vers cette zone */
};
typedef struct _zone zone;

struct _zones{
    /* 11 zones car la carte "Lucienne Pacave" ajoute une 11e zone au jeu*/
    zone tab_zones[11]; /* la case i représente la zone i */
};
typedef struct _zones zones;


/**
 * @brief créer les 11 zones du jeu, avec une proba de 0 pour la 11e
 *        et 0.1 pour chacune des autres
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
 * @param n numéro de la zone
 * @return zone* pointeur vers la zone de numéro n
 */
zone* trouveZone(int n);


/**
 * @brief modifie la probabilité de la zone en fonction du capital investi
 *        proba est augmenté/diminué de 0.1 par capital investi
 * @param n numéro de la zone
 * @param capital capital investi
 * @param action indique si on augmente (action = 1) ou retire (action = 0) de la probabilité
 */
void modifierZone(int n, int capital, int action);


/**
 * @brief renvoie la prochaine zone
 * 
 * @param ens_zones 
 * @return la prochaine zone
 */
zone prochaineZone(zones ens_zones);

#endif