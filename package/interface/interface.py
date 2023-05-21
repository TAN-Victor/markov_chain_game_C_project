##==============================================================================================
# Fichier: interface.py
# Brief: Interface du jeu
# Necessités: Python 3.11, Pygame 2.4.0
##==============================================================================================

import pygame
import os
import sys
pygame.init()

current_dir = os.path.dirname(os.path.abspath(sys.argv[0]))


##==============================================================================================
# Fenêtre
##==============================================================================================

largeur = 1080
longueur = 1920
pygame.display.set_caption("Jeu de la survie des IIENS")
fenetre = pygame.display.set_mode((longueur, largeur))


##==============================================================================================
# UI Fixe
##==============================================================================================

# Zones du jeu
pygame.draw.rect(fenetre, (200, 200, 200), (10, 10, longueur*70/100, largeur*80/100))
liste_des_zones = ["Zone 1", "Zone 2", "Zone 3", "Zone 4", "Zone 5", "Zone 6", "Zone 7", "Zone 8", "Zone 9", "Zone 10", "Zone 11"]
couleurs_zones = [(230, 138, 143), (180, 205, 147), (163, 181, 204), (237, 210, 136), (190, 149, 170), (177, 214, 206), (217, 183, 139), (199, 203, 178), (210, 178, 200), (174, 207, 169), (216, 170, 185)]
for i in range(0, 3):
    for j in range(0, 3):
        pygame.draw.rect(fenetre, couleurs_zones[i + j * 3], (40 + i * 420, 40 + j * 200, 400, 180)) # Séparation des zones
        pygame.draw.rect(fenetre, (0, 0, 0), (40 + i * 420, 40 + j * 200, 400, 180), 3)
        texte = pygame.font.SysFont("Source Sans Pro", 30).render(liste_des_zones[i + j * 3], True, (0, 0, 0))
        fenetre.blit(texte, (210 + i * 420, 45 + j * 200))
for i in range(0, 2):
    pygame.draw.rect(fenetre, couleurs_zones[i + 9], (250 + i * 420, 640, 400, 180)) # Séparation des zones
    pygame.draw.rect(fenetre, (0, 0, 0), (250 + i * 420, 640, 400, 180), 3)
    texte = pygame.font.SysFont("Source Sans Pro", 30).render(liste_des_zones[i + 9], True, (0, 0, 0))
    fenetre.blit(texte, (420 + i * 420, 45 + 3 * 200))

# Joueuses
pygame.draw.rect(fenetre, (200, 200, 200), (longueur*70/100 + 20, 10, longueur*30/100 - 30, largeur*80/100))
for i in range(1, 3):
    pygame.draw.line(fenetre, (0, 0, 0), (longueur*(70 + i * 10)/100 + 20, 10), (longueur*(70 + i * 10)/100 + 20, largeur*80/100 + 9), 3) # Séparation des joueuses
pygame.draw.line(fenetre, (0, 0, 0), (longueur*70/100 + 20, 70), (longueur - 11, 70), 5)
for i in range(1, 12):
    pygame.draw.line(fenetre, (0, 0, 0), (longueur*70/100 + 20, 70 + i * 50), (longueur - 11, 70 + i * 50), 3) # Séparation des personnages et des cartes
liste_des_joueuses = ["Joueuse n°1", "Joueuse n°2", "Monstres"]
for i in range(3):
    texte = pygame.font.SysFont("Source Sans Pro", 30).render(liste_des_joueuses[i], True, (0, 0, 0))
    fenetre.blit(texte, (longueur*(70 + i * 10)/100 + 50, 30))

# Actions
pygame.draw.rect(fenetre, (200, 200, 200), (longueur*70/100 + 20, largeur*80/100 + 20, longueur*30/100 - 30, largeur*20/100 - 30)) 

# Console
pygame.draw.rect(fenetre, (200, 200, 200), (10, largeur*80/100 + 20, longueur*70/100, largeur*20/100 - 30))




##==============================================================================================
# UI Dynamique
##==============================================================================================

class ObjetFixe:

    def __init__(self, x, y, longueur, image_path):
        self.x = x
        self.y = y
        self.longueur = longueur
        self.image = pygame.image.load(image_path)
        self.image = self.redimensionner(longueur)

    def redimensionner(self, nouvelle_longueur):
        ratio = self.image.get_width() / self.image.get_height()
        return pygame.transform.scale(self.image, (nouvelle_longueur, int(nouvelle_longueur / ratio)))

    def afficher(self, fenetre):
        fenetre.blit(self.image, (self.x, self.y))
    
    def deplacer(self, x, y):
        self.x = x
        self.y = y

liste_objets = []
for i in range (0, 3):
    for j in range(1, 6):
        liste_objets.append(ObjetFixe(longueur*(70 + i * 10)/100 + 25, 65 + j * 50, 50, "images/" + str(j) + "_" + str(i) + ".png"))
        liste_objets.append(ObjetFixe(longueur*(70 + i * 10)/100 + 85, 75 + j * 50, 100, "images/" + "En vie" + "_" + str(i) + ".png"))







# Boucle de jeu
continuer = True
while continuer:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            continuer = False
        elif event.type == pygame.MOUSEBUTTONDOWN:
            x, y = pygame.mouse.get_pos()
            print(f"Clic en ({x}, {y})")


    for objets in liste_objets:
        objets.afficher(fenetre)










    pygame.display.flip() # Rafraichissement de l'écran