/**
 * @file interface.c
 * @author Victor TAN
 * @brief Implémentation des fonctions de "interface.h"
 *        Contiendra:
 * - \b afficher_toute_info(joueuse,joueuse,joueuse,zones) qui permet d'afficher dans la console toutes les informations du jeu: les zones du jeu, les personnages qui sont dessus, la joueuse dont c'est le tour, le capital des joueuses, ...
 * - \b demander_capital(joueuse) pour demander à une joueuse combien de capital elle veut utiliser (elle peut répondre ne pas vouloir en utiliser)
 * - \b demander_carte(joueuse) pour demander à une joueuse si elle veut jouer une carte et si oui, laquelle
 * - \b demander_zones(zones) pour demander à une joueuse sur quel zone il faudrait augmenter la probabilité et sur laquelle il faudrait la baisser à partir de la zone où elle effectue cette action
 * - \b message_fin_du_jeu(joueuse,joueuse) qui permet d'afficher dans la console un message quand le jeu est fini
 * - \b messsage_generique(int,joueuse,int) pour afficher des messages génériques (par exemple si un membre a été mangé)
 * 
 * 
 * @necessities interface.h
*/




#include "../headers/interface.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * \brief Affiche dans la console toutes les informations du jeu: les zones du jeu, les personnages qui sont dessus, la joueuse dont c'est le tour, le capital des joueuses, ...
 * \param j1, la joueuse dont c'est le tour
 * \param j2, la joueuse adverse
 * \param m, la liste des monstres
 * \param zones, l'ensemble des zones
 * \return rien
*/
void afficher_toute_info(joueuse j1, joueuse j2, joueuse m, zones liste_zones) {

        printf("\033[2J"); // Nettoyer le terminal
        printf("===================================================\n");
        printf("======= C'est le tour de la joueuse n° %d ! =======\n", j1.id); //TODO
        printf("===================================================\n"); 
        printf("Votre capital actuel: %d crédit(s)\n", j1.capital);//TODO
        printf("Votre main de cartes: \n");
        printf("Il vous reste actuellement %n membre(s)\n");
        printf("---------------------------------------------------\n");
        
        if (j1.tours_restants_bonus_capital > 0) {
            printf("Votre bonus de capital dure encore %n tour(s)\n");
        }
        if (j1.proba_par_capital > 0.1) {
            printf("Chaque unité de capital investi modifie de %n les probabilités\n");
        }
        if (j1.tours_restants_invincibilite > 0) {
            printf("Votre bonus d'invincibilité dure encore %n tour(s)\n");
        }
        if (j1.tours_restants_jouer > 1) {
            printf("Vous pouvez jouer %n tour(s)\n");
        }
        printf("---------------------------------------------------\n");

        //printf("↓ Appuyez sur la flèche du bas pour afficher les zones ↓\n");
        //printf("Appuyez sur Entrée pour continuer de jouer\n");
        //printf("---------------------------------------------------\n");
        
        printf("Vos membres d'école sont sur les zones: \n")
        for (int i = 0; i < j1.taille; i += 1) {//TODO
            printf("%2d", j1.membres[i]->zone_courante);//TODO
        }
        printf("Less membres d'école adverse sont sur les zones: \n")
        for (int i = 0; i < j2.taille; i += 1) {//TODO
            printf("%2d", j2.membres[i]->zone_courante);//TODO
        }
        printf("Le(s) monstre(s) sont sur les zones: \n")
        for (int i = 0; i < m.taille; i += 1) {//TODO
            printf("%2d", m.membres[i]->zone_courante);//TODO
        }
        printf("---------------------------------------------------\n");
}

    


/**
 * \brief Demande à une joueuse combien de capital elle souhaite utiliser (elle peut répondre ne pas vouloir en utiliser)
 *          Si la réponse est négative ou nulle, aucune action n'est réalisée
 *          Si la réponse est supérieure au capital de la joueuse, aucune action n'est réalisée
 * \param j1, la joueuse auquelle on pose la question
 * \return le nombre de capital que la joueuse souhaite dépenser, 0 sinon
*/
int demander_capital(joueuse j1) {
    int montant;
    int capital = j1.capital //TODO
    printf("Vous avez actuellement un capital de %d crédit(s): \n", capital);
    printf("Combien de capital voulez-vous utiliser ?\n Entrez un entier négatif ou nul pour annuler\n");
    scanf("%d", &montant);

    if (montant <= 0) {
        return 0
    }
    else {
        if (capital < montant) {
            fprintf(stderr, "Attention, vous n'avez pas assez de capital pour réaliser l'action.\n");
            return 0;
        }
        else {
            return montant;
        }
    }
}


/**
 * \brief Demande à une joueuse si elle veut jouer une carte qu'elle possède et si oui, laquelle
 * \param j1, la joueuse auquelle on pose la question
 * \return la carte correspondante, NULL sinon
*/
carte demander_carte(joueuse j1) {
    int choix = 0;
    int taille_main_cartes = j1.main_du_joueur->nb_cartes; //TODO
    printf("Vous avez les cartes suivantes: \n");
    for (int i = 0; i < taille_main_cartes; i += 1) {
        printf("%s  ", getName(lecture_cartes(getMains(j1), i)));
    }
    printf("\n Quelle carte voulez-vous utiliser ?\n");
    scanf("%d", &choix);

    if (choix <= 0) {
        return 0
    }
    else {
        if (taille_main_cartes < choix) {
            fprintf(stderr, "Attention, vous n'avez pas cette carte.\n");
            return 0;
        }
        else {
            return lecture_cartes(getMains(j1), choix-1);
        }
    }
}

/**
 * \brief Demande à une joueuse où elle veut augmenter la probabilité et une autre où elle doit diminuer, elle peut répondre NULL si elle veut rien modifier
 * \param zones afin de savoir sur quelle zone intéragir (un paramamètre joueuse n'est pas utile car dans le main on sait déjà sur quelle joueuse demander)
 * \return un tableau contenant 3 int représentant le numéro de la zone de départ et 2 zones où la probabilité est à modifier(le premier sera celle à augmenter et le deuxième celle à diminuer), NULL sinon
*/
int* demander_zones(zones liste_zones) {
    int choix_a_augmenter = -1;
    int choix_a_diminuer = -1;
    int choix_depart = -1;
    int nombre_de_zones = NB_DE_ZONES;
    printf("Choissez une zone de départ entre 1 et %d: \n", nombre_de_zones);
    scanf("%d", &choix_depart);
    if (choix_depart <= 0 || choix_depart > nombre_de_zones) {
        fprintf(stderr, "Attention, vous n'avez pas entré une zone correcte.\n");
        return null;
    }
    printf("Choisissez une zone dont vous souhaitez AUGMENTER la probabilité entre 1 et %d: \n", nombre_de_zones);
    scanf("%d", &choix_a_augmenter);

    if (choix_a_augmenter <= 0 || choix_a_augmenter > nombre_de_zones) {
        fprintf(stderr, "Attention, vous n'avez pas entré une zone correcte.\n");
        return null;
    }
    else {
        printf("Vous avez choisi la zone %d; \n Choisissez une zone dont vous souhaitez DIMINUER la probabilité entre 1 et %d (%d exclu): \n", choix_a_augmenter, nombre_de_zones, choix_a_diminuer);
        if (choix_a_diminuer <= 0 || choix_a_diminuer > nombre_de_zones) {
            fprintf(stderr, "Attention, vous n'avez pas entré une zone correcte.\n");
            return null;
        }
        else {
            printf("Vous avez choisi la zone %d. \n", choix_a_diminuer);
            int *triplet = [choix_depart, choix_a_augmenter, choix_a_diminuer];
            return triplet;
        }
    }
}

/**
 * \brief Affiche dans la console un message quand le jeu est fini
 * \param joueuse,joueuse afin d'avoir les informations si tout les membres de l'école d'une joueuse ont été mangés
 * \return rien
*/
void message_fin_du_jeu(joueuse j1, joueuse j2) {
    printf("\033[2J"); // Nettoyer le terminal
    printf("===================================================\n");
    printf("============ La partie est terminée !! ============\n");
    printf("===================================================\n");
    if (tous_manges(j1)) {
        printf("C'est la joueuse 2 qui gagne ! Il lui reste %d personnages !\n", j2->taille); //TODO
    } 
    else {
        printf("C'est la joueuse 1 qui gagne ! Il lui reste %d personnages !\n", j1->taille); //TODO
    }
}

/**
* \brief Affiche des messages génériques
* \param int Numéro du message à afficher
* \param joueuse Joueuse concernéé par le message
* \param int* Index du personnage de la joueuse ou index du numéro de carte utilisé, ... m=0 lorsqu'il n'est pas utile
*/
void message_generique(int n, joueuse j1, int* option, carte option2) {
    switch (n) {
        case 1: fprintf(stderr, "Les personnages ont été correctement initialisés. \n");
                break;
        case 2: fprintf(stderr, "Les zones ont été correctement initialisés. \n");
                break;
        case 3: printf("La joueuse n° %d a utilisé %d de capital. \n", j1->id, option[0]); //TODO
                break;
        case 4: printf("La probabilité de passer de la zone %d à la zone %d a changé de %d. \n", option[0], option[1], option[2]);
                break;
        case 5: printf("La joueuse n° %d a utilisé la carte %s", j1->id, getName(option2)); //TODO
                break;
        case 6: printf("Tous les personnages ont bougé. \n");
                break;
        case 7: printf("Le personnage n° %d de la joueuse n° %d a été mangé. \n", option[0], j1->id); //TODO
                break;
        case 8: printf("Le tour est terminé, le capital a été réintialisé. \n");
                break;
        case 9: fprintf(stderr, "Les personnages ont été correctement libéré par free(). \n");
                break;
        case 10: fprintf(stderr, "Les zones ont été correctement libérées par free(). \n");
                break;
    }
}


