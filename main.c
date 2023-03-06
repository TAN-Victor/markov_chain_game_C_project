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

    joueuse_1 = creation_joueuse();
    joueuse_2 = creation_joueuse();
    fprintf(stderr, "Etape 1: creation des joueuses succes.\n");


    /**
     * @brief Tant qu'aucune des deux joueuses n'a plus de personnages, ...
     * @stop Le nombre de personnages diminuera à chaque fois que le monstre mange,
     * la partie se termine lorsqu'une des deux joueuses n'a plus de personnages.
     * 
     */
    while(!tous_manges(joueuse_1) || !tous_manges(joueuse_2)) {

        for 

    }






}