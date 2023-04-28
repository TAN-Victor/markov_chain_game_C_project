#include "../headers/personnages.h"

/* Getters et Setters */
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

/**
 * @brief renvoie le nombre de tours restant avant que le bonus de pas ne disparaisse
 * 
 * @param p un personnage dont on souhaite obtenir le nombre de tours restant avant que le bonus de pas ne disparaisse
 * @return le nombre de tours restant avant que le bonus de pas ne disparaisse, -1 si bonus permananent
 */
int getToursRestantsBonusPas(personnage p){
    return p->tours_restants_bonus_pas;
}

/**
 * @brief modifie le nombre de tours restant avant que le bonus de pas ne disparaisse
 * 
 * @param p un personnage dont on souhaite modifier le nombre de tours restant avant que le bonus de pas ne disparaisse
 * @param toursRestantsBonusPas le nouveau nombre de tours restant avant que le bonus de pas ne disparaisse, -1 si bonus permanent
 */
void setToursRestantsBonusPas(personnage p, int toursRestantsBonusPas){
    p->tours_restants_bonus_pas = toursRestantsBonusPas;
}

/**
 * @brief renvoie un personnages de type:
            - monstre si n = 0
            - membre d'école de joueuse 1 si n = 1
            - membre d'école de jouese 2 si n = 2,
          le place sur la zone z passée en argument
          et initialise son statut sur vivant (ie 1)
 * @author Adam Ouzegdouh
 * @param n le type de personnage
 * @param id_to_put l'id à mettre qui sera généré aléatoirement, vaut 0 si le personnage est un monstre
 * @param nz le numéro de la zone
 * @return personnage un pointeur vers le personnage crée 
 */
personnage nouveauPersonnage(int n, int id_to_put, int nz){
    personnage perso=malloc(sizeof(struct _personnage));
    setType(perso,n);
    setStatut(perso,1); // 1 car vivant
    setIdPersonnage(perso,id_to_put); // id du personnage
    setZoneCourante(perso,nz);
    setZonePrecedente(perso,-1); // -1 car vient d'être créé
    setDeNbPas(perso,1);
    setToursRestantsBonusPas(perso,0);
    setPeutSeDeplacer(perso,1);
    setNbDeTourDisparuRestant(perso,0);
    return perso;
}

/**
 * @brief libère l'espace occupé par la case mémoire pointée par p 
 * @
 * @param p un personnage que l'on souhaite libérer 
 */
void liberePersonnage(personnage p){
    free(p);
}

/**
 * @brief déplace le personnage sur la zone z
 * 
 * @param p est un personnage qui se déplace
 * @param z est la zone d'arrivée
 */
void deplacer(personnage p, zone z){
    setZonePrecedente(p,getZoneCourante(p));
    setZoneCourante(p,getNumero(z));
}

/**
 * @brief renvoie le numéro de la zone dans laquelle se trouve le personnage
 * 
 * @param p un personnage dont on souhaite obtenir la zone
 * @return le numéro de la zone du personnage, -1 en cas d'erreur
 */
int zonePersonnage(personnage p){
    if(getZoneCourante(p)<0){
        return -1;
    }
    else {
        return getZoneCourante(p);
    }
}

/**
 * @brief met à jour le statut du personnage p
 * 
 * @param p le personnage qui a été mangé
 */
void estMange(personnage p){
   setStatut(p,0);
   setPeutSeDeplacer(p,0);
}

