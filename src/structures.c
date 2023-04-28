/**
 * @file structures.c
 * @author Théo Taillefumier
 * @brief structures de données
 * @date 2023-03-31
 * 
 * @necessities
 * 
 * 
 */


#include "../headers/structures.h"

/* Getter et Setters */
/**
 * @brief renvoie un entier correspondant au nombre de cartes présentes dans la liste
 * 
 * @param lc 
 * @return int correspondant au nombre de cartes 
 */
int getNbCartes(liste_cartes lc){
    return lc->nb_cartes;
}

/**
 * @brief met à jour le nombre de cartes de la main
 * 
 * @param n 
 */
void setNbCartes(liste_cartes lc, int n){
    lc->nb_cartes = n;
}

/**
 * @brief renvoie la liste de cartes de la liste de cartes passés en arguments
 * 
 * @param lc 
 * @return carte* tableau de cartes
 */
carte* getCartes(liste_cartes lc){
    return lc->cartes;
}

/**
 * @brief renvoie la taille de la matrice
 * 
 * @param matrice un pointeur vers la matrice de probas
 * 
 * @return int la taille de la matrice
*/
int getTailleMatrice(matrice_probas matrice){
    return matrice->taille_matrice;
}

/**
 * @brief met à jour la taille de la matrice
 * 
 * @param taille la nouvelle taille de la matrice
*/
void setTailleMatrice(matrice_probas matrice, int taille){
    matrice->taille_matrice = taille;
}

void ajout_carte(liste_cartes liste, carte carte){
    setNbCartes(liste,getNbCartes(liste)+1);
    liste->cartes = realloc(liste->cartes,getNbCartes(liste)*sizeof(carte));
    liste->cartes[getNbCartes(liste)-1] = carte;
}

carte lecture_cartes(liste_cartes liste, int index){
    if (index < getNbCartes(liste)){
        return getCartes(liste)[index];
    }
    fprintf(stderr,"index out of range");
    return NULL;
}

void suppr_cartes(liste_cartes liste, carte carte){
    int index = 0;
    while (index < getNbCartes(liste) && getCartes(liste)[index] != carte){
        index++;
    }
    if (index < getNbCartes(liste)){ //si on vérifie cette condition c'est que on a trouvé une carte dans la lsite qui corespond à celle passée en argument
        setNbCartes(liste,getNbCartes(liste)-1);
        for (int i = index; i < getNbCartes(liste); i++){//on parcours la liste à partir de l'indice de la carte à supprimer
            liste->cartes[i] = getCartes(liste)[i + 1];
        }
        free(getCartes(liste)[getNbCartes(liste)]); //on libère la mémoire de la carte supprimée, la dernière de la liste, le -1 est déjà fait à la ligne 85
        liste->cartes = realloc(getCartes(liste), getNbCartes(liste) * sizeof(carte)); 
    }
}

/**
 * @brief libère la mémoire allouée à la liste de cartes
 * 
 * @param liste 
 */
void libere_liste_cartes(liste_cartes liste){
    for (int i = 0; i < getNbCartes(liste); i++){
        free(liste->cartes[i]);
    }
    free(liste->cartes);
    free(liste);
}

liste_cartes creer_liste_cartes_global() {
    liste_cartes liste_cartes_global=malloc(sizeof(struct liste_cartes)); // Correction sizeof du struct et pas du pointeur
    setNbCartes(liste_cartes_global,0);

    carte carte_Merabet=creer_carte("Massinissa Merabet", "Pendant vos 3 prochains tours, votre capital augmente de 2.");
    ajout_carte(liste_cartes_global,carte_Merabet);


    carte carte_Bannour=creer_carte("Fetia Bannour","Choisissez deux zones, les personnages présents sur ces deux zones sont échangés.");
    ajout_carte(liste_cartes_global,carte_Bannour);

    carte carte_Honore=creer_carte("Valentin Honoré","Chaque monstre se déplace 3 fois. Chaque membre d'école qu'un monstre rencontre est mangé.");
    ajout_carte(liste_cartes_global,carte_Honore);

    carte carte_Rioboo=creer_carte("Renaud Rioboo","Lors du prochain tour, la joueuse adverse ne choisit pas comment est utilisé son capital. Chaque point de capital est utilisé aléatoirement: pour chaque point, choisissez les trois zones Z1, Z2 et Z3 uniformément parmi les triplets pouvant être choisis.");
    ajout_carte(liste_cartes_global,carte_Rioboo);

    carte carte_Goilard=creer_carte("Kevin Goilard","Lors du prochain tour et du suivant, c'est vous qui jouez. Lors des deux tours suivant, c'est la joueuse adverse qui joue.");
    ajout_carte(liste_cartes_global,carte_Goilard);

    carte carte_Bourard=creer_carte("Laurence Bourard","Lors du prochain déplacement, si deux membres d'écoles adverses se retrouvent sur la même zone, ils se déplacent de nouveau. Si ces deux membres sont sur la zone du monstre avant le second déplacement, ils ne sont pas mangés. On recommence l'opération au plus 100 fois, jusqu'à ce que les membres des écoles adverses soient sur des zones distinctes.");
    ajout_carte(liste_cartes_global,carte_Bourard);

    carte carte_Munante=creer_carte("Denisse Munante","Les membres d'écoles présents sur la zone où était un monstre avant son dernier déplacement sont mangés.");
    ajout_carte(liste_cartes_global,carte_Munante);

    carte carte_Benezet=creer_carte("Cyril Benezet","Déplacez un des monstres sur la zone de votre choix. Si un membre d'école se trouve sur la zone du monstre, il n'est pas mangé.");
    ajout_carte(liste_cartes_global,carte_Benezet);

    carte carte_Ligozat=creer_carte("Anne-Laure Ligozat","Choisissez un membre de votre école, il effectue désormais deux déplacements au lieu d'un à chaque tour.");
    ajout_carte(liste_cartes_global,carte_Ligozat);

    carte carte_Mouilleron=creer_carte("Christophe Mouilleron","Choisissez un membre de l'école de la joueuse adverse. Ce membre devient un membre de votre école.");
    ajout_carte(liste_cartes_global,carte_Mouilleron);

    carte carte_DembeleCabot=creer_carte("Djibril-Aurelien Dembele-Cabot","Sacrifiez un membre de votre école de votre choix. Vous avez 15 points de capital en plus à votre prochain tour.");
    ajout_carte(liste_cartes_global,carte_DembeleCabot);

    carte carte_Pacave=creer_carte("Lucienne Pacave","Créez une nouvelle zone. Les membres de votre école sont les seuls à pouvoir se déplacer sur cette zone. Un membre de l'école de l'autre joueuse qui devrait se déplacer sur cette zone ne se déplace pas. La probabilité d'aller sur cette zone est de 0. Depuis cette zone, la probabilité de rester sur cette zone est 1.");
    ajout_carte(liste_cartes_global,carte_Pacave);

    carte carte_Huet=creer_carte("Jerome Huet","Chaque zone effectue une rotation de probabilité. La probabilité d'aller de la zone i à la zone j devient la probabilité d'aller de la zone i à la zone j + 1. La probabilité d'aller de la zone i à la zone 10 devient la probabilité d'aller de la zone i à la zone 1.");
    ajout_carte(liste_cartes_global,carte_Huet);

    carte carte_Matias=creer_carte("Christine Matias","Chaque monstre disparaît pendant 2 tours. Il réapparaîtra sur la zone d'où il est parti.");
    ajout_carte(liste_cartes_global,carte_Matias);

    carte carte_Salhab=creer_carte("Katrin Salhab","Pendant vos 3 prochains tours, un point de capital permet de déplacer une quantité 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9 ou 1 de probabilité.");
    ajout_carte(liste_cartes_global,carte_Salhab);

    carte carte_PulidoNino=creer_carte("Sergio Pulido-Nino","Mettez à 0 les probabilités permettant de sortir de la zone de chaque monstre et mettez à 1 la probabilité de rester dans la zone de chaque monstre.");
    ajout_carte(liste_cartes_global,carte_PulidoNino);

    carte carte_Watel=creer_carte("Dimitri Watel","Choisissez un membre de votre école, il devient FISA et effectue désormais son déplacement un tour sur deux.");
    ajout_carte(liste_cartes_global,carte_Watel);

    carte carte_Szafranski=creer_carte("Marie Szafranski","Ajoutez un monstre sur la zone 1, un membre de votre école sur la zone 2 et un membre de l'école adverse sur la zone 3. Si un membre d'école se trouve sur la même zone qu'un monstre, il n'est pas mangé.");
    ajout_carte(liste_cartes_global,carte_Szafranski);

    carte carte_Forest=creer_carte("Julien Forest","Mettez toutes les probabilités à 0. Puis, pour chaque zone, la probabilité de se déplacer de cette zone vers la zone contenant le monstre passe à 0.5 (s'il y a plusieurs monstres, un des monstres est choisi aléatoirement) ; et la probabilité de se déplacer de cette zone vers une autre zone ne contenant pas de monstre choisie aléatoirement passe également à 0.5.");
    ajout_carte(liste_cartes_global,carte_Forest);

    carte carte_Prevel=creer_carte("Laurent Prével","Pendant 4 tours, les membres de votre école ne peuvent être mangés par un monstre. S'ils sont sur sa zone à la fin du tour, rien ne se passe, ils restent sur cette case.");
    ajout_carte(liste_cartes_global,carte_Prevel); 

    return liste_cartes_global;
}


matrice_probas creer_matrice(int taille){
    matrice_probas matrice = malloc(sizeof(struct matrice_probas)); // Correction size of struct et pas le pointeur
    matrice->taille_matrice = taille;
    matrice->proba = malloc(taille * sizeof(float*));
    for (int i = 0; i < taille; i++){
        matrice->proba[i] = malloc(taille * sizeof(float));
    }
    return matrice;
}

float lecture_probas(matrice_probas matrice, int i, int j){
    return matrice->proba[i][j];
}

void modifier_proba(matrice_probas matrice, int i, int j, float proba){
    matrice->proba[i][j] = proba;
}

void suppression_matrice(matrice_probas matrice){
    for (int i = 0; i < matrice->taille_matrice; i++){
        free(matrice->proba[i]);
    }
    free(matrice->proba);
    free(matrice);
}

matrice_probas produit_matrice(matrice_probas matrice1, matrice_probas matrice2){
    if (matrice1->taille_matrice != matrice2->taille_matrice){
        return NULL;
    }
    matrice_probas matrice = creer_matrice(matrice1->taille_matrice);
    for (int i = 0; i < matrice->taille_matrice; i++){
        for (int j = 0; j < matrice->taille_matrice; j++){
            float somme = 0;
            for (int k = 0; k < matrice->taille_matrice; k++){
                somme += matrice1->proba[i][k] * matrice2->proba[k][j];
            }
            matrice->proba[i][j] = somme;
        }
    }
    return matrice;
}
