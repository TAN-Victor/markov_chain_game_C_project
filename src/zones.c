#include "../headers/zones.h"
/* implémente les interfaces des setters et getters de zones.h*/

int getNumero(zone z){
    return z.numero;
}

float* getProbas(zone z){
    return z.probas;
}

zone* getZones(zones z){
    return z->tab_zones;
}

void addZone(zones z){
    /* on incrémente le nombre de zone */
    z->nb_zones++;
    /* on réalloue la mémoire pour ajouter une zone */
    z->tab_zones = realloc(z->tab_zones, z->nb_zones * sizeof(zone));
    /* on initialise la nouvelle zone */
    z->tab_zones[z->nb_zones-1].numero = z->nb_zones-1;
    z->tab_zones[z->nb_zones-1].probas = malloc(sizeof(int) * z->nb_zones);
    /* les probas de se déplacer vers d'autres zones sont nulles */
    for(int i = 0; i < z->nb_zones-1; i++){
        z->tab_zones[z->nb_zones-1].probas[i] = 0;
    }
    /* la proba de se déplacer vers cette zone quand on s'y trouve déjà vaut 1 */
    z->tab_zones[z->nb_zones-1].probas[z->nb_zones-1] = 1;

    /* on s'occupe de mettre les proba de se diriger vers la nouvelle zone à 0 */
    for (int i = 0; i < z->nb_zones-1; i++){
        z->tab_zones[i].probas[z->nb_zones-1] = 0;
    }
}
