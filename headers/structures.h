/**
 * @file structures.h
 * @author Théo Taillefumier
 * @brief structures de données
 * @date 2023-03-31
 * 
 * @necessities
 * 
 * 
 */
#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "cartes.h"

/* Création des constantes */
#define NB_CARTES_MAIN_JOUEUSE 5
#define NB_DE_ZONES 10

//structures concernant les cartes
struct liste_cartes {
    int nb_cartes;
    carte *cartes;
};
typedef struct liste_cartes* liste_cartes;

/* Getter et Setters */
/**
 * @brief renvoie un entier correspondant au nombre de cartes présentes dans la liste
 * 
 * @param lc 
 * @return int correspondant au nombre de cartes 
 */
int getNbCartes(liste_cartes lc);

/**
 * @brief met à jour le nombre de cartes de la main
 * 
 * @param n 
 */
void setNbCartes(int n);

/**
 * @brief renvoie la liste de cartes de la liste de cartes passés en arguments
 * 
 * @param lc 
 * @return carte* tableau de cartes
 */
carte* getCartes(liste_cartes lc);

/**
 * @brief ajoute une carte à la liste
 * 
 * @param liste un pointeur vers la liste de cartes
 * @param carte la carte à ajouter
*/
void ajout_carte(liste_cartes liste, carte carte);


/**
 * @brief supprime une carte à la liste
 * 
 * @param liste un pointeur vers la liste des cartes
 * @param carte la carte à supprimer
*/
void suppr_cartes(liste_cartes liste, carte carte);

/**
 * @brief lecture de la carte d'indice index
 * 
 * @param liste un pointeur vers la liste des cartes
 * @param index l'indice dont on veut la carte
 * 
 * @return carte* un pointeur vers la carte d'indice index
*/
carte lecture_cartes(liste_cartes liste, int index);






//structures concernant les probas
struct matrice_probas {
    float** proba;
    int taille_matrice;
};
typedef struct matrice_probas* matrice_probas;

/**
 * @brief lecture de la probabilité d'indice i,j
 * 
 * @param matrice un pointeur vers la matrice de probas
 * @param i 
 * @param j 
 * 
 * @return float la valeur de la proba d'indice i,j
*/
float lecture_probas(matrice_probas matrice, int i, int j);


/* Getters et Setters */
/**
 * @brief renvoie la taille de la matrice
 * 
 * @param matrice un pointeur vers la matrice de probas
 * 
 * @return int la taille de la matrice
*/
int getTaille(matrice_probas matrice);

/**
 * @brief met à jour la taille de la matrice
 * 
 * @param taille la nouvelle taille de la matrice
*/
void setTaille(int taille);

/**
 * @brief création d'une matrice de probas de taille taille
 * 
 * @param taille la taille de la matrice
*/
matrice_probas creer_matrice(int taille);

/**
 * @brief écriture de la probabilité d'indice i,j
 * 
 * @param matrice un pointeur vers la matrice de probas
 * @param i 
 * @param j 
 * @param proba la valeur de la proba à écrire
*/
void modifier_proba(matrice_probas matrice, int i, int j, float proba);


/**
 * @brief suppression d'une matrice de probas
 * 
 * @param matrice un pointeur vers la matrice de probas
*/
void suppression_matrice(matrice_probas matrice);

/**
 * @brief produit de deux matrices de probas
 * 
 * @param matrice1 un pointeur vers la première matrice
 * @param matrice2 un pointeur vers la deuxième matrice
 * 
 * @return matrice_probas un pointeur vers la matrice résultat
*/
matrice_probas produit_matrice(matrice_probas matrice1, matrice_probas matrice2);

#endif
