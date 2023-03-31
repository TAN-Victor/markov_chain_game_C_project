#include "../headers/personnages.h"
struct _personnage {
    int type; /* 0 pour monstre et 1 ou 2 pour membre d'école*/
    int statut; /* 0 si mort, 1 si en vie, -1 si disparu, 2 si peut jouer 2 fois, 3 si FISA */
    int id; /* entier compris entre 1 et 5 pour les membres d'école, permettant de les identifier plus facilement */ 
    int zone_courante; /* numéro de la zone courante du personnage*/
    int zone_precedente; /* numéro de la zone précédente */
    int nb_de_pas_restant; /* nombre de pas restant, initialisé à 1 à chaque tour sauf cas particuliers */
    int peut_jouer; /* 1 si peut jouer ce tour, 0 sinon */
    int nb_de_tour_disparu; /* vaut 0 initialement */

};