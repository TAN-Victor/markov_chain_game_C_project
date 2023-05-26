##==============================================================================================
# Fichier: interface.py
# Brief: Interface du jeu
# Necessités: effets.py, Python 3.11, Pygame 2.4.0
##==============================================================================================

import sys
import os
import threading

import pygame

current_dir = os.path.dirname(os.path.abspath(sys.argv[0]))+"\package"
sys.path.insert(0, current_dir)
print(current_dir)
os.chdir(current_dir)

from package.effets import *


def main():

    ##================================================================================================
    # Initialisation des variables
    ##================================================================================================

    liste_cartes_globale = [Merabet(), Bannour(), Honore(), Rioboo(), Goilard(), Bourard(), Munante(), Benezet(), Ligozat(), Mouilleron(),
                                      Dembele_Cabot(),  Pacave(), Huet(), Matias(), Salhab(), Pulido_Nino(), Watel(), Szafranski(), Forest(), Prevel()]


    joueuse_1 = Joueuse(1, liste_cartes_globale)
    joueuse_2 = Joueuse(2, liste_cartes_globale)
    monstres = ListeMonstre()

    liste_joueuses = [joueuse_1, joueuse_2, monstres]
    message_generique(1, None, None, None)

    liste_zones = Zones(10)
    message_generique(2, None, None, None)


    i = 0 # // Va valoir 0 si c'est le tour de la joueuse 1, 1 si c'est le tour de la joueuse 2
    etat = 0 # // Va valoir 0 si on est dans la sélection principale, 1 si on choisi le capital, 2 si on choisit une carte, 3 si on choisit une zone, 4 si on est dans un effet de
                # carte, 5 si on est dans un effet de zone, 6 si on est en déplacement

    ##================================================================================================
    # Initialisation de la fenêtre
    ##================================================================================================

    map_objets = {}
    map_boutons = {}


    def initialiser_objets():
        for i in range (0, 3):
            for j in range(0, 6):
                map_objets["personnage_" + str(i+1) + "_" + str(j+1) + "liste"] = (ObjetPersonnageListe(longueur*(70 + i * 10)/100 + 25, 65 + j * 50, 50, "interface/images/" + str(j+1) + "_" + str(i) + ".png", [j+1, "Joueuse n°" + str(i+1)]))
                map_objets["statut_" + str(i+1) + "_" + str(j+1) + "liste"] = (ObjetStatut(longueur*(70 + i * 10)/100 + 85, 75 + j * 50, 100, "interface/images/" + "En vie" + "_" + str(i) + ".png", [j+1, "Joueuse n°" + str(i+1), "En vie"]))
                if (j == 5 or (i == 2 and j != 0)):
                    map_objets["personnage_" + str(i+1) + "_" + str(j+1) + "liste"].cacher()
                    map_objets["statut_" + str(i+1) + "_" + str(j+1) + "liste"].cacher()
        map_objets["tour"] = (ObjetFixe(longueur*(70)/100 + 25, 10, longueur*10/100 -20, None))
        
        for i in range(0, 2):
            for j in range(0, 5):
                map_objets["carte_" + str(i+1) + "_" + str(j+1)] = ObjetCarte(longueur*(70 + i * 10)/100 + 25, 430 + j * 50, -30, "interface/images/" + liste_joueuses[i].liste_cartes[j].getNom() + "_" + str(i) + ".png", [j+1, "Joueuse n°" + str(i+1)])
        
        
        map_boutons["bouton_choix_capital"] = BoutonChoix((longueur*70/100 + 30, largeur*83/100 + 40), (longueur*10/100 - 20, largeur*10/100 - 10), "Utiliser capital", (140, 215, 140), (0, 0, 0))
        map_boutons["bouton_choix_carte"] = BoutonChoix((longueur*80/100 + 30, largeur*83/100 + 40), (longueur*10/100 - 20, largeur*10/100 - 10), "Utiliser carte", (140, 215, 140), (0, 0, 0))
        map_boutons["bouton_choix_rien"] = BoutonChoix((longueur*90/100 + 30, largeur*83/100 + 40), (longueur*8/100 - 10, largeur*10/100 - 10), "Ne rien faire", (227, 140, 140), (0, 0, 0))

        map_boutons["bouton_plus"] = BoutonValeur((longueur*90/100 + 30, largeur*82/100 + 40), (longueur*8/100 - 20, largeur*6/100 - 10), "+", (140, 140, 215), (0, 0, 0))
        map_boutons["bouton_moins"] = BoutonValeur((longueur*72/100 + 30, largeur*82/100 + 40), (longueur*8/100 - 20, largeur*6/100 - 10), "-", (140, 140, 215), (0, 0, 0))
        map_boutons["bouton_valeur"] = BoutonValeur((longueur*80/100 + 30, largeur*82/100 + 40), (longueur*10/100 - 20, largeur*6/100 - 10), BoutonValeur.valeur, (140, 140, 215), (0, 0, 0))
        map_boutons["bouton_valeur_valider"] = BoutonValeur((longueur*70/100 + 30, largeur*92/100 + 20), (longueur*15/100 - 50, largeur*8/100 - 30), "Valider", (50, 227, 50), (0, 0, 0))
        map_boutons["bouton_valeur_annuler"] = BoutonValeur((longueur*85/100 + 30, largeur*92/100 + 20), (longueur*15/100 - 50, largeur*8/100 - 30), "Annuler", (227, 50, 50), (0, 0, 0))

        map_boutons["bouton_carte_valider"] = BoutonValiderCarte((longueur*70/100 + 30, largeur*92/100 + 20), (longueur*15/100 - 50, largeur*8/100 - 30), "Valider", (50, 227, 50), (0, 0, 0))
        map_boutons["bouton_carte_annuler"] = BoutonValeur((longueur*85/100 + 30, largeur*92/100 + 20), (longueur*15/100 - 50, largeur*8/100 - 30), "Annuler", (227, 50, 50), (0, 0, 0))

        couleurs_zones = [(230, 138, 143), (180, 205, 147), (163, 181, 204), (237, 210, 136), (190, 149, 170), (177, 214, 206), (217, 183, 139), (199, 203, 178), (210, 178, 200), (174, 207, 169), (216, 170, 185)]
        for i in range(0, 3):
            for j in range(0, 3):
                map_boutons["zone_" + str(i+3*j+1)] = BoutonZone((40 + i * 420, 40 +j *200), (400, 180), "Zone n°" + str(i+3*j+1), couleurs_zones[i+3*j], (0, 0, 0), "haut_centre", 0, True)
        for i in range(0, 2):
            map_boutons["zone_" + str(i+10)] = BoutonZone((250 + i * 420, 640), (400, 180), "Zone n°" + str(i+10), couleurs_zones[i+9], (0, 0, 0), "haut_centre", 0, True)



        demander_action(map_boutons, map_objets, liste_joueuses[0])





    initialiser_objets()




    ##==============================================================================================
    # Boucle de jeu
    ##==============================================================================================

    continuer = True
    while continuer:
        for event in pygame.event.get():
            fenetre.fill((0, 0, 0)) # Couleur de fond
            joueuses()
            actions()
            zones_jeu()
            console()

            if (liste_joueuses[0].getTour() == True):
                i = 0
            else:
                i = 1


            if event.type == pygame.QUIT:
                continuer = False
            elif event.type == pygame.MOUSEBUTTONDOWN or event.type == pygame.MOUSEBUTTONUP:
                x, y = pygame.mouse.get_pos()
                print(f"Clic en ({x}, {y})")
                for boutons in map_boutons.values():
                    boutons.clic(event, map_boutons, map_objets, liste_joueuses[i])
                    boutons.afficher(fenetre)
                for objets in map_objets.values():
                    objets.clic(event)
                    objets.afficher(fenetre)
                    



            for objets in map_objets.values():
                objets.afficher(fenetre)


            for boutons in map_boutons.values():
                boutons.afficher(fenetre)





        pygame.display.flip() # Rafraichissement de l'écran
        clock.tick(60) # 60 FPS

main()