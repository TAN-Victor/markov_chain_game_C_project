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
 * - reinitialise_capital(j) pour remettre le capital d'une joueuse à 5
 * - utilise_capital(j,capital) pour utiliser le capital de la joeuse de la valeur souhaitée
 * - utilise_carte(j,carte) pour jouer la carte demandée
 */
#ifndef JOUEUSES_H
#define JOUEUSES_H

#include "personnages.h"


/* Création de constantes */
#define CAPITAL_DE_BASE 5
#define NB_DE_MONSTRE 1
#define NB_MEMBRES_JOUEUSE 5
#define PROBA_PAR_CAPITAL 0.1
#define NB_TOURS_RESTANTS_JOUER 1

 struct joueuse
{
    int capital;/*initialisé à 5*/
    personnage* membres;/*une liste de pointeur de personnage de taille 7 (=taille max de l'équipe)*/
    liste_cartes main_du_joueur; /*une liste contenant les cartes de la joueuse*/
    int id; /*on identifie une joueuse par un numéro unique, 0 si c'est la liste de monstres, 1 si c'est la joueuse 1, 2 si c'est la joueuse 2*/
    int tour; /*cette valeur est égale à 0 si c'est le tour de la joueuse et 1 sinon*/
    int taille; /*nombre de membres de l'équipe (doit être inférieur à 7), initialisée à 5*/
    int tours_restants_bonus_capital; /*tours restants pendant lesquels on peut recevoir plus de capital, initialisé à 1*/
    int tours_restants_invincibilite; /*nb de tour pendant lesquels les membres d'une joueuse ne peuvent pas etre manges */
    int tours_restants_jouer;/*tours restants pendant lesquels on peut faire des déplacements, initialisé à 1 (correspond au nombre de tours d'affilés)*/
    float proba_par_capital; /*la valeur de la modification de la proba par une joueuse par unité de capital (cf Katrin Salhab), initialisée à 0.1*/
    int bonus_temporaire; /* vaut un entier strictement positif si le bonus est actif, correspondant à la valeur du bonus de capital pendant un tour uniquement, et est remise à 0 au tour suivant. Vaut 0 si aucun bonus de capital */
    int tours_restants_bonus_proba_par_capital; /*nb de tour pendant lesquels la proba par capital est modifiée*/
};
typedef struct joueuse* joueuse;

/** 
 * @brief renvoit une joueuse :
 *          - on initialise le capital à 5
            - on initialise les 5 membres du joueurs
            - on initialise la main_du_joueur avec 5 cartes aléatoires
            - on associe à la joeuse une clée unique (1 ou 2)-> cette clef permet de savoir qui est le joueur n°1
 * @param n un entier si n=0 on cree un ensemble de monstre avec un seul monstre, si n=1 on cree une joueuse 1, si n=2 on cree une joueuse 2
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
 * @brief la carte c est retirer de la main du joueur et on applique les effets de la carte (il faut aussi s'assurer que le joueur possède la carte)
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
 * @return liste_cartes* : la liste des cartes de la main d'une joueuse 
 */
liste_cartes getMain(joueuse j);

/**
 * @brief renvoie l'id d'une joueuse
 * 
 * @param j : une joueuse 
 * @return int : l'id d'une joueuse
 */
int getIdJoueuse(joueuse j);

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
int getInvincibilite(joueuse j);

/**
 * @brief renvoie le nombre de tours restants pendant lesquels les membres de la joueuse sont invinsibles
 * 
 * @param j : une joueuse 
 * @return int : le nombre de tours restants pendant lesquels les membres de la joueuse sont invinsibles
 */
int getToursInvincibilite(joueuse j);

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
 * @brief met à jour la proba_par_capital de la joueuse
 * 
 * @param j 
 * @param proba 
 */
void setProbaParCapital(joueuse j, float proba);

/**
 * @brief modifie le capital d'une joueuse
 * 
 * @param j : une joueuse 
 * @param capital : le nouveau capital
 */
void setCapital(joueuse j, int capital);

/**
 * @brief ajoute un personnage aux membres de la joueuse
 * 
 * @param j : une joueuse 
 * @param p : le personnage à ajouter
 */
void addMembres(joueuse j, personnage p);

/**
 * @brief supprime un personnage des membres de la joueuse
 * 
 * @param j : une joueuse 
 * @param id : l'id du personnage à supprimer
 */
void removeMembres(joueuse j, int id);

/**
 * @brief modifie l'id d'une joueuse
 * 
 * @param j : une joueuse 
 * @param id : le nouvel id
 */
void setIdJoueuse(joueuse j, int id);

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
 * @brief renvoie la valeur du nombre restant de tours sous invinsibilité
 * 
 * @param j : une joueuse 
 * @return int : le nombre restant de tours sous invinsibilité
 */
int getToursRestantsInvincibilite(joueuse j);

/**
 * @brief modifie la valeur du nombre restant de tours sous invinsibilité
 * 
 * @param j : une joueuse 
 * @param toursRestants : le nouveau nombre de tours restants sous invinsibilité
 */
void setToursRestantsInvincibilite(joueuse j, int toursRestants);

/**
 * @brief modifie le nombre de tours restants pendant lesquels la joueuse peut jouer plusieurs fois par tour
 * 
 * @param j : la joueuse 
 * @param toursRestants : le nouveau nombre de tours restants pendant lesquels la joueuse peut jouer plusieurs fois par tour
 */
void setToursRestantsJouer(joueuse j, int toursRestants);

/**
 * @brief renvoie le le bonus_temporaire
 * 
 * @param j 
 * @return int : la valeur du bonus pendant ce tour
 */
int getBonusTemporaire(joueuse j);

/**
 * @brief modifie le bonus_temporaire
 * 
 * @param j 
 * @param bonus : le nouveau bonus_capital, doit être positif
 */
void setBonusTemporaire(joueuse j, int bonus);

/**
 * @brief renvoie le nombre de tours restants pendant lesquels la proba par capital est augmentée
 * 
 * @param j 
 * @return int : le nombre de tours restants pendant lesquels la proba par capital est augmentée
 */
int getToursRestantsBonusProbaParCapital(joueuse j);

/**
 * @brief modifie le nombre de tours restants pendant lesquels la proba par capital est augmentée
 * 
 * @param j 
 * @param toursRestants : le nouveau nombre de tours restants pendant lesquels la proba par capital est augmentée
 */
void setToursRestantsBonusProbaParCapital(joueuse j, int toursRestants);

#endif
