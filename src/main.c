/**
 * @file main.c
 * @author Victor Tan
 * @brief Fichier source avec le main
 * @necessities interface.h
 * @date 2023-03-06
 * 
 */

#include "../headers/interface.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int main() {

    /**
     * @brief Création de 3 "joueuses"; l'ensemble des monstres correspondra à une joueuse 
     * 
     */
    joueuse joueuse_1 = creation_joueuse(1); // 1 pour dire que l'on crée une joueuse jouable
    joueuse joueuse_2 = creation_joueuse(1); // 1 pour dire que l'on crée une joueuse jouable
    joueuse monstres = creation_joueuse(0); // 0 pour dire que l'on crée une liste de monstres, il n'y aura qu'un seul monstre au début

    joueuse liste_joueuses[3] = { joueuse_1, joueuse_2, monstres }; // Mettre les monstres et les joueuses ensemble permettra de les faire déplacer tous ensemble avec une même fonction

    /**
     * @brief Création des Zones du jeu (10 au début)
     * 
     */
    zones liste_zones = nouvellesZones();


    /**
     * @brief Tant qu'aucune des deux joueuses n'a plus de personnages, le jeu continue
     * @stop Le nombre de personnages diminuera à chaque fois que le monstre mange,
     * la partie se termine lorsqu'une des deux joueuses n'a plus de personnages.
     * 
     */
    do {
        /**
         * @brief Alternance entre les 2 joueuses
         * 
         */
        for (int i = 0; i < 2; i += 1) {

    
            /**
             * @brief Affiche toutes les informations actuelles du jeu 
             * 
             */
            afficher_toute_info(liste_joueuses[i], liste_joueuses[(i+1)%2],liste_joueuses[2], liste_zones); // Appelle notamment tour_joueuse pour savoir qui joue
            
            

            /**
             * @brief Modification du plateau de jeu par utilisation du capital ou d'une carte
             * 
             */
            int n = demander_capital(liste_joueuses[i]);
            if (n > 0) {
                int* zones_modifiees = demander_zones(liste_zones);
                utilise_capital(liste_joueuses[i], n);
                modifierZone(liste_zones, zones_modifiees[0], zones_modifiees[1], n, 1); // Augmentation de la probabilité d'aller de la zone 0 à la zone 1
                modifierZone(liste_zones, zones_modifiees[0], zones_modifiees[2], n, 0); // Réduction de la probabilité d'aller de la zone 0 à la zone 2
                //message_generique(//int des modifs de zones, // peu importe, //0);  // voir avec interface.c
            }
            else { // Exclusion, ne peut pas jouer de carte si le capital a été dépensé
                carte c = demander_carte(liste_joueuses[i]); // Doit vérifier si la carte est jouable
                if (c != NULL) { // Si la joueuse veut jouer une carte
                    utilise_carte(liste_joueuses[i], c); // A modifier dans le futur, car une carte pourra augmenter le nombre de zone donc la fonction devrait prendre d'autres arguments
                    //message_generique(//int des modifs de zones, // peu importe, //0);  // voir avec interface.c
                }
            }



        /**
         * @brief Déplacement des monstres
         * 
         */
        int nombre_monstre = nb_membre_ecole(liste_joueuses[2]); // Nombre de monstres dans le jeu
        for (int j = 0; j < nombre_monstre; j += 1) {
            deplacer(getMembres(liste_joueuses[2])[j], *trouveZone(liste_zones, prochaineZone(liste_zones, zonePersonnage(getMembres(liste_joueuses[2])[j])))); // Déplacement des monstres vers leur prochaine zone
            //message_generique( //int des déplacements des monstres, //3, //zones); // voir avec interface.c
        }


        /**
         * @brief Déplacement des personnages des joueuses
         * 
         */
        for (int j = 0; j < 2; j += 1) {
            int nombre_personnage = nb_membre_ecole(liste_joueuses[j]); // Nombre de personnages dans l'école de la joueuse_(i+1)
            for (int k = 0; k < nombre_personnage; k += 1) {
                deplacer(getMembres(liste_joueuses[j])[k], *trouveZone(liste_zones, prochaineZone(liste_zones, zonePersonnage(getMembres(liste_joueuses[i])[j])))); // Déplacement des personnages vers leur prochaine zone
                //message_generique( //int des déplacements des personnages, //i, //zones); // voir avec interface.c
            }
        }

        /**
         * @brief Vérification de la présence des personnages dans les zones des monstres
         * 
         */
        for (int k = 0; k < nombre_monstre; k += 1) {
            for (int l = 0; l < 2; l += 1) {
                for (int m = 0; m < nb_membre_ecole(liste_joueuses[l]); m += 1) {
                    if (zonePersonnage(getMembres(liste_joueuses[l])[m]) == zonePersonnage(getMembres(liste_joueuses[2])[k])) {
                        estMange(getMembres(liste_joueuses[l])[m]);
                        //message_generique( //int du message de mort, //i, //m); // voir avec interface.c
                    }
                }
            }
        }
        reinitialise_capital(liste_joueuses[i]); // Réinitialisation du capital de la joueuse, à modifier dans le futur pour être plutôt une actualisation_joueuse
                                            // Par ex, actualiser le nombre de tours d'invincibilité, le nombre de tours de bonus de capital, ...
        }            

    } while(!tous_manges(liste_joueuses[0]) || !tous_manges(liste_joueuses[1]));


    /**
     * @brief Fin du jeu
     * 
     */
    message_fin_du_jeu(liste_joueuses[0], liste_joueuses[1]);
    free_joueuse(liste_joueuses[0]);    // Libération de la mémoire par appel à liberePersonnage
    free_joueuse(liste_joueuses[1]);
    free_joueuse(liste_joueuses[2]);
    libereZones(liste_zones);
    return 0;

}
