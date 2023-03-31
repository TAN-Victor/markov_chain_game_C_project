/**
 * @file joueuses.h
 * @author Théo Taillefumier
 * @brief interface des joueuses
 * @date 2023-03-11
 * 
 * @necessities personnages.h cartes.h
 * 
 * Ce fichier decrit un ensemble de fonctions joueuse utiles.
 * Il contient 1 type et 11 fonctions : 
 * - le type joueuse définit une joeuse
 * - creation_joueuse() pour créer une joueuse et initialier tous ces arguments
 * - free_joueuse(j) pour libérer l'espace mémoire d'une joueuse
 * - tout_joueuse(j1,j2) pour savoir quelle joueuse peut jouer
 * - membre_ecole(j) pour obtenir tous les membres de l'école d'une joueuse
 * - nb_membre_ecole(j) pour obtenir le nombre de membres de l'école d'une joueuse
 * - tous_manges(j) pour tester si tous les membres d'une joueuse ont été mangés
 * - reinitialise_capital(j) pour remettre le capital d'une joeuse à 5
 * - utilise_capital(j,capital) pour utiliser le capital de la joeuse de la valeur souhaitée
 * - utilise_carte(j,carte) pour jouer la carte demandée
 */
#ifndef JOUEUSES_H
#define JOUEUSES_H

#include "personnages.h"
#include "cartes.h"
#include "zones.h"


 struct joueuse
{
    int capital;/*initialisé à 5*/
    personnage* membres;/*une liste de pointeur de personnage de taille 7 (=taille max de l'équipe)*/
    carte* main_du_joueur; /*une liste contenant les cartes de la joueuse*/
    int id; /*on identifie une joueuse par un numéro unique*/
    int tour; /*cette valeur est égale à 0 si c'est le tour de la joueuse et 1 sinon*/
    int taille; /*nombre de membres de l'équipe (doit être inférieur à 7), initialisée à 5*/
    int tours_restants_bonus_capital; /*tours restants pendant lesquels on peut recevoir plus de capital, initialisé à 1*/
    int tours_restants_invinsibilite; /*nb de tour pendant lesquels les membres d'une joeuse ne peunvent pas etre manges */
    int invinsibilite; /*vaut 1 si les membres sont invinsibles et 0 sinon, initialise à 0*/
    int tours_restants_jouer;/*tours restants pendant lesquels on peut faire plus de déplacement, initialisé à 1*/
    float proba_par_capital; /*la valeur de la modification de la proba par une joueuse par unité de capital (cf Katrin Salhab), initialisée à 0.1*/
};
typedef struct joueuse* joueuse;

/** 
 * @brief renvoit une joueuse :
 *          - on initialise le capital à 5
            - on initialise les 5 membres du joueurs
            - on initialise la main_du_joueur avec 5 cartes aléatoires
            - on associe à la joeuse une clée unique (1 ou 2)-> cette clef permet de savoir qui est le joueur n°1
 * @param n un entier si n=0 on cree un monstre dans un ensemble de monstres, si n=1 on cree une joueuse
 * @return joueuse un pointeur vers la joueuse crée
*/
joueuse creation_joueuse(int n);


/**
 * @brief libère l'espace mémoire occupée par la case mémoire pointée par pj
 * @param pj pointeur vers la case mémoire occupée par la joueuse que l'on souhaite libérer
*/
void free_joueuse(joueuse pj);


/**
 * @brief renvoie la joueuse dont c'est le tour en testant sur les deux joueuses, celle dont la valeur tour vaut 0
 * @param pj1 pointeur vers la joueuse 1
 * @param pj2 pointeur vers la joueuse 2
 * @return un pointeur vers la joueuse dont c'est le tour
*/
joueuse tour_joueuse(joueuse pj1, joueuse pj2);


/**
 * @brief renvoie la liste de personnage (de type membre de d'école) de la joueuse sélectionnée
 * @param pj pointeur vers la joueuse sélectionnée
 * @return une liste de personreinitialisese* pj;
*/
personnage* getMembres(joueuse pj);

/**
 * @brief renvoie le nombre de membres de la joueuse
 * @param pj  pointeur vers la joueuse dont on veut connaitre le nombre de membre
*/
int nb_membre_ecole(joueuse pj);


/**
 * @brief on test si tous les membres d'une joueuse ont été mangés
 * @param pj pointeur vers la joueuse dont on veux savoir s'il lui reste des membres
 * @return 1 (=vrai) si tous les membres sont mangés et 0 (=faux) sinon
*/
int tous_manges(joueuse pj);


/**
 * @brief on réinitialise le capital de la joueuse choisie (on le remet à 5) on gère en meme temps les bonus dans cette fonction (tours_restants)
 * @param pj pointeur vers la joueuse dont le capital va être réinitialisé
*/
void reinitialise_capital(joueuse pj);


/**
 * @brief on retire du capital à la jouesuse sélectionnée du montant choisit (en vérifiant que son capital ne passe pas en négatif)
 * @param pj pointeur vers la joueuse dont le capital va être modifié
 * @param capital entier que l'on va soustraire au capital de la joueuse
*/
void utilise_capital(joueuse pj, int capital);


/**
 * @brief la carte c est retirer de la main du joueur et on applique les effets de la carte (il faut assi s'assurer que le joueur possède la carte)
 * @param pj pointeur vers une joueuse
 * @param c la carte que la joueuse souhaite jouer
*/
void utilise_carte(joueuse pj, carte c);

/* ---------------------------------------------------------------------------------------------------------- */
/* Getters and Setters */

/**
 * @brief renvoie le capital d'une joueuse
 * 
 * @param j : une joueuse
 * @return int : le capital
 */
int getCapital(joueuse j);

/**
 * @brief renvoie la liste des cartes de la main d'une joueuse
 * 
 * @param j : une joueuse 
 * @return carte* : la liste des cartes de la main d'une joueuse 
 */
carte* getMains(joueuse j);

/**
 * @brief renvoie l'id d'une joueuse
 * 
 * @param j : une joueuse 
 * @return int : l'id d'une joueuse
 */
int getId(joueuse j);

/**
 * @brief renvoie 1 si c'est à la joueuse de jouer, 0 sinon
 * 
 * @param j : une joueuse 
 * @return int : 1 si c'est à la joueuse de jouer, 0 sinon
 */
int getTour(joueuse j);

/**
 * @brief renvoie la taille de l'équipe d'une joueuse
 * 
 * @param j : une joueuse 
 * @return int : le taille de l'équipe
 */
int getTaille(joueuse j);

/**
 * @brief renvoie le nombre de tours restants sous bonus de capital de la joueuse
 * 
 * @param j : une joueuse 
 * @return int : le nombre de tours restants sous bonus
 */
int getToursRestantsBonusCapital(joueuse j);

/**
 * @brief renvoie la valeur de invinsibilite
 * 
 * @param j : une joueuse 
 * @return int : 1 si les membres de la joueuse sont invinsibles, 0 sinon
 */
int getInvinsibilite(joueuse j);

/**
 * @brief renvoie le nombre de tours restants pendant lesquels les membres de la joueuse sont invinsibles
 * 
 * @param j : une joueuse 
 * @return int : le nombre de tours restants pendant lesquels les membres de la joueuse sont invinsibles
 */
int getToursInvinsibilite(joueuse j);

/**
 * @brief renvoie le nombre de tours restants pendant lesquels la joueuse peut jouer plusieurs fois par tour
 * 
 * @param j 
 * @return int : le nombre de tours restant pendant lequels elle peut jouer plusieurs fois
 */
int getToursRestantsJouer(joueuse j);

/**
 * @brief renvoie la proba par capital de la joueuse
 * 
 * @param j 
 * @return float : la proba par capital de la joueuse
 */
float getProbaParCapital(joueuse j);

/**
 * @brief modifie le capital d'une joueuse
 * 
 * @param j : une joueuse 
 * @param capital : le nouveau capital
 */
void setCapital(joueuse j, int capital);

/**
 * @brief modifie la liste des personnages d'une joueuse
 * 
 * @param j : une joueuse 
 * @param p : le personnage à modifier
 */
void setPersonnages(joueuse j, personnage* p);

/**
 * @brief modifie la liste des cartes de la main d'une joueuse
 * 
 * @param j : une joueuse 
 * @param c : une pointeur vers la carte à modifier 
 */
void setCartes(joueuse j, carte c);

/**
 * @brief modifie l'id d'une joueuse
 * 
 * @param j : une joueuse 
 * @param id : le nouvel id
 */
void setId(joueuse j, int id);

/**
 * @brief modifie le tour d'une joueuse
 * 
 * @param j : une joueuse 
 * @param tour : 1 si c'est à la joueuse de jouer, 0 sinon
 */
void setTour(joueuse j, int tour);

/**
 * @brief modifie la taille de l'équipe d'une joueuse
 * 
 * @param j : une joueuse 
 * @param taille : la nouvelle taille de l'équipe
 */
void setTaille(joueuse j, int taille);

/**
 * @brief modifie le nombre de tours restants sous bonus capital de la joueuse
 * 
 * @param j : une joueuse 
 * @param toursRestants : le nouveau nombre de tours restants sous bonus capital
 */
void setToursRestantsBonusCapital(joueuse j, int toursRestants);

/**
 * @brief modifie la valeur du nombre restant de tours sous invinsibilité
 * 
 * @param j : une joueuse 
 * @param toursRestants : le nouveau nombre de tours restants sous invinsibilité
 */
void setToursRestantsInvinsibilite(joueuse j, int toursRestants);

/**
 * @brief modifie le nombre de tours restants pendant lesquels la joueuse peut jouer plusieurs fois par tour
 * 
 * @param j : la joueuse 
 * @param toursRestants : le nouveau nombre de tours restants pendant lesquels la joueuse peut jouer plusieurs fois par tour
 */
void setToursRestantsJouer(joueuse j, int toursRestants);

#endif