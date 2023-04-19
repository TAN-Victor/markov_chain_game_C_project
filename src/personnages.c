#include "../headers/personnages.h"

/**
 * @brief renvoie le type du personnage
 * 
 * @param p un personnage dont on souhaite obtenir le type
 * @return le type du personnage, -1 en cas d'erreur
 */
int getType(personnage p){
    return p->type;
}

/**
 * @brief renvoie l'id du personnage
 * 
 * @param p un personnage dont on souhaite obtenir l'id
 * @return l'id du personnage, -1 en cas d'erreur
 */
int getIdPersonnage(personnage p){
    return p->id;
}

/**
 * @brief renvoie le statut du personnage
 * 
 * @param p un personnage dont on souhaite obtenir le statut
 * @return le statut du personnage, -1 en cas d'erreur
 */
int getStatut(personnage p){
    return p->statut;
}

/**
 * @brief renvoie la zone courante du personnage p
 * 
 * @param p 
 * @return int correspondant au numéro de la zone courante du personnage p
 */
int getZoneCourante(personnage p){
    return p->zone_courante;
}

/**
 * @brief renvoie la zone précédente du personnage p
 * 
 * @param p 
 * @return int correspondant au numéro de la zone précédente du personnage p
 */
int getZonePrecedente(personnage p){
    return p->zone_precedente;
}

/**
 * @brief renvoie le nombre de pas restant du personnage
 * 
 * @param p un personnage dont on souhaite obtenir le nombre de pas restant
 * @return le nombre de pas restant du personnage, -1 en cas d'erreur
 */
int getNbPas(personnage p){
    return p->nb_de_pas;
}

/**
 * @brief renvoie le nombre de tour restant avant que le personnage ne réapparaisse
 * 
 * @param p un personnage dont on souhaite obtenir le nombre de tour restant avant que le personnage ne réapparaisse
 * @return le nombre de tour restant avant que le personnage ne réapparaisse, -1 en cas d'erreur
 */
int getNbTourDisparuRestant(personnage p){
    return p->nb_de_tour_disparu_restant;
}

/**
 * @brief renvoie le booléen permettant de savoir si le personnage peut se déplacer ou non
 * 
 * @param p un personnage dont on souhaite savoir si il peut se déplacer ou non
 * @return le booléen permettant de savoir si le personnage peut se déplacer ou non, -1 en cas d'erreur
 */
int getPeutSeDeplacer(personnage p){
    return p->peut_se_deplacer;
}

/**
 * @brief modifie le type du personnage
 * 
 * @param p un personnage dont on souhaite modifier le type
 * @param type le nouveau type du personnage
 */
void setType(personnage p, int type){
    p->type = type;
}

/**
 * @brief modifie l'id du personnage
 * 
 * @param p un personnage dont on souhaite modifier l'id
 * @param id le nouveau id du personnage
 */
void setIdPersonnage(personnage p, int id){
    p->id = id;
}

/**
 * @brief modifie le statut du personnage
 * 
 * @param p un personnage dont on souhaite modifier le statut
 * @param statut le nouveau statut du personnage : 0 si mort, 1 si en vie, -1 si disparu, 2 si peut jouer 2 fois, 3 si FISA
 */
void setStatut(personnage p, int statut){
    p->statut = statut;
}

/**
 * @brief modifie la zone courante du personnage
 * 
 * @param p un personnage dont on souhaite modifier la zone courante
 * @param zoneCourante la nouvelle zone courante du personnage, compris entre 0 et nb_zones-1
 */
void setZoneCourante(personnage p, int zoneCourante){
    p->zone_courante = zoneCourante;
}

/**
 * @brief modifie la zone précédente du personnage
 * 
 * @param p 
 * @param zonePrecedente la nouvelle zone précédente du personnage, compris entre 0 et nb_zones-1
 */
void setZonePrecedente(personnage p, int zonePrecedente){
    p->zone_precedente = zonePrecedente;
}

/**
 * @brief modifie le nombre de pas restant du personnage
 * 
 * @param p un personnage dont on souhaite modifier le nombre de pas restant
 * @param nbPasRestant le nouveau nombre de pas restant du personnage
 */
void setDeNbPas(personnage p, int nbDePas){
    p->nb_de_pas = nbDePas;
}

/**
 * @brief modifie le nombre de tour restant avant que le personnage ne réapparaisse
 * 
 * @param p un personnage dont on souhaite modifier le nombre de tour restant avant que le personnage ne réapparaisse
 * @param nbTourDisparu le nouveau nombre de tour restant avant que le personnage ne réapparaisse
 */
void setNbDeTourDisparuRestant(personnage p, int nbTourDisparu){
    p->nb_de_tour_disparu_restant = nbTourDisparu;
}

/**
 * @brief modifie le booléen permettant de savoir si le personnage peut jouer ou non
 * 
 * @param p un personnage dont on souhaite modifier le booléen permettant de savoir si le personnage peut jouer ou non
 * @param peutJouer le nouveau booléen permettant de savoir si le personnage peut jouer ou non
 */
void setPeutSeDeplacer(personnage p, int peutSeDeplacer){
    p->peut_se_deplacer = peutSeDeplacer;
}
