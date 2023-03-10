/**
 * @file personnages.h
 * @author Noah Kwa Moutome
 * @brief interface des personnages
 * @date 2023-03-10
 * 
 * @necessities zones.h 
 * 
 */
#ifndef PERSONNAGES_H
#define PERSONNAGES_H

#include "zones.h"

struct _personnage {
    int type; /* 0 pour monstre et 1 ou 2 pour membre d'école*/
    int statut; /* 0 si mort, 1 si en vie */
    zone zone_courante; /* zone courante sur laquelle se trouve le personnage*/
    int nb_de_pas_restant; /* nombre de pas restant, initialisé à 1 à chaque tour */
};
typedef struct _personnage personnage;

/**
 * @brief renvoie un pointeur vers un personnages de type:
            - monstre si n = 0
            - membre d'école de joueuse 1 si n = 1
            - membre d'école de jouese 2 si n = 2,
          le place sur la zone z passée en argument
          et initialise son statut sur vivant (ie 1)
 * 
 * @param n le type de personnage
 * @param z le numéro de la zone
 * @return personnage* un pointeur vers le personnage crée 
 */
personnage* nouveauPersonnage(int n, zone z);

/**
 * @brief libère l'espace occupé par la case mémoire pointée par pp 
 * 
 * @param pp pointeur vers la case mémoire occupée par le personnage que l'on souhaite libérer 
 */
void liberePersonnage(personnage* pp);


/**
 * @brief déplace le personnage pointé sur la zone z
 * 
 * @param pp est un pointeur vers la case mémoire du personnage qui se déplace
 * @param z est la zone d'arrivée
 */
void deplacer(personnage* pp, zone z);


/**
 * @brief renvoie la zone dans laquelle se trouve le personnage
 * 
 * @param pp un personnage dont on souhaite obtenir la zone
 * @return la zone du personnage
 */
zone zonePersonnage(personnage p);


/**
 * @brief met à jour le statut du personnage pointé par pp
 * 
 * @param pp un pointeur vers le personnage qui a été mangé
 */
void estMange(personnage* pp);

#endif