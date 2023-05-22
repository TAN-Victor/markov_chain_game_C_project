/**
 * @file effets.c
 * @author Victor Tan
 * @brief Fichier d'implémentation des effets de cartes
 * @necessities effets.h
 * 
 */

#include "../headers/effets.h"


/**
 * @brief Execute le pouvoir de la carte en fonction du nom de la carte
 * @param liste_joueuses Pour savoir sur quelles joueuses et monstres intéragir
 * @param liste_zones la liste des zones
 * @param nom_carte le nom de la carte pour savoir quel pouvoir executer
 * @return rien
 */
void wrapper_pouvoir_carte(joueuse* liste_joueuses, zones liste_zones, char* nom_carte) {
    if (strcmp(nom_carte, "Massinissa Merabet") == 0) {
        pouvoir_carte_Merabet(liste_joueuses[0]);
    }
    else if (strcmp(nom_carte, "Fetia Bannour") == 0) {
        pouvoir_carte_Bannour(liste_zones, liste_joueuses);
    }
    else if (strcmp(nom_carte, "Valentin Honoré") == 0) {
        pouvoir_carte_Honore(liste_joueuses, liste_zones);
    }
    else if (strcmp(nom_carte, "Renaud Rioboo") == 0) {
        pouvoir_carte_Rioboo(liste_joueuses[1], liste_zones);
    }
    else if (strcmp(nom_carte, "Kevin Goilard") == 0) {
        pouvoir_carte_Goilard(liste_joueuses);
    }
    else if (strcmp(nom_carte, "Laurence Bourard") == 0) {
        pouvoir_carte_Bourard(liste_joueuses, liste_zones);
    }
    else if (strcmp(nom_carte, "Denisse Munante") == 0) {
        pouvoir_carte_Munante(liste_joueuses);
    }
    else if (strcmp(nom_carte, "Cyril Benezet") == 0) {
        pouvoir_carte_Benezet(liste_joueuses, liste_zones);
    }
    else if (strcmp(nom_carte, "Anne-Laure Ligozat") == 0) {
        pouvoir_carte_Ligozat(liste_joueuses[0]);
    }
    else if (strcmp(nom_carte, "Christophe Mouilleron") == 0) {
        pouvoir_carte_Mouilleron(liste_joueuses);
    }
    else if (strcmp(nom_carte, "Djibril-Aurelien Dembele-Cabot") == 0) {
        pouvoir_carte_DembeleCabot(liste_joueuses[0]);
    }
    else if (strcmp(nom_carte, "Lucienne Pacave") == 0) {
        pouvoir_carte_Pacave(liste_zones, liste_joueuses[0]);
    }
    else if (strcmp(nom_carte, "Jerome Huet") == 0) {
        pouvoir_carte_Huet(liste_zones);
    }
    else if (strcmp(nom_carte, "Christine Matias") == 0) {
        pouvoir_carte_Matias(liste_joueuses[2]);
    }
    else if (strcmp(nom_carte, "Katrin Salhab") == 0) {
        pouvoir_carte_Salhab(liste_joueuses[0]);
    }
    else if (strcmp(nom_carte, "Sergio Pulido-Nino") == 0) {
        pouvoir_carte_PulidoNino(liste_zones, liste_joueuses[2]);
    }
    else if (strcmp(nom_carte, "Dimitri Watel") == 0) {
        pouvoir_carte_Watel(liste_joueuses[0]);
    }
    else if (strcmp(nom_carte, "Marie Szafranski") == 0) {
        pouvoir_carte_Szafranski(liste_joueuses, liste_zones);
    }
    else if (strcmp(nom_carte, "Julien Forest") == 0) {
        pouvoir_carte_Forest(liste_zones, liste_joueuses[2]);
    }
    else if (strcmp(nom_carte, "Laurent Prével") == 0) {
        pouvoir_carte_Prevel(liste_joueuses[0]);
    }
}



/** 1
 * @brief Execute le pouvoir de la carte Massinissa Merabet
 * Pendant vos 3 prochains tours, votre capital augmente de 2
 * @param jou Pour savoir sur quelle joueuse intéragir
 * @return rien
 */
void pouvoir_carte_Merabet(joueuse jou) {
    setToursRestantsBonusCapital(jou, 3);
    setCapital(jou, getCapital(jou) + 2);
    int options[2] = {getCapital(jou), getToursRestantsBonusCapital(jou)};
    message_generique(201, NULL, options, NULL);
}

/** 2
 * @brief Execute le pouvoir de la carte Fetia Bannour
 * Choisissez deux zones, les personnages présents sur ces deux zones sont échangés
 * @param zones la liste des zones
 * @param liste_joueuses La liste de tout les joueurs afin de savoir la zone courante de chacun des personnages de chaque joueur
 * @return rien
 */
void pouvoir_carte_Bannour(zones liste_zones, joueuse* liste_joueuses) {
    int zone_1 = demander_zones_depart(liste_zones);
    int zone_2 = demander_zones_autre(liste_zones, zone_1);
    for (int i = 0; i < 2; i += 1) {
        for (int j = 0; j < getTaille(liste_joueuses[i]); j += 1) {
            if (getZoneCourante(getMembres(liste_joueuses[i])[j]) == zone_1) {
                setZoneCourante(getMembres(liste_joueuses[i])[j], zone_2); 
                int options[3] = {j, zone_1, zone_2};
                message_generique(202, liste_joueuses[i], options, NULL);
            }
            else if (getZoneCourante(getMembres(liste_joueuses[i])[j]) == zone_2) {
                setZoneCourante(getMembres(liste_joueuses[i])[j], zone_1);
                int options[3] = {j, zone_2, zone_1};
                message_generique(202, liste_joueuses[i], options, NULL);
            }
        }
    }
}

/** 3
 * @brief Execute le pouvoir de la carte  Valentin Honoré
 * Chaque montre se déplace 3 fois. Chaque membre d'école qu'un monstre rencontre est mangé
 * @param liste_joueuses_dont_monstres La liste de tout les joueurs et monstres afin de savoir la zone courante de chacun des personnages de chaque joueur
 * @param liste_zones la liste des zones
 * @return rien
 */
void pouvoir_carte_Honore(joueuse* liste_joueuses_dont_monstres, zones liste_zones) {
    for (int i = 0; i < 3; i += 1) { // 3 déplacements et on bloque le déplacement des monstres pendant 1 tour pour éviter un 4eme déplacement
        for (int j = 0; j < getTaille(liste_joueuses_dont_monstres[2]); j += 1) { // pour chaque monstre
            deplacer(getMembres(liste_joueuses_dont_monstres[2])[j], trouveZone(liste_zones, prochaineZone(liste_zones, zonePersonnage(getMembres(liste_joueuses_dont_monstres[2])[j]))));
            int options[2] = {j, getZoneCourante(getMembres(liste_joueuses_dont_monstres[2])[j])};
            message_generique(203, NULL, options, NULL);
            for (int k = 0; k < 2; k += 1) { // pour chaque joueuse
                for (int l = 0; l < getTaille(liste_joueuses_dont_monstres[k]); l += 1) { // pour chaque membre d'école
                    if (getZoneCourante(getMembres(liste_joueuses_dont_monstres[k])[l]) + 1 == getZoneCourante(getMembres(liste_joueuses_dont_monstres[2])[j]) + 1 && (getStatut(getMembres(liste_joueuses_dont_monstres[k])[l]) == 1 || getStatut(getMembres(liste_joueuses_dont_monstres[k])[l]) == 3)) {
                        // Si le membre d'école est dans la même zone que le monstre et (qu'il est en vie ou qu'il est FIPA)
                        estMange(getMembres(liste_joueuses_dont_monstres[k])[l]);
                        message_generique(7, liste_joueuses_dont_monstres[k], &l, NULL);
                    }
                }
            }
        }
    }
    for (int j = 0; j < getTaille(liste_joueuses_dont_monstres[2]); j += 1) { // pour chaque monstre
        setPeutSeDeplacer(getMembres(liste_joueuses_dont_monstres[2])[j], 0);
    }
}

/** 4
 * @brief Execute le pouvoir de la carte Renaud Rioboo
 * Lors du prochain tour, la joueuse adverse ne choisit pas comment est utilisé son capital. Chaque 
 * point de capital est utilisé aléatoirement: pour chaque point, choisissez les trois zones Z1, Z2 et 
 * Z3 uniformément parmi les triplets pouvant être choisis.
 * @param adverse la joueuse adverse
 * @param zo l'ensemble des zones où la proba va être modifié pour certaines 
 * @return rien
 */
void pouvoir_carte_Rioboo(joueuse adverse, zones zo) {
    int capital = getCapital(adverse);
    float proba_par_capital = getProbaParCapital(adverse);
    for (int i = 0; i < capital; i += 1) {
        int nombre_zones = getTailleMatrice(getMatrice(zo)); // TODO: changer le nombre de zones
        int zone_1 = rand() % nombre_zones;
        int zone_2 = rand() % nombre_zones;
        int zone_3 = rand() % nombre_zones;
        while (zone_2 == zone_3 || lecture_probas(getMatrice(zo), zone_1, zone_2) + proba_par_capital > 1 || lecture_probas(getMatrice(zo), zone_1, zone_3) - proba_par_capital < 0) {
            zone_1 = rand() % nombre_zones;
            zone_2 = rand() % nombre_zones;
            zone_3 = rand() % nombre_zones;
        }
        modifierZone(zo, zone_1, zone_2, getProbaParCapital(adverse), 1);
        modifierZone(zo, zone_1, zone_3, getProbaParCapital(adverse), 0);
        int triplet_augmenter[3] = {zone_1, zone_2, proba_par_capital*10};
        int triplet_diminuer[3] = {zone_1, zone_3, -proba_par_capital*10};
        message_generique(4, NULL, triplet_augmenter, NULL);
        message_generique(4, NULL, triplet_diminuer, NULL);
    }
    utilise_capital(adverse, capital);
    message_generique(3, adverse, &capital, NULL);
}

/** 5
 * @brief Execute le pouvoir de la carte Kevin Goilard
 * Lors du prochain tour et du suivant, c'est vous qui jouez. Lors des deux 
 * tours suivant, c'est la joueuse adverse qui joue.
* @param liste_joueuses permet d'avoir l'ensemble des 2 joueuses
 * @return rien
 */
void pouvoir_carte_Goilard(joueuse* liste_joueuses) {
    for (int i = 0; i < 2; i += 1) {
        setToursRestantsJouer(liste_joueuses[i], getToursRestantsJouer(liste_joueuses[i]) + 2);
        int option[1] = {getToursRestantsJouer(liste_joueuses[i])};
        message_generique(205, liste_joueuses[i], option, NULL);
    }
}


/** 6
 * @brief Execute le pouvoir de la carte Laurence Bourard
 * Lors du prochain déplacement, si deux membres d'écoles adverses se retrouvent sur la même zone,
 * ils se déplacent de nouveau. Si ces deux membres sont sur la zone du monstre avant le second déplacement,
 * ils ne sont pas mangés. On recommence l'opération au plus 100 fois, jusqu'à ce que les membres des écoles 
 * adverses soient sur des zones distinctes.
 * @param liste_joueuses permet d'avoir l'ensemble des 2 joueuses et des monstres
 * @param liste_zones permet d'avoir l'ensemble des zones
 * @return rien
*/
void pouvoir_carte_Bourard(joueuse* liste_joueuses, zones liste_zones) {
    // Consumme les mouvements des monstres
    int nombre_monstre = nb_membre_ecole(liste_joueuses[2]);
    for (int j = 0; j < nombre_monstre; j += 1) {
        if (getPeutSeDeplacer(getMembres(liste_joueuses[2])[j]) == 1 && getStatut(getMembres(liste_joueuses[2])[j]) == 1) {
            for (int k = 0; k < getNbPas(getMembres(liste_joueuses[2])[j]); k += 1) {
                deplacer(getMembres(liste_joueuses[2])[j], trouveZone(liste_zones, prochaineZone(liste_zones, zonePersonnage(getMembres(liste_joueuses[2])[j])))); // Déplacement des monstres vers leur prochaine zone
            }
            setPeutSeDeplacer(getMembres(liste_joueuses[2])[j], 0);
        }
    }

    // Déplacement des joueuses
    for (int i = 0; i < 2; i += 1) {
        for (int j = 0; j < getTaille(liste_joueuses[i]); j += 1) {
            if (getPeutSeDeplacer(getMembres(liste_joueuses[i])[j]) == 1 && getStatut(getMembres(liste_joueuses[i])[j]) == 1) {
                for (int k = 0; k < getNbPas(getMembres(liste_joueuses[i])[j]); k += 1) {
                    deplacer(getMembres(liste_joueuses[i])[j], trouveZone(liste_zones, prochaineZone(liste_zones, zonePersonnage(getMembres(liste_joueuses[i])[j])))); // Déplacement des joueuses vers leur prochaine zone
                }
            }
        }
    }
    int continuer = 1;
    int nb_tour = 0;
    while (continuer == 1 && nb_tour < 100) {
        continuer = 0;
        for (int i = 0; i < getTaille(liste_joueuses[0]); i += 1) {
            for (int j = 0; j < getTaille(liste_joueuses[1]); j += 1) {
                if (getZoneCourante(getMembres(liste_joueuses[0])[i]) == getZoneCourante(getMembres(liste_joueuses[1])[j])) {
                    continuer = 1;
                    nb_tour += 1;
                    deplacer(getMembres(liste_joueuses[0])[i], trouveZone(liste_zones, prochaineZone(liste_zones, zonePersonnage(getMembres(liste_joueuses[0])[i])))); // Déplacement des personnages vers leur prochaine zone
                    deplacer(getMembres(liste_joueuses[1])[j], trouveZone(liste_zones, prochaineZone(liste_zones, zonePersonnage(getMembres(liste_joueuses[1])[j])))); // Déplacement des personnages vers leur prochaine zone
                }
            }
        }
    }
    // Empêche les joueuses de se déplacer de nouveau
    for (int i = 0; i < 2; i += 1) {
        for (int j = 0; j < getTaille(liste_joueuses[i]); j += 1) {
            setPeutSeDeplacer(getMembres(liste_joueuses[i])[j], 0);
        }
    }
    


}

/** 7
 * @brief Execute le pouvoir de la carte Denisse Munante
 * Les membres d'écoles présents sur la zone où était un monstre avant son dernier déplacement sont mangés.
 * @param liste_joueuses permet d'avoir l'ensemble des 2 joueuses et des monstres
 * @return rien
*/
void pouvoir_carte_Munante(joueuse* liste_joueuses) {
    for (int i = 0; i < getTaille(liste_joueuses[2]); i += 1) {
        for (int j = 0; j < 2; j += 1) {
            for (int k = 0; k < getTaille(liste_joueuses[j]); k += 1) {
                if (getZoneCourante(getMembres(liste_joueuses[j])[k])  + 1 == getZonePrecedente(getMembres(liste_joueuses[2])[i]) + 1 && (getStatut(getMembres(liste_joueuses[j])[k]) == 1 || getStatut(getMembres(liste_joueuses[j])[k]) == 3)) {
                    estMange(getMembres(liste_joueuses[j])[k]);
                    message_generique(7, liste_joueuses[j], &k, NULL);
                }
            }
        }
    }
}

/** 8
 * @brief Execute le pouvoir de la carte Cyril Benezet
 * Déplacez un des monstres sur la zone de votre choix. Si un membre d'école se trouve sur la zone du monstre, il n'est pas mangé.
 * @param liste_joueuses permet d'avoir la liste de tous les joueuses
 * @param liste_zones permet d'avoir l'ensemble des zones
 * @return rien
*/
void pouvoir_carte_Benezet(joueuse* liste_joueuses, zones liste_zones) {
    joueuse monstres = liste_joueuses[2];
    int choix = demander_personnage(monstres);
    setPeutSeDeplacer(getMembres(monstres)[choix], 0);
    int zone = demander_zones_depart(liste_zones);
    setZonePrecedente(getMembres(monstres)[choix], getZoneCourante(getMembres(monstres)[choix]));
    setZoneCourante(getMembres(monstres)[choix], zone);
    int options[2] = {choix, zone};
    message_generique(203, NULL, options, NULL);
}

/** 9
 * @brief Execute le pouvoir de la carte Anne-Laure Ligozat
 * Choisissez un membre de votre école, il effectue désormais deux déplacements au lieu d'un à chaque tour.
 * @param jou permet d'avoir la joueuse
 * @return rien
*/
void pouvoir_carte_Ligozat(joueuse jou) {
    int choix = demander_personnage(jou);
    setDeNbPas(getMembres(jou)[choix], 2);
    message_generique(209, NULL, &choix, NULL);
}

/** 10
 * @brief Execute le pouvoir de la carte Christophe Mouilleron
 * Choisissez un membre de l'école de la joueuse adverse. Ce membre devient un membre de votre école.
 * @param liste_joueuses permet d'avoir l'ensemble des 2 joueuses et des monstres
 * @return rien
*/
void pouvoir_carte_Mouilleron(joueuse* liste_joueuses) {
    int i;
    if (getTour(liste_joueuses[0]) == 1) {
        i = 0;
    }
    else {
        i = 1;
    }
    int choix = demander_personnage(liste_joueuses[(i+1)%2]);
    setType(getMembres(liste_joueuses[(i+1)%2])[choix], getIdJoueuse(liste_joueuses[i]));
    addMembres(liste_joueuses[i], getMembres(liste_joueuses[(i+1)%2])[choix]);
    setIdPersonnage(getMembres(liste_joueuses[(i+1)%2])[choix], getTaille(liste_joueuses[i]));
    removeMembres(liste_joueuses[(i+1)%2], choix+1);
    int options[4] = {choix, getIdJoueuse(liste_joueuses[i]), getTaille(liste_joueuses[i]), getIdJoueuse(liste_joueuses[(i+1)%2])};
    message_generique(210, NULL, options, NULL);
}

/** 11
 * @brief Execute le pouvoir de la carte Djibril-Aurelien Dembele-Cabot
 * Sacrifiez un membre de votre école de votre choix. Vous avez 15 points de capital en plus à votre
 * prochain tour.
 * @param jou permet d'avoir la joueuse
 * @return rien
 */
void pouvoir_carte_DembeleCabot(joueuse jou) {
    int choix = demander_personnage(jou);
    setBonusTemporaire(jou, getBonusTemporaire(jou) + 15);
    message_generique(211, NULL, NULL, NULL);
    estMange(getMembres(jou)[choix]);
    message_generique(7, jou, &choix, NULL);
}

/** 12
 * @brief Execute le pouvoir de la carte Lucienne Pacave
 * Créez une nouvelle zone. Les membres de votre école sont les seuls à pouvoir se déplacer sur cette zone.
 * Un membre de l'école de l'autre joueuse qui devrait se déplacer sur cette zone ne se déplace pas.
 * La probabilité d'aller sur cette zone est de 0. Depuis cette zone, la probabilité de rester sur cette zone est 1.
 * @param zo permet d'avoir l'ensemble des zones
 * @param jou permet d'avoir la joueuse
 * @return rien
 */
void pouvoir_carte_Pacave(zones zo, joueuse jou) {
    addZone(zo);
    message_generique(212, NULL, NULL, NULL);
    setEstAutorise(getTabZones(zo)[getTailleMatrice(getMatrice(zo)) - 1], getIdJoueuse(jou));
    modifier_proba(getMatrice(zo), getTailleMatrice(getMatrice(zo)) - 1, getTailleMatrice(getMatrice(zo)) - 1, 1);
}

/** 13
 * @brief Execute le pouvoir de la carte Jerome Huet
 * Chaque zone effectue une rotation de probabilité. La probabilité d'aller de la zone i à la zone j devient la 
 * probabilité d'aller de la zone i à la zone j + 1. La probabilité d'aller de la zone i à la zone 10 devient la
 * probabilité d'aller de la zone i à la zone 1.
 * @param zo permet d'avoir l'ensemble des zones
 * @return rien
 */
void pouvoir_carte_Huet(zones zo) {
    matrice_probas matrice = getMatrice(zo);
    int taille = getTailleMatrice(getMatrice(zo));
    for (int i = 0; i < taille; i += 1) {
         float proba = lecture_probas(matrice, i, i);
        for (int j = 0; j < taille - 1; j += 1) {
            modifier_proba(matrice, i, j, lecture_probas(matrice, i, j + 1));
        }
        modifier_proba(matrice, i, taille - 1, proba);
    }
    message_generique(213, NULL, NULL, NULL);
}

/** 14
 * @brief Execute le pouvoir de la carte Christine Matias
 * Chaque monstre disparaît pendant 2 tours. Il réapparaîtra sur la zone d'où il est parti.
 * @param liste_monstres permet d'avoir l'ensemble des monstres
 * @return rien
 */
void pouvoir_carte_Matias(joueuse liste_monstres) {
    for (int i = 0; i < getTaille(liste_monstres); i += 1) {
        setIdPersonnage(getMembres(liste_monstres)[i], -1);
        setNbDeTourDisparuRestant(getMembres(liste_monstres)[i], 3); // Les 2 prochains tours après l'utilisation de cette carte
    }
    message_generique(214, NULL, NULL, NULL);
}

/** 15
 * @brief Execute le pouvoir de la carte Katrin Salhab
 * Pendant vos 3 prochains tours, un point de capital permet de déplacer une quantité 
 * 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9 ou 1 de probabilité.
 * @param jou permet d'avoir la joueuse
 * @return rien
 */
void pouvoir_carte_Salhab(joueuse jou) {
    int proba_par_capital = getProbaParCapital(jou);
    setProbaParCapital(jou, proba_par_capital);
    int option[1] = {proba_par_capital*10};
    message_generique(215, NULL, option, NULL);
    setToursRestantsBonusProbaParCapital(jou, 4); // 4 car 1 tour sera perdu après l'utilisation de cette carte
}

/** 16
 * @brief Execute le pouvoir de la carte Sergio Pulido-Nino
 * Mettez à 0 les probabilités permettant de sortir de la zone de chaque monstre et mettez à 1 la probabilité de rester dans la zone de chaque monstre.
 * @param zo permet d'avoir l'ensemble des zones
 * @param monstres permet d'avoir l'ensemble des monstres
 * @return rien
 */
void pouvoir_carte_PulidoNino(zones zo, joueuse monstres) {
    matrice_probas matrice = getMatrice(zo);
    for (int i = 0; i < getTaille(monstres); i += 1) {
        int j = getZoneCourante(getMembres(monstres)[i]);
        for (int k = 0; k < getTailleMatrice(getMatrice(zo)); k += 1) {
            modifier_proba(matrice, j, k, 0);
            int options[3] = {j, k, 0};
            message_generique(216, NULL, options, NULL);
        }
        modifier_proba(matrice, j, j, 1);
        int options2[3] = {j, j, 10};
        message_generique(216, NULL, options2, NULL);
    }
}

/** 17
 * @brief Execute le pouvoir de la carte Dimitri Watel
 * Choisissez un membre de votre école, il devient FISA et effectue désormais son déplacement un tour sur deux.
 * @param jou permet d'avoir la joueuse
 * @return rien
 */
void pouvoir_carte_Watel(joueuse jou) {
    int choix = demander_personnage(jou);
    setStatut(getMembres(jou)[choix - 1], 3);
    message_generique(217, jou, &choix, NULL);
}

/** 18
 * @brief Execute le pouvoir de la carte Marie Szafranski
 * Ajoutez un monstre sur la zone 1, un membre de votre école sur la zone 2 et un membre de l'école adverse sur 
 * la zone 3. Si un membre d'école se trouve sur la même zone qu'un monstre, il n'est pas mangé.
 * @param liste_joueuses permet d'avoir l'ensemble des 2 joueuses et des monstres
 * @param zo permet d'avoir l'ensemble des zones
 * @return rien
 */
void pouvoir_carte_Szafranski(joueuse* liste_joueuses, zones zo) {
    for (int i = 0; i < 3; i += 1) {
        int id = getTaille(liste_joueuses[i]);
        personnage nouveau = nouveauPersonnage(i, id+1, getNumero(getTabZones(zo)[i+1]));
        addMembres(liste_joueuses[i], nouveau); 
    }
}

/**
 * @brief Execute le pouvoir de la carte Julien Forest
 * Mettez toutes les probabilités à 0. Puis, pour chaque zone, la probabilité de se déplacer de cette zone vers la zone contenant
 *  le monstre passe à 0.5 (s'il y a plusieurs monstres, un des monstres est choisi au hasard) ; et la probabilité de se déplacer de cette zone vers une autre zone ne contenant pas de monstre choisie aléatoirement passe également à 0.5.
 * @param zones permet d'avoir l'ensemble des zones
 * @param monstres permet d'avoir l'ensemble des monstres
 * @return rien
 */
void pouvoir_carte_Forest(zones zo, joueuse monstres) {
    matrice_probas matrice = getMatrice(zo);
    for (int i = 0; i < getTailleMatrice(matrice); i += 1) {
        for (int j = 0; j < getTailleMatrice(matrice); j += 1) {
            modifier_proba(matrice, i, j, 0);
        }
    }
    int random = rand() % getTaille(monstres);
    int zone_monstre = getZoneCourante(getMembres(monstres)[random]);
    for (int i = 0; i < getTailleMatrice(matrice); i += 1) {
        modifier_proba(matrice, i, zone_monstre, 0.5);
        int random2 = rand() % getTailleMatrice(matrice);
        while (random2 == zone_monstre) {
            random2 = rand() % getTailleMatrice(matrice);
        }
        modifier_proba(matrice, i, random2, 0.5);
    }
}

/**
 * @brief Execute le pouvoir de la carte Laurent Prével
 * Pendant 4 tours, les membres de votre école ne peuvent être mangés par un monstre. S'ils sont sur 
 * sa zone à la fin du tour, rien ne se passe, ils restent sur cette case.
 * @param jou permet d'avoir la joueuse
 * @return rien
*/
void pouvoir_carte_Prevel(joueuse jou) {
    setToursRestantsInvincibilite(jou, 4);
}

