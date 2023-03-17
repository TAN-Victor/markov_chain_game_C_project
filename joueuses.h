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
 * - deplacement_tout_le_monde(j) pour déplacer tous les membres d'une joueuse
 * - manger(j) pour manger tous les membres d'une joueuse qui sont sur une case d'un
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
    int taille; /*nombre de membres de l'équipe (doit être inférieur à 7, initialisée à 5*/
    int tours_restants_bonus_capital; /*tours restants pendant lesquels on peut recevoir plus de capital, initialisé à 1*/
    int tours_restants_invinsibilite; /*nb de tour pendant lesquels les membres d'une joeuse ne peunvent pas etre manges */
    int invinsibilite; /*vaut 1 si les membres sont invinsibles et 0 sinon, initialise à 0*/
    int tours_restants_jouer;/*tours restants pendant lesquels on peut faire plus de déplacement, initialisé à 1*/
    int proba_par_capital; /*la valeur de la modification de la proba par une joueuse par unité de capital (cf Katrin Salhab), initialisée à 0.1*/
};
typedef struct joueuse joueuse;

/** 
 * @brief renvoit un pointeur vers une joueuse :
 *          - on initialise le capital à 5
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
 * @return une liste de personreinitialisese* pj);


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


/**reinitialise
 * @brief on réinitialise le capital de la joueuse choisie (on le remet à 5) on gère en meme temps les bonus dans cette fonction (tours_restants)
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

/**
 * @brief cette fonction déplace tout le monde
 * @param liste_joueuses un pointeur vers les deux joueuses et les monstres
 * @param liste_zones l'ensembles des zones
*/
void deplacement_tout_le_monde(joueuse* liste_joueuses, zones liste_zones);

/**
 * @brief détermine si un personnage est dans la zone d'un monstre et si oui alors il est mangé
 * @param liste_joueuses pointeur vers les deux joueuses et les monstres
*/
void manger(joueuse* liste_joueuses);
#endif