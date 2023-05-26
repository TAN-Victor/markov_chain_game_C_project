##==============================================================================================
# Fichier: interface.py
# Brief: Interface du jeu
# Necessités: effets.py, Python 3.11, Pygame 2.4.0
##==============================================================================================

import sys
import os

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
                                      Demebele_Cabot(),  Pacave(), Huet(), Matias(), Salhab(), Pulido_Nino(), Watel(), Szanfranski(), Forest(), Prevel()]


    joueuse_1 = Joueuse(1, liste_cartes_globale)
    joueuse_2 = Joueuse(2, liste_cartes_globale)
    monstres = ListeMonstre()

    liste_joueuses = [joueuse_1, joueuse_2, monstres]
    message_generique(1, None, None, None)

    liste_zones = Zones(10)
    message_generique(2, None, None, None)


    i = 0 # // Va valoir 0 si c'est le tour de la joueuse 1, 1 si c'est le tour de la joueuse 2


    ##================================================================================================
    # Initialisation de la fenêtre
    ##================================================================================================

    map_objets = {}


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
                map_objets["carte_" + str(i+1) + "_" + str(j+1)] = ObjetCarte(longueur*(70 + i * 10)/100 + 25, 260 + j * 50, 100, "interface/images/" + liste_joueuses[i].liste_cartes[j].getNom() + "_" + str(i) + ".png", [j+1, "Joueuse n°" + str(i+1)])
        
        
        demander_action()

    initialiser_objets()




    ##==============================================================================================
    # Boucle de jeu
    ##==============================================================================================

    continuer = True
    while continuer:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                continuer = False

            elif event.type == pygame.MOUSEBUTTONDOWN or event.type == pygame.MOUSEBUTTONUP:
                x, y = pygame.mouse.get_pos()
                print(f"Clic en ({x}, {y})")
                for boutons in map_boutons.values():
                    boutons.clic(event, joueuse_1)
                    boutons.afficher(fenetre)
                for objets in map_objets.values():
                    objets.clic(event)
                    objets.afficher(fenetre)
                    

            fenetre.fill((0, 0, 0)) # Couleur de fond
            joueuses()
            actions()
            zones_jeu()
            console()

            for objets in map_objets.values():
                objets.afficher(fenetre)


            for boutons in map_boutons.values():
                boutons.afficher(fenetre)


        if liste_joueuses[0].getTour() == 1:
            i = 0
        else:
            i = 1
        





        pygame.display.flip() # Rafraichissement de l'écran
        clock.tick(60) # 60 FPS




main()