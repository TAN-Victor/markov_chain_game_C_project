#include "../headers/cartes.h"
#include "../headers/personnages.h"
#include "../headers/cartes.h"

/**
 * @brief renvoie le nom d'une carte
 * 
 * @param c 
 * @return char* le nom de la carte
 */
char* getNom(carte c){
    return c->nom;
}

/**
 * @brief renvoie la description de la carte
 * 
 * @param c 
 * @return char* la description
 */
char* getDescription(carte c){
    return c->description;
}
