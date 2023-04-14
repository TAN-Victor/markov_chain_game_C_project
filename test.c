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
//ce test est à chier
int test_init_joueuses()
{
    joueuse j = creation_joueuse(1,1); /*on créé une joueuse*/
    if (j==NULL){
        return 0;
    }
    if (getCapital(j) != 5){
        fprintf("pb capital\n");
        return 0;
    }
    if (getTaille(j) != 5){
        fprintf("pb taille\n");
        return 0;
    }
    if (getIdJoueuse(j) != 1){
        fprintf("pb id\n");
        return 0;
    }
    if (getTour(j) != 1){
        fprintf("pb tour\n");
        return 0;
    }
    if (getToursRestantsBonusCapital(j) != 1){
        fprintf("pb tours restants bonus capital\n");
        return 0;
    }
    if (getToursInvinsibilite(j) != 0){
        frprintf("pb tours invinsibilite\n");
        return 0;
    }
    if (getToursRestantsJouer(j) != 1){
        fprintf("pb tours restants jouer\n");
        return 0;
    }
    if (getProbaParCapital(j) != 0.1){
        fprintf("pb proba par capital\n");
        return 0;
    }
    if (getMains(j) == NULL){
        fprintf("pb mains\n");
        return 0;
    }
    if (getMembres(j) == NULL){
        fprintf("pb membres\n");
        return 0;
    }
    //tester la création des personnages
    free(j);
    return 1
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
        return 0;
    }
    if (getNbZones(z) != 10){
        fprintf("pb nb zones\n");
        return 0;
    }
    for (int i=0; i<10; i++){
        if (getZones(z,i) == NULL){
            fprintf("pb zone %d\n",i);
            return 0;
        }
        for (int j=0; j<getNbZones(z); j++){
            if (getProbas(z)[i][j] != 0.1){
                fprintf("pb proba %d %d\n",i,j);
                return 0;
            }
            }
        }
    }
    free(z);
    return 1;
}