/**
 * @file test.c
 * @author Théo TAILLEFUMIER 
 * @brief 
 * @necessities 
 * @date 2023-03-31
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#include "headers/joueuses.h"


/**
 * @brief test si la joueuse est initialisée
 * 
 * @param nothing
 * 
 * @return int 1 si initialisée correctement, 0 sinon
 * 
 */
int test_init_joueuses()
{
    joueuse j = creation_joueuse(1); /*on créé une joueuse*/
    if (j==NULL){
        return 0;
    }
    if (getCapital(j) != 5){
        fprintf(stderr,"pb capital\n");
        return 0;
    }
    if (getTaille(j) != 5){
        fprintf(stderr,"pb taille\n");
        return 0;
    }
    if (getIdJoueuse(j) != 1){
        fprintf(stderr,"pb id\n");
        return 0;
    }
    if (getTour(j) != 1){
        fprintf(stderr,"pb tour\n");
        return 0;
    }
    if (getToursRestantsBonusCapital(j) != 1){
        fprintf(stderr,"pb tours restants bonus capital\n");
        return 0;
    }
    if (getToursInvincibilite(j) != 0){
        fprintf(stderr,"pb tours invinsibilite\n");
        return 0;
    }
    if (getToursRestantsJouer(j) != 1){
        fprintf(stderr,"pb tours restants jouer\n");
        return 0;
    }
    if (getProbaParCapital(j) != 0.1){
        fprintf(stderr,"pb proba par capital\n");
        return 0;
    }
    if (getMain(j) == NULL){
        fprintf(stderr,"pb mains\n");
        return 0;
    }
    if (getMembres(j) == NULL){
        fprintf(stderr,"pb membres\n");
        return 0;
    }
    //tester la création des personnages
    free(j);

    joueuse m = creation_joueuse(0); /*on créé un monstre*/
    //adapter aux valeurs choisit par adam dans la fonction creation_joueuse
    if (m==NULL){
        return 0;
    }
    if (getCapital(m) != -1){
        fprintf(stderr,"pb capital\n");
        return 0;
    }
    if (getTaille(m) != 1){
        fprintf(stderr,"pb taille\n");
        return 0;
    }
    if (getIdJoueuse(m) != 0){
        fprintf(stderr,"pb id\n");
        return 0;
    }
    if (getTour(m) != 1){
        fprintf(stderr,"pb tour\n");
        return 0;
    }
    if (getToursRestantsBonusCapital(m) != 1){
        fprintf(stderr,"pb tours restants bonus capital\n");
        return 0;
    }
    if (getToursInvincibilite(m) != -1){
        fprintf(stderr,"pb tours invinsibilite\n");
        return 0;
    }
    if (getToursRestantsJouer(m) != 1){
        fprintf(stderr,"pb tours restants jouer\n");
        return 0;
    }
    if (getProbaParCapital(m) != 0.1){
        fprintf(stderr,"pb proba par capital\n");
        return 0;
    }
    if (getMain(m) == NULL){
        fprintf(stderr,"pb mains\n");
        return 0;
    }
    if (getMembres(m) == NULL){
        fprintf(stderr,"pb membres\n");
        return 0;
    }
    //tester la création des personnages
    free(m);
    
    return 1;
}


/**
 * @brief test si les zones sont initialisées correctement
 * 
 * @param nothing
 * 
 * @return int 1 si initialisée correctement, 0 sinon
 * 
 */
int test_init_zones(){
    zones z = nouvellesZones(); /*on créé 10 zones*/
    if (z==NULL){
        fprintf(stderr,"NULL pointer");
        return 0;
    }
    if (getNbZones(z) != 10){
        fprintf(stderr,"pb nb zones\n");
        return 0;
    }
    for (int i=0; i<10; i++){
    if (getTabZones(z)[i] == NULL){
            fprintf(stderr,"pb zone %d\n",i);
            return 0;
        }
        for (int j=0; j<getNbZones(z); j++){
            if (getProbas(getTabZones(z)[i])[j] != 0.1){
                fprintf(stderr,"pb proba %d %d\n",i,j);
                return 0;
            }
            }
        }
    free(z);
    return 1;
}


int test_init_personnage(){
    zones zs = nouvellesZones();
    personnage perso  = nouveauPersonnage(1,trouveZone(zs,0));//membre de l'équipe 1
    if (perso == NULL){
        fprintf(stderr,"NULL pointer");
        return 0;
    }
    free(perso);
    return 1;
}


int main(){
    int test_zones = test_init_zones();
    int test_joueuses = test_init_joueuses();
    printf("%d",test_zones);
    printf("%d",test_joueuses);
}