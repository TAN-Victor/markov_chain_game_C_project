/**
 * @file main.c
 * @author Victor Tan
 * @brief Fichier source avec le main
 * @necessities joueuses.h
 * @date 2023-03-06
 * 
 */

#include "joueuses.h"





int main() {

    joueuse joueuse_1 = creation_joueuse();
    joueuse joueuse_2 = creation_joueuse();
    //personnage monstre = newPersonnage();
    fprintf(stderr, "Etape 1: creation des joueuses succes.\n");

    joueuse liste_joueuses[] = { joueuse_1, joueuse_2 };

    /**
     * @brief Tant qu'aucune des deux joueuses n'a plus de personnages, ...
     * @stop Le nombre de personnages diminuera à chaque fois que le monstre mange,
     * la partie se termine lorsqu'une des deux joueuses n'a plus de personnages.
     * 
     */
    
    while(!tous_manges(joueuse_1) || !tous_manges(joueuse_2)) {

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
            printf("Choississez votre action à effectuer: \n \t * 1 : Utiliser du capital \n \t * 2 : Utiliser une carte \n \t * 3 : Directement se déplacer\n");

            while (choix < 0) {
                if (scanf("%d", &choix) != 1) {
                    while (getchar() != '\n') { // Permet de réinitialiser le choix
                        continue;
                    }
                }
                switch (choix) {
                    case 1:
                        printf("Vous avez choisi le choix n° %d.\n", choix);
                        //utiliser_capital();
                        break;
                    case 2:
                        printf("Vous avez choisi le choix n° %d.\n", choix);
                        //utiliser_carte();
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
            //moveTo(&monstre, nextZone);

    }






}