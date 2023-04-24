/**
 * @file test.c
 * @author Théo TAILLEFUMIER 
 * @brief 
 * @necessities 
 * @date 2023-03-31
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#include "./headers/joueuses.h"
#include "./headers/zones.h"
#include "./headers/personnages.h"
#include "./headers/cartes.h"
#include "./headers/structures.h"


/**
 * @brief test si la joueuse est initialisée
 * 
 * @param nothing
 * 
 * @return nothing
 * 
 */
void test_init_joueuses()
{
    joueuse j = creation_joueuse(1); /*on créé une joueuse*/
    if (j==NULL){
        free_joueuse(j);
        return;
    }
    if (getCapital(j) != 5){
        fprintf(stderr,"pb capital\n");
        free_joueuse(j);
        return;
    }
    if (getTaille(j) != 5){
        fprintf(stderr,"pb taille\n");
        free_joueuse(j);
        return;
    }
    if (getIdJoueuse(j) != 1){
        fprintf(stderr,"pb id\n");
        free_joueuse(j);
        return;
    }
    if (getTour(j) != 1){
        fprintf(stderr,"pb tour\n");
        free_joueuse(j);
        return;
    }
    if (getToursRestantsBonusCapital(j) != 1){
        fprintf(stderr,"pb tours restants bonus capital\n");
        free_joueuse(j);
        return;
    }
    if (getToursInvincibilite(j) != 0){
        fprintf(stderr,"pb tours invinsibilite\n");
        free_joueuse(j);
        return;
    }
    if (getToursRestantsJouer(j) != 1){
        fprintf(stderr,"pb tours restants jouer\n");
        free_joueuse(j);
        return;
    }
    if (getProbaParCapital(j) != 0.1){
        fprintf(stderr,"pb proba par capital\n");
        free_joueuse(j);
        return;
    }
    if (getMain(j) == NULL){
        fprintf(stderr,"pb mains\n");
        free_joueuse(j);
        return;
    }
    if (getMembres(j) == NULL){
        fprintf(stderr,"pb membres\n");
        free_joueuse(j);
        return;
    }
    //tester la création des personnages
    free_joueuse(j);

    joueuse m = creation_joueuse(0); /*on créé un monstre*/
    //adapter aux valeurs choisit par adam dans la fonction creation_joueuse
    if (m==NULL){
        free_joueuse(m);
        return;
    }
    if (getCapital(m) != -1){
        fprintf(stderr,"pb capital\n");
        free_joueuse(m);
        return;
    }
    if (getTaille(m) != 1){
        fprintf(stderr,"pb taille\n");
        free_joueuse(m);
        return;
    }
    if (getIdJoueuse(m) != 0){
        fprintf(stderr,"pb id\n");
        free_joueuse(m);
        return;
    }
    if (getTour(m) != 1){
        fprintf(stderr,"pb tour\n");
        free_joueuse(m);
        return;
    }
    if (getToursRestantsBonusCapital(m) != 1){
        fprintf(stderr,"pb tours restants bonus capital\n");
        free_joueuse(m);
        return;
    }
    if (getToursInvincibilite(m) != -1){
        fprintf(stderr,"pb tours invinsibilite\n");
        free_joueuse(m);
        return;
    }
    if (getToursRestantsJouer(m) != 1){
        fprintf(stderr,"pb tours restants jouer\n");
        free_joueuse(m);
        return;
    }
    if (getProbaParCapital(m) != 0.1){
        fprintf(stderr,"pb proba par capital\n");
        free_joueuse(m);
        return;
    }
    if (getMain(m) == NULL){
        fprintf(stderr,"pb mains\n");
        free_joueuse(m);
        return;
    }
    if (getMembres(m) == NULL){
        fprintf(stderr,"pb membres\n");
        free_joueuse(m);
        return;
    }
    //tester la création des personnages
    free_joueuse(m);
    fprintf(stdout,"test init joueuses ok\n");
}


/**
 * @brief test si les zones sont initialisées correctement
 * 
 * @param nothing
 * 
 * @return nothing
 * 
 */
void test_init_zones(){
    zones z = nouvellesZones(); /*on créé 10 zones*/
    if (z==NULL){
        fprintf(stderr,"NULL pointer");
        libereZones(z);
        return;
    }
    if (getTailleMatrice(getMatrice(z)) != 10){
        fprintf(stderr,"pb nb zones\n");
        libereZones(z);
        return;
    }
    for (int i=0; i<10; i++){
    if (getTabZones(z)[i] == NULL){
            fprintf(stderr,"pb zone %d\n",i);
            libereZones(z);
            return;
        }
        for (int j=0; j<getTailleMatrice(getMatrice(z)); j++){
            if (lecture_probas(getMatrice(z),i,j) != 0.1){
                fprintf(stderr,"pb proba %d %d\n",i,j);
                libereZones(z);
                return;
            }
            }
        }
    free(z);
    fprintf(stdout,"test init zones ok\n");
}


/**
 * @brief test si les personnages sont initialisés correctement
 * 
 * @param nothing
 * 
 * @return nothing
*/
void test_init_personnage(){
    zones zs = nouvellesZones();
    personnage perso  = nouveauPersonnage(1,trouveZone(zs,0));//membre de l'équipe 1
    if (perso == NULL){
        fprintf(stderr,"NULL pointer");
        libereZones(zs);
        liberePersonnage(perso);
        return;
    }
    //tester le type:
    if (getType(perso) != 1){
        fprintf(stderr,"pb type joueur 1\n");
        libereZones(zs);
        liberePersonnage(perso);
        return;
    }
    //tester le statut:
    if (getStatut(perso) != 1){
        fprintf(stderr,"pb statut\n");
        libereZones(zs);
        liberePersonnage(perso);
        return;
    }
    //tester id:
    if (getIdPersonnage(perso) != 1){
        fprintf(stderr,"pb id\n");
        libereZones(zs);
        liberePersonnage(perso);
        return;
    }
    //tester la zone courante:
    if (getZoneCourante(perso) != getNumero(trouveZone(zs,0))){
        fprintf(stderr,"pb zone courante\n");
        libereZones(zs);
        liberePersonnage(perso);
        return;
    }
    //tester la zone précédente:
    if (getZonePrecedente(perso) != getNumero(trouveZone(zs,0))){
        fprintf(stderr,"pb zone precedente\n");
        libereZones(zs);
        liberePersonnage(perso);
        return;
    }
    //tester le nombre de pas:
    if (getNbPas(perso) != 1){
        fprintf(stderr,"pb nb pas\n");
        libereZones(zs);
        liberePersonnage(perso);
        return;
    }
    //tester le nombre de tours restants:
    if (getNbTourDisparuRestant(perso) != 0){
        fprintf(stderr,"pb nb tours restants\n");
        libereZones(zs);
        liberePersonnage(perso);
        return;
    }
    //tester si le personnage peut se déplacer:
    if (getPeutSeDeplacer(perso) != 1){
        fprintf(stderr,"pb peut se deplacer\n");
        libereZones(zs);
        liberePersonnage(perso);
        return;
    }
    liberePersonnage(perso);

    personnage perso2 = nouveauPersonnage(2,trouveZone(zs,0));//memebre de l'équipe 2
    if (perso2 == NULL){
        fprintf(stderr,"NULL pointer");
        libereZones(zs);
        liberePersonnage(perso2);
        return;
    }
    //tester le type:
    if (getType(perso2) != 2){
        fprintf(stderr,"pb type joueur 2\n");
        libereZones(zs);
        liberePersonnage(perso2);
        return;
    }
    //tester le statut:
    if (getStatut(perso2) != 1){
        fprintf(stderr,"pb statut\n");
        libereZones(zs);
        liberePersonnage(perso2);
        return;
    }
    //tester id:
    if (getIdPersonnage(perso2) != 1){
        fprintf(stderr,"pb id\n");
        libereZones(zs);
        liberePersonnage(perso2);
        return;
    }
    //tester la zone courante:
    if (getZoneCourante(perso2) != getNumero(trouveZone(zs,0))){
        fprintf(stderr,"pb zone courante\n");
        libereZones(zs);
        liberePersonnage(perso2);
        return;
    }
    //tester la zone précédente:
    if (getZonePrecedente(perso2) != getNumero(trouveZone(zs,0))){
        fprintf(stderr,"pb zone precedente\n");
        libereZones(zs);
        liberePersonnage(perso2);
        return;
    }
    //tester le nombre de pas:
    if (getNbPas(perso2) != 1){
        fprintf(stderr,"pb nb pas\n");
        libereZones(zs);
        liberePersonnage(perso2);
        return;
    }
    //tester le nombre de tours restants:
    if (getNbTourDisparuRestant(perso2) != 0){
        fprintf(stderr,"pb nb tours restants\n");
        libereZones(zs);
        liberePersonnage(perso2);
        return;
    }
    //tester si le personnage peut se déplacer:
    if (getPeutSeDeplacer(perso2) != 1){
        fprintf(stderr,"pb peut se deplacer\n");
        libereZones(zs);
        liberePersonnage(perso2);
        return;
    }
    free(perso2);

    personnage monstre = nouveauPersonnage(0,trouveZone(zs,0));//monstre
    if (monstre == NULL){
        fprintf(stderr,"NULL pointer");
        libereZones(zs);
        liberePersonnage(monstre);
        return;
    }
    //tester le type:
    if (getType(monstre) != 0){
        fprintf(stderr,"pb type monstre\n");
        libereZones(zs);
        liberePersonnage(monstre);
        return;
    }
    //tester le statut:
    if (getStatut(monstre) != 1){
        fprintf(stderr,"pb statut\n");
        libereZones(zs);
        liberePersonnage(monstre);
        return;
    }
    //tester id:
    if (getIdPersonnage(monstre) != 1){
        fprintf(stderr,"pb id\n");
        libereZones(zs);
        liberePersonnage(monstre);
        return;
    }
    //tester la zone courante:
    if (getZoneCourante(monstre) != getNumero(trouveZone(zs,0))){
        fprintf(stderr,"pb zone courante\n");
        libereZones(zs);
        liberePersonnage(monstre);
        return;
    }
    //tester la zone précédente:
    if (getZonePrecedente(monstre) != getNumero(trouveZone(zs,0))){
        fprintf(stderr,"pb zone precedente\n");
        libereZones(zs);
        liberePersonnage(monstre);
        return;
    }
    //tester le nombre de pas:
    if (getNbPas(monstre) != 1){
        fprintf(stderr,"pb nb pas\n");
        libereZones(zs);
        liberePersonnage(monstre);
        return;
    }
    //tester le nombre de tours restants:
    if (getNbTourDisparuRestant(monstre) != 0){
        fprintf(stderr,"pb nb tours restants\n");
        libereZones(zs);
        liberePersonnage(monstre);
        return;
    }
    //tester si le personnage peut se déplacer:
    if (getPeutSeDeplacer(monstre) != 1){
        fprintf(stderr,"pb peut se deplacer\n");
        libereZones(zs);
        liberePersonnage(monstre);
        return;
    }
    free(monstre);
    free(zs);
    fprintf(stdout,"test init personnage ok\n");
}

/**
 * @brief test les déplcements d'un personnage et les modifications de satut ainsi que si le personnage est mangé ou non
 * 
 * @param nothing
 * 
 * @return nothing
*/
void test_vie_d_un_personnage(){
    zones zs = nouvellesZones();
    personnage perso = nouveauPersonnage(1,trouveZone(zs,0));
    if (getPeutSeDeplacer(perso)){ //on test si le personnage peut se déplacer sur chacune des zones
        for (int i=0; i<10; i++){
            deplacer(perso,trouveZone(zs,i));
            if (getZoneCourante(perso) != i){
                fprintf(stderr,"probleme de deplacement\n");
                libereZones(zs);
                return;
            }
        }
    }
    setStatut(perso,0);
    if (getStatut(perso) != 0){
        fprintf(stderr,"probleme de mis a jour du statut à 0\n");
        libereZones(zs);
        return;
    }
    setStatut(perso,1); 
    if (getStatut(perso) != 1){
        fprintf(stderr,"probleme de mis a jour du statut à 1\n");
        libereZones(zs);
        return;
    }
    setStatut(perso,-1);
    if (getStatut(perso) != -1){
        fprintf(stderr,"probleme de mis a jour du statut à -1\n");
        libereZones(zs);
        return;
    }
    setStatut(perso,3);
    if (getStatut(perso) != 3){
        fprintf(stderr,"probleme de mis a jour du statut à 3\n");
        libereZones(zs);
        return;
    }
    estMange(perso);
    if (getStatut(perso) != 0){
        fprintf(stderr,"probleme de mis a jour du statut lorsque le personnage est mangé\n");
        libereZones(zs);
        return;
    }
    free(perso);
    free(zs);
    fprintf(stdout,"test vie d'un personnage ok\n");
}


/**
 * @brief test si la modification de la proba avec le capital fonctionne
 * 
 * @param nothing
 * 
 * @return nothing
*/
void test_modif_proba_avec_capital(){
    zones zs = nouvellesZones();
    joueuse j1 = creation_joueuse(1);
    float coeff = getProbaParCapital(j1);
    for (int i=0; i<10; i++){ //on test si la modif
        float sum = 0;
        for (int j=0; j<10; j++){
            float prob = lecture_probas(getMatrice(zs),i,j);
            modifierZone(zs,i,j,3,1);
            if (3*coeff + prob > 1 || 3*coeff + prob != lecture_probas(getMatrice(zs),i,j)){
                fprintf(stderr,"probleme de modification de la proba avec le capital\n");
                free_joueuse(j1);
                libereZones(zs);
                return;
            }
            sum += lecture_probas(getMatrice(zs),i,j);
        }
        if (sum != 1){
            fprintf(stderr,"probleme de somme des probas\n");
            free_joueuse(j1);
            libereZones(zs);
            return;
        }
    }
    free_joueuse(j1);
    libereZones(zs);
    fprintf(stdout,"test modif proba avec capital ok\n");
}


/**
 * @brief test le déroulement du jeu (vainqueur, fin du jeu, démarage du jeu)
 * 
 * @param nothing
 * 
 * @return nothing
*/
void test_deroulement_du_jeu(){
    joueuse j1 = creation_joueuse(1);
    joueuse j2 = creation_joueuse(2);
    personnage* persos1 = getMembres(j1);
    int i = 0;
    while (persos1[i] != NULL){
        estMange(persos1[i]);
        i++;
    }
    if (!tous_manges(j1)){
        fprintf(stderr,"probleme en fin de partie, le joeur 2 ne peut pas gagner\n");
        free_joueuse(j2);
        free_joueuse(j1);
        return;
    }
    free_joueuse(j1);
    personnage* persos2 = getMembres(j2);
    joueuse j1_ = creation_joueuse(1);
    while (persos2[i] != NULL){
        estMange(persos1[i]);
        i++;
    }
    if (!tous_manges(j2)){
        fprintf(stderr,"probleme en fin de partie, le joeur 1 ne peut pas gagner\n");
        free_joueuse(j2);
        free_joueuse(j1_);
        return;
    }
    free_joueuse(j1_);
    free_joueuse(j2);
}

/**
 * @brief test si l'initialisation de la main d'une joueuse se fait sans problème
 * 
 * @param nothing
 * 
 * @return nothing
*/
void test_init_main(){
    joueuse j = creation_joueuse(1);
    liste_cartes main_j = getMain(j);
    if (getNbCartes(main_j)!=5){
        fprintf(stderr,"erreur: il n'y pas assez de cartes lors de l'initialisation");
        free_joueuse(j);
        return;
    }
    for (int i=0; i<5; i++){
        if(getCartes(main_j)[i]==NULL){
            fprintf(stderr,"erreur: la %d ème carte est NULL",i);
            free_joueuse(j);
            return;
        }
    }
    fprintf(stdout,"test_init_main ok");
}

void test_demarage_du_jeu(){
    joueuse j1 = creation_joueuse(1);
    joueuse j2 = creation_joueuse(2);
    joueuse m = creation_joueuse(0);
    //test s'il n'y a qu'un seul monstre et s'il se trouve dans la zone 1;
    if (getTaille(m)!=1) {
        free_joueuse(m);
        free_joueuse(j2);
        free_joueuse(j1);
        fprintf(stderr,"erreur: il y a plus d'un monstre\n");
        return;
    }
    if (getZone(getMembres(m)[0])!=1){
        free_joueuse(m);
        free_joueuse(j2);
        free_joueuse(j1);
        fprintf(stderr,"erreur: le monstre n'est pas dans la zone 1\n");
        return;
    }
    free_joueuse(m);
    if (getTaille(j1)!=5){
        free_joueuse(j2);
        free_joueuse(j1);
        fprintf(stderr,"erreur: il n'y a pas assez de joueuses\n")
        return;
    }
    if (getTaille(j2)!=5){
        free_joueuse(j2);
        free_joueuse(j1);
        fprintf(stderr,"erreur: il n'y a pas assez de joueuses\n")
        return;
    }
    if (getZone(getMembres(j1)[0])!=2 || getZone(j1)!=3){
        free_joueuse(j2);
        free_joueuse(j1);
        fprintf(stderr,"erreur: la joueuse 1 n'est pas dans la zone 2 ou 3\n")
        return;
    }
    if (getZone(getMembres(j2)[0])!=4 || getZone(j2)!=5){
        free_joueuse(j2);
        free_joueuse(j1);
        fprintf(stderr,"erreur: la joueuse 2 n'est pas dans la zone 4 ou 5\n")
        return;
    }
}

int main(){
    test_init_zones();
    test_init_joueuses();
    test_init_personnage();
    test_vie_d_un_personnage();
    test_modif_proba_avec_capital();
    test_init_main();
    test_deroulement_du_jeu();
    test_demarage_du_jeu();

    return 0;
}