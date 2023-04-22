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

#include "headers/joueuses.h"
#include "headers/zones.h"
#include "headers/personnages.h"
#include "headers/cartes.h"


/**
 * @brief test si la joueuse est initialisée
 * 
 * @param nothing
 * 
 * @return int 1 si initialisée correctement, 0 sinon
 * 
 */
int test_init_joueuses()
{
    joueuse j = creation_joueuse(1); /*on créé une joueuse*/
    if (j==NULL){
        return 0;
    }
    if (getCapital(j) != 5){
        fprintf(stderr,"pb capital\n");
        return 0;
    }
    if (getTaille(j) != 5){
        fprintf(stderr,"pb taille\n");
        return 0;
    }
    if (getIdJoueuse(j) != 1){
        fprintf(stderr,"pb id\n");
        return 0;
    }
    if (getTour(j) != 1){
        fprintf(stderr,"pb tour\n");
        return 0;
    }
    if (getToursRestantsBonusCapital(j) != 1){
        fprintf(stderr,"pb tours restants bonus capital\n");
        return 0;
    }
    if (getToursInvincibilite(j) != 0){
        fprintf(stderr,"pb tours invinsibilite\n");
        return 0;
    }
    if (getToursRestantsJouer(j) != 1){
        fprintf(stderr,"pb tours restants jouer\n");
        return 0;
    }
    if (getProbaParCapital(j) != 0.1){
        fprintf(stderr,"pb proba par capital\n");
        return 0;
    }
    if (getMain(j) == NULL){
        fprintf(stderr,"pb mains\n");
        return 0;
    }
    if (getMembres(j) == NULL){
        fprintf(stderr,"pb membres\n");
        return 0;
    }
    //tester la création des personnages
    free(j);

    joueuse m = creation_joueuse(0); /*on créé un monstre*/
    //adapter aux valeurs choisit par adam dans la fonction creation_joueuse
    if (m==NULL){
        return 0;
    }
    if (getCapital(m) != -1){
        fprintf(stderr,"pb capital\n");
        return 0;
    }
    if (getTaille(m) != 1){
        fprintf(stderr,"pb taille\n");
        return 0;
    }
    if (getIdJoueuse(m) != 0){
        fprintf(stderr,"pb id\n");
        return 0;
    }
    if (getTour(m) != 1){
        fprintf(stderr,"pb tour\n");
        return 0;
    }
    if (getToursRestantsBonusCapital(m) != 1){
        fprintf(stderr,"pb tours restants bonus capital\n");
        return 0;
    }
    if (getToursInvincibilite(m) != -1){
        fprintf(stderr,"pb tours invinsibilite\n");
        return 0;
    }
    if (getToursRestantsJouer(m) != 1){
        fprintf(stderr,"pb tours restants jouer\n");
        return 0;
    }
    if (getProbaParCapital(m) != 0.1){
        fprintf(stderr,"pb proba par capital\n");
        return 0;
    }
    if (getMain(m) == NULL){
        fprintf(stderr,"pb mains\n");
        return 0;
    }
    if (getMembres(m) == NULL){
        fprintf(stderr,"pb membres\n");
        return 0;
    }
    //tester la création des personnages
    free(m);
    fprintf(stdout,"test init joueuses ok\n");
    return 1;
}


/**
 * @brief test si les zones sont initialisées correctement
 * 
 * @param nothing
 * 
 * @return int 1 si initialisée correctement, 0 sinon
 * 
 */
int test_init_zones(){
    zones z = nouvellesZones(); /*on créé 10 zones*/
    if (z==NULL){
        fprintf(stderr,"NULL pointer");
        return 0;
    }
    if (getMatrice(z)->taille != 10){
        fprintf(stderr,"pb nb zones\n");
        return 0;
    }
    for (int i=0; i<10; i++){
    if (getTabZones(z)[i] == NULL){
            fprintf(stderr,"pb zone %d\n",i);
            return 0;
        }
        for (int j=0; j<getMatrice(z)->taille; j++){
            if (lecture_probas(getMatrice(z),i,j) != 0.1){
                fprintf(stderr,"pb proba %d %d\n",i,j);
                return 0;
            }
            }
        }
    free(z);
    fprintf(stdout,"test init zones ok\n");
    return 1;
}


/**
 * @brief test si les personnages sont initialisés correctement
 * 
 * @param nothing
 * 
 * @return int 1 si initialisée correctement, 0 sinon
*/
int test_init_personnage(){
    zones zs = nouvellesZones();
    personnage perso  = nouveauPersonnage(1,trouveZone(zs,0));//membre de l'équipe 1
    if (perso == NULL){
        fprintf(stderr,"NULL pointer");
        return 0;
    }
    //tester le type:
    if (getType(perso) != 1){
        fprintf(stderr,"pb type joueur 1\n");
        return 0;
    }
    //tester le statut:
    if (getStatut(perso) != 1){
        fprintf(stderr,"pb statut\n");
        return 0;
    }
    //tester id:
    if (getIdPersonnage(perso) != 1){
        fprintf(stderr,"pb id\n");
        return 0;
    }
    //tester la zone courante:
    if (getZoneCourante(perso) != getNumero(trouveZone(zs,0))){
        fprintf(stderr,"pb zone courante\n");
        return 0;
    }
    //tester la zone précédente:
    if (getZonePrecedente(perso) != getNumero(trouveZone(zs,0))){
        fprintf(stderr,"pb zone precedente\n");
        return 0;
    }
    //tester le nombre de pas:
    if (getNbPas(perso) != 1){
        fprintf(stderr,"pb nb pas\n");
        return 0;
    }
    //tester le nombre de tours restants:
    if (getNbTourDisparuRestant(perso) != 0){
        fprintf(stderr,"pb nb tours restants\n");
        return 0;
    }
    //tester si le personnage peut se déplacer:
    if (getPeutSeDeplacer(perso) != 1){
        fprintf(stderr,"pb peut se deplacer\n");
        return 0;
    }
    free(perso);

    personnage perso2 = nouveauPersonnage(2,trouveZone(zs,0));//memebre de l'équipe 2
    if (perso2 == NULL){
        fprintf(stderr,"NULL pointer");
        return 0;
    }
    //tester le type:
    if (getType(perso2) != 2){
        fprintf(stderr,"pb type joueur 2\n");
        return 0;
    }
    //tester le statut:
    if (getStatut(perso2) != 1){
        fprintf(stderr,"pb statut\n");
        return 0;
    }
    //tester id:
    if (getIdPersonnage(perso2) != 1){
        fprintf(stderr,"pb id\n");
        return 0;
    }
    //tester la zone courante:
    if (getZoneCourante(perso2) != getNumero(trouveZone(zs,0))){
        fprintf(stderr,"pb zone courante\n");
        return 0;
    }
    //tester la zone précédente:
    if (getZonePrecedente(perso2) != getNumero(trouveZone(zs,0))){
        fprintf(stderr,"pb zone precedente\n");
        return 0;
    }
    //tester le nombre de pas:
    if (getNbPas(perso2) != 1){
        fprintf(stderr,"pb nb pas\n");
        return 0;
    }
    //tester le nombre de tours restants:
    if (getNbTourDisparuRestant(perso2) != 0){
        fprintf(stderr,"pb nb tours restants\n");
        return 0;
    }
    //tester si le personnage peut se déplacer:
    if (getPeutSeDeplacer(perso2) != 1){
        fprintf(stderr,"pb peut se deplacer\n");
        return 0;
    }
    free(perso2);

    personnage monstre = nouveauPersonnage(0,trouveZone(zs,0));//monstre
    if (monstre == NULL){
        fprintf(stderr,"NULL pointer");
        return 0;
    }
    //tester le type:
    if (getType(monstre) != 0){
        fprintf(stderr,"pb type monstre\n");
        return 0;
    }
    //tester le statut:
    if (getStatut(monstre) != 1){
        fprintf(stderr,"pb statut\n");
        return 0;
    }
    //tester id:
    if (getIdPersonnage(monstre) != 1){
        fprintf(stderr,"pb id\n");
        return 0;
    }
    //tester la zone courante:
    if (getZoneCourante(monstre) != getNumero(trouveZone(zs,0))){
        fprintf(stderr,"pb zone courante\n");
        return 0;
    }
    //tester la zone précédente:
    if (getZonePrecedente(monstre) != getNumero(trouveZone(zs,0))){
        fprintf(stderr,"pb zone precedente\n");
        return 0;
    }
    //tester le nombre de pas:
    if (getNbPas(monstre) != 1){
        fprintf(stderr,"pb nb pas\n");
        return 0;
    }
    //tester le nombre de tours restants:
    if (getNbTourDisparuRestant(monstre) != 0){
        fprintf(stderr,"pb nb tours restants\n");
        return 0;
    }
    //tester si le personnage peut se déplacer:
    if (getPeutSeDeplacer(monstre) != 1){
        fprintf(stderr,"pb peut se deplacer\n");
        return 0;
    }
    free(monstre);
    fprintf(stdout,"test init personnage ok\n");
    return 1;
}


int test_vie_d_un_personnage(){
    personnage perso = nouveauPersonnage(1,trouveZone(zs,0));
    if (getPeutSeDeplacer(perso)){ //on test si le personnage peut se déplacer sur chacune des zones
        for (int i, i<10, i++){
            deplacer(perso,i);
        }
    }
    setStatut(perso,0);
    if (getStatut(perso) != 0){
        fprintf(stderr,"probleme de mis a jour du statut à 0\n");
    }
    setStatut(perso,1); 
    if (getStatut(perso) != 1){
        fprintf(stderr,"probleme de mis a jour du statut à 1\n");
    }
    setStatut(perso,-1);
    if (getStatut(perso) != -1){
        fprintf(stderr,"probleme de mis a jour du statut à -1\n");
    }
    setStatut(perso,3);
    if (getStatut(perso) != 3){
        fprintf(stderr,"probleme de mis a jour du statut à 3\n");
    }
    estMange(personnage perso);
    if (getStatut(perso) != 0){
        fprintf(stderr,"probleme de mis a jour du statut lorsque le personnage est mangé\n");
    }
    free(perso);
    fprintf(stdout,"test vie d'un personnage ok\n");
    return 1;
}

int test_modif_proba_avec_capital(){
    
}

int main(){
    int test_zones = test_init_zones();
    int test_joueuses = test_init_joueuses();
    int test_personnage = test_init_personnage();
    return 0;
}