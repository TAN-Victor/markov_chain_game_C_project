/**
 * \file interface.h
 * Ce fichier décrit un ensemble de fonctions utile à une interface optimale.
 * Il contient les 5 fonctions suivantes :
 * - \b afficher_toute_info(joueuse[],zones,personnage[]) qui permet d'afficher dans la console toutes les informations du jeu: les zones du jeu, les personnages qui sont dessus, la joueuse dont c'est le tour, le capital des joueuses, ...
 * - \b demander_capital(joueuse) pour demander à une joueuse combien de capital elle veut utiliser (elle peut répondre ne pas vouloir en utiliser)
 * - \b demander_carte(joueuse,carte[]) pour demander à une joueuse si elle veut jouer une carte et si oui, laquelle.
 * - \b afficher_fin_du_jeu(joueuse) qui permet d'afficher dans la console un message quand le jeu est fini.
 * - \b afficher_info(personnage,joueuse) pour afficher des messages génériques (par exemple si un membre a été mangé).
*/

/**
 * \brief Affiche dans la console toutes les informations du jeu: les zones du jeu, les personnages qui sont dessus, la joueuse dont c'est le tour, le capital des joueuses, ...
 * \param joueuse[] est un tableau contenant 2 éléments de type joueuse afin de récupérer les informations leur concernant.
 * \param zones afin de récupérer les informations sur toute les zones du jeu.
 * \param personnage[] est un tableau de tout les personnages présent sur le plateau (Pour avoir accès aux informations leurs concernants)
 * \return rien.
*/
void afficher_toute_info(joueuse[],zones,personnage[]);

/**
 * \brief Demande à une joueuse combien de capital elle souhaite utiliser (elle peut répondre ne pas vouloir en utiliser)
 * \param joueuse afin de savoir à quelle joueuse demander.
 * \return le nombre de capital que la joueuse souhaite dépenser, 0 sinon.
*/
int demander_capital(joueuse);

/**
 * \brief Demande à une joueuse si elle veut jouer une carte et si oui, laquelle.
 * \param joueuse afin de savoir à quelle joueuse demander.
 * \param carte[] qui correspond à la main de la joueuse.
 * \return le nom de la carte qu'elle souhaite utiliser, NULL sinon.
*/
char* demander_carte(joueuse,carte[]);

/**
 * \brief Affiche dans la console un message quand le jeu est fini.
 * \param joueuse afin d'avoir l'information si tout les membres de l'école de la joueuse ont été mangés.
 * \return rien.
*/
void afficher_fin_du_jeu(joueuse);

/**
 * \brief Affiche des messages génériques (par exemple si un membre a été mangé).
 * \param joueuse afin d'avoir des informations concernant le joueur.
 * \param personnage afin d'avoir des informations concernant un des personnages du jeu.
 * \return rien.
*/
void afficher_info(joueuse,personnage);

