/**
 * @file main.c
 * @author Victor Tan
 * @brief Fichier source avec le main
 * @necessities joueuses.h
 * @date 2023-03-06
 * 
 */

#include "interface.h"

#include <stdio.h>
#include <stdlib.h>




int main() {

    /**
     * @brief Création de 3 "joueuses" car l'ensemble des monstres correspondra à une joueuse 
     * 
     */
    joueuse* joueuse_1 = creation_joueuse();
    joueuse* joueuse_2 = creation_joueuse();
    joueuse* monstres = creation_joueuse();
    fprintf(stderr, "Etape 1: creation des joueuses succes.\n"); // debug

    joueuse* liste_joueuses[3] = { joueuse_1, joueuse_2, monstres };

    /**
     * @brief Création des Zones du jeu (10 au début)
     * 
     */
    zones* liste_zones = nouvellesZones();


    /**
     * @brief Tant qu'aucune des deux joueuses n'a plus de personnages, le jeu continue
     * @stop Le nombre de personnages diminuera à chaque fois que le monstre mange,
     * la partie se termine lorsqu'une des deux joueuses n'a plus de personnages.
     * 
     */
    
    while(!tous_manges(liste_joueuses[0]) || !tous_manges(liste_joueuses[1])) {

        /**
         * @brief Alternance entre les 2 joueuses
         * 
         */
        for (int i = 0; i < 2; i += 1) {

    
            /**
             * @brief Affiche toutes les informations actuelles du jeu 
             * 
             */
            afficher_toute_info(liste_joueuses[i], liste_joueuses[(i+1)%2], *liste_zones);
            int n = demander_capital(liste_joueuses[i]);

            if (n > 0) {
                int zones_modifiees = demander_zones(*liste_zones);
                utilise_capital(liste_joueuses[i], n);
                modifierZone(zones_modifiees[0], zones_modifiees[1], n, 1);
                modifierZone(zones_modifiees[0], zones_modifiees[2], n, 0);
                //message_generique(//int des modifs de zones, // peu importe, //0);  // voir avec interface.c
            }
            else { // Exclusion, ne peut pas jouer de carte si le capital a été dépensé
                carte c = demander_carte(liste_joueuses[i]);
                if (c == NULL) {  // Sujet à modification, lorsque l'on choisit une carte qui est correcte
                    utilise_carte(liste_joueuses[i], c);
                    //message_generique(//int des modifs de zones, // peu importe, //0);  // voir avec interface.c
                }
            }
            deplacement_tout_le_monde(liste_joueuses, *liste_zones);
            manger(liste_joueuses);
            reinitialise_capital(liste_joueuses[i]);
        }



    }

    message_fin_du_jeu(*liste_joueuses[0], *liste_joueuses[1]);
    free_joueuse(liste_joueuses[0],liste_joueuses[1]);

    return 0;

}