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
 * @return une liste de personnage* pj;
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
 * @brief renvoie le nombre de tours restants sous bonus de capital de la joueuse
 * 
 * @param j : une joueuse 
 * @return int : le nombre de tours restants sous bonus
 */
int getToursRestantsBonusCapital(joueuse j){
    return j->tours_restants_bonus_capital;
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
void setProbaParCapital(joueuse j, float proba){
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
 * @brief renvoie la valeur du nombre restant de tours sous invinsibilité
 * 
 * @param j : une joueuse 
 * @return int : le nombre restant de tours sous invinsibilité
 */
int getToursRestantsInvincibilite(joueuse j){
    return j->tours_restants_invincibilite;
}

/**
 * @brief modifie la valeur du nombre restant de tours sous invinsibilité
 * 
 * @param j : une joueuse 
 * @param toursRestants : le nouveau nombre de tours restants sous invinsibilité
 */
void setToursRestantsInvincibilite(joueuse j, int toursRestants){
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
 * @return int : la valeur du bonus pendant ce tour
 */
int getBonusTemporaire(joueuse j){
    return j->bonus_temporaire;
}

/**
 * @brief modifie le bonus_temporaire
 * 
 * @param j 
 * @param bonus : le nouveau bonus_capital, doit être positif
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
void addMembres(joueuse j, personnage p){
    j->membres = realloc(j->membres, (j->taille+1)*sizeof(personnage*));
    setTaille(j,getTaille(j)+1);
    j->membres[j->taille-1] = p;
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
 * @brief renvoie le nombre de tours restants pendant lesquels la proba par capital est augmentée
 * 
 * @param j 
 * @return int : le nombre de tours restants pendant lesquels la proba par capital est augmentée
 */
int getToursRestantsBonusProbaParCapital(joueuse j){
    return j->tours_restants_bonus_proba_par_capital;
}

/**
 * @brief modifie le nombre de tours restants pendant lesquels la proba par capital est augmentée
 * 
 * @param j 
 * @param toursRestants : le nouveau nombre de tours restants pendant lesquels la proba par capital est augmentée
 */
void setToursRestantsBonusProbaParCapital(joueuse j, int toursRestants){
    j->tours_restants_bonus_proba_par_capital = toursRestants;
}

/** 
 * @brief renvoit une joueuse :
 *          - on initialise le capital à 5
            - on initialise les 5 membres du joueurs
            - on initialise la main_du_joueur avec 5 cartes aléatoires
            - on associe à la joeuse une clée unique (1 ou 2)-> cette clef permet de savoir qui est le joueur n°1
 * @param n un entier si n=0 on cree un monstre dans un ensemble de monstres, si n=1 on cree une joueuse
 * @param liste_cartes_global la liste de toutes les cartes du jeu
 * @return joueuse un pointeur vers la joueuse crée
*/
joueuse creation_joueuse(int n, liste_cartes liste_cartes_global){
    if(n!=1 && n!=2 && n!=0){
        fprintf(stderr," creation_joueuse : n doit avoir pour valeur 0 , 1 ou 2");
        exit(1);
    }

    joueuse jou=malloc(sizeof(struct joueuse));
    setCapital(jou, CAPITAL_DE_BASE);
    setIdJoueuse(jou, n);
    if (n == 0 ) {
        setTour(jou, -1);
    }
    else {
        setTour(jou, n%2);
    }
    personnage* liste_membres = (personnage *) malloc (sizeof(personnage));
    jou->membres = liste_membres;
    setTaille(jou, 0);
    if (n == 0) {
        personnage monstre = nouveauPersonnage(n, 1, 1);
        addMembres(jou, monstre);
    }
    
}

/**
 * @brief libère l'espace mémoire occupée par la case mémoire pointée par pj
 * @param pj pointeur vers la case mémoire occupée par la joueuse que l'on souhaite libérer
*/
void free_joueuse(joueuse pj){
    for(int i=0;i<getTaille(pj);i++){
        free(pj->membres[i]);
    }
    for(int i=0;i<getNbCartes(getMain(pj));i++){
        free(pj->main_du_joueur->cartes[i]);
    }
    free(pj->main_du_joueur);
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
    if((getTour(pj1)==0 && getTour(pj2)==0) || (getTour(pj1)==1 && getTour(pj2)==1) ){ // Utile pour un futur débugage
        fprintf(stderr,"tour_joueuse : le tour des 2 joueuses est à 0 ou 1");
        exit(2);
    }
    else if(getTour(pj1)==1 && getTour(pj2)==0){
        return pj1;
    }
    else {
        return pj2;
    }
}

/**
 * @brief renvoie le nombre de membres de la joueuse
 * @param pj  pointeur vers la joueuse dont on veut connaitre le nombre de membre
*/
int nb_membre_ecole(joueuse pj){
    if(getTaille(pj)>7){
        fprintf(stderr,"nb_membre_ecole : joueuse %d possède plus de 7 membres",getIdJoueuse(pj));
        exit(3);
    }
    else if(getTaille(pj)<0){
        fprintf(stderr,"nb_membre_ecole : joueuse %d possède en dessous de 0 membres",getIdJoueuse(pj));
        exit(4);
    }
    else {
        return getTaille(pj);
    }
}

/**
 * @brief on test si tous les membres d'une joueuse ont été mangés
 * @param pj pointeur vers la joueuse dont on veux savoir s'il lui reste des membres
 * @return 1 (=vrai) si tous les membres sont mangés et 0 (=faux) sinon
*/
int tous_manges(joueuse pj){
    if(getTaille(pj)==0){
        return 1;
    }
    int manges=0;
    for(int i=0;i<getTaille(pj);i++){
        if(getStatut(getMembres(pj)[i])==0){
            manges+=1;
        }
    }
    if(manges==getTaille(pj)){
        return 1;
    }
    else if(getTaille(pj)<0){
        fprintf(stderr,"tous_manges : joueuse %d possède en dessous de 0 membres",getIdJoueuse(pj));
        exit(5);
    }
    else {
        return 0;
    }
}

/**
 * @brief on réinitialise le capital de la joueuse choisie (on le remet à 5) on gère en meme temps les bonus dans cette fonction (tours_restants)
 * @param pj pointeur vers la joueuse dont le capital va être réinitialisé
*/
void reinitialise_capital(joueuse pj){
    setCapital(pj,CAPITAL_DE_BASE);
    setBonusTemporaire(pj,1);
}

/**
 * @brief on retire du capital à la joueuse sélectionnée du montant choisit (en vérifiant que son capital ne passe pas en négatif)
 * @param pj pointeur vers la joueuse dont le capital va être modifié
 * @param capital entier que l'on va soustraire au capital de la joueuse
*/
void utilise_capital(joueuse pj, int capital){
    if(getCapital(pj)-capital<0){
        fprintf(stderr,"utilise_capital : joueuse %d %d-%d négatif",getIdJoueuse(pj),getCapital(pj),capital);
        exit(6);
    }
    else{
        setCapital(pj,getCapital(pj)-capital);
    }
}

/**
 * @brief la carte c est retirer de la main du joueur et on applique les effets de la carte (il faut aussi s'assurer que le joueur possède la carte)
 * @param liste_joueuses liste des joueuses dont monstres
 * @param liste_zones liste des zones du jeu
 * @param c la carte que la joueuse souhaite jouer
*/
void utilise_carte(joueuse* liste_joueuses, zones liste_zones, carte c){
    int exist_carte=0;
    for(int i=0;i<getNbCartes(getMain(liste_joueuses[0]));i++){
        if(lecture_cartes(getMain(liste_joueuses[0]),i)==c){
            exist_carte=1;
            break;
        }
    }
    if(exist_carte==1){
        wrapper_pouvoir_carte(liste_joueuses,liste_zones,getNom(c));
        suppr_cartes(liste_joueuses[0],c);
    }
    else{
         printf("La carte utilisé n'est pas dans votre main, joueuse %d",getIdJoueuse(liste_joueuses[0]));
    }
}


