/**
 * @file main.c
 * @author Victor Tan
 * @brief Fichier source avec le main
 * @necessities effets.h
 * @date 2023-03-06
 * 
 */

#include "../headers/cartes.h"
#include "../headers/structures.h"
#include "../headers/zones.h"
#include "../headers/personnages.h"
#include "../headers/joueuses.h"
#include "../headers/interface.h"
#include "../headers/effets.h"






int main() {

    /**
     * @brief Création de la liste_cartes_global
     * 
     */
    creer_liste_cartes_global();
    /**
     * @brief Création de 3 "joueuses"; l'ensemble des monstres correspondra à une joueuse 
     * 
     */
    joueuse joueuse_1 = creation_joueuse(1); // 1 pour dire que l'on crée une joueuse jouable n°1
    joueuse joueuse_2 = creation_joueuse(2); // 2 pour dire que l'on crée une joueuse jouable n°2
    joueuse monstres = creation_joueuse(0); // 0 pour dire que l'on crée une liste de monstres, il n'y aura qu'un seul monstre au début

    joueuse liste_joueuses[3] = { joueuse_1, joueuse_2, monstres }; // Mettre les monstres et les joueuses ensemble permettra de les faire déplacer tous ensemble avec une même fonction
    message_generique(1, NULL, NULL, NULL);
    /**
     * @brief Création des Zones du jeu (10 au début)
     * 
     */
    zones liste_zones = nouvellesZones();
    message_generique(2, NULL, NULL, NULL);

    int i = -1; // Vaut 0 si c'est le tour de la joueuse 1, 1 si c'est le tour de la joueuse 2
    /**
     * @brief Tant qu'aucune des deux joueuses n'a plus de personnages, le jeu continue
     * @stop Le nombre de personnages diminuera à chaque fois que le monstre mange,
     * la partie se termine lorsqu'une des deux joueuses n'a plus de personnages.
     * 
     */
    do {
        /**
         * @brief i vaut 0 si c'est le tour de la joueuse 1, 1 si c'est le tour de la joueuse 2
         * Il faudra donc utiliser les setTour à la fin de la boucle pour changer les tours
         * 
         */
        if (getTour(liste_joueuses[0]) == 1) {
            i = 0;
        }
        else {
            i = 1;
        }

    
            /**
             * @brief Affiche toutes les informations actuelles du jeu 
             * 
             */
            afficher_toute_info(liste_joueuses[i], liste_joueuses[(i+1)%2],liste_joueuses[2], liste_zones); // La joueuse du 1er argument est celle qui joue en ce moment
            
            

            /**
             * @brief Modification du plateau de jeu par utilisation du capital ou d'une carte
             * 
             */
            int n = demander_capital(liste_joueuses[i]);
            if (n > 0) {
                int zone_depart = demander_zones_depart(liste_zones);
                int zone_arrivee_augmenter = demander_zones_arrivee_augmenter(liste_zones);
                int zone_arrivee_diminuer = demander_zones_arrivee_diminuer(liste_zones, zone_arrivee_augmenter);
                utilise_capital(liste_joueuses[i], n);
                message_generique(3, liste_joueuses[i], &n, NULL);
                int proba_par_capital = getProbaParCapital(liste_joueuses[i]); // Voir si la carte de Katrin Salhab permet de modifier cette valeur une fois pour 3 tours ou tous les tours pendant 3 tours
                int m = n * proba_par_capital;
                modifierZone(liste_zones, zone_depart, zone_arrivee_augmenter, m, 1); // Augmentation de la probabilité d'aller de la zone 0 à la zone 1
                modifierZone(liste_zones, zone_depart, zone_arrivee_diminuer, m, 0); // Réduction de la probabilité d'aller de la zone 0 à la zone 2
                int triplet_augmenter[3] = {zone_depart, zone_arrivee_augmenter, m};
                int triplet_diminuer[3] = {zone_depart, zone_arrivee_diminuer, -m};
                message_generique(4, NULL, triplet_augmenter, NULL);
                message_generique(4, NULL, triplet_diminuer, NULL);
            }
            else { // Exclusion, ne peut pas jouer de carte si le capital a été dépensé
                carte c = demander_carte(liste_joueuses[i]); // Doit vérifier si la carte est jouable
                if (c != NULL) { // Si la joueuse veut jouer une carte
                    message_generique(5, liste_joueuses[i], NULL, c);  // voir avec interface.c
                    utilise_carte(liste_joueuses[i], c); // A modifier dans le futur, car une carte pourra augmenter le nombre de zone donc la fonction devrait prendre d'autres arguments
                }
            }



        /**
         * @brief Déplacement des monstres
         * 
         */
        int nombre_monstre = nb_membre_ecole(liste_joueuses[2]); // Nombre de monstres dans le jeu
        for (int j = 0; j < nombre_monstre; j += 1) {
            if (getPeutSeDeplacer(getMembres(liste_joueuses[2])[j]) == 1 && getStatut(getMembres(liste_joueuses[2])[j]) == 1) {
                for (int k = 0; k < getNbPas(getMembres(liste_joueuses[2])[j]); k += 1) {
                    deplacer(getMembres(liste_joueuses[2])[j], trouveZone(liste_zones, prochaineZone(liste_zones, zonePersonnage(getMembres(liste_joueuses[2])[j])))); // Déplacement des monstres vers leur prochaine zone
                }
            }
        }


        /**
         * @brief Déplacement des personnages des joueuses
         * 
         */
        for (int j = 0; j < 2; j += 1) {
            int nombre_personnage = nb_membre_ecole(liste_joueuses[j]); // Nombre de personnages dans l'école de la joueuse_(i+1)
            for (int k = 0; k < nombre_personnage; k += 1) {
                if (getPeutSeDeplacer(getMembres(liste_joueuses[j])[k]) == 1 && (getStatut(getMembres(liste_joueuses[j])[k]) == 1 || getStatut(getMembres(liste_joueuses[j])[k]) == 3) ) {
                    // Si le personnage peut se déplacer et ( qu'il est vivant ou (qu'il est un FIPA et peut jouer))
                    for (int l = 0; l < getNbPas(getMembres(liste_joueuses[j])[k]); l += 1) {    
                        deplacer(getMembres(liste_joueuses[j])[k], trouveZone(liste_zones, prochaineZone(liste_zones, zonePersonnage(getMembres(liste_joueuses[i])[j])))); // Déplacement des personnages vers leur prochaine zone
                    }
                }
            }
        }
        message_generique(6, NULL, NULL, NULL);


        /**
         * @brief Vérification de la présence des personnages dans les zones des monstres
         * 
         */
        for (int k = 0; k < nombre_monstre; k += 1) {
            for (int l = 0; l < 2; l += 1) {
                for (int m = 0; m < nb_membre_ecole(liste_joueuses[l]); m += 1) {
                    if (zonePersonnage(getMembres(liste_joueuses[l])[m]) == zonePersonnage(getMembres(liste_joueuses[2])[k])) {
                        if (getToursInvincibilite(liste_joueuses[l]) == 0 && (getStatut(getMembres(liste_joueuses[l])[m]) == 1 || getStatut(getMembres(liste_joueuses[l])[m]) == 3)) {
                            // Si le personnage n'est pas invincible et (qu'il est vivant ou qu'il est un FIPA)
                            estMange(getMembres(liste_joueuses[l])[m]);
                            message_generique(7, liste_joueuses[l], &m, NULL);
                        }
                    }
                }
            }
        }
        reinitialise_capital(liste_joueuses[i]); // Réinitialisation du capital de la joueuse active
        int tours_restants_bonus_capital = getToursRestantsBonusCapital(liste_joueuses[i]);
        int tours_restants_invincibilite = getToursInvincibilite(liste_joueuses[i]);
        int tours_restants_jouer = getToursRestantsJouer(liste_joueuses[i]);
        if (tours_restants_bonus_capital > 0) {
            setToursRestantsBonusCapital(liste_joueuses[i], tours_restants_bonus_capital - 1); // Diminution du nombre de tours restants pour le bonus de capital
        }
        if (tours_restants_bonus_capital == 0) {
            setProbaParCapital(liste_joueuses[i], PROBA_PAR_CAPITAL); // Réinitialisation de la probabilité par capital
        }
        if (tours_restants_invincibilite > 0) {
            setToursRestantsInvincibilite(liste_joueuses[i], tours_restants_invincibilite - 1); // Diminution du nombre de tours restants pour l'invincibilité
        }
        if (tours_restants_jouer > 0) {
            setToursRestantsJouer(liste_joueuses[i], tours_restants_jouer - 1); // Diminution du nombre de tours restants pour le bonus de capital
        }
        if (tours_restants_jouer == 0) { // Si le nombre de tours restants pour jouer est égal à 0, c'est au tour de l'autre joueuse
            setTour(liste_joueuses[i], 0);
            setTour(liste_joueuses[(i+1)%2], 1);
        }
        message_generique(8, NULL, NULL, NULL);            

    } while(!tous_manges(liste_joueuses[0]) || !tous_manges(liste_joueuses[1]));


    /**
     * @brief Fin du jeu
     * 
     */
    message_fin_du_jeu(liste_joueuses[0], liste_joueuses[1]);
    free_joueuse(liste_joueuses[0]);    // Libération de la mémoire par appel à liberePersonnage
    free_joueuse(liste_joueuses[1]);
    free_joueuse(liste_joueuses[2]);
    message_generique(9, NULL, NULL, NULL);
    libereZones(liste_zones);
    message_generique(10, NULL, NULL, NULL);
    return 0;

}
