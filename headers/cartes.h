/**
 * \file cartes.h
 * Ce fichier décrit le type \b carte qui sera composé d'un \b nom et d'une \b description tout deux de type \b char* .
 * De plus, par la suite un tableau statique de taille 20 qui contiendra les 20 cartes du jeu sera implémenté dans le \b main.c au début,
 * ainsi que 2 autres tableaux de cartes de taille 5 contenant les cartes tirées qui seront la main de chaque joueur.
*/

struct carte{
    char* nom;
    char* description;
};
typedef struct carte* carte;

/**
 * Idée d'implémentation dans le .c :
 * carte carte_test=(carte)malloc(sizeof(struct carte));
 * carte_test->nom="...";
 * carte_test->description="...";
 *
 * Implémenter une fonction "pouvoir" pour chaque carte puis créer une autre fonction qui va appeler la fonction "pouvoir"    correspondant au nom de la carte
 */

 /**
 * \brief Créer une carte vide
 * \return Retourne une carte vide
*/
carte creer_carte();

/**
 * @brief renvoie le nom d'une carte
 * 
 * @param c 
 * @return char* le nom de la carte
 */
char* getNom(carte c);

/**
 * @brief renvoie la description de la carte
 * 
 * @param c 
 * @return char* la description
 */
char* getDescription(carte c);

/**
 * \brief Execute le pouvoir de la carte Massinissa Merabet
 * \param jou Pour savoir sur quelle joueuse intéragir
 * \return rien
 */
void pouvoir_carte_Merabet(joueuse jou);

/**
 * \brief Execute le pouvoir de la carte Fetia Bannour
 * \param z1,z2 Pour savoir sur quelle zone échanger les personnages
 * \param list_joueuses La liste de tout les joueurs afin de savoir la zone courante de chacun des personnages de chaque joueur
 * \return rien
 */
void pouvoir_carte_Bannour(zone z1,zone z2,joueuse* list_joueuses);

/**
 * \brief Execute le pouvoir de la carte  Valentin Honoré
 * \param z1,z2 Pour savoir sur quelle zone échanger les personnages
 * \param list_joueuses_dont_monstres La liste de tout les joueurs et monstres afin de savoir la zone courante de chacun des personnages de chaque joueur
 * \return rien
 */
void pouvoir_carte_Bannour(joueuse* list_joueuses_dont_monstres);


