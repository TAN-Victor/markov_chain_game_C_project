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
    liste_compteur = [0]*10
    message_generique(2, None, None, None)


    i = 0 # // Va valoir 0 si c'est le tour de la joueuse 1, 1 si c'est le tour de la joueuse 2
    etat = 0 # // Va valoir 0 si on est dans la sélection principale, 1 si on choisi le capital, 2 si on choisit une carte, 3 si on choisit une zone, 4 si on est dans un effet de
                # carte, 5 si on est dans un effet de zone, 6 si on est en déplacement, 7 si on change les proba

    ##================================================================================================
    # Initialisation de la fenêtre
    ##================================================================================================

    map_objets = {}
    map_boutons = {}
    Zone_joueuse1 = pygame.Rect((longueur*70/100 + 30, largeur*70/100 + 40), (longueur*10/100 - 20, largeur*5/100 - 10))
    Zone_joueuse2 = pygame.Rect((longueur*80/100 + 30, largeur*70/100 + 40), (longueur*10/100 - 20, largeur*5/100 - 10))
    Zone_Zones = pygame.Rect((longueur*50/100 + 30, largeur*80/100 + 40), (longueur*20/100 - 20, largeur*20/100 - 10))

    def initialiser_objets():
        for i in range (0, 3):
            for j in range(0, 6):
                map_objets["personnage_" + str(i+1) + "_" + str(j+1) + "liste"] = (ObjetPersonnageListe(longueur*(70 + i * 10)/100 + 25, 65 + j * 50, 50, "interface/images/" + str(i) + "_" + str(j+1) + ".png", [j+1, "Joueuse n°" + str(i+1)]))
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

        nb_zones = liste_zones.getMatrice().getTailleMatrice()
        for i in range(nb_zones):
            for nb in range(0, 3):
                for j in range(liste_joueuses[nb].taille):
                    if liste_joueuses[nb].getMembres()[j].zone_courante == i:
                        map_objets["personnage_" + str(nb) + "_" + str(j+1)] = ObjetPersonnage(40 + i%3 * 420 + liste_compteur[i] * 60, 60 + i//3 * 200, 75, "interface/images/" + str(nb) + "_" + str(j+1) + ".png", [j+1, "Joueuse n°" + str(nb + 1)])
                        liste_compteur[i] += 1

        



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
            probabilites()

            info_joueuse(liste_joueuses[0])
            info_joueuse(liste_joueuses[1])


            if (liste_joueuses[0].getTour() == True):
                i = 0
            else:
                i = 1


            if event.type == pygame.QUIT:
                continuer = False
            elif event.type == pygame.MOUSEMOTION:
                if Zone_joueuse1.collidepoint(event.pos):
                    info_joueuse_hover_afficher(liste_joueuses[0])
                elif Zone_joueuse2.collidepoint(event.pos):
                    info_joueuse_hover_afficher(liste_joueuses[1])
                elif Zone_Zones.collidepoint(event.pos):
                    info_zones(liste_zones, map_boutons, map_objets)
                else:
                    for bouton in map_boutons.values():
                        if isinstance(bouton, BoutonZone):
                            bouton.montrer()
                    for objet in map_objets.values():
                        if isinstance(objet, ObjetPersonnage):
                            objet.montrer()
            elif event.type == pygame.MOUSEBUTTONDOWN or event.type == pygame.MOUSEBUTTONUP:
                x, y = pygame.mouse.get_pos()
                print(f"Clic en ({x}, {y})")

                if etat == 0: # Menu principal
                    demander_action(map_boutons, map_objets, liste_joueuses[0])
                    if map_boutons["bouton_choix_capital"].rect.collidepoint(event.pos):
                        map_boutons["bouton_choix_capital"].clic(event, map_boutons, map_objets, liste_joueuses[i])
                        map_boutons["bouton_choix_capital"].afficher(fenetre)
                        if event.type == pygame.MOUSEBUTTONUP:    
                            etat = 1
                    elif map_boutons["bouton_choix_carte"].rect.collidepoint(event.pos):
                        map_boutons["bouton_choix_carte"].clic(event, map_boutons, map_objets, liste_joueuses[i])
                        map_boutons["bouton_choix_carte"].afficher(fenetre)
                        etat = 2
                    elif map_boutons["bouton_choix_rien"].rect.collidepoint(event.pos):
                        map_boutons["bouton_choix_rien"].clic(event, map_boutons, map_objets, liste_joueuses[i])
                        map_boutons["bouton_choix_rien"].afficher(fenetre)
                        if event.type == pygame.MOUSEBUTTONUP:    
                            etat = 6

                if etat == 1: # Choix du capital
                    if map_boutons["bouton_moins"].rect.collidepoint(event.pos):
                        map_boutons["bouton_moins"].clic(event, map_boutons, map_objets, liste_joueuses[i])
                        map_boutons["bouton_moins"].afficher(fenetre)
                        map_boutons["bouton_valeur"].afficher(fenetre)
                    elif map_boutons["bouton_plus"].rect.collidepoint(event.pos):
                        map_boutons["bouton_plus"].clic(event, map_boutons, map_objets, liste_joueuses[i])
                        map_boutons["bouton_plus"].afficher(fenetre)
                        map_boutons["bouton_valeur"].afficher(fenetre)
                    elif map_boutons["bouton_valeur_valider"].rect.collidepoint(event.pos):
                        capital_utilise = map_boutons["bouton_valeur_valider"].clic(event, map_boutons, map_objets, liste_joueuses[i])
                        map_boutons["bouton_valeur_valider"].afficher(fenetre)
                        if event.type == pygame.MOUSEBUTTONUP:  
                            if capital_utilise > 0:
                                etat = 7
                            else:
                                etat = 0    
                    elif map_boutons["bouton_valeur_annuler"].rect.collidepoint(event.pos):
                        map_boutons["bouton_valeur_annuler"].clic(event, map_boutons, map_objets, liste_joueuses[i])
                        map_boutons["bouton_valeur_annuler"].afficher(fenetre)
                        if event.type == pygame.MOUSEBUTTONUP:    
                            etat = 0
                    
                if etat == 6: #Déplacements
                    print("Déplacements")

                    for indice_monstre in range (0, liste_joueuses[2].getTaille()):
                        print("Monstre en position : ", liste_joueuses[2].getMembres()[indice_monstre].zone_personnage() + 1)
                        if (liste_joueuses[2].getMembres()[indice_monstre].peut_se_deplacer and liste_joueuses[2].getMembres()[indice_monstre].statut == 1):
                            zone_actuelle = liste_joueuses[2].getMembres()[indice_monstre].zone_personnage()
                            for nombre_de_deplacement in range (0, liste_joueuses[2].getMembres()[indice_monstre].nb_de_pas):
                                prochaine_zone = (liste_zones.prochaineZone(liste_joueuses[2].getMembres()[indice_monstre].zone_personnage()))
                                liste_joueuses[2].getMembres()[indice_monstre].deplacer(prochaine_zone)
                            liste_compteur[zone_actuelle] -= 1
                            if prochaine_zone//3 > 2: # Zone 10 ou 11
                                map_objets["personnage_2_" + str(indice_monstre + 1)].deplacer(250 + prochaine_zone%3 * 420 + liste_compteur[prochaine_zone] * 60, 60 + prochaine_zone//3 * 200)                       
                            else:
                                map_objets["personnage_2_" + str(indice_monstre + 1)].deplacer(40 + prochaine_zone%3 * 420 + liste_compteur[prochaine_zone] * 60, 60 + prochaine_zone//3 * 200)                       
                            liste_compteur[prochaine_zone] += 1
                        print("Monstre en position : ", liste_joueuses[2].getMembres()[indice_monstre].zone_personnage() + 1)

                    etat = 0
            
            
            for boutons in map_boutons.values():
                boutons.afficher(fenetre)
            for objets in map_objets.values():
                objets.afficher(fenetre)








        pygame.display.flip() # Rafraichissement de l'écran
        clock.tick(60) # 60 FPS

main()