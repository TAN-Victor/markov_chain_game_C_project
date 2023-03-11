/**
 * @file joueuses.h
 * @author Théo Taillefumier
 * @brief interface des joueuses
 * @date 2023-03-11
 * 
 * @necessities personnages.h cartes.h
 * 
 */
#ifndef JOUEUSES_H
#define JOUEUSES_H

#include "personnages.h"
#include "cartes.h"


 struct joueuse
{
    int capital;
    personnage[5] membres;
    cartes[5] main_du_joueur; /*une liste contenant les cartes de la joueuse*/
    int id; /*on identifie une joueuse par un numéro unique*/
    int tour; /*cette valeur est égale à 0 si c'est le tour de la joueuse et 1 sinon*/
};
typedef struct joueuse joueuse;


/**
 * @brief renvoie un pointeur vers une joueuse :
            - on initialise le capital à 5
            - on initialise les 5 membres du joueurs
            - on initialise la main_du_joueur avec 5 cartes aléatoires
            - on associe à la joeuse une clée unique (1 ou 2)-> cette clef permet de savoir qui est le joueur n°1
 * @param
 * @return joueuse* un pointeur vers la joueuse crée
*/
joueuse* creation_joueuse();


/**
 * @brief libère l'espace mémoire occupée par la case mémoire pointée par pj
 * @param pj pointeur vers la case mémoire occupée par la joueuse que l'on souhaite libérer
*/
void free_joueuse(joueuse* pj);


/**
 * @brief renvoie la joueuse dont c'est le tour en testant sur les deux joueuses, celle dont la valeur tour vaut 0
 * @param pj1 pointeur vers la joueuse 1
 * @param pj2 pointeur vers la joueuse 2
 * @return un pointeur vers la joueuse dont c'est le tour
*/
joueuse* tour_joueuse(joueuse* pj1, joueuse* pj2);


/**
 * @brief renvoie la liste de personnage (de type membre de d'école) de la joueuse sélectionnée
 * @param pj pointeur vers la joueuse sélectionnée
 * @return une liste de personnage
*/
personnage[] membre_ecole(joueuse* pj);


/**
 * @brief renvoie le nombre de membres de la joueuse
 * @param pj  pointeur vers la joueuse dont on veut connaitre le nombre de membre
*/
int nb_membre_ecole(joueuse* pj);


/**
 * @brief on test si tous les membres d'une joueuse ont été mangés
 * @param pj pointeur vers la joueuse dont on veux savoir s'il lui reste des membres
 * @return 1 (=vrai) si tous les membres sont mangés et 0 (=faux) sinon
*/
int tous_manges(joueuse* pj);


/**
 * @brief on réinitialise le capital de la joueuse choisie (on le remet à 5)
 * @param pj pointeur vers la joueuse dont le capital va être réinitialisé
*/
void reinitialise_capital(joueuse* pj);


/**
 * @brief on retire du capital à la jouesuse sélectionnée du montant choisit (en vérifiant que son capital ne passe pas en négatif)
 * @param pj pointeur vers la joueuse dont le capital va être modifié
 * @param capital entier que l'on va soustraire au capital de la joueuse
*/
void utilise_capital(joueuse* pj, int capital);


/**
 * @brief la carte c est retirer de la main du joueur et on applique les effets de la carte (il faut assi s'assurer que le joueur possède la carte)
 * @param pj pointeur vers une joueuse
 * @param c la carte que la joueuse souhaite jouer
*/
void utilise_carte(joueuse* pj, carte c);

#endif