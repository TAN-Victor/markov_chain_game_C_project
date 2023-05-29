##==============================================================================================
# Fichier: interface.py
# Brief: Interface du jeu
# Necessités: joueuses.py
##==============================================================================================

import pygame
import os
import sys
from joueuses import *

pygame.init()
clock = pygame.time.Clock()
current_dir = os.path.dirname(os.path.abspath(sys.argv[0]))
print(current_dir)




##==============================================================================================
# Fenêtre
##==============================================================================================

largeur = 1080
longueur = 1920
pygame.display.set_caption("Jeu de la survie des IIENS")
fenetre = pygame.display.set_mode((longueur, largeur))
couleur_fond = (200, 200, 200)


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
    pygame.draw.rect(fenetre, couleur_fond, (10, 10, longueur*70/100, largeur*80/100))

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
    pygame.draw.rect(fenetre, couleur_fond, (longueur*70/100 + 20, 10, longueur*30/100 - 30, largeur*80/100))
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
    pygame.draw.rect(fenetre, couleur_fond, (longueur*70/100 + 20, largeur*80/100 + 20, longueur*30/100 - 30, largeur*20/100 - 30)) 

# Console
def console():
    """
    Dessine le fond de l'UI de la console
    Taille: 50% de la longueur et 20% de la largeur de l'écran (en 1080p par défaut)
    Couleur de fond: (200, 200, 200) Gris clair
    """
    pygame.draw.rect(fenetre, couleur_fond, (10, largeur*80/100 + 20, longueur*50/100, largeur*20/100 - 30))

# Probalités
def probabilites():
    """
    Dessine le fond de l'UI des probabilités
    Taille: 20% de la longueur et 20% de la largeur de l'écran (en 1080p par défaut)
    Couleur de fond: (200, 200, 200) Gris clair
    """
    pygame.draw.rect(fenetre, couleur_fond, (longueur*50/100 + 20, largeur*80/100 + 20, longueur*20/100 -10, largeur*20/100 - 30))
    texte = pygame.font.SysFont("Source Sans Pro", 30).render("Voir les probabilités", True, (0, 0, 0))
    fenetre.blit(texte, (longueur*54/100 + 30, largeur*86/100 + 30))


##================================================================================================
# Initialisation des objets
##================================================================================================

map_objets = {}
map_boutons = {}
Zone_joueuse1 = pygame.Rect((longueur*70/100 + 30, largeur*70/100 + 40), (longueur*10/100 - 20, largeur*5/100 - 10))
Zone_joueuse2 = pygame.Rect((longueur*80/100 + 30, largeur*70/100 + 40), (longueur*10/100 - 20, largeur*5/100 - 10))
Zone_Zones = pygame.Rect((longueur*50/100 + 30, largeur*80/100 + 40), (longueur*20/100 - 20, largeur*20/100 - 10))
liste_compteur = [0]*10
choix_zones = []
console_phrase = []

def initialiser_objets(liste_joueuses, liste_zones):
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
















##==============================================================================================
# UI Dynamique
##==============================================================================================

class ObjetFixe:

    def __init__(self, x, y, longueur, image_path):
        self.x = x
        self.y = y
        self.longueur = longueur
        if image_path != None:
            self.image = pygame.image.load(image_path)
            self.image = self.redimensionner(longueur)
            self.rect = pygame.Rect(x-5, y+5, self.image.get_width(), self.image.get_height())
            self.largeur = self.image.get_height()
        else:
            self.image = None
            self.rect = pygame.Rect(x, y, longueur, longueur/3)
        self.visible = True
        self.selected = False
        self.actif = False

    def redimensionner(self, nouvelle_longueur):
        ratio = self.image.get_width() / self.image.get_height()
        if nouvelle_longueur > 0:
            return pygame.transform.scale(self.image, (nouvelle_longueur, int(nouvelle_longueur / ratio)))
        else: # Si nouvelle_longueur < 0, on redimensionne en fonction de la longueur de l'objet
            return pygame.transform.scale(self.image, (int(-nouvelle_longueur * ratio), -nouvelle_longueur))



    def afficher(self, fenetre):
        if self.visible:
            if self.image == None:
                pygame.draw.rect(fenetre, (215, 0, 0), self.rect, 2)
            else:
                fenetre.blit(self.image, (self.x, self.y))
            if self.selected:
                pygame.draw.rect(fenetre, (255, 255, 153), self.rect, 3)
            
    
    def deplacer(self, x, y):
        self.x = x
        self.y = y
        if self.image != None:
            self.rect = pygame.Rect(x-5, y+5, self.image.get_width(), self.image.get_height())
        else:
            self.rect = pygame.Rect(x, y, self.longueur, self.longueur/3)


    def changer_image(self, image_path):
        self.image = pygame.image.load(image_path)
        self.image = self.redimensionner(-self.largeur)

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
    
    def action(self):
        pass

class ObjetPersonnageListe(ObjetFixe):

    def __init__(self, x, y, longueur, image_path, info):
        super().__init__(x, y, longueur, image_path)
        self.info = info

    def action(self):
        print("Personnage n° {} de {} sélectionné".format(self.info[0], self.info[1]))


class ObjetStatut(ObjetFixe):

    def __init__(self, x, y, longueur, image_path, info):
        super().__init__(x, y, longueur, image_path)
        self.info = info

    def action(self):
        print("Statut du personnage n° {} de {} sélectionné: {}".format(self.info[0], self.info[1], self.info[2]))


class ObjetCarte(ObjetFixe):

    def __init__(self, x, y, longueur, image_path, info):
        super().__init__(x, y, longueur, image_path)
        self.info = info

    def action(self):
        print("Carte n° {} de {} sélectionnée".format(self.info[0], self.info[1]))

class ObjetPersonnage(ObjetFixe):

    def __init__(self, x, y, longueur, image_path, info, zone, position):
        super().__init__(x, y, longueur, image_path)
        self.info = info
        self.zone = zone
        self.position = position # Position dans la zone, à partir de 0

    def action(self):
        print("Personnage n° {} de {} sélectionné".format(self.info[0], self.info[1]))

    def deplacer(self, x, y, zone, position):
        self.x = x
        self.y = y
        self.zone = zone
        self.position = position

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
            try:
                int(self.texte)
                self.texte = self.valeur
            except:
                if isinstance(self, BoutonValeur):
                    if type(self.texte) != str:
                        if type(self.texte) == list and type(self.valeur) == list:
                            self.texte = (self.valeur[1])
            if self.radius == 1:
                pygame.draw.rect(fenetre, self.couleur, self.rect, border_radius= int (min(self.dimensions)//6))
                pygame.draw.rect(fenetre, (0, 0, 0), self.rect, 3, border_radius= int (min(self.dimensions)//6))
            else:
                pygame.draw.rect(fenetre, self.couleur, self.rect)
                pygame.draw.rect(fenetre, (0, 0, 0), self.rect, 3)
            texte = pygame.font.SysFont("Source Sans Pro", 30).render(str(self.texte), True, self.couleur_texte)
            if self.alignement == "centre":
                fenetre.blit(texte, texte.get_rect(center=self.rect.center))
            if self.alignement == "haut_centre":
                fenetre.blit(texte, (texte.get_rect(midtop=self.rect.midtop).x, texte.get_rect(midtop=self.rect.midtop).y + 5))

    
    def cacher(self):
        self.visible = False

    def montrer(self):
        self.visible = True

    def clic(self, event, map_boutons: dict, map_objets: dict, joueuse: Joueuse):
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
                return self.action(map_boutons, map_objets, joueuse)

    def activer(self):
        self.actif = True
    
    def desactiver(self):
        self.actif = False

class BoutonValeur(Bouton):
    
    valeur = "0"

    def action(self, map_boutons, map_objets, joueuse: Joueuse):
        print("Click sur le bouton {}".format(self.texte))
        if (self.texte == "+" and int(self.valeur) < joueuse.getCapital()):
            self.changer_valeur(1)
        if (self.texte == "-" and int(self.valeur) > 0):
            self.changer_valeur(-1)
        if (self.texte == "Valider"):
            return (self.valider(map_boutons, map_objets, joueuse))
        if (self.texte == "Annuler"):
            self.annuler(map_boutons, map_objets, joueuse)

    @classmethod
    def changer_valeur(cls, incr):
        cls.valeur = str(int(cls.valeur) + incr)

    @classmethod
    def changer_valeur_liste(cls, val: list):
        cls.valeur = (val)

    @classmethod
    def changer_valeur_str(cls, val: str):
        cls.valeur = (val)

    @classmethod
    def valider(cls, map_boutons, map_objets, joueuse: Joueuse):
        try:
            tmp = int(cls.valeur)
            cls.valeur = "0"
            print("Valeur validée : {}".format(tmp))
            if tmp > 0:
                return tmp
            else:
                demander_action(map_boutons, map_objets, joueuse)
                return 0
        except:
            if type(cls.valeur) == list:
                if type(cls.valeur[0]) == str: # carte
                    tmp = cls.valeur
                    cls.valeur = "0"
                    return tmp
                else:
                    tmp = cls.valeur[1] # zone
                    if len(tmp) == cls.valeur[0]:
                        cls.valeur = "0"
                        return tmp
            
    
    @classmethod
    def annuler(cls, map_boutons, map_objets, joueuse: Joueuse):
        cls.valeur = "0"
        demander_action(map_boutons, map_objets, joueuse)
        return 0
    

class BoutonChoix(Bouton):

    def action(self, map_boutons, map_objets, joueuse: Joueuse):
        if self.texte == "Choix d'un personnage 1":
            print("Choix d'un personnage 1")
        elif self.texte == "Choix d'un personnage 2":
            print("Choix d'un personnage 2")
        elif self.texte == "Choix d'un monstre":
            print("Choix d'un monstre")
        elif self.texte == "Utiliser carte":
            print("Choix d'une carte")
            demander_carte(map_boutons, joueuse)
        elif self.texte == "Choix d'une zone":
            print("Choix d'une zone")
        elif self.texte == "Choix d'une autre zone":
            print("Choix d'une autre zone")
        elif self.texte == "Utiliser capital":
            print("Choix de capital")
            demander_capital(map_boutons, joueuse)
        elif self.texte == "Ne rien faire":
            print("Ne rien faire")

class BoutonZone(Bouton):

    def action(self, map_boutons, map_objets, joueuse: Joueuse):
        print("Choix de la zone {}".format(self.texte))


class BoutonValiderCarte(Bouton):

    def action(self, map_boutons, map_objets: dict, joueuse: Joueuse):
        for objet in map_objets.values():
            if objet.__class__.__name__ == "ObjetCarte" and objet.selected:
                print("Carte {} validée".format(objet.nom))

class BoutonAnnulerCarte(Bouton):

    def action(self, map_boutons, map_objets: dict, joueuse: Joueuse):
        for objet in map_objets.values():
            if objet.__class__.__name__ == "ObjetCarte" and objet.selected:
                print("Carte {} annulée".format(objet.nom))

class BoutonFin(Bouton):

    def action(self, map_boutons, map_objets, joueuse: Joueuse):
        pygame.quit()
#================================================================================================
# Informations du jeu
#================================================================================================

def info_joueuse(joueuse: Joueuse):
    """
    Affiche les informations principales de la joueuse
    """
    x, y = (longueur*(70 + (joueuse.getId() - 1) * 10)/100 + 20, 75 + 12 * 50)
    font = pygame.font.SysFont("Source Sans Pro", 24)
    texte = font.render("Capital: {}".format(joueuse.capital), True, (0, 0, 0))
    fenetre.blit(texte, (x, y))
    texte = font.render("Nombre personnages: {}".format(joueuse.taille), True, (0, 0, 0))
    fenetre.blit(texte, (x, y + 20))
    texte = font.render("Tours restants à jouer: {}".format(joueuse.getToursRestantsJouer()), True, (0, 0, 0))
    fenetre.blit(texte, (x, y + 40))
    texte = font.render("Proba par capital: {}".format(joueuse.getProbaParCapital()), True, (0, 0, 0))
    fenetre.blit(texte, (x, y + 60))
    invincibilite = joueuse.getInvincibilite()
    if invincibilite:
        texte = font.render("Invincibilité: Oui", True, (0, 0, 0))
    else:
        texte = font.render("Invincibilité: Non", True, (0, 0, 0))
    fenetre.blit(texte, (x, y + 80))
    texte = font.render("    BONUS", True, (0, 0, 0))
    fenetre.blit(texte, (x, y + 140))    

def info_joueuse_hover_afficher(joueuse: Joueuse):
    """
    Affiche les informations bonus de la joueuse
    """
    x, y = (longueur*(60 + (joueuse.getId() - 1) * 10)/100 + 20, 75 + 13 * 50)
    pygame.draw.rect(fenetre, couleur_fond, (x-20, y-20, 500, 200))
    pygame.draw.rect(fenetre, (0, 0, 0), (x-20, y-20, 500, 200), 2)
    
    font = pygame.font.SysFont("Source Sans Pro", 24)
    texte = font.render("Tours restants Bonus Capital: {} tour(s)".format(joueuse.getTourRestantsBonusCapital()), True, (0, 0, 0))
    fenetre.blit(texte, (x, y))
    texte = font.render("Tours restants Bonus Invincibilité: {} tour(s)".format(joueuse.getToursRestantsInvincibilite()), True, (0, 0, 0))
    fenetre.blit(texte, (x, y + 20))
    texte = font.render("Tours restants Bonus Probabilité par Capital: {} tour(s)".format(joueuse.getToursRestantsBonusProbaParCapital()), True, (0, 0, 0))
    fenetre.blit(texte, (x, y + 40))
    texte = font.render("Bonus temporaire de capital: {}".format(joueuse.getBonusTemporaire()), True, (0, 0, 0))
    fenetre.blit(texte, (x, y + 60))
    texte = font.render("Tour: {}".format(joueuse.getTour()), True, (0, 0, 0))
    fenetre.blit(texte, (x, y + 80))
    texte = font.render("Statuts: {}".format([joueuse.getMembres()[i].statut for i in range(joueuse.getTaille())]), True, (0, 0, 0))
    fenetre.blit(texte, (x, y + 100))

def info_zones(zones: Zones, map_bouton: Bouton, map_objets: dict):
    """
    Affiche les informations des zones et désaffiche les zones
    """
    for bouton in map_bouton.values():
        if isinstance(bouton, BoutonZone):
            bouton.cacher()
    for objet in map_objets.values():
        if isinstance(objet, ObjetPersonnage):
            objet.cacher()
    taille = zones.getMatrice().getTailleMatrice()
    x, y = (130, 30)
    font = pygame.font.SysFont("Source Sans Pro", 60)
    for i in range(taille):
        texte = font.render(str(i+1), True, (0, 0, 0))
        fenetre.blit(texte, (x + i*100, y))
        texte = font.render(str(i+1), True, (0, 0, 0))
        fenetre.blit(texte, (x - 100, y + (i+1)*60))
        for j in range(taille):
            val = round(zones.getMatrice().lecture_probas(j, i), 1)
            texte = font.render(str(val), True, (0, 0, 0))
            fenetre.blit(texte, (x + i*100, y + (j+1)*60))


def fin(map_objets: dict, map_boutons: dict, message: str):
    for objets in map_objets.values():
        objets.cacher()
        del objets
    for boutons in map_boutons.values():
        if not isinstance(boutons, BoutonFin):
            boutons.cacher()
            del boutons
    pygame.draw.rect(fenetre, couleur_fond, (100, 100, longueur -200, largeur - 200))
    pygame.draw.rect(fenetre, (0, 0, 0), (100, 100, longueur -200, largeur - 200), 2)
    font = pygame.font.SysFont("Source Sans Pro", 130)
    texte = font.render("La partie est terminée !", True, (0, 0, 0))
    fenetre.blit(texte, (longueur*40/100, largeur*10/100))
    texte = font.render(message, True, (0, 0, 0))
    fenetre.blit(texte, (longueur*40/100, largeur*40/100))
    map_boutons["bouton_fin"].montrer()
    map_boutons["bouton_fin"].activer()
    map_boutons["bouton_fin"].afficher(fenetre)
    
##==============================================================================================
# Actions
##==============================================================================================

def demander_action(map_boutons: dict, map_objets: dict, joueuse: Joueuse):
    """
    Affiche les boutons d'action principaux: Utiliser du capital, Utiliser une carte, Ne rien faire
    Les rend cliquables (actifs)
    """
    for bouton in map_boutons.values():
        if not isinstance(bouton, BoutonZone):
            bouton.desactiver()
            bouton.cacher()

    map_boutons["bouton_choix_rien"].activer()
    map_boutons["bouton_choix_rien"].montrer()
    map_boutons["bouton_choix_capital"].activer()
    map_boutons["bouton_choix_capital"].montrer()
    map_boutons["bouton_choix_carte"].activer()
    map_boutons["bouton_choix_carte"].montrer()



def demander_capital(map_boutons:dict, joueuse: Joueuse):
    """
    Doit être appelé par le bouton "Utiliser capital"

    Désaffiche et désactive les boutons d'action principaux #see demander_action()
    Affiche les boutons d'action du capital: +, -, valeur, valider, annuler
    Les rend cliquables (actifs)
    """
    map_boutons["bouton_choix_rien"].desactiver()
    map_boutons["bouton_choix_rien"].cacher()
    map_boutons["bouton_choix_capital"].desactiver()
    map_boutons["bouton_choix_capital"].cacher()
    map_boutons["bouton_choix_carte"].desactiver()
    map_boutons["bouton_choix_carte"].cacher()

    map_boutons["bouton_plus"].activer()
    map_boutons["bouton_moins"].activer()
    map_boutons["bouton_plus"].montrer()
    map_boutons["bouton_moins"].montrer()
    map_boutons["bouton_valeur"].activer()
    map_boutons["bouton_valeur"].montrer()
    map_boutons["bouton_valeur_valider"].activer()
    map_boutons["bouton_valeur_valider"].montrer()
    map_boutons["bouton_valeur_annuler"].activer()
    map_boutons["bouton_valeur_annuler"].montrer()


def demander_carte(map_boutons: dict, joueuse: Joueuse):
    """
    Doit être appelé par le bouton "Utiliser carte"	
    
    Désaffiche et désactive les boutons d'action principaux #see demander_action()
    Permet de sélectionner une carte de la joueuse qui est en argument
    Affiche les boutons valider, annuler
    Les rend cliquables (actifs)
    """
    map_boutons["bouton_choix_rien"].desactiver()
    map_boutons["bouton_choix_rien"].cacher()
    map_boutons["bouton_choix_capital"].desactiver()
    map_boutons["bouton_choix_capital"].cacher()
    map_boutons["bouton_choix_carte"].desactiver()
    map_boutons["bouton_choix_carte"].cacher()

    map_boutons["bouton_valeur"].activer()
    map_boutons["bouton_valeur"].montrer()
    map_boutons["bouton_valeur_valider"].activer()
    map_boutons["bouton_valeur_valider"].montrer()
    map_boutons["bouton_valeur_annuler"].activer()
    map_boutons["bouton_valeur_annuler"].montrer()



def ne_rien_faire(map_boutons: dict):
    """
    Doit être appelé par le bouton "Ne rien faire"

    Désaffiche et désactive les boutons d'action principaux #see demander_action()
    Appelle la fonction pour déplacer les monstres et les personnages

    N'affiche aucun bouton
    """
    map_boutons["bouton_choix_rien"].desactiver()
    map_boutons["bouton_choix_rien"].cacher()
    map_boutons["bouton_choix_capital"].desactiver()
    map_boutons["bouton_choix_capital"].cacher()
    map_boutons["bouton_choix_carte"].desactiver()
    map_boutons["bouton_choix_carte"].cacher()


def demander_zone(map_boutons: dict, nb_zones, nombre_demande: int):
    """
    Doit être appelé par le bouton "Valider" de "Utiliser Capital" pour choisir des zones,
    ou par une carte

    Désaffiche et désactive les boutons d'action du capital #see demander_capital()
    Affiche les boutons de choix de zone

    nombre_demande permet de savoir combien de zone il faut choisir
    """
    map_boutons["bouton_moins"].cacher()
    map_boutons["bouton_plus"].cacher()
    choix_zones = [nombre_demande, []]
    map_boutons["bouton_valeur"].changer_valeur_liste(choix_zones)
    for indice_zone in range(nb_zones):
        map_boutons["zone_" + str(indice_zone+1)].actif = True


def demander_personnage(map_objets: dict, map_boutons: dict, joueuse: Joueuse):
    """
    Doit être appelé par une carte

    Affiche les boutons pour valider ou annuler
    Permet de sélectionner les personnages
    """
    map_boutons["bouton_valeur"].changer_valeur_str("Choix d'un personnage")
    for objet in map_objets.values():
        if isinstance(objet, ObjetPersonnage):
            objet.actif = True
            objet.montrer()
            objet.cacher()
    for i in range(joueuse.getTaille()):
        map_objets["personnage_" + str(joueuse.getId()) + "_" + str(i+1)].actif = True
        map_objets["personnage_" + str(joueuse.getId()) + "_" + str(i+1)].montrer()


##==============================================================================================
# Messages génériques
##==============================================================================================

def message_generique(n: int, joueuse: ListePNJ, option: list, option2: Carte, console_phrase: list):
    if n == 0:
        phrase = ("La partie est terminée. C'est la joueuse n°" + str(joueuse.getId()) + " qui a gagné.")
    elif n == -1:
        phrase = ("La partie est terminée. Egalité !")
    elif n == 1:
        phrase = ("Bienvenue dans le jeu de la survie des IIENS !")
    elif n == 2:
        phrase = ("La joueuse dont c'est le tour de jouer a un cadrant rouge autour de son nom.")
    elif n == 3:
        phrase = (f"La joueuse n°{joueuse.getId()} a utilisé {option[0]} de capital.")
    elif n == 4:
        phrase = (f"La probabilité de passer de la zone {option[0]+1} à la zone {option[1]+1} a changé de {option[2]*0.1}.")
    elif n == 5:
        phrase = (f"La joueuse n°{joueuse.getId()} a utilisé la carte {option2.getNom()}.")
    elif n == 6:
        phrase = ("Tous les personnages ont bougé.")
    elif n == 7:
        phrase = (f"Le personnage n°{option[0]+1} de la joueuse n°{joueuse.getId()} est décédé.")
    elif n == 8:
        phrase = ("Le tour est terminé, le capital et les effets des joueuses ont été réinitialisés.")
    elif n == 9:
        phrase = ("Vous avez actuellement {} points de capital, combien voulez-vous en utiliser ?".format(joueuse.getCapital()))
    elif n == 10:
        phrase = ("Quelle carte voulez-vous utiliser ?")
    elif n == 11:
        phrase = ("Quelle zone de départ voulez-vous choisir ?")
    elif n == 12:
        phrase = ("Quelle zone d'arrivée dont la probabilité d'y aller va AUGMENTER voulez-vous choisir ?")
    elif n == 13:
        phrase = ("Quelle zone d'arrivée dont la probabilité d'y aller va DIMINUER voulez-vous choisir ?")
    elif n == 14:
        phrase = ("Que voulez-vous faire ? Utiliser du capital, une carte ou simplement ne rien faire ?")
    elif n == 100:
        phrase = ("Attention, la probabilité de la zone n'est plus dans l'intervalle [0, 1]. L'action a été annulée.")
    elif n == 101:
        phrase = ("Attention, la carte n'a pas pu s'activer. L'action a été annulée.")

    elif n == 201:
        phrase = (f"Votre nouveau capital est de {option[0]} pour {option[1]} tours.")
    elif n == 202:
        phrase = (f"Le personnage n°{option[0]+1} de la joueuse n°{joueuse.getId()} a été déplacé de la zone {option[1]+1} à la zone {option[2]+1}.")
    elif n == 203:
        phrase = (f"Le monstre {option[0]+1} s'est déplacé à la zone {option[1]+1}.")
    elif n == 205:
        phrase = (f"Le nombre de tours restants de la joueuse {joueuse.getId()} est passé à {option[0]}.")
    elif n == 209:
        phrase = (f"Le nombre de déplacements par tour de votre personnage {option[0]+1} est passé à 2.")
    elif n == 210:
        phrase = (f"Le personnage n°{option[0]+1} de la joueuse n°{option[1]} est devenu le personnage n°{option[2]} de la joueuse n°{option[3]}.")
    elif n == 211:
        phrase = ("Vous avez obtenu 15 points de capital supplémentaires pour 1 seul tour.")
    elif n == 212:
        phrase = ("Une nouvelle zone a été créée.")
    elif n == 213:
        phrase = ("Les probabilités ont subi une rotation.")
    elif n == 214:
        phrase = ("Les monstres sont devenus invisibles pour 2 tours.")
    elif n == 215:
        phrase = (f"La probabilité par capital est passée à {option[0]*0.1} pour 3 tours.")
    elif n == 216:
        phrase = (f"La probabilité de passer de la zone {option[0]+1} à la zone {option[1]+1} est passée à {option[2]*0.1}.")
    elif n == 217:
        phrase = (f"Le personnage {option[0]+1} de la joueuse {joueuse.getId()} est devenu un FISA.")
    elif n == 218:
        phrase = ("Un nouveau personnage a été attribué à chaque joueuse, et un monstre a été ajouté.")
    elif n == 219:
        phrase = ("Les probabilités de passer de toutes les zones à celle d'un monstre (choisi aléatoirement) est passé à 0.5.")
    elif n == 220:
        phrase = (f"Les membres de la joueuse {joueuse.getId()} sont invincibles pour 4 tours.")
    
    if len(console_phrase) > 0 and console_phrase[-1] != phrase:
        console_phrase.append(phrase)  
        console()
        afficher_console_phrase(console_phrase)
    elif len(console_phrase) == 0:
        console_phrase.append(phrase)  
        console()
        afficher_console_phrase(console_phrase)

def afficher_console_phrase(console_phrase: list):
    font = pygame.font.SysFont("Source Sans Pro", 25)
    x, y = 20, largeur*80/100 + 30,
    if len(console_phrase) > 7:
        console_phrase.pop(0)
    for i in range(len(console_phrase)):
        texte = font.render(console_phrase[i], True, (0, 0, 0))
        fenetre.blit(texte, (x, y + 23*i))