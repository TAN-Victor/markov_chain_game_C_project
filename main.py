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
    console_phrase = []

    liste_cartes_globale = [Merabet(), Bannour(), Honore(), Rioboo(), Goilard(), Bourard(), Munante(), Benezet(), Ligozat(), Mouilleron(),
                                      Dembele_Cabot(),  Pacave(), Huet(), Matias(), Salhab(), Pulido_Nino(), Watel(), Szafranski(), Forest(), Prevel()]


    joueuse_1 = Joueuse(1, liste_cartes_globale)
    joueuse_2 = Joueuse(2, liste_cartes_globale)
    monstres = ListeMonstre()

    liste_joueuses = [joueuse_1, joueuse_2, monstres]
    message_generique(1, None, None, None, console_phrase)

    liste_zones = Zones(10)
    liste_compteur = [0]*10
    message_generique(2, None, None, None, console_phrase)


    i = 0 # // Va valoir 0 si c'est le tour de la joueuse 1, 1 si c'est le tour de la joueuse 2
    etat = 0 # // Va valoir 0 si on est dans la sélection principale, 1 si on choisi le capital, 2 si on choisit une carte, 3 si on choisit une zone, 4 si on est dans un effet de
                # carte, 5 si on est dans un effet de zone, 6 si on est en déplacement, 7 si on vérifie les morts, 8 si on est en fin de tour, 9 si on est en fin de partie

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
                map_objets["carte_" + str(i+1) + "_" + str(j+1)] = ObjetCarte(longueur*(70 + i * 10)/100 + 25, 430 + j * 50, -30, "interface/images/" + liste_joueuses[i].liste_cartes[j].getNom() + "_" + str(i) + ".png", [j+1, i+1])
        
        
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
                        map_objets["personnage_" + str(nb) + "_" + str(j+1)] = ObjetPersonnage(40 + i%3 * 420 + liste_compteur[i] * 60, 60 + i//3 * 200, 75, "interface/images/" + str(nb) + "_" + str(j+1) + ".png", [j+1, "Joueuse n°" + str(nb + 1)], i, liste_compteur[i])
                        liste_compteur[i] += 1

        
        map_boutons["bouton_fin"] = BoutonFin((longueur*35/100 + 30, largeur*70/100 + 40), (longueur*10/100 - 10, largeur*10/100 - 10), "Fin", (227, 140, 140), (0, 0, 0))


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
            afficher_console_phrase(console_phrase)
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
                        if event.type == pygame.MOUSEBUTTONUP:
                            etat = 2
                            choix_carte = []
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
                                etat = 3
                                choix_zones = []
                            else:
                                etat = 0    
                    elif map_boutons["bouton_valeur_annuler"].rect.collidepoint(event.pos):
                        map_boutons["bouton_valeur_annuler"].clic(event, map_boutons, map_objets, liste_joueuses[i])
                        map_boutons["bouton_valeur_annuler"].afficher(fenetre)
                        if event.type == pygame.MOUSEBUTTONUP:    
                            etat = 0

                if etat == 2: # Choix de la carte
                    map_boutons["bouton_moins"].cacher()
                    map_boutons["bouton_plus"].cacher()
                    map_boutons["bouton_valeur"].changer_valeur_str(choix_carte)
                    for j in range(len(liste_joueuses[i].liste_cartes)):
                        map_objets["carte_" + str(i+1) + "_"+ str(j+1)].actif = True
                        map_objets["carte_" + str(i+1) + "_"+ str(j+1)].clic(event)
                        map_objets["carte_" + str(i+1) + "_"+ str(j+1)].afficher(fenetre)
                        if map_objets["carte_" + str(i+1) + "_"+ str(j+1)].rect.collidepoint(event.pos):
                            choix_carte = [liste_joueuses[i].liste_cartes[j].getNom()]
                    map_boutons["bouton_valeur"].afficher(fenetre)
                    if map_boutons["bouton_valeur_valider"].rect.collidepoint(event.pos):
                        if map_boutons["bouton_valeur_valider"].clic(event, map_boutons, map_objets, liste_joueuses[i]) == choix_carte:
                            map_boutons["bouton_valeur_valider"].afficher(fenetre)
                            if event.type == pygame.MOUSEBUTTONUP:
                                print("IJIYJ")
                                etat = 6



                if etat == 3: # Choix de la zone
                    map_boutons["bouton_moins"].cacher()
                    map_boutons["bouton_plus"].cacher()
                    map_boutons["bouton_valeur"].changer_valeur_liste(choix_zones)
                    zn_zones = liste_zones.getMatrice().getTailleMatrice()
                    for indice_zone in range(zn_zones):
                        map_boutons["zone_" + str(indice_zone+1)].actif = True
                        if map_boutons["zone_" + str(indice_zone+1)].rect.collidepoint(event.pos) and len(choix_zones) < 3:
                            map_boutons["zone_" + str(indice_zone+1)].clic(event, map_boutons, map_objets, liste_joueuses[i])
                            map_boutons["zone_" + str(indice_zone+1)].afficher(fenetre)
                            if event.type == pygame.MOUSEBUTTONUP:    
                                choix_zones.append(indice_zone+1)
                                map_boutons["zone_" + str(indice_zone+1)].clic(event, map_boutons, map_objets, liste_joueuses[i])
                                map_boutons["zone_" + str(indice_zone+1)].afficher(fenetre)
                    print(map_boutons["bouton_valeur"].texte)
                    map_boutons["bouton_valeur"].afficher(fenetre)
                    print(choix_zones)
                    if map_boutons["bouton_valeur_valider"].rect.collidepoint(event.pos):
                        if map_boutons["bouton_valeur_valider"].clic(event, map_boutons, map_objets, liste_joueuses[i]) == choix_zones:
                            map_boutons["bouton_valeur_valider"].afficher(fenetre)
                            m = capital_utilise * liste_joueuses[i].getProbaParCapital()
                            if event.type == pygame.MOUSEBUTTONUP:
                                if liste_zones.getMatrice().lecture_probas(choix_zones[0] -1, choix_zones[1] -1) + m <= 1 and liste_zones.getMatrice().lecture_probas(choix_zones[0] -1, choix_zones[2] -1) - m>= 0:
                                    liste_joueuses[i].utiliseCapital(capital_utilise)
                                    message_generique(3, liste_joueuses[i], [capital_utilise], None, console_phrase) 
                                    liste_zones.modifierZone(choix_zones[0] -1 , choix_zones[1] -1, m, 1)
                                    liste_zones.modifierZone(choix_zones[0] -1, choix_zones[2] -1, m, 0)
                                    message_generique(4, None, [choix_zones[0], choix_zones[1], m*10], None, console_phrase)
                                    message_generique(4, None, [choix_zones[0], choix_zones[2], -m*10], None, console_phrase)
                                    etat = 6
                                else:
                                    message_generique(100, None, None, None, console_phrase)
                                    etat = 0 
                    elif map_boutons["bouton_valeur_annuler"].rect.collidepoint(event.pos):
                        map_boutons["bouton_valeur_annuler"].clic(event, map_boutons, map_objets, liste_joueuses[i])
                        map_boutons["bouton_valeur_annuler"].afficher(fenetre)
                        if event.type == pygame.MOUSEBUTTONUP:    
                            etat = 0

                if etat == 6: #Déplacements
                    print("Déplacements")
                    print(liste_compteur)
                    
                    for indice_monstre in range (0, liste_joueuses[2].getTaille()):
                        if (liste_joueuses[2].getMembres()[indice_monstre].peut_se_deplacer and liste_joueuses[2].getMembres()[indice_monstre].statut == 1):
                            zone_actuelle = liste_joueuses[2].getMembres()[indice_monstre].zone_personnage()
                            for nombre_de_deplacement in range (0, liste_joueuses[2].getMembres()[indice_monstre].nb_de_pas):
                                prochaine_zone = (liste_zones.prochaineZone(liste_joueuses[2].getMembres()[indice_monstre].zone_personnage()))
                                liste_joueuses[2].getMembres()[indice_monstre].deplacer(prochaine_zone)
                            if prochaine_zone != zone_actuelle:
                                liste_compteur[zone_actuelle] -= 1
                                position = map_objets["personnage_2_" + str(indice_monstre + 1)].position
                                if prochaine_zone//3 > 2: # Zone 10 ou 11
                                    map_objets["personnage_2_" + str(indice_monstre + 1)].deplacer(250 + prochaine_zone%3 * 420 + liste_compteur[prochaine_zone] * 60, 60 + prochaine_zone//3 * 200, prochaine_zone, liste_compteur[prochaine_zone])                       
                                else:
                                    map_objets["personnage_2_" + str(indice_monstre + 1)].deplacer(40 + prochaine_zone%3 * 420 + liste_compteur[prochaine_zone] * 60, 60 + prochaine_zone//3 * 200, prochaine_zone, liste_compteur[prochaine_zone])                       
                                liste_compteur[prochaine_zone] += 1
                                print("Monstre " + str(indice_monstre + 1) + " déplacé de " + str(zone_actuelle+1) + " à " + str(prochaine_zone+1))


                                for cle, objet in map_objets.items(): # Décalage des personnages sur les zones pour éviter supeposition
                                        if isinstance(objet, ObjetPersonnage):
                                            if objet.zone == zone_actuelle and objet.position > position:
                                                objet.position -= 1
                                                map_objets[cle].deplacer(objet.x - 60, objet.y, objet.zone, objet.position)
                                                print(cle + " décalé de " + str(objet.position + 1) + " à " + str(objet.position) + " dans la zone " + str(objet.zone+1))

                    
                    for j in range (2):
                        nombre_personnage = liste_joueuses[j].getTaille()
                        for k in range(nombre_personnage):
                            if liste_joueuses[j].getMembres()[k].peut_se_deplacer and (liste_joueuses[j].getMembres()[k].statut == 1 or liste_joueuses[j].getMembres()[k].statut == 3):
                                # Si le personnage peut se dépalcer et ( qu'il est vivant ou qu'il soit un FIPA)
                                zone_actuelle = liste_joueuses[j].getMembres()[k].zone_personnage()
                                for nombre_de_deplacement in range (0, liste_joueuses[j].getMembres()[k].nb_de_pas):
                                    prochaine_zone = (liste_zones.prochaineZone(liste_joueuses[j].getMembres()[k].zone_personnage()))
                                    liste_joueuses[j].getMembres()[k].deplacer(prochaine_zone)
                                if prochaine_zone != zone_actuelle:
                                    liste_compteur[zone_actuelle] -= 1
                                    position = map_objets["personnage_" + str(j) + "_" + str(k + 1)].position
                                    if prochaine_zone//3 > 2: # Zone 10 ou 11
                                        map_objets["personnage_" + str(j) + "_" + str(k + 1)].deplacer(250 + prochaine_zone%3 * 420 + liste_compteur[prochaine_zone] * 60, 60 + prochaine_zone//3 * 200, prochaine_zone, liste_compteur[prochaine_zone])
                                    else:
                                        map_objets["personnage_" + str(j) + "_" + str(k + 1)].deplacer(40 + prochaine_zone%3 * 420 + liste_compteur[prochaine_zone] * 60, 60 + prochaine_zone//3 * 200, prochaine_zone, liste_compteur[prochaine_zone])
                                    liste_compteur[prochaine_zone] += 1
                                    print("Personnage " + str(j) + " " + str(k + 1) + " déplacé de " + str(zone_actuelle+1) + " à " + str(prochaine_zone+1) + " avec position " + str(liste_compteur[prochaine_zone]-1))

                                    for cle, objet in map_objets.items(): # Décalage des personnages sur les zones pour éviter supeposition
                                        if isinstance(objet, ObjetPersonnage):
                                            if objet.zone == zone_actuelle and objet.position > position:
                                                objet.position -= 1
                                                map_objets[cle].deplacer(objet.x - 60, objet.y, objet.zone, objet.position)
                                                print(cle + " décalé de " + str(objet.position + 1) + " à " + str(objet.position) + " dans la zone " + str(objet.zone+1))


                    message_generique(6, None, None, None, console_phrase)
                    etat = 7

                if etat == 7: # Vérification des présences et morts
                    for indice_monstre in range(0, liste_joueuses[2].getTaille()):
                        for indice_joueuse in range(0, 2):
                            for indice_personnage in range(0, liste_joueuses[indice_joueuse].getTaille()):
                                if liste_joueuses[indice_joueuse].getMembres()[indice_personnage].zone_personnage() == liste_joueuses[2].getMembres()[indice_monstre].zone_personnage():
                                    if not liste_joueuses[indice_joueuse].getInvincibilite() and (liste_joueuses[indice_joueuse].getMembres()[indice_personnage].statut == 1 or liste_joueuses[indice_joueuse].getMembres()[indice_personnage].statut == 3):
                                        liste_joueuses[indice_joueuse].getMembres()[indice_personnage].est_mange()
                                        map_objets["statut_" + str(indice_joueuse+1) + "_" + str(indice_personnage + 1) + "liste"].changer_image("interface/images/Mort_" + str(indice_joueuse) + ".png")
                                        message_generique(7, liste_joueuses[indice_joueuse], [indice_personnage], None, console_phrase)

                                        liste_compteur[liste_joueuses[indice_joueuse].getMembres()[indice_personnage].zone_personnage()] -= 1
                                        position = map_objets["personnage_" + str(indice_joueuse) + "_" + str(indice_personnage + 1)].position
                                        del map_objets["personnage_" + str(indice_joueuse) + "_" + str(indice_personnage + 1)]
                                        for cle, objet in map_objets.items(): # Décalage des personnages sur les zones pour éviter supeposition
                                            if isinstance(objet, ObjetPersonnage):
                                                if objet.zone == liste_joueuses[indice_joueuse].getMembres()[indice_personnage].zone_personnage() and objet.position > position:
                                                    objet.position -= 1
                                                    map_objets[cle].deplacer(objet.x - 60, objet.y, objet.zone, objet.position)
                                                    print(cle + " décalé de " + str(objet.position + 1) + " à " + str(objet.position) + " dans la zone " + str(objet.zone+1))

                    tous_manges_joueuse1 = liste_joueuses[0].tous_manges()
                    tous_manges_joueuse2 = liste_joueuses[1].tous_manges()
                    if tous_manges_joueuse1 or tous_manges_joueuse2:
                        print(tous_manges_joueuse1)
                        print(tous_manges_joueuse2)
                        etat = 9
                    else:
                        etat = 8

                if etat == 8: # Fin de tour

                    tours_restants_jouer = liste_joueuses[i].getToursRestantsJouer()
                    tours_restants_invincibilite = liste_joueuses[i].getToursRestantsInvincibilite()
                    tours_restants_bonus_capital = liste_joueuses[i].getTourRestantsBonusCapital()
                    tours_restants_bonus_proba_par_capital = liste_joueuses[i].getToursRestantsBonusProbaParCapital()

                    if tours_restants_bonus_capital == 0:
                        liste_joueuses[i].setCapital(5)
                    if tours_restants_bonus_capital > 0:
                        liste_joueuses[i].setTourRestantsBonusCapital(tours_restants_bonus_capital - 1)

                    if tours_restants_bonus_proba_par_capital == 0:
                        liste_joueuses[i].setProbaParCapital(0.1)
                    if tours_restants_bonus_proba_par_capital > 0:
                        liste_joueuses[i].setToursRestantsBonusProbaParCapital(tours_restants_bonus_proba_par_capital - 1)

                    if tours_restants_jouer == 0:
                        liste_joueuses[i].setTour(False)
                        liste_joueuses[(i+1)%2].setTour(True)
                        map_objets["tour"].deplacer(longueur*70/100 + 25 + (i+1)%2 * (longueur*10/100 + 5), 10)
                        map_objets["tour"].afficher(fenetre)
                    if tours_restants_jouer > 0:
                        liste_joueuses[i].setToursRestantsJouer(tours_restants_jouer - 1)

                    if tours_restants_invincibilite > 0:
                        liste_joueuses[i].setToursRestantsInvincibilite(tours_restants_invincibilite - 1)

                    
                    if liste_joueuses[i].getBonusTemporaire() != 0:
                        liste_joueuses[i].setCapital(liste_joueuses[i].getCapital() + liste_joueuses[i].getBonusTemporaire())
                        if liste_joueuses[i].getBonusTemporaire() > 0:
                            liste_joueuses[i].setBonusTemporaire(-liste_joueuses[i].getBonusTemporaire()) #Mis en négatif pour savoir qu'il faudra le soustraire au prochain tour
                        else:
                            liste_joueuses[i].setBonusTemporaire(0)

                    for j in range(0, liste_joueuses[i].getTaille()):
                        if liste_joueuses[i].getMembres()[j].statut == 3:
                            liste_joueuses[i].getMembres()[j].peut_se_deplacer = not liste_joueuses[i].getMembres()[j].peut_se_deplacer
                        if liste_joueuses[i].getMembres()[j].statut == 1 and liste_joueuses[i].getMembres()[j].peut_se_deplacer == False: # Cas où les personnages vivants non FIPA ne pouvaient pas se déplacer pour 1 tour
                            liste_joueuses[i].getMembres()[j].peut_se_deplacer = True

                    for k in range(0, liste_joueuses[2].getTaille()):
                        if liste_joueuses[2].getMembres()[k].statut == -1: #Monstres disparus
                            if liste_joueuses[2].getMembres()[k].nb_de_tour_disparu_restant == 0:
                                liste_joueuses[2].getMembres()[k].statut = 1
                            elif liste_joueuses[2].getMembres()[k].nb_de_tour_disparu_restant > 0:
                                liste_joueuses[2].getMembres()[k].nb_de_tour_disparu_restant -= 1
                        elif liste_joueuses[2].getMembres()[k].peut_se_deplacer == False: # Cas où les monstres ne pouvaient pas se déplacer pour 1 tour
                            liste_joueuses[2].getMembres()[k].peut_se_deplacer = True


                    message_generique(8, None, None, None, console_phrase)
                    etat = 0

                if etat == 9: # Fin de partie
                    if liste_joueuses[0].tous_manges() and not liste_joueuses[1].tous_manges():
                        message_generique(0, liste_joueuses[1], None, None, console_phrase)
                    elif liste_joueuses[1].tous_manges() and not liste_joueuses[0].tous_manges():
                        message_generique(0, liste_joueuses[0], None, None, console_phrase)
                    else:
                        message_generique(-1, None, None, None, console_phrase)
                    
                    print("Fin de partie")





            
            for boutons in map_boutons.values():
                boutons.afficher(fenetre)
            for objets in map_objets.values():
                objets.afficher(fenetre)








        pygame.display.flip() # Rafraichissement de l'écran
        clock.tick(60) # 60 FPS



main()