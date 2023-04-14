#include "../headers/zones.h"
/* Implémentation des setters et getters */
/**
 * @brief renvoie le numéro de la zone z
 * 
 * @param z zone 
 * @return int numéro de la zone
 */
int getNumero(zone z){
    return z->numero;
}

/**
 * @brief renvoie la tableau des proba de se déplacer vers les zones du jeu à partir de la zone z passée en argument
 * 
 * @param z une zone
 * @return float* le tableau des proba
 */
float* getProbas(zone z){
    return z->probas;
}

/**
 * @brief renvoie un entier correspondant au type de joueurs autorisés sur la zone
 * 
 * @param z la zone en question
 * @return int 
 */
int getEstAutorise(zone z){
    return z->est_autorise;
}

/**
 * @brief met à jour l'entier est_autorise
 * 
 * @param z la zone à modifier
 */
void setEstAutorise(zone z, int n){
    z->est_autorise = n;
}

/**
 * @brief renvoie la liste des zones du jeu
 * 
 * @param z les zones du jeu
 * @return zone* 
 */
zone* getTabZones(zones z){
    return z->tab_zones;
}

/**
 * @brief renvoie le nombre de zones des zones du jeu
 * 
 * @param z l'ensemble des zones du jeu
 * @return int le nombre de zones
 */
int getNbZones(zones z){
    return z->nb_zones;
}

/**
 * @brief met à jour le nombre de zone
 * 
 * @param z l'ensemble des zones
 * @param n le nouveau nombre de zones
 */
void setNbZones(zones z, int n){
    z->nb_zones = n;
}

void addZone(zones z){
    /* on incrémente le nombre de zone */
    z->nb_zones++;
    /* on réalloue la mémoire pour ajouter une zone */
    z->tab_zones = realloc(z->tab_zones, z->nb_zones * sizeof(zone));
    /* on initialise la nouvelle zone */
    z->tab_zones[z->nb_zones-1]->numero = z->nb_zones-1;
    z->tab_zones[z->nb_zones-1]->probas = malloc(sizeof(int) * z->nb_zones);
    /* les probas de se déplacer vers d'autres zones sont nulles */
    for(int i = 0; i < z->nb_zones-1; i++){
        z->tab_zones[z->nb_zones-1]->probas[i] = 0;
    }
    /* la proba de se déplacer vers cette zone quand on s'y trouve déjà vaut 1 */
    z->tab_zones[z->nb_zones-1]->probas[z->nb_zones-1] = 1;

    /* on s'occupe de mettre les proba de se diriger vers la nouvelle zone à 0 */
    for (int i = 0; i < z->nb_zones-1; i++){
        z->tab_zones[i]->probas[z->nb_zones-1] = 0;
    }
}
