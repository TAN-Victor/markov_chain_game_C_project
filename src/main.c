/**
 * @file main.c
 * @author Victor Tan
 * @brief Fichier source avec le main
 * @necessities effets.h
 * @date 2023-03-06
 * 
 */

#include "../headers/effets.h"






int main() {

    /**
     * @brief Création de la liste_cartes_global
     * 
     */
    liste_cartes liste_cartes_global = creer_liste_cartes_global();
        for (int i = 0; i < 20; i += 1) {
        printf("CARTE %d : %s \n",i, getNom(getCartes(liste_cartes_global)[i]));
        printf("EFFET: %s \n", getDescription(getCartes(liste_cartes_global)[i]));
        fflush(stdout);
    }
    /**
     * @brief Création de 3 "joueuses"; l'ensemble des monstres correspondra à une joueuse 
     * 
     */
    joueuse joueuse_1 = creation_joueuse(1, liste_cartes_global); // 1 pour dire que l'on crée une joueuse jouable n°1
    joueuse joueuse_2 = creation_joueuse(2, liste_cartes_global); // 2 pour dire que l'on crée une joueuse jouable n°2
    joueuse monstres = creation_joueuse(0, liste_cartes_global); // 0 pour dire que l'on crée une liste de monstres, il n'y aura qu'un seul monstre au début

    joueuse liste_joueuses[3] = { joueuse_1, joueuse_2, monstres }; // Mettre les monstres et les joueuses ensemble permettra de les faire déplacer tous ensemble avec une même fonction
    message_generique(1, NULL, NULL, NULL); // Les messages génériques sont là pour afficher des messages à l'écran, ils sont définis dans interface.c. Ici, le message dit que les joueuses sont bien créees.
    /**
     * @brief Création des Zones du jeu (10 au début)
     * 
     */
    zones liste_zones = nouvellesZones();
    message_generique(2, NULL, NULL, NULL); // Le message dit que les zones sont bien créees.



    int i = -1; // Va valoir 0 si c'est le tour de la joueuse 1, 1 si c'est le tour de la joueuse 2
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
        // la joueuse i est donc celle qui joue, et sera en 1er argument des fonctions
    
            /**
             * @brief Affiche toutes les informations actuelles du jeu 
             * 
             */
            afficher_toute_info(liste_joueuses[i], liste_joueuses[(i+1)%2],liste_joueuses[2], liste_zones); // Affiche les joueuses, les monstres, les zones et qui sont sur les zones
            // Le message est très simpliste, mais il permet de voir si les fonctions marchent bien + sera utilisé pour l'interface graphique du lot C
            
            

            /**
             * @brief Modification du plateau de jeu par utilisation du capital ou d'une carte
             * 
             */
            int n = demander_capital(liste_joueuses[i]); // Demande un nombre de capital à utiliser que la joueuse possède (teste si la joueuse a assez de capital)
            if (n > 0) { // Si la joueuse veut utiliser son capital
                int zone_depart = demander_zones_depart(liste_zones);
                int zone_arrivee_augmenter = demander_zones_arrivee_augmenter(liste_zones); // Zone vers laquelle la proba d'aller à partir de zone_depart augmente
                int zone_arrivee_diminuer = demander_zones_arrivee_diminuer(liste_zones, zone_arrivee_augmenter); // Zone vers laquelle la proba d'aller à partir de zone_depart diminue
                utilise_capital(liste_joueuses[i], n); // Retire le capital demandé
                message_generique(3, liste_joueuses[i], &n, NULL); // Message générique qui dit que la joueuse a utilisé son capital
                int proba_par_capital = getProbaParCapital(liste_joueuses[i]); // Récupère le nombre de proba par capital de la joueuse, qui peut être modifié par une carte
                int m = n * proba_par_capital; // m est la proba à ajouter ou à retirer
                modifierZone(liste_zones, zone_depart, zone_arrivee_augmenter, m, 1); // Augmentation de la probabilité d'aller de la zone 0 à la zone 1
                modifierZone(liste_zones, zone_depart, zone_arrivee_diminuer, m, 0); // Réduction de la probabilité d'aller de la zone 0 à la zone 2
                int triplet_augmenter[3] = {zone_depart, zone_arrivee_augmenter, m}; // Triplet qui sera utilisé aux lignes 88 et 89
                int triplet_diminuer[3] = {zone_depart, zone_arrivee_diminuer, -m};
                message_generique(4, NULL, triplet_augmenter, NULL);
                message_generique(4, NULL, triplet_diminuer, NULL);
            }
            else { // Exclusion, ne peut pas jouer de carte si le capital a été dépensé
                carte c = demander_carte(liste_joueuses[i]); // Doit vérifier si la carte est jouable
                if (c != NULL) { // Si la joueuse veut jouer une carte
                    message_generique(5, liste_joueuses[i], NULL, c);  // voir avec interface.c
                    utilise_carte(liste_joueuses[i], c); 
                    wrapper_pouvoir_carte(liste_joueuses, liste_zones, getNom(c));
                }
            }



        /**
         * @brief Déplacement des monstres
         * 
         */
        int nombre_monstre = nb_membre_ecole(liste_joueuses[2]); // Nombre de monstres dans le jeu
        for (int j = 0; j < nombre_monstre; j += 1) {
            if (getPeutSeDeplacer(getMembres(liste_joueuses[2])[j]) == 1 && getStatut(getMembres(liste_joueuses[2])[j]) == 1) {
                for (int k = 0; k < getNbPas(getMembres(liste_joueuses[2])[j]); k += 1) { // Le monstre se déplace nb_pas fois
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
                    // Si le personnage peut se déplacer et ( qu'il est vivant ou (qu'il est un FIPA))
                    for (int l = 0; l < getNbPas(getMembres(liste_joueuses[j])[k]); l += 1) {    
                        deplacer(getMembres(liste_joueuses[j])[k], trouveZone(liste_zones, prochaineZone(liste_zones, zonePersonnage(getMembres(liste_joueuses[i])[j])))); // Déplacement des personnages vers leur prochaine zone
                    }
                }
            }
        }
        message_generique(6, NULL, NULL, NULL); // Dit simplement que les personnages se sont déplacés mais pas où
        afficher_toute_info(liste_joueuses[i], liste_joueuses[(i+1)%2],liste_joueuses[2], liste_zones); // Affiche les joueuses, les monstres, les zones et qui sont sur les zones


        /**
         * @brief Vérification de la présence des personnages dans les zones des monstres; pour les manger
         * 
         */
        for (int k = 0; k < nombre_monstre; k += 1) {
            for (int l = 0; l < 2; l += 1) {
                for (int m = 0; m < nb_membre_ecole(liste_joueuses[l]); m += 1) {
                    if (zonePersonnage(getMembres(liste_joueuses[l])[m]) == zonePersonnage(getMembres(liste_joueuses[2])[k])) {
                        if (getToursInvincibilite(liste_joueuses[l]) == 0 && (getStatut(getMembres(liste_joueuses[l])[m]) == 1 || getStatut(getMembres(liste_joueuses[l])[m]) == 3)) {
                            // Si le personnage n'est pas invincible et (qu'il est vivant ou qu'il est un FIPA)
                            estMange(getMembres(liste_joueuses[l])[m]);
                            message_generique(7, liste_joueuses[l], &m, NULL); // Dit quel personnage a été mangé
                        }
                    }
                }
            }
        }


        int tours_restants_bonus_capital = getToursRestantsBonusCapital(liste_joueuses[i]);
        int tours_restants_invincibilite = getToursInvincibilite(liste_joueuses[i]);
        int tours_restants_jouer = getToursRestantsJouer(liste_joueuses[i]);
        int tours_restants_bonus_proba_par_capital = getToursRestantsBonusProbaParCapital(liste_joueuses[i]);
        if (tours_restants_bonus_capital > 0) {
            setToursRestantsBonusCapital(liste_joueuses[i], tours_restants_bonus_capital - 1); // Diminution du nombre de tours restants pour le bonus de capital
        }
        if (tours_restants_bonus_capital == 0) {
            reinitialise_capital(liste_joueuses[i]); // Réinitialisation du capital si le nombre de tours restants pour le bonus de capital est égal à 0
        }
        if (tours_restants_invincibilite > 0) {
            setToursRestantsInvincibilite(liste_joueuses[i], tours_restants_invincibilite - 1); // Diminution du nombre de tours restants pour l'invincibilité
        }
        if (tours_restants_jouer > 0) {
            setToursRestantsJouer(liste_joueuses[i], tours_restants_jouer - 1); // Diminution du nombre de tours restants pour jouer
        }
        if (tours_restants_jouer == 0) { // Si le nombre de tours restants pour jouer est égal à 0, c'est au tour de l'autre joueuse
            setTour(liste_joueuses[i], 0);
            setTour(liste_joueuses[(i+1)%2], 1);
        }
        if (tours_restants_bonus_proba_par_capital > 0) {
            setToursRestantsBonusProbaParCapital(liste_joueuses[i], tours_restants_bonus_proba_par_capital - 1); // Diminution du nombre de tours restants pour le bonus de probabilité par capital
        }
        if (tours_restants_bonus_proba_par_capital == 0) {
            setProbaParCapital(liste_joueuses[i], PROBA_PAR_CAPITAL); // Réinitialisation du bonus de probabilité par capital si le nombre de tours restants pour le bonus de probabilité par capital est égal à 0
        }
        setBonusTemporaire(liste_joueuses[i], 0); // Réinitialisation du bonus temporaire

        for (int j = 0; j < getTaille(liste_joueuses[i]); i += 1) { // Permet aux FIPA de se déplacer (ou non) + permet aux personnages vivants qui ne pouvaient pas se déplacer, de se déplacer
            if (getStatut(getMembres(liste_joueuses[i])[j]) == 3) {
                setPeutSeDeplacer(getMembres(liste_joueuses[i])[j], (getPeutSeDeplacer(getMembres(liste_joueuses[i])[j]) + 1)%2); // Inversion de la possibilité de jouer du FIPA
            }
            if (getStatut(getMembres(liste_joueuses[i])[j]) == 1 && getPeutSeDeplacer(getMembres(liste_joueuses[i])[j]) == 0) {
                setPeutSeDeplacer(getMembres(liste_joueuses[i])[j], 1); // Re-permet aux personnages vivants de se déplacer
            }
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
