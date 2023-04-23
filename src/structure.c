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
#include "../headers/structures.h"

/* Getter et Setters */
/**
 * @brief renvoie un entier correspondant au nombre de cartes présentes dans la liste
 * 
 * @param lc 
 * @return int correspondant au nombre de cartes 
 */
int getNbCartes(liste_cartes lc){
    return lc->nb_cartes;
}

/**
 * @brief met à jour le nombre de cartes de la main
 * 
 * @param n 
 */
void setNbCartes(int n){
    lc->nb_cartes = n;
}

/**
 * @brief renvoie la liste de cartes de la liste de cartes passés en arguments
 * 
 * @param lc 
 * @return carte* tableau de cartes
 */
carte* getCartes(liste_cartes lc){
    return lc->cartes;
}

/**
 * @brief renvoie la taille de la matrice
 * 
 * @param matrice un pointeur vers la matrice de probas
 * 
 * @return int la taille de la matrice
*/
int getTailleMatrice(matrice_probas matrice){
    return matrice->taille;
}

/**
 * @brief met à jour la taille de la matrice
 * 
 * @param taille la nouvelle taille de la matrice
*/
void setTailleMatrice(int taille){
    matrice->taille = taille;
}


void ajout_carte(liste_cartes liste, carte carte){
    liste->nb_cartes++;
    liste->cartes = realloc(liste->cartes, liste->nb_cartes * sizeof(carte));
    liste->cartes[liste->nb_cartes - 1] = carte;
}

carte lecture_cartes(liste_cartes liste, int index){
    if (index < liste->nb_cartes){
        return &liste->cartes[index];
    }
    return NULL;
}

void suppr_cartes(liste_cartes liste, carte carte){
    int index = 0;
    while (index < liste->nb_cartes && liste->cartes[index] != carte){
        index++;
    }
    if (index < liste->nb_cartes){
        liste->nb_cartes--;
        for (int i = index; i < liste->nb_cartes; i++){
            liste->cartes[i] = liste->cartes[i + 1];
        }
        liste->cartes = realloc(liste->cartes, liste->nb_cartes * sizeof(carte));
    }
}

matrice_probas creer_matrice(int taille){
    matrice_probas matrice = malloc(sizeof(matrice_probas));
    matrice->taille = taille;
    matrice->proba = malloc(taille * sizeof(float*));
    for (int i = 0; i < taille; i++){
        matrice->proba[i] = malloc(taille * sizeof(float));
    }
    return matrice;
}

float lecture_probas(matrice_probas matrice, int i, int j){
    return matrice->proba[i][j];
}

void modifier_proba(matrice_probas matrice, int i, int j, float proba){
    matrice->proba[i][j] = proba;
}

void suppression_matrice(matrice_probas matrice){
    for (int i = 0; i < matrice->taille; i++){
        free(matrice->proba[i]);
    }
    free(matrice->proba);
    free(matrice);
}

matrice_probas produit_matrice(matrice_probas matrice1, matrice_probas matrice2){
    if (matrice1->taille != matrice2->taille){
        return NULL;
    }
    matrice_probas matrice = creer_matrice(matrice1->taille);
    for (int i = 0; i < matrice->taille; i++){
        for (int j = 0; j < matrice->taille; j++){
            float somme = 0;
            for (int k = 0; k < matrice->taille; k++){
                somme += matrice1->proba[i][k] * matrice2->proba[k][j];
            }
            matrice->proba[i][j] = somme;
        }
    }
    return matrice;
}
