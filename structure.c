/**
 * @file structures.c
 * @author Théo Taillefumier
 * @brief structures de données
 * @date 2023-03-31
 * 
 * @necessities
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "headers/structures.h"



void ajout_carte(liste_cartes *liste, carte carte){
    liste->nb_cartes++;
    liste->cartes = realloc(liste->cartes, liste->nb_cartes * sizeof(carte));
    liste->cartes[liste->nb_cartes - 1] = carte;
}

carte lecture_cartes(liste_cartes *liste, int index){
    if (index < liste->nb_cartes){
        return &liste->cartes[index];
    }
    return NULL;
}

void suppr_cartes(liste_cartes *liste, carte carte){
    int i = 0;
    while (i < liste->nb_cartes && liste->cartes[i]->nom != carte->nom ){
        i++;
    }
    if (i < liste->nb_cartes){
        liste->nb_cartes--;
        liste->cartes[i] = liste->cartes[liste->nb_cartes];
        liste->cartes = realloc(liste->cartes, liste->nb_cartes * sizeof(carte));
    }
}

matrice_probas* creer_matrice(int taille){
    matrice_probas* matrice = malloc(sizeof(matrice_probas));
    matrice->proba = malloc(taille * sizeof(float*));
    for (int i = 0; i < taille; i++){
        matrice->proba[i] = malloc(taille * sizeof(float));
    }
    matrice->taille = taille;
    return matrice;
}

float lecture_probas(matrice_probas *matrice, int i, int j){
    return matrice->proba[i][j];
}

void modifier_proba(matrice_probas* matrice, int i, int j, float proba){
    matrice->proba[i][j] = proba;
}