#include "../headers/cartes.h"


 /**
 * \brief Créer une carte
 * \param nom_to_put le nom de la carte à créer
 * \param description_to_put La description de la carte à créer
 * \return Retourne une carte personnalisé
*/
carte creer_carte(char* nom_to_put,char* description_to_put){
    carte c=(carte)malloc(sizeof(carte));
    c->nom=nom_to_put;
    c->description=description_to_put;
    return c;
}

/* Getter et Setter */
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
