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
    int statut; /* 0 si mort, 1 si en vie, -1 si disparu, 2 si peut jouer 2 fois, 3 si FISA */
    int id; /* entier compris entre 1 et 5 pour les membres d'école, permettant de les identifier plus facilement */ 
    int zone_courante; /* numéro de la zone courante du personnage*/
    int zone_precedente; /* numéro de la zone précédente */
    int nb_de_pas_restant; /* nombre de pas restant, initialisé à 1 à chaque tour sauf cas particuliers */
    int peut_jouer; /* 1 si peut jouer ce tour, 0 sinon */
    int nb_de_tour_disparu; /* vaut 0 initialement */

};
typedef struct _personnage* personnage;

/**
 * @brief renvoie un personnages de type:
            - monstre si n = 0
            - membre d'école de joueuse 1 si n = 1
            - membre d'école de jouese 2 si n = 2,
          le place sur la zone z passée en argument
          et initialise son statut sur vivant (ie 1)
 * 
 * @param n le type de personnage
 * @param z le numéro de la zone
 * @return personnage un pointeur vers le personnage crée 
 */
personnage nouveauPersonnage(int n, zone z);

/**
 * @brief libère l'espace occupé par la case mémoire pointée par p 
 * 
 * @param p un personnage que l'on souhaite libérer 
 */
void liberePersonnage(personnage p);


/**
 * @brief déplace le personnage sur la zone z
 * 
 * @param p est un personnage qui se déplace
 * @param z est la zone d'arrivée
 */
void deplacer(personnage p, zone z);


/**
 * @brief renvoie le numéro de la zone dans laquelle se trouve le personnage
 * 
 * @param p un personnage dont on souhaite obtenir la zone
 * @return le numéro de la zone du personnage, -1 en cas d'erreur
 */
int zonePersonnage(personnage p);


/**
 * @brief met à jour le statut du personnage p
 * 
 * @param p le personnage qui a été mangé
 */
void estMange(personnage p);

/* ---------------------------------------------------------------------------- */
/* Getters and Setters */

/* code les getter des paramètres du struct personnage */

#endif