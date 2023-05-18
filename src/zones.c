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
 * @brief initialise nb_zones à NB_DE_ZONES et créer les zones du jeu 
 * 
 * @return renvoie un pointeur vers l'ensemble des zones du jeu 
 */
zones nouvellesZones(){
    // on alloue la mémoire nécessaire pour les zones
    zones zos=(zones)malloc(sizeof(struct _zones));
    zos->tab_zones=(zone*)malloc(NB_DE_ZONES * sizeof(zone));
    // on alloue la mémoire nécessaire pour la matrice de probas
    zos->matrice=creer_matrice(NB_DE_ZONES);

    // on initialise les zones
    float prob = 1/(float)NB_DE_ZONES;
    for (int i=0; i<NB_DE_ZONES; i++) {
        for (int j=0; j<NB_DE_ZONES; j++) {
            modifier_proba(zos->matrice, i, j, prob);
        }
        zos->tab_zones[i]=(zone)malloc(sizeof(struct _zone));
        setNumero(zos->tab_zones[i], i);
        setEstAutorise(zos->tab_zones[i], 0);
    }
    return zos;
}


/**
 * @brief libère toutes les zones du jeu
 * 
 * @param pz une adresse vers un ensemble de zones valide
 */
void libereZones(zones pz){
    for(int i=0;i<getTailleMatrice(pz->matrice);i++){ // j'ai pris en compte le taille de la matrice car c'est elle qui me permet de savoir si il y a 10 ou 11 zones
        free(getTabZones(pz)[i]);
    }
    free(pz->tab_zones);
    suppression_matrice(getMatrice(pz));
    free(pz);
}

/**
 * @brief renvoie un pointeur vers la zone dont le numéro est n
 * 
 * @param n numéro de la zone compris entre 0 et nb_zones-1
 * @return zone la zone numéro n
 */
zone trouveZone(zones z, int n){
    // on regarde si le nombre de zone vaut 10
    if(getTailleMatrice(getMatrice(z))==10)
    {
        // on regarde si le numéro de la zone est compris entre 0 et 9
        if(n<0 || n>10)
        {
            fprintf(stderr," trouveZone : n<0 ou n>9, en effet, n=%d",n);
            exit(n);
        }
        else
        {
            for(int i=0;i<getTailleMatrice(getMatrice(z));i++)
            {
                if(getNumero(getTabZones(z)[i])==n)
                {
                    return getTabZones(z)[i];
                }
            }
            fprintf(stderr," trouveZone : aucune zone trouver pour n=%d",n);
            exit(n);
        }
    }
    else // le nombre de zones vaut 11 dans ce cas là
    {
        // on regarde si le numéro de la zone est compris entre 0 et 10
        if(n<0 || n>11)
        {
            fprintf(stderr," trouveZone : n<0 ou n>11, en effet, n=%d",n);
            exit(n);
        }
        else
        {
            for(int i=0;i<getTailleMatrice(getMatrice(z));i++)
            {
                if(getNumero(getTabZones(z)[i])==n)
                {
                    return getTabZones(z)[i];
                }
            }
            fprintf(stderr," trouveZone : aucune zone trouver pour n=%d",n);
            exit(n);
        }
    }
}

/**
 * @brief renvoie le numéro de la prochaine zone
 * 
 * @param nz numéro de la zone actuelle compris entre 0 et taille_matrice-1
 * @return le numéro de la prochaine zone, -1 en cas d'erreur 
 */
int prochaineZone(zones z, int nz){
    // on regarde si le nombre de zone vaut 10
    if(getTailleMatrice(z->matrice)==10)
    {
        // on regarde si le numéro de la zone est compris entre 0 et 9
        if(nz<0 || nz>9){
            fprintf(stderr," prochaineZone : nz<0 ou nz>9, en effet, nz=%d",nz);
            return -1;
        }
        double x = (double)rand() / RAND_MAX; // Générer un nombre aléatoire entre 0 et 1
        double sum = 0.0;
        int next_case = -1;
        // Parcourir le tableau des probabilités et accumuler les probabilités
        for (int i = 0; i < getTailleMatrice(getMatrice(z)); i++) // on parcourt la matrice de proba
        {
            sum += (getMatrice(z)->proba)[nz][i]; // on se place sur la nz-eme ligne et on parcours les colonnes
            if (sum >= x)
            {
                next_case = i;
                break;
            }
        }
        // renvoie -1 en  cas d'erreur, et le numéro de la prochaine zone sinon
        return next_case;
    }
    else // le nombre de zones vaut 11 dans ce cas là
    {
        // on regarde si le numéro de la zone est compris entre 0 et 10
        if(nz<0 || nz>10){
            fprintf(stderr," prochaineZone : nz<0 ou nz>10, en effet, nz=%d",nz);
            return -1;
        }
        double x = (double)rand() / RAND_MAX; // Générer un nombre aléatoire entre 0 et 1
        double sum = 0.0;
        int next_case = -1;
        // Parcourir le tableau des probabilités et accumuler les probabilités
        for (int i = 0; i < getTailleMatrice(getMatrice(z)); i++) // on parcourt la matrice de proba
        {
            sum += (getMatrice(z)->proba)[nz][i]; // on se place sur la nz-eme ligne et on parcours les colonnes
            if (sum >= x)
            {
                next_case = i;
                break;
            }
        }
        // renvoie -1 en  cas d'erreur, et le numéro de la prochaine zone sinon
        return next_case;
    } 
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

/**
 * @brief ajoute une zone au jeu
 * 
 * @param z les zones du jeu
 */
void addZone(zones z) {
    matrice_probas matrice = malloc(sizeof(struct matrice_probas));
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
