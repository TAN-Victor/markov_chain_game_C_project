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



/**
 * \brief Affiche dans la console toutes les informations du jeu: les zones du jeu, les personnages qui sont dessus, la joueuse dont c'est le tour, le capital des joueuses, ...
 * \param j1, la joueuse dont c'est le tour
 * \param j2, la joueuse adverse
 * \param m, la liste des monstres
 * \param zones, l'ensemble des zones
 * \return rien
*/
void afficher_toute_info(joueuse j1, joueuse j2, joueuse m, zones liste_zones) {

        //printf("\033[2J"); // Nettoyer le terminal
        printf("=======================================================================================\n");
        printf("========================= C'est le tour de la joueuse n° %d ! =========================\n", getIdJoueuse(j1));
        printf("=======================================================================================\n"); 
        printf("Votre capital actuel: %d crédit(s)\n", getCapital(j1));
        printf("Votre main de cartes: ");
        for (int i = 0; i < getNbCartes(j1->main_du_joueur); i += 1) {
            printf("[%d] %s; ", i+1, getNom(lecture_cartes(j1->main_du_joueur, i)));
        }
        printf("\n");
        printf("Il vous reste actuellement %d membre(s)\n", getTaille(j1));
        printf("---------------------------------------------------\n");
        
        if (getToursRestantsBonusCapital(j1) > 0) {
            printf("Votre bonus de capital dure encore %d tour(s)\n", getToursRestantsBonusCapital(j1));
        }
        if (getProbaParCapital(j1) > 0.1) {
            printf("Chaque unité de capital investi modifie de %f les probabilités\n", getProbaParCapital(j1));
        }
        if (getToursInvincibilite(j1) > 0) {
            printf("Votre bonus d'invincibilité dure encore %d tour(s)\n", getToursInvincibilite(j1));
        }
        if (getToursRestantsJouer(j1) > 1) {
            printf("Vous pouvez jouer %d tour(s)\n", getToursRestantsJouer(j1));
        }
        if (getBonusTemporaire(j1) != 0) {
            printf("Vous avez un bonus temporaire: %d\n", getBonusTemporaire(j1));
        }
        printf("---------------------------------------------------\n");

        //printf("↓ Appuyez sur la flèche du bas pour afficher les zones ↓\n");
        //printf("Appuyez sur Entrée pour continuer de jouer\n");
        //printf("---------------------------------------------------\n");
        
        printf("Vos membres d'école sont sur les zones: \n");  // Pourrait être modifiée par une meilleure interface
        for (int i = 0; i < getTaille(j1); i += 1) {
            printf("         %d (", getStatut(getMembres(j1)[i]));
            if (getStatut(getMembres(j1)[i]) == 1 || getStatut(getMembres(j1)[i]) == 3) {   //Si le membre est en vie
                printf("%2d", getZoneCourante(getMembres(j1)[i]));
            }
        }
        printf("\n");
        printf("Les membres d'école adverse sont sur les zones: \n");
        for (int i = 0; i < getTaille(j2); i += 1) {
            printf("          %d (", getStatut(getMembres(j2)[i]));
            if (getStatut(getMembres(j2)[i]) == 1 || getStatut(getMembres(j2)[i]) == 3) {  //Si le membre est en vie
                printf("%2d", getZoneCourante(getMembres(j2)[i]));
            }
        }
        printf("\n");
        printf("Le(s) monstre(s) sont sur les zones: \n");
        for (int i = 0; i < getTaille(m); i += 1) {
            printf("%2d", getZoneCourante(getMembres(m)[i]));
        }
        printf("\n");
        printf("Il y a %d zones. \n", getTailleMatrice(getMatrice(liste_zones)));

        printf("---------------------------------------------------\n");

        for (int i = 0; i < getTailleMatrice(getMatrice(liste_zones)); i += 1) {
            printf("%d: ",getNumero(getTabZones(liste_zones)[i]) + 1);
            for (int j = 0; j < getTailleMatrice(getMatrice(liste_zones)); j += 1) {
                printf("%.2f ", lecture_probas(getMatrice(liste_zones), i, j));
                fflush(stdout);
            }
            printf("\n");
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
    int capital = getCapital(j1);
    printf("Vous avez actuellement un capital de %d crédit(s): \n", capital);
    while (1)  {
        printf("Combien de capital voulez-vous utiliser ?\n Entrez un entier négatif ou nul pour annuler\n");
        if (scanf("%d", &montant) != 1) {
            fprintf(stderr, "Erreur : la saisie doit être un nombre entier\n");
            while (getchar() != '\n');
        } else if (montant > capital) {
            fprintf(stderr, "Attention, vous n'avez pas assez de capital pour réaliser l'action.\n");
        } else if (montant <= 0) {
            fprintf(stderr, "Vous avez décidé de ne pas utiliser de capital.\n");
            return 0;
        } else {
            break;
        }
    }
    return montant;
    
}


/**
 * \brief Demande à une joueuse si elle veut jouer une carte qu'elle possède et si oui, laquelle
 * \param j1, la joueuse auquelle on pose la question
 * \return la carte correspondante, NULL sinon
*/
carte demander_carte(joueuse j1) {
    int choix = 0;
    int taille_main_cartes = getNbCartes(getMain(j1));
    printf("Vous avez les cartes suivantes: \n");
    for (int i = 0; i < taille_main_cartes; i += 1) {
        printf("%d] %s\n", i+1, getNom(lecture_cartes(getMain(j1), i)));
    }
    while (1) {
        printf("\n Quelle carte voulez-vous utiliser ?\n");
        if (scanf("%d", &choix) != 1) {
            fprintf(stderr, "Erreur : la saisie doit être un nombre entier\n");
            while (getchar() != '\n');
        }
        else if (taille_main_cartes < choix) {
            fprintf(stderr, "Attention, vous n'avez pas cette carte.\n");
        }
        else if (choix <= 0) {
            fprintf(stderr, "Vous avez décidé de ne pas utiliser de carte.\n");
            return NULL;
        }
        else {
            break;
        }
    }
    return lecture_cartes(getMain(j1), choix-1);
}


/**
 * \brief Demande à une joueuse le numéro de la zone de départ dont elle veut modifier les probabilités d'accéder à une autre zone 
 * \param zones afin de savoir sur quelle zone intéragir
 * \return le numéro de la zone entre 1 et la taille de la liste - 1 pour avoir son indice dans la liste
*/
int demander_zones_depart(zones liste_zones) {
    int choix_depart = -1;
    int nombre_de_zones = getTailleMatrice(getMatrice(liste_zones));
    while (1) {
        printf("Choissez une zone de départ entre 1 et %d: \n", nombre_de_zones);
        if (scanf("%d", &choix_depart) != 1) {
            fprintf(stderr, "Erreur : la saisie doit être un nombre entier\n");
            while (getchar() != '\n');
        }
        else if (choix_depart <= 0 || choix_depart > nombre_de_zones) {
            fprintf(stderr, "Attention, cette zone n'existe pas.\n");
        }
        else {
            break;
        }
    }
    return (choix_depart-1);
}

/**
 * \brief Demande à une joueuse le numéro de la zone d'arrivée dont elle veut augmenter les probabilités d'accéder à cette zone
 * \param zones afin de savoir sur quelle zone intéragir
 * \return le numéro de la zone entre 1 et la taille de la liste - 1 pour avoir son indice dans la liste
*/
int demander_zones_arrivee_augmenter(zones liste_zones) {
    int choix_a_augmenter = -1;
    int nombre_de_zones = getTailleMatrice(getMatrice(liste_zones));
    while (1) {
        printf("Choisissez une zone dont vous souhaitez AUGMENTER la probabilité entre 1 et %d: \n", nombre_de_zones);
        if (scanf("%d", &choix_a_augmenter) != 1) {
            fprintf(stderr, "Erreur : la saisie doit être un nombre entier\n");
            while (getchar() != '\n');
        }
        else if (choix_a_augmenter <= 0 || choix_a_augmenter > nombre_de_zones) {
            fprintf(stderr, "Attention, cette zone n'existe pas.\n");
        }
        else {
            break;
        }
    }
    return (choix_a_augmenter-1);
}

/**
 * \brief Demande à une joueuse le numéro de la zone d'arrivée dont elle veut diminuer les probabilités d'accéder à une autre zone
 *          La zone doit être différente de la zone d'arrivée dont on veut augmenter la probabilité
 * \param zones afin de savoir sur quelle zone intéragir
 * \return le numéro de la zone entre 1 et la taille de la liste - 1 pour avoir son indice dans la liste
*/
int demander_zones_arrivee_diminuer(zones liste_zones, int zone_augmentee) {
    int choix_a_diminuer = -1;
    int nombre_de_zones = getTailleMatrice(getMatrice(liste_zones));
    while (1) {
        printf("Choisissez une zone dont vous souhaitez DIMINUER la probabilité entre 1 et %d (%d exclu): \n", nombre_de_zones, zone_augmentee + 1);
        if (scanf("%d", &choix_a_diminuer) != 1) {
            fprintf(stderr, "Erreur : la saisie doit être un nombre entier\n");
            while (getchar() != '\n');
        }
        else if (choix_a_diminuer <= 0 || choix_a_diminuer > nombre_de_zones) {
            fprintf(stderr, "Attention, cette zone n'existe pas.\n");
        }
        else if (choix_a_diminuer == zone_augmentee + 1) {
            fprintf(stderr, "Attention, vous ne pouvez pas choisir la même zone que celle dont vous voulez augmenter la probabilité.\n");
        }
        else {
            break;
        }
    }
    return (choix_a_diminuer-1);
}

/**
 * \brief Demande à une joueuse le numéro d'une autre zone que zone_depart
 * \param zones afin de savoir sur quelle zone intéragir
 * \param zone_depart afin de savoir quelle zone ne pas proposer
 * \return le numéro de la zone entre 1 et la taille de la liste - 1 pour avoir son indice dans la liste
*/
int demander_zones_autre(zones liste_zones, int zone_depart) {
    int choix = -1;
    int nombre_de_zones = getTailleMatrice(getMatrice(liste_zones));
    while (1) {
        printf("Choissez une zone entre 1 et %d (%d exclu): \n", nombre_de_zones, zone_depart);
        if (scanf("%d", &choix) != 1) {
            fprintf(stderr, "Erreur : la saisie doit être un nombre entier\n");
            while (getchar() != '\n');
        }
        else if (choix <= 0 || choix > nombre_de_zones) {
            fprintf(stderr, "Attention, cette zone n'existe pas.\n");
        }
        else if (choix == zone_depart) {
            fprintf(stderr, "Attention, vous ne pouvez pas choisir la même zone que celle de départ.\n");
        }
        else {
            break;
        }
    }
    return (choix-1);
}


/**
 * \brief Demande à une joueuse le numéro d'un personnage de la joueuse (ou liste de monstres) 
 * \param joueuse afin de savoir sur quelle joueuse ou liste de monstres intéragir
 * \return le numéro du personnage entre 1 et la taille de la liste - 1 pour avoir son indice dans la liste
*/
int demander_personnage(joueuse j1) {
    int choix = -1;
    int taille = getTaille(j1);
    while (1) {
        printf("Choissez un personnage entre 1 et %d: \n", taille);
        if (scanf("%d", &choix) != 1) {
            fprintf(stderr, "Erreur : la saisie doit être un nombre entier\n");
            while (getchar() != '\n');
        }
        else if (choix <= 0 || choix > taille) {
            fprintf(stderr, "Attention, ce personnage n'existe pas.\n");
        }
        else {
            break;
        }
    }
    return (choix-1);
}


/**
 * \brief Demande à une joueuse quelle probabilité par capital elle souhaite avoir entre 0.1 et 1
 * \return la valeur de probabilité par capital que la joueuse souhaite avoir
*/
float demander_proba_par_capital() {
    float choix = -1.;
    while (1) {
        printf("Choissez une probabilité par capital entre 0.1 et 1: \n");
        if (scanf("%f", &choix) != 1) {
            fprintf(stderr, "Erreur : la saisie doit être un nombre décimal multiple de 0.1\n");
            while (getchar() != '\n');
        }
        else if (choix < 0.1 || choix > 1) {
            fprintf(stderr, "Attention, cette probabilité n'est pas comprise entre 0.1 et 1.\n");
        }
        else if (fabs( choix * 10 - floor(choix * 10)) > 0.0001) {
            fprintf(stderr, "Attention, cette probabilité n'est pas multiple de 0.1.\n");
        }
        else {
            break;
        }
    }   
    return 0.1 * floor(choix * 10); // Pour convertir en un multiple de 0.1 exactement
}


/**
 * \brief Affiche dans la console un message quand le jeu est fini
 * \param joueuse,joueuse afin d'avoir les informations si tout les membres de l'école d'une joueuse ont été mangés
 * \return rien
*/
void message_fin_du_jeu(joueuse j1, joueuse j2) {
    //printf("\033[2J"); // Nettoyer le terminal
    printf("===================================================\n");
    printf("============ La partie est terminée !! ============\n");
    printf("===================================================\n");
    if (tous_manges(j1)) {
        int sum = 0;
        for (int i = 0; i < getTaille(j1); i++) {
            if (getStatut(getMembres(j2)[i]) != 0) {
                sum  += 1;
            }
        }
        printf("C'est la joueuse 2 qui gagne ! Il lui reste %d personnages !\n", sum);
    } 
    else {
        int sum = 0;
        for (int i = 0; i < getTaille(j1); i++) {
            if (getStatut(getMembres(j2)[i]) != 0) {
                sum  += 1;
            }
        }
        printf("C'est la joueuse 1 qui gagne ! Il lui reste %d personnages !\n", sum);
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
        case 3: printf("La joueuse n° %d a utilisé %d de capital. \n", getIdJoueuse(j1), option[0]);
                break;
        case 4: printf("La probabilité de passer de la zone %d à la zone %d a changé de %.2f. \n", option[0], option[1], option[2]*0.1);
                break;
        case 5: printf("La joueuse n° %d a utilisé la carte %s", getIdJoueuse(j1), getNom(option2));
                break;
        case 6: printf("Tous les personnages ont bougé. \n");
                break;
        case 7: printf("Le personnage n° %d de la joueuse n° %d est décédé. \n", option[0], getIdJoueuse(j1));
                break;
        case 8: printf("Le tour est terminé, le capital et les effets des joueuses ont été réintialisés. \n");
                break;
        case 9: fprintf(stderr, "Les personnages ont été correctement libéré par free(). \n");
                break;
        case 10: fprintf(stderr, "Les zones ont été correctement libérées par free(). \n");
                break;
        case 100: fprintf(stderr, "Attention, la probabilité de la zone n'est plus dans l'intervalle [0, 1]. L'action a été annulée. \n");
                break;
    }
}


