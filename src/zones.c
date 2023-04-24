#include "../headers/zones.h"
/* Implémentation des setters et getters */

/**
 * @brief modifie la probabilité de la zone en fonction du capital investi
 *        proba est augmenté/diminué de 0.1 par capital investi
 * @param n1 numéro de la zone de départ compris entre 0 et nb_zones-1
 * @param n2 numéro de la zone d'arrivée compris entre 0 et nb_zones-1
 * @param proba quantité de probabilité à ajouter ou retirer, est posiftif
 * @param action indique si on augmente (action = 1) ou retire (action = 0) de la probabilité
 */
void modifierZone(zones z, int n1, int n2, float proba, int action) {
    if (action == 1) {
        modifier_proba(getMatrice(z), n1, n2, lecture_probas(getMatrice(z), n1, n2) + proba);
 
    }
    else if (action == 0) {
        modifier_proba(getMatrice(z), n1, n2, lecture_probas(getMatrice(z), n1, n2) - proba);
    }
}

/**
 * @brief initialise nb_zones à 10 et créer les zones du jeu 
 * 
 * @return renvoie un pointeur vers l'ensemble des zones du jeu 
 */
zones nouvellesZones(){
    zones zos=(zones)malloc(sizeof(zones));
    zos->tab_zones=(zone*)malloc(NB_DE_ZONES*sizeof(struct _zone));
    zos->matrice=(matrice_probas)malloc(sizeof(matrice_probas));
    for(int i=0;i<NB_DE_ZONES;i++){
        addZone(zos);
    }
    return zos;
}

/**
 * @brief libère toutes les zones du jeu
 * 
 * @param pz une adresse vers un ensemble de zones valide
 */
void libereZones(zones pz){
    free(pz->tab_zones);
    free(pz->matrice);
    free(pz);
}

/**
 * @brief renvoie un pointeur vers la zone dont le numéro est n
 * 
 * @param n numéro de la zone compris entre 0 et nb_zones-1
 * @return zone la zone numéro n
 */
zone trouveZone(zones z, int n){
    if(n<0 || n>9){
        fprintf(stderr," trouveZone : n<0 ou n>9, en effet, n=%d",n);
        exit(n);
    }
    if(getTailleMatrice(z->matrice)==11 && (n<0 || n>10)){
        fprintf(stderr," trouveZone : n<0 ou n>10, en effet, n=%d",n);
        exit(n);
    }
    for(int i=0;i<getTailleMatrice(z->matrice);i++) { // Ici j'ai pris en compte la taille de la matrice car c'est elle qui change si on ajoute une 11ième zone
        if(getNumero(getTabZones(z)[i])==n){
            return getTabZones(z)[i];
        }
    }
    fprintf(stderr," trouveZone : aucune zone trouver pour n=%d",n);
    exit(n);
}

/**
 * @brief renvoie le numéro de la prochaine zone
 * 
 * @param nz numéro de la zone actuelle compris entre 
 * @return le numéro de la prochaine zone, -1 en cas d'erreur 
 */
int prochaineZone(zones z, int nz){
    if(nz<0 || nz>8){
        fprintf(stderr," prochaineZone : nz<0 ou nz>8, en effet, nz=%d",nz);
        return -1;
    }
    if(getTailleMatrice(z->matrice)==11 && (nz<0 || nz>9)){
        fprintf(stderr," prochaineZone : nz<0 ou nz>10, en effet, nz=%d",nz);
        return -1;
    }
    return getNumero(getTabZones(z)[nz+1]);   
}

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
 * @brief met à jour le numéro de la zone
 * 
 * @param z la zone à modifier
 * @param n le nouveau numéro
 */
void setNumero(zone z, int n){
    z->numero = n;
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
 * @brief renvoie la matrice des probabilités de se déplacer entre les zones
 * 
 * @param z les zones du jeu
 * @return matrice_probas 
 */
matrice_probas getMatrice(zones z){
    return z->matrice;
}

/**
 * @brief met à jour la matrice des probabilités de se déplacer entre les zones
 * 
 * @param z les zones du jeu
 * @param m la nouvelle matrice
 */
void setMatrice(zones z, matrice_probas m){
    z->matrice = m;
}

void addZone(zones z) {
    matrice_probas matrice = malloc(sizeof(matrice_probas));
    int new_taille = getMatrice(z)->taille_matrice + 1;
    setTailleMatrice(matrice, new_taille);

    /* on alloue la nouvelle zone */
    matrice->proba = realloc(matrice->proba, new_taille * sizeof(float*));
    matrice->proba[new_taille - 1] = malloc(new_taille * sizeof(float));

    /* on initialise les probas de la nouvelle zone */
    for (int i = 0; i < new_taille-1; i++){
        matrice->proba[new_taille - 1][i] = 0;
    }
    matrice->proba[new_taille - 1][new_taille - 1] = 1;

    /* on initialise les probas des zones existantes */
    for (int i = 0; i < new_taille-1; i++){
        matrice->proba[i] = realloc(matrice->proba[i], new_taille * sizeof(float));
        matrice->proba[i][new_taille - 1] = 0;
    }

    /* on met à jour la matrice */
    setMatrice(z, matrice);

    /* on met à jour la nouvelle zone */
    zone new_zone = malloc(sizeof(zone));
    setNumero(new_zone, new_taille);
    setEstAutorise(new_zone,0);

    /* on met à jour le tableau de zones */
    z->tab_zones = realloc(z->tab_zones, new_taille * sizeof(zone));
    z->tab_zones[new_taille - 1] = new_zone;

}
