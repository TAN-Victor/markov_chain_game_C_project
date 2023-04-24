/**
 * \file cartes.h
 * Ce fichier décrit le type \b carte qui sera composé d'un \b nom et d'une \b description tout deux de type \b char* .
 * De plus, par la suite un tableau statique de taille 20 qui contiendra les 20 cartes du jeu sera implémenté dans le \b main.c au début,
 * ainsi que 2 autres tableaux de cartes de taille 5 contenant les cartes tirées qui seront la main de chaque joueur.
*/

#ifndef CARTES_H
#define CARTES_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct carte{
    char* nom;
    char* description;
};
typedef struct carte* carte;

/**
 * Idée d'implémentation dans le .c :
 * carte carte_test=(carte)malloc(sizeof(struct carte));
 * carte_test->nom="...";
 * carte_test->description="...";
 *
 * Implémenter une fonction "pouvoir" pour chaque carte puis créer une autre fonction qui va appeler la fonction "pouvoir"    correspondant au nom de la carte
 */

 /**
 * \brief Créer une carte
 * \param nom_to_put le nom de la carte à créer
 * \param description_to_put La description de la carte à créer
 * \return Retourne une carte personnalisé
*/
carte creer_carte(char* nom_to_put,char* description_to_put);

/**
 * @brief renvoie le nom d'une carte
 * 
 * @param c 
 * @return char* le nom de la carte
 */
char* getNom(carte c);

/**
 * @brief renvoie la description de la carte
 * 
 * @param c 
 * @return char* la description
 */
char* getDescription(carte c);

#endif
