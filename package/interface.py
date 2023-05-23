##==============================================================================================
# Fichier: interface.py
# Brief: Interface du jeu
# Necessités: Python 3.11, Pygame 2.4.0
##==============================================================================================

import pygame
import os
import sys
#import joueuses

pygame.init()
clock = pygame.time.Clock()

current_dir = os.path.dirname(os.path.abspath(sys.argv[0]))
os.chdir(current_dir)




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
def zones_jeu():
    """
    Dessine le rectangle des zones du jeu
    Taille: 70% de la longueur et 80% de la largeur de l'écran (en 1080p par défaut)
    Couleur de fond: (200, 200, 200) Gris clair
    """
    pygame.draw.rect(fenetre, (200, 200, 200), (10, 10, longueur*70/100, largeur*80/100))

# Joueuses
def joueuses():
    """
    Dessine le fond de l'UI des joueuses (personnages et cartes)
    Taille: 30% de la longueur et 80% de la largeur de l'écran(en 1080p par défaut)
    Couleur de fond: (200, 200, 200) Gris clair
    Nombre de joueuses: 2 + 1 pour les monstres
    Nombre de personnages par joueuse au maximum: 7
    Nombre de cartes par joueuse au maximum: 5
    """
    pygame.draw.rect(fenetre, (200, 200, 200), (longueur*70/100 + 20, 10, longueur*30/100 - 30, largeur*80/100))
    for i in range(1, 3):
        pygame.draw.line(fenetre, (0, 0, 0), (longueur*(70 + i * 10)/100 + 20, 10), (longueur*(70 + i * 10)/100 + 20, largeur*80/100 + 9), 3) # Séparation des joueuses
    pygame.draw.line(fenetre, (0, 0, 0), (longueur*70/100 + 20, 70), (longueur - 11, 70), 5)
    for i in range(1, 13):
        pygame.draw.line(fenetre, (0, 0, 0), (longueur*70/100 + 20, 70 + i * 50), (longueur - 11, 70 + i * 50), 3) # Séparation des personnages et des cartes
    liste_des_joueuses = ["Joueuse n°1", "Joueuse n°2", "Monstres"]
    for i in range(3):
        texte = pygame.font.SysFont("Source Sans Pro", 30).render(liste_des_joueuses[i], True, (0, 0, 0))
        fenetre.blit(texte, (longueur*(70 + i * 10)/100 + 50, 30))

# Actions
def actions():
    """
    Dessine le fond de l'UI des actions
    Taille: 30% de la longueur et 20% de la largeur de l'écran (en 1080p par défaut)
    Couleur de fond: (200, 200, 200) Gris clair
    """
    pygame.draw.rect(fenetre, (200, 200, 200), (longueur*70/100 + 20, largeur*80/100 + 20, longueur*30/100 - 30, largeur*20/100 - 30)) 

# Console
def console():
    """
    Dessine le fond de l'UI de la console
    Taille: 70% de la longueur et 20% de la largeur de l'écran (en 1080p par défaut)
    Couleur de fond: (200, 200, 200) Gris clair
    """
    pygame.draw.rect(fenetre, (200, 200, 200), (10, largeur*80/100 + 20, longueur*70/100, largeur*20/100 - 30))



##==============================================================================================
# UI Dynamique
##==============================================================================================

class ObjetFixe:

    def __init__(self, x, y, longueur, image_path, info: list):
        self.x = x
        self.y = y
        self.longueur = longueur
        self.info = info
        self.image = pygame.image.load(image_path)
        self.image = self.redimensionner(longueur)
        self.rect = pygame.Rect(x-5, y+5, self.image.get_width(), self.image.get_height())
        self.visible = True
        self.selected = False
        self.actif = True

    def redimensionner(self, nouvelle_longueur):
        ratio = self.image.get_width() / self.image.get_height()
        return pygame.transform.scale(self.image, (nouvelle_longueur, int(nouvelle_longueur / ratio)))

    def afficher(self, fenetre):
        if self.visible:
            fenetre.blit(self.image, (self.x, self.y))
            if self.selected:
                pygame.draw.rect(fenetre, (255, 255, 153), self.rect, 3)
            
    
    def deplacer(self, x, y):
        self.x = x
        self.y = y

    def changer_image(self, image_path):
        self.image = pygame.image.load(image_path)
        self.image = self.redimensionner(self.longueur)

    def cacher(self):
        self.visible = False

    def montrer(self):
        self.visible = True

    def clic(self, event):
        if event.type == pygame.MOUSEBUTTONDOWN:
            if self.visible:
                if self.actif:
                    if self.rect.collidepoint(event.pos):
                        self.selected = True
                    else:
                        self.selected = False
                    if self.selected == True:
                        self.action()

    def activer(self):
        self.actif = True

    def desactiver(self):
        self.actif = False

class ObjetPersonnageListe(ObjetFixe):

    def action(self):
        print("Personnage n° {} de {} sélectionné".format(self.info[0], self.info[1]))


class ObjetStatut(ObjetFixe):

    def action(self):
        print("Statut du personnage n° {} de {} sélectionné: {}".format(self.info[0], self.info[1], self.info[2]))



map_objets = {}
for i in range (0, 3):
    for j in range(0, 6):
        map_objets["personnage_" + str(i+1) + "_" + str(j+1) + "liste"] = (ObjetPersonnageListe(longueur*(70 + i * 10)/100 + 25, 65 + j * 50, 50, "interface/images/" + str(j+1) + "_" + str(i) + ".png", [j+1, "Joueuse n°" + str(i+1)]))
        map_objets["statut_" + str(i+1) + "_" + str(j+1) + "liste"] = (ObjetStatut(longueur*(70 + i * 10)/100 + 85, 75 + j * 50, 100, "interface/images/" + "En vie" + "_" + str(i) + ".png", [j+1, "Joueuse n°" + str(i+1), "En vie"]))
        if (j == 5 or (i == 2 and j != 0)):
            map_objets["personnage_" + str(i+1) + "_" + str(j+1) + "liste"].cacher()
            map_objets["statut_" + str(i+1) + "_" + str(j+1) + "liste"].cacher()

#================================================================================================

class Bouton:

    def __init__(self, position, dimensions, texte, couleur, couleur_texte, alignement="centre", radius=1, visible=False):
        self.rect = pygame.Rect(position[0], position[1], dimensions[0], dimensions[1])
        self.position = position
        self.dimensions = dimensions
        self.texte = texte
        self.alignement = alignement
        self.radius = radius
        self.couleur = couleur
        self.couleur_texte = couleur_texte
        self.visible = visible
        self.actif = False
        self.clicked = False

    def afficher(self, fenetre):
        if self.visible:
            if self.radius == 1:
                pygame.draw.rect(fenetre, self.couleur, self.rect, border_radius= int (min(self.dimensions)//6))
                pygame.draw.rect(fenetre, (0, 0, 0), self.rect, 3, border_radius= int (min(self.dimensions)//6))
            else:
                pygame.draw.rect(fenetre, self.couleur, self.rect)
                pygame.draw.rect(fenetre, (0, 0, 0), self.rect, 3)
            texte = pygame.font.SysFont("Source Sans Pro", 30).render(self.texte, True, self.couleur_texte)
            if self.alignement == "centre":
                fenetre.blit(texte, texte.get_rect(center=self.rect.center))
            if self.alignement == "haut_centre":
                fenetre.blit(texte, (texte.get_rect(midtop=self.rect.midtop).x, texte.get_rect(midtop=self.rect.midtop).y + 5))
            try:
                int(self.texte)
                self.texte = self.valeur
            except:
                pass
    
    def cacher(self):
        self.visible = False

    def montrer(self):
        self.visible = True

    def clic(self, event):
        if self.visible and self.actif:
            if event.type == pygame.MOUSEBUTTONDOWN:
                if self.rect.collidepoint(event.pos):
                    self.clicked = True
                    self.position = (self.position[0] - 5, self.position[1] + 5)
                    self.rect = pygame.Rect(self.position[0], self.position[1], self.dimensions[0], self.dimensions[1])
            if event.type == pygame.MOUSEBUTTONUP and self.clicked == True:
                self.clicked = False
                self.position = (self.position[0] +5, self.position[1] -5)
                self.rect = pygame.Rect(self.position[0], self.position[1], self.dimensions[0], self.dimensions[1])
                self.action()

    def activer(self):
        self.actif = True
    
    def desactiver(self):
        self.actif = False

class BoutonValeur(Bouton):
    
    valeur = "0"

    def action(self):
        print("Click sur le bouton {}".format(self.texte))
        if (self.texte == "+"):
            self.changer_valeur(1)
        if (self.texte == "-"):
            self.changer_valeur(-1)

    @classmethod
    def changer_valeur(cls, incr):
        cls.valeur = str(int(cls.valeur) + incr)
        print(cls.valeur)
        
class BoutonAnnuler(Bouton):

    def action(self):
        print("Annulation")
        self.actif = False

class BoutonValider(Bouton):

    def action(self):
        print("Validation")
        self.actif = False

class BoutonChoix(Bouton):

    def action(self):
        if self.texte == "Choix d'un personnage 1":
            print("Choix d'un personnage 1")
        elif self.texte == "Choix d'un personnage 2":
            print("Choix d'un personnage 2")
        elif self.texte == "Choix d'un monstre":
            print("Choix d'un monstre")
        elif self.texte == "Utiliser carte":
            print("Choix d'une carte")
        elif self.texte == "Choix d'une zone":
            print("Choix d'une zone")
        elif self.texte == "Choix d'une autre zone":
            print("Choix d'une autre zone")
        elif self.texte == "Utiliser capital":
            print("Choix de capital")
            demander_capital()
        elif self.texte == "Ne rien faire":
            print("Ne rien faire")

class BoutonZone(Bouton):

    def action(self):
        print("Choix de la zone {}".format(self.texte))


map_boutons = {}
map_boutons["bouton_annuler"] = BoutonAnnuler((longueur*85/100 + 30, largeur*92/100 + 20), (longueur*15/100 - 50, largeur*8/100 - 30), "Annuler", (227, 50, 50), (0, 0, 0))
map_boutons["bouton_valider"] = BoutonValider((longueur*70/100 + 30, largeur*92/100 + 20), (longueur*15/100 - 50, largeur*8/100 - 30), "Valider", (50, 227, 50), (0, 0, 0))
map_boutons["bouton_choix_capital"] = BoutonChoix((longueur*70/100 + 30, largeur*83/100 + 40), (longueur*10/100 - 20, largeur*10/100 - 10), "Utiliser capital", (140, 215, 140), (0, 0, 0))
map_boutons["bouton_choix_carte"] = BoutonChoix((longueur*80/100 + 30, largeur*83/100 + 40), (longueur*10/100 - 20, largeur*10/100 - 10), "Utiliser carte", (140, 215, 140), (0, 0, 0))
map_boutons["bouton_choix_rien"] = BoutonChoix((longueur*90/100 + 30, largeur*83/100 + 40), (longueur*8/100 - 10, largeur*10/100 - 10), "Ne rien faire", (227, 140, 140), (0, 0, 0))
map_boutons["boutons_plus"] = BoutonValeur((longueur*90/100 + 30, largeur*82/100 + 40), (longueur*8/100 - 20, largeur*6/100 - 10), "+", (140, 140, 215), (0, 0, 0))
map_boutons["boutons_moins"] = BoutonValeur((longueur*72/100 + 30, largeur*82/100 + 40), (longueur*8/100 - 20, largeur*6/100 - 10), "-", (140, 140, 215), (0, 0, 0))
map_boutons["boutons_valeur"] = BoutonValeur((longueur*80/100 + 30, largeur*82/100 + 40), (longueur*10/100 - 20, largeur*6/100 - 10), BoutonValeur.valeur, (140, 140, 215), (0, 0, 0))

couleurs_zones = [(230, 138, 143), (180, 205, 147), (163, 181, 204), (237, 210, 136), (190, 149, 170), (177, 214, 206), (217, 183, 139), (199, 203, 178), (210, 178, 200), (174, 207, 169), (216, 170, 185)]
for i in range(0, 3):
    for j in range(0, 3):
        map_boutons["zone_" + str(i+3*j+1)] = BoutonZone((40 + i * 420, 40 +j *200), (400, 180), "Zone n°" + str(i+3*j+1), couleurs_zones[i+3*j], (0, 0, 0), "haut_centre", 0, True)
for i in range(0, 2):
    map_boutons["zone_" + str(i+10)] = BoutonZone((250 + i * 420, 640), (400, 180), "Zone n°" + str(i+10), couleurs_zones[i+9], (0, 0, 0), "haut_centre", 0, True)


##==============================================================================================
# Actions
##==============================================================================================

def demander_action():
    """
    Affiche les boutons d'action principaux: Utiliser du capital, Utiliser une carte, Ne rien faire
    Les rend cliquables (actifs)
    """
    map_boutons["bouton_choix_rien"].activer()
    map_boutons["bouton_choix_rien"].montrer()
    map_boutons["bouton_choix_capital"].activer()
    map_boutons["bouton_choix_capital"].montrer()
    map_boutons["bouton_choix_carte"].activer()
    map_boutons["bouton_choix_carte"].montrer()

def demander_capital(): # TODO: Add joueuses
    """
    Doit être appelé par le bouton "Utiliser capital"

    Désaffiche et désactive les boutons d'action principaux #see demander_action()
    Affiche les boutons d'action du capital: +, -, valeur, valider, annuler
    Les rend cliquables (actifs)

    Bloque les boutons afin que le capital soit entre 0 et le capital de la joueuse
    """
    map_boutons["bouton_choix_rien"].desactiver()
    map_boutons["bouton_choix_rien"].cacher()
    map_boutons["bouton_choix_capital"].desactiver()
    map_boutons["bouton_choix_capital"].cacher()
    map_boutons["bouton_choix_carte"].desactiver()
    map_boutons["bouton_choix_carte"].cacher()

    map_boutons["boutons_plus"].activer()
    map_boutons["boutons_moins"].activer()
    map_boutons["boutons_plus"].montrer()
    map_boutons["boutons_moins"].montrer()
    map_boutons["boutons_valeur"].activer()
    map_boutons["boutons_valeur"].montrer()
    map_boutons["bouton_valider"].activer()
    map_boutons["bouton_valider"].montrer()
    map_boutons["bouton_annuler"].activer()
    map_boutons["bouton_annuler"].montrer()


demander_action()

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
                boutons.clic(event)
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







    pygame.display.flip() # Rafraichissement de l'écran
    clock.tick(60) # 60 FPS