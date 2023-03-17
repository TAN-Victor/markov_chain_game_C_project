/**
 * @file main.c
 * @author Victor Tan
 * @brief Fichier source avec le main
 * @necessities joueuses.h
 * @date 2023-03-06
 * 
 */

#include "joueuses.h"

#include <stdio.h>
#include <stdlib.h>




int main() {

    joueuse* joueuse_1 = creation_joueuse();
    joueuse* joueuse_2 = creation_joueuse();
    joueuse* monstres = creation_joueuse();
    fprintf(stderr, "Etape 1: creation des joueuses succes.\n");

    joueuse* liste_joueuses[3] = { joueuse_1, joueuse_2, monstres };


    zones* liste_zones = nouvellesZones();


    /**
     * @brief Tant qu'aucune des deux joueuses n'a plus de personnages, ...
     * @stop Le nombre de personnages diminuera à chaque fois que le monstre mange,
     * la partie se termine lorsqu'une des deux joueuses n'a plus de personnages.
     * 
     */
    
    while(!tous_manges(&joueuse_1) || !tous_manges(&joueuse_2)) {

        for (int i = 0; i < 2; i += 1) {

            /**
             * @brief Information du jeu
             * 
             */
            printf("C'est le tour du joueur n° %d, qui a un capital de %d points. \n", i, liste_joueuses[i]->capital);

            /**
             * @brief Choix d'une action
             * 
             */

            int choix = -1;
            printf("Choississez votre action à effectuer: \n \t * 1 : Utiliser du capital \n \t * 2 : Utiliser une carte \n \t * 3 : Ne rien faire \n");

            while (choix < 0) {
                if (scanf("%d", &choix) != 1) {
                    while (getchar() != '\n') { // Permet de réinitialiser le choix
                        continue;
                    }
                }
                switch (choix) {
                    case 1:
                        printf("Vous avez choisi le choix n° %d.\n", choix);
                        int* zones_modifiees = demander_zones(*liste_zones);
                        int n = demander_capital(liste_joueuses[i]);
                        utilise_capital(liste_joueuses[i], n);
                        modifierZone(zones_modifiees[0], zones_modifiees[1], n, 1); // action = 1 pour augmenter la proba
                        modifierZone(zones_modifiees[0], zones_modifiees[2], n, 0); // action = 0 pour réduire la proba
                        //message_generique(//int des modifs de zones, //peu importe, //0); // voir avec le interface.c, pas très important pour l'instant
                        break;
                    case 2:
                        printf("Vous avez choisi le choix n° %d.\n", choix);
                        carte c = demander_carte(liste_joueuses[i]);   // à vérifier
                        //utiliser_carte(liste_joueuses[i], c); // à vérifier
                        //effet_carte(); // à vérifier
                        //message_generique(//int modifs carte, liste_joueuses[i], //un numéro); // voir avec le interface.c, pas très important pour l'instant
                        break;
                    case 3:
                        printf("Vous avez choisi le choix n° %d.\n", choix);
                        break;
                    default:
                        printf("Désolé, veuillez entrer un choix correct.\n");
                        choix = -1;
                        break;
                }
            }
            //deplacement_tout_le_monde(liste_joueuses, *liste_zones);
            //manger(liste_joueuses);

        }



    }

    return 0;

}