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
#include <stdlib.h>
#include <stdio.h>


/* Création des Constantes */
#define NB_DE_PAS 1
#define NB_DE_TOUR_DISPARU_RESTANT 0
#define PEUT_SE_DEPLACER 1
#define STATUT 1

struct _personnage {
    int type; /* 0 pour monstre et 1 ou 2 pour membre d'école*/
    int statut; /* 0 si mort, 1 si en vie, -1 si disparu, 3 si FISA */
    int id; /* entier compris entre 1 et 5 pour les membres d'école, permettant de les identifier plus facilement */ 
    int zone_courante; /* numéro de la zone courante du personnage*/
    int zone_precedente; /* numéro de la zone précédente */
    int nb_de_pas; /* nombre de pas par tour, initialisé à 1 */
    int tours_restants_bonus_pas; /* nombre de tours restants pour le bonus de pas, initialisé à 0, vaut n positif si bonus temporaire, et -1 si bonus permanent */
    int peut_se_deplacer; /* 1 si peut se déplacer ce tour, 0 sinon */
    int nb_de_tour_disparu_restant; /* vaut 0 initialement */
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

/**
 * @brief renvoie le type du personnage
 * 
 * @param p un personnage dont on souhaite obtenir le type
 * @return le type du personnage, -1 en cas d'erreur
 */
int getType(personnage p);

/**
 * @brief renvoie l'id du personnage
 * 
 * @param p un personnage dont on souhaite obtenir l'id
 * @return l'id du personnage, -1 en cas d'erreur
 */
int getIdPersonnage(personnage p);

/**
 * @brief renvoie le statut du personnage
 * 
 * @param p un personnage dont on souhaite obtenir le statut
 * @return le statut du personnage, -1 en cas d'erreur
 */
int getStatut(personnage p);

/**
 * @brief renvoie la zone courante du personnage p
 * 
 * @param p 
 * @return int correspondant au numéro de la zone courante du personnage p
 */
int getZoneCourante(personnage p);

/**
 * @brief renvoie la zone précédente du personnage p
 * 
 * @param p 
 * @return int correspondant au numéro de la zone précédente du personnage p
 */
int getZonePrecedente(personnage p);

/**
 * @brief renvoie le nombre de pas restant du personnage
 * 
 * @param p un personnage dont on souhaite obtenir le nombre de pas restant
 * @return le nombre de pas restant du personnage, -1 en cas d'erreur
 */
int getNbPas(personnage p);

/**
 * @brief renvoie le nombre de tour restant avant que le personnage ne réapparaisse
 * 
 * @param p un personnage dont on souhaite obtenir le nombre de tour restant avant que le personnage ne réapparaisse
 * @return le nombre de tour restant avant que le personnage ne réapparaisse, -1 en cas d'erreur
 */
int getNbTourDisparuRestant(personnage p);

/**
 * @brief renvoie le booléen permettant de savoir si le personnage peut jouer ou non
 * 
 * @param p un personnage dont on souhaite savoir si il peut jouer ou non
 * @return le booléen permettant de savoir si le personnage peut jouer ou non, -1 en cas d'erreur
 */
int getPeutSeDeplacer(personnage p);

/**
 * @brief modifie le type du personnage
 * 
 * @param p un personnage dont on souhaite modifier le type
 * @param type le nouveau type du personnage
 */
void setType(personnage p, int type);

/**
 * @brief modifie l'id du personnage
 * 
 * @param p un personnage dont on souhaite modifier l'id
 * @param id le nouveau id du personnage
 */
void setIdPersonnage(personnage p, int id);

/**
 * @brief modifie le statut du personnage
 * 
 * @param p un personnage dont on souhaite modifier le statut
 * @param statut le nouveau statut du personnage : 0 si mort, 1 si en vie, -1 si disparu, 2 si peut jouer 2 fois, 3 si FISA
 */
void setStatut(personnage p, int statut);

/**
 * @brief modifie la zone courante du personnage
 * 
 * @param p un personnage dont on souhaite modifier la zone courante
 * @param zoneCourante la nouvelle zone courante du personnage, compris entre 0 et nb_zones-1
 */
void setZoneCourante(personnage p, int zoneCourante);

/**
 * @brief modifie la zone précédente du personnage
 * 
 * @param p 
 * @param zonePrecedente la nouvelle zone précédente du personnage, compris entre 0 et nb_zones-1
 */
void setZonePrecedente(personnage p, int zonePrecedente);

/**
 * @brief modifie le nombre de pas restant du personnage
 * 
 * @param p un personnage dont on souhaite modifier le nombre de pas restant
 * @param nbPasRestant le nouveau nombre de pas restant du personnage
 */
void setDeNbPas(personnage p, int nbDePas);

/**
 * @brief modifie le nombre de tour restant avant que le personnage ne réapparaisse
 * 
 * @param p un personnage dont on souhaite modifier le nombre de tour restant avant que le personnage ne réapparaisse
 * @param nbTourDisparu le nouveau nombre de tour restant avant que le personnage ne réapparaisse
 */
void setNbDeTourDisparuRestant(personnage p, int nbTourDisparu);

/**
 * @brief modifie le booléen permettant de savoir si le personnage peut jouer ou non
 * 
 * @param p un personnage dont on souhaite modifier le booléen permettant de savoir si le personnage peut jouer ou non
 * @param peutJouer le nouveau booléen permettant de savoir si le personnage peut jouer ou non
 */
void setPeutSeDeplacer(personnage p, int peutSeDeplacer);

/**
 * @brief renvoie le nombre de tours restant avant que le bonus de pas ne disparaisse
 * 
 * @param p un personnage dont on souhaite obtenir le nombre de tours restant avant que le bonus de pas ne disparaisse
 * @return le nombre de tours restant avant que le bonus de pas ne disparaisse, -1 si bonus permananent
 */
int getToursRestantsBonusPas(personnage p);

/**
 * @brief modifie le nombre de tours restant avant que le bonus de pas ne disparaisse
 * 
 * @param p un personnage dont on souhaite modifier le nombre de tours restant avant que le bonus de pas ne disparaisse
 * @param toursRestantsBonusPas le nouveau nombre de tours restant avant que le bonus de pas ne disparaisse, -1 si bonus permanent
 */
void setToursRestantsBonusPas(personnage p, int toursRestantsBonusPas);

#endif
