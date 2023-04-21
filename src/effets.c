/**
 * @file effets.c
 * @author Victor Tan
 * @brief Fichier d'implémentation des effets de cartes
 * @necessities effets.h
 * 
 */

#include "../headers/effets.h"

/**
 * @brief Execute le pouvoir de la carte Massinissa Merabet
 * Pendant vos 3 prochains tours, votre capital augmente de 2
 * @param jou Pour savoir sur quelle joueuse intéragir
 * @return rien
 */
void pouvoir_carte_Merabet(joueuse jou) {
    setToursRestantsBonusCapital(jou, 3);
    setCapital(jou, getCapital(jou) + 2);
}

/**
 * @brief Execute le pouvoir de la carte Fetia Bannour
 * Choisissez deux zones, les personnages présents sur ces deux zones sont échangés
 * @param z1,z2 Pour savoir sur quelle zone échanger les personnages
 * @param list_joueuses La liste de tout les joueurs afin de savoir la zone courante de chacun des personnages de chaque joueur
 * @return rien
 */
void pouvoir_carte_Bannour(zone z1, zone z2, joueuse* list_joueuses) {
    int zone_1 = getNumero(z1);
    int zone_2 = getNumero(z2);
    for (int i = 0; i < 2; i += 1) {
        for (int j = 0; j < getTaille(list_joueuses[i]); j += 1) {
            if (getZoneCourante(getMembres(list_joueuses[i])[j]) == zone_1) {
                setZoneCourante(getMembres(list_joueuses[i])[j], zone_2); 
            }
            else if (getZoneCourante(getMembres(list_joueuses[i])[j]) == zone_2) {
                setZoneCourante(getMembres(list_joueuses[i])[j], zone_1);
            }
        }
    }
}

/**
 * @brief Execute le pouvoir de la carte  Valentin Honoré
 * Chaque montre se déplace 3 fois. Chaque membre d'école qu'un monstre rencontre est mangé
 * @param list_joueuses_dont_monstres La liste de tout les joueurs et monstres afin de savoir la zone courante de chacun des personnages de chaque joueur
 * @return rien
 */
void pouvoir_carte_Honore(joueuse* list_joueuses_dont_monstres) {
    for (int i = 0; i < 3; i += 1) {
        for (int j = 0; j < getTaille(list_joueuses_dont_monstres[2]); j += 1) {
            
        }
    }
}

/**
 * @brief Execute le pouvoir de la carte Renaud Rioboo
 * Lors du prochain tour, la joueuse adverse ne choisit pas comment est utilisé son capital. Chaque 
 * point de capital est utilisé aléatoirement: pour chaque point, choisissez les trois zones Z1, Z2 et 
 * Z3 uniformément parmi les triplets pouvant être choisis.
 * @param list_joueuses La liste de tout les joueurs afin d'avoir les informations sur les 2 joueuses
 * @param zo l'ensemble des zones où la proba va être modifié pour certaines 
 * @return rien
 */
void pouvoir_carte_Rioboo(joueuse* list_joueuses, zones zo);

/**
 * @brief Execute le pouvoir de la carte Kevin Goilard
 * Lors du prochain tour et du suivant, c'est vous qui jouez. Lors des deux 
 * tours suivant, c'est la joueuse adverse qui joue.
* @param list_joueuses permet d'avoir l'ensemble des 2 joueuses
 * @return rien
 */
void pouvoir_carte_Goilard(joueuse* list_joueuses);


/**
 * @brief Execute le pouvoir de la carte Laurence Bourard
 * Lors du prochain déplacement, si deux membres d'écoles adverses se retrouvent sur la même zone,
 * ils se déplacent de nouveau. Si ces deux membres sont sur la zone du monstre avant le second déplacement,
 * ils ne sont pas mangés. On recommence l'opération au plus 100 fois, jusqu'à ce que les membres des écoles 
 * adverses soient sur des zones distinctes.
 * @param list_joueuses permet d'avoir l'ensemble des 2 joueuses et des monstres
 * @return rien
*/
void pouvoir_carte_Bourard(joueuse* list_joueuses);

/**
 * @brief Execute le pouvoir de la carte Denisse Munante
 * Les membres d'écoles présents sur la zone où était un monstre avant son dernier déplacement sont mangés.
 * @param list_joueuses permet d'avoir l'ensemble des 2 joueuses et des monstres
 * @return rien
*/
void pouvoir_carte_Munante(joueuse* list_joueuses);

/**
 * @brief Execute le pouvoir de la carte Cyril Benezet
 * Déplacez un des monstres sur la zone de votre choix. Si un membre d'école se trouve sur la zone du monstre, il n'est pas mangé.
 * @param list_joueuses permet d'avoir l'ensemble des 2 joueuses et des monstres
 * @return rien
*/
void pouvoir_carte_Benezet(joueuse* list_joueuses);

/**
 * @brief Execute le pouvoir de la carte Anne-Laure Ligozat
 * Choisissez un membre de votre école, il effectue désormais deux déplacements au lieu d'un à chaque tour.
 * @param jou permet d'avoir la joueuse
 * @return rien
*/
void pouvoir_carte_Ligozat(joueuse jou);

/**
 * @brief Execute le pouvoir de la carte Christophe Mouilleron
 * Choisissez un membre de l'école de la joueuse adverse. Ce membre devient un membre de votre école.
 * @param list_joueuses permet d'avoir l'ensemble des 2 joueuses et des monstres
 * @return rien
*/
void pouvoir_carte_Mouilleron(joueuse* list_joueuses);

/**
 * @brief Execute le pouvoir de la carte Djibril-Aurelien Dembele-Cabot
 * Sacrifiez un membre de votre école de votre choix. Vous avez 15 points de capital en plus à votre
 * prochain tour.
 * @param jou permet d'avoir la joueuse
 * @return rien
 */
void pouvoir_carte_DembeleCabot(joueuse jou);

/**
 * @brief Execute le pouvoir de la carte Lucienne Pacave
 * Créez une nouvelle zone. Les membres de votre école sont les seuls à pouvoir se déplacer sur cette zone.
 * Un membre de l'école de l'autre joueuse qui devrait se déplacer sur cette zone ne se déplace pas.
 * La probabilité d'aller sur cette zone est de 0. Depuis cette zone, la probabilité de rester sur cette zone est 1.
 * @param zo permet d'avoir l'ensemble des zones
 * @return rien
 */
void pouvoir_carte_Pacave(zones zo);

/**
 * @brief Execute le pouvoir de la carte Jerome Huet
 * Chaque zone effectue une rotation de probabilité. La probabilité d'aller de la zone i à la zone j devient la 
 * probabilité d'aller de la zone i à la zone j + 1. La probabilité d'aller de la zone i à la zone 10 devient la
 * probabilité d'aller de la zone i à la zone 1.
 * @param zo permet d'avoir l'ensemble des zones
 * @return rien
 */
void pouvoir_carte_Huet(zones zo);

/**
 * @brief Execute le pouvoir de la carte Christine Matias
 * Chaque monstre disparaît pendant 2 tours. Il réapparaîtra sur la zone d'où il est parti.
 * @param list_monstres permet d'avoir l'ensemble des monstres
 * @return rien
 */
void pouvoir_carte_Matias(joueuse list_monstres);

/**
 * @brief Execute le pouvoir de la carte Katrin Salhab
 * Pendant vos 3 prochains tours, un point de capital permet de déplacer une quantité 
 * 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9 ou 1 de probabilité.
 * @param jou permet d'avoir la joueuse
 * @return rien
 */
void pouvoir_carte_Salhab(joueuse jou);

/**
 * @brief Execute le pouvoir de la carte Sergio Pulido-Nino
 * Mettez à 0 les probabilités permettant de sortir de la zone de chaque monstre et mettez à 1 la probabilité de rester dans la zone de chaque monstre.
 * @param zo permet d'avoir l'ensemble des zones
 * @return rien
 */
void pouvoir_carte_PulidoNino(zones zo);

/**
 * @brief Execute le pouvoir de la carte Dimitri Watel
 * Choisissez un membre de votre école, il devient FISA et effectue désormais son déplacement un tour sur deux.
 * @param jou permet d'avoir la joueuse
 * @return rien
 */
void pouvoir_carte_Watel(joueuse jou);

/**
 * @brief Execute le pouvoir de la carte Marie Szafranski
 * Ajoutez un monstre sur la zone 1, un membre de votre école sur la zone 2 et un membre de l'école adverse sur 
 * la zone 3. Si un membre d'école se trouve sur la même zone qu'un monstre, il n'est pas mangé.
 * @param list_joueuses permet d'avoir l'ensemble des 2 joueuses et des monstres
 * @return rien
 */
void pouvoir_carte_Szafranski(joueuse* list_joueuses);

/**
 * @brief Execute le pouvoir de la carte Julien Forest
 * Mettez toutes les probabilités à 0. Puis, pour chaque zone, la probabilité de se déplacer de cette zone vers la zone contenant
 *  le monstre passe à 0.5 (s'il y a plusieurs monstres, un des monstres est choisi au hasard) ; et la probabilité de se déplacer de cette zone vers une autre zone ne contenant pas de monstre choisie aléatoirement passe également à 0.5.
 * @param list_joueuses permet d'avoir l'ensemble des 2 joueuses et des monstres
 * @return rien
 */
void pouvoir_carte_Forest(joueuse* list_joueuses);

/**
 * @brief Execute le pouvoir de la carte Laurent Prével
 * Pendant 4 tours, les membres de votre école ne peuvent être mangés par un monstre. S'ils sont sur 
 * sa zone à la fin du tour, rien ne se passe, ils restent sur cette case.
 * @param jou permet d'avoir la joueuse
 * @return rien
*/
void pouvoir_carte_Prevel(joueuse jou);

