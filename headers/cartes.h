/**
 * \file cartes.h
 * Ce fichier décrit le type \b carte qui sera composé d'un \b nom et d'une \b description tout deux de type \b char* .
 * De plus, par la suite un tableau statique de taille 20 qui contiendra les 20 cartes du jeu sera implémenté dans le \b main.c au début,
 * ainsi que 2 autres tableaux de cartes de taille 5 contenant les cartes tirées qui seront la main de chaque joueur.
*/

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
 */
 








