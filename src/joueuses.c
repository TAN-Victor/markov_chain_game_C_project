#include "../headers/joueuses.h"

/* Setters et Getters */

/**
 * @brief renvoie le capital d'une joueuse
 * 
 * @param j : une joueuse
 * @return int : le capital
 */
int getCapital(joueuse j){
    return j->capital;
}

/**
 * @brief renvoie la liste des cartes de la main d'une joueuse
 * 
 * @param j : une joueuse 
 * @return carte* : la liste des cartes de la main d'une joueuse 
 */
liste_cartes getMain(joueuse j){
    return j->main_du_joueur;
}

/**
 * @brief renvoie l'id d'une joueuse
 * 
 * @param j : une joueuse 
 * @return int : l'id d'une joueuse
 */
int getIdJoueuse(joueuse j){
    return j->id;
}

/**
 * @brief renvoie 1 si c'est à la joueuse de jouer, 0 sinon
 * 
 * @param j : une joueuse 
 * @return int : 1 si c'est à la joueuse de jouer, 0 sinon
 */
int getTour(joueuse j){
    return j->tour;
}

/**
 * @brief renvoie la taille de l'équipe d'une joueuse
 * 
 * @param j : une joueuse 
 * @return int : le taille de l'équipe
 */
int getTaille(joueuse j){
    return j->taille;
}

/**
 * @brief renvoie le nombre de tours restants sous bonus de capital de la joueuse
 * 
 * @param j : une joueuse 
 * @return int : le nombre de tours restants sous bonus
 */
int getNbToursBonusCapital(joueuse j){
    return j->tours_restants_bonus_capital;
}

/**
 * @brief renvoie la valeur de invinsibilite
 * 
 * @param j : une joueuse 
 * @return int : 1 si les membres de la joueuse sont invinsibles, 0 sinon
 */
int getInvincibilite(joueuse j){
    return getToursInvincibilite(j) > 0;
}

/**
 * @brief renvoie le nombre de tours restants pendant lesquels les membres de la joueuse sont invinsibles
 * 
 * @param j : une joueuse 
 * @return int : le nombre de tours restants pendant lesquels les membres de la joueuse sont invinsibles
 */
int getToursInvincibilite(joueuse j){
    return j->tours_restants_invincibilite;
}

/**
 * @brief renvoie la liste de personnage (de type membre de d'école) de la joueuse sélectionnée
 * @param pj pointeur vers la joueuse sélectionnée
 * @return une liste de personreinitialisese* pj;
*/
personnage* getMembres(joueuse pj){
    return pj->membres;
}
/**
 * @brief renvoie le nombre de tours restants pendant lesquels la joueuse peut jouer plusieurs fois par tour
 * 
 * @param j 
 * @return int : le nombre de tours restant pendant lequels elle peut jouer plusieurs fois
 */
int getToursRestantsJouer(joueuse j){
    return j->tours_restants_jouer;
}

/**
 * @brief renvoie la proba par capital de la joueuse
 * 
 * @param j 
 * @return float : la proba par capital de la joueuse
 */
float getProbaParCapital(joueuse j){
    return j->proba_par_capital;
}

/**
 * @brief met à jour la proba_par_capital de la joueuse
 * 
 * @param j 
 * @param proba 
 */
void setProbaProbaParCapital(joueuse j, float proba){
    j->proba_par_capital = proba;
}

/**
 * @brief modifie le capital d'une joueuse
 * 
 * @param j : une joueuse 
 * @param capital : le nouveau capital
 */
void setCapital(joueuse j, int capital){
    j->capital = capital;
}

/**
 * @brief modifie l'id d'une joueuse
 * 
 * @param j : une joueuse 
 * @param id : le nouvel id
 */
void setIdJoueuse(joueuse j, int id){
    j->id = id;
}

/**
 * @brief modifie le tour d'une joueuse
 * 
 * @param j : une joueuse 
 * @param tour : 1 si c'est à la joueuse de jouer, 0 sinon
 */
void setTour(joueuse j, int tour){
    j->tour = tour;
}

/**
 * @brief modifie la taille de l'équipe d'une joueuse
 * 
 * @param j : une joueuse 
 * @param taille : la nouvelle taille de l'équipe
 */
void setTaille(joueuse j, int taille){
    j->taille = taille;
}

/**
 * @brief modifie le nombre de tours restants sous bonus capital de la joueuse
 * 
 * @param j : une joueuse 
 * @param toursRestants : le nouveau nombre de tours restants sous bonus capital
 */
void setToursRestantsBonusCapital(joueuse j, int toursRestants){
    j->tours_restants_bonus_capital = toursRestants;
}

/**
 * @brief modifie la valeur du nombre restant de tours sous invinsibilité
 * 
 * @param j : une joueuse 
 * @param toursRestants : le nouveau nombre de tours restants sous invinsibilité
 */
void setToursRestantsInvinsibilite(joueuse j, int toursRestants){
    j->tours_restants_invincibilite = toursRestants;
}

/**
 * @brief modifie le nombre de tours restants pendant lesquels la joueuse peut jouer plusieurs fois par tour
 * 
 * @param j : la joueuse 
 * @param toursRestants : le nouveau nombre de tours restants pendant lesquels la joueuse peut jouer plusieurs fois par tour
 */
void setToursRestantsJouer(joueuse j, int toursRestants){
    j->tours_restants_jouer = toursRestants;
}

/**
 * @brief renvoie le le bonus_temporaire
 * 
 * @param j 
 * @return int : le bonus_temporaire 1 ou 0
 */
int getBonusTemporaire(joueuse j){
    return j->bonus_temporaire;
}

/**
 * @brief modifie le bonus_temporaire
 * 
 * @param j 
 * @param bonus : le nouveau bonus_capital, 1 ou 0
 */
void setBonusTemporaire(joueuse j, int bonus){
    j->bonus_temporaire = bonus;
}

/**
 * @brief ajoute un personnage aux membres de la joueuse
 * 
 * @param j : une joueuse 
 * @param p : le personnage à ajouter
 */
void addMembres(joueuse j, personnage* p){
    j->membres = realloc(j->membres, (j->taille+1)*sizeof(personnage*));
    j->membres[j->taille] = p;
}

/**
 * @brief supprime un personnage des membres de la joueuse
 * 
 * @param j : une joueuse 
 * @param id : l'id du personnage à supprimer
 */
void removeMembres(joueuse j, int id){
    int i;
    for(i=0; i<j->taille; i++){
        if(getIdPersonnage(j->membres[i]) == id){
            j->membres[i] = j->membres[j->taille-1];
            j->taille--;
            j->membres = realloc(j->membres, j->taille*sizeof(personnage*));
            break;
        }
    }
}

/** 
 * @brief renvoit une joueuse :
 *          - on initialise le capital à 5
            - on initialise les 5 membres du joueurs
            - on initialise la main_du_joueur avec 5 cartes aléatoires
            - on associe à la joeuse une clée unique (1 ou 2)-> cette clef permet de savoir qui est le joueur n°1
 * @param n un entier si n=0 on cree un monstre dans un ensemble de monstres, si n=1 on cree une joueuse
 * @return joueuse un pointeur vers la joueuse crée
*/
joueuse creation_joueuse(int n){
    if(n!=1 || n!=2 || n!=0){
        fprintf(stderr," creation_joueuse : n doit avoir pour valeur 0 , 1 ou 2");
        exit(1);
    }
    joueuse jou=malloc(sizeof(struct joueuse));
    jou->capital=5;
    jou->membres=malloc(sizeof(7*struct _personnage));
    // En cours de développement pour l'implémentation des cartes : Besoin d'avoir une liste de carte global en paramètre ou mettre la liste de carte en paramètre
    jou->id=n;
    if(n==1){
        jou->tour=1;
    }
    else{
        jou->tour=0;
    }
    jou->taille=5;
    jou->tours_restants_bonus_capital=1;
    jou->tours_restants_invinsibilite=0;
    jou->tours_restants_jouer=1;
    jou->proba_par_capital=0.1;
    return jou;
}

/**
 * @brief libère l'espace mémoire occupée par la case mémoire pointée par pj
 * @param pj pointeur vers la case mémoire occupée par la joueuse que l'on souhaite libérer
*/
void free_joueuse(joueuse pj){
    free(pj->membres);
    free(pj);
}

/**
 * @brief renvoie la joueuse dont c'est le tour en testant sur les deux joueuses, celle dont la valeur tour vaut 0
 * @param pj1 pointeur vers la joueuse 1
 * @param pj2 pointeur vers la joueuse 2
 * @return un pointeur vers la joueuse dont c'est le tour
*/
joueuse tour_joueuse(joueuse pj1, joueuse pj2){
    if((pj1->tour==0 && pj2->tour==0) || (pj1->tour==1 && pj2->tour==1) ){
        fprintf(stderr,"tour_joueuse : le tour des 2 joueuses est à 0 ou 1");
        exit(2);
    }
    else if(pj1->tour==1 && pj2->tour==0){
        return pj1;
    }
    else if(pj1->tour==0 && pj2->tour==1){
        return pj2;
    }
}

