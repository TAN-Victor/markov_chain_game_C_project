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
    Taille: 70% de la longueur et 20% de la largeur de l'écran (en 1080p par défaut)
    Couleur de fond: (200, 200, 200) Gris clair
    """
    pygame.draw.rect(fenetre, couleur_fond, (10, largeur*80/100 + 20, longueur*70/100, largeur*20/100 - 30))



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
                self.action(map_boutons, map_objets, joueuse)

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
            self.valider()
        if (self.texte == "Annuler"):
            self.annuler()

    @classmethod
    def changer_valeur(cls, incr):
        cls.valeur = str(int(cls.valeur) + incr)
        print(cls.valeur)

    @classmethod
    def valider(cls):
        tmp = int(cls.valeur)
        cls.valeur = "0"
        print("Valeur validée : {}".format(tmp))
        return tmp
    
    @classmethod
    def annuler(cls):
        cls.valeur = "0"
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
            demander_carte(map_boutons, map_objets, joueuse)
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

#================================================================================================


##==============================================================================================
# Actions
##==============================================================================================

def demander_action(map_boutons: dict, map_objets: dict, joueuse: Joueuse):
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


def demander_carte(map_boutons: dict, map_objets: dict, joueuse: Joueuse):
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

    i = joueuse.getId()
    for j in range(0, len(joueuse.getCartes())):
        map_objets["carte_" + str(i) + "_" + str(j+1)].activer()

        map_boutons["bouton_carte_valider"].activer()
        map_boutons["bouton_carte_valider"].montrer()
        map_boutons["bouton_carte_annuler"].activer()
        map_boutons["bouton_carte_annuler"].montrer()



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







##==============================================================================================
# Messages génériques
##==============================================================================================

def message_generique(n: int, joueuse: ListePNJ, option: list, option2: Carte):
    if n == 1:
        print("Les personnages ont été correctement initialisés.")
    elif n == 2:
        print("Les zones ont été correctement initialisées.")
    elif n == 3:
        print(f"La joueuse n°{joueuse.getId()} a utilisé {option[0]} de capital.")
    elif n == 4:
        print(f"La probabilité de passer de la zone {option[0]+1} à la zone {option[1]+1} a changé de {option[2]*0.1}.")
    elif n == 5:
        print(f"La joueuse n°{joueuse.getId()} a utilisé la carte {option2.getNom()}.")
    elif n == 6:
        print("Tous les personnages ont bougé.")
    elif n == 7:
        print(f"Le personnage n°{option[0]+1} de la joueuse n°{joueuse.getId()} est décédé.")
    elif n == 8:
        print("Le tour est terminé, le capital et les effets des joueuses ont été réinitialisés.")
    elif n == 9:
        print("Les personnages ont été correctement libérés par free().")
    elif n == 10:
        print("Les zones ont été correctement libérées par free().")
    elif n == 11:
        print("La matrice des zones a été correctement libérée par free().")
    elif n == 12:
        print("Les cartes ont été correctement libérées par free().")
    elif n == 100:
        print("Attention, la probabilité de la zone n'est plus dans l'intervalle [0, 1]. L'action a été annulée.")
    elif n == 201:
        print(f"Votre nouveau capital est de {option[0]} pour {option[1]} tours.")
    elif n == 202:
        print(f"Le personnage n°{option[0]+1} de la joueuse n°{joueuse.getId()} a été déplacé de la zone {option[1]+1} à la zone {option[2]+1}.")
    elif n == 203:
        print(f"Le monstre {option[0]+1} s'est déplacé à la zone {option[1]+1}.")
    elif n == 205:
        print(f"Le nombre de tours restants de la joueuse {joueuse.getId()} est passé à {option[0]}.")
    elif n == 209:
        print(f"Le nombre de déplacements par tour de votre personnage {option[0]+1} est passé à 2.")
    elif n == 210:
        print(f"Le personnage n°{option[0]+1} de la joueuse n°{option[1]} est devenu le personnage n°{option[2]} de la joueuse n°{option[3]}.")
    elif n == 211:
        print("Vous avez obtenu 15 points de capital supplémentaires pour 1 seul tour.")
    elif n == 212:
        print("Une nouvelle zone a été créée.")
    elif n == 213:
        print("Les probabilités ont subi une rotation.")
    elif n == 214:
        print("Les monstres sont devenus invisibles pour 2 tours.")
    elif n == 215:
        print(f"La probabilité par capital est passée à {option[0]*0.1} pour 3 tours.")
    elif n == 216:
        print(f"La probabilité de passer de la zone {option[0]+1} à la zone {option[1]+1} est passée à {option[2]*0.1}.")
    elif n == 217:
        print(f"Le personnage {option[0]+1} de la joueuse {joueuse.getId()} est devenu un FISA.")
    elif n == 218:
        print("Un nouveau personnage a été attribué à chaque joueuse, et un monstre a été ajouté.")
    elif n == 219:
        print("Les probabilités de passer de toutes les zones à celle d'un monstre (choisi aléatoirement) est passé à 0.5.")
    elif n == 220:
        print(f"Les membres de la joueuse {joueuse.getId()} sont invincibles pour 4 tours.")
    