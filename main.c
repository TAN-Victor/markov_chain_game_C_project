/**
 * @file main.c
 * @author Victor Tan
 * @brief Fichier source avec le main
 * @necessities interface.h
 * @date 2023-03-06
 * 
 */

#include "interface.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int main() {

    /**
     * @brief Création de 3 "joueuses"; l'ensemble des monstres correspondra à une joueuse 
     * 
     */
    joueuse* joueuse_1 = creation_joueuse(1); // 1 pour dire que l'on crée une joueuse jouable
    joueuse* joueuse_2 = creation_joueuse(1); // 1 pour dire que l'on crée une joueuse jouable
    joueuse* monstres = creation_joueuse(0); // 0 pour dire que l'on crée une liste de monstres, il n'y aura qu'un seul monstre au début
    fprintf(stderr, "Etape 1: creation des joueuses succes.\n"); // debug

    joueuse* liste_joueuses[3] = { joueuse_1, joueuse_2, monstres };

    /**
     * @brief Création des Zones du jeu (10 au début)
     * 
     */
    zones* liste_zones = nouvellesZones();

    struct carte A;
    A.nom = "A";
    A.description = "Description A";
    carte liste_cartes[1] = { &A }; // A compléter plus tard avec l'ensemble des cartes, avec une fonction dans le main ou dans cartes.c

    


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
            afficher_toute_info(*liste_joueuses[i], *liste_joueuses[(i+1)%2], *liste_zones);
            int n = demander_capital(*liste_joueuses[i]);

            if (n > 0) {
                int* zones_modifiees = demander_zones(*liste_zones);
                utilise_capital(liste_joueuses[i], n);
                modifierZone(zones_modifiees[0], zones_modifiees[1], n, 1);
                modifierZone(zones_modifiees[0], zones_modifiees[2], n, 0);
                //message_generique(//int des modifs de zones, // peu importe, //0);  // voir avec interface.c
            }
            else { // Exclusion, ne peut pas jouer de carte si le capital a été dépensé
                int c = demander_carte(*liste_joueuses[i]);
                if (c != -1) {  // Sujet à modification, lorsque l'on choisit une carte qui est correcte
                    utilise_carte(liste_joueuses[i], liste_cartes[c]);
                    //message_generique(//int des modifs de zones, // peu importe, //0);  // voir avec interface.c
                }
            }
            deplacement_tout_le_monde(*liste_joueuses, *liste_zones); // Fonction qui n'est pas dans le sujet mais à implémenter en appelant plusieurs fois les déplacements
            manger(*liste_joueuses); // Fonction qui n'est pas dans le sujet mais à implémenter en appelant plusieurs fois les tests de positions
            reinitialise_capital(liste_joueuses[i]); // à modifier à "actualiser_joueuse", comme par exemple réduire le nombre de tours d'invinsibilité"
        }



    } while(!tous_manges(liste_joueuses[0]) || !tous_manges(liste_joueuses[1]));

    message_fin_du_jeu(*liste_joueuses[0], *liste_joueuses[1]);
    free_joueuse(liste_joueuses[0]);
    free_joueuse(liste_joueuses[1]);
    return 0;

}