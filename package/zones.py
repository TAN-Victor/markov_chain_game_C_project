from structures.py import MatriceProbas
from structures.py import ListeCartes
import random
import sys

class Zone:
    def __init__(self, numero, est_autorise):
        self.numero = numero
        self.est_autorise = est_autorise #vaut 0 si tous les personnages sont autorisés, 1 si uniquement ceux de joueuse 1, 2 si ceux de joueuse 2

class Zones:
    def __init__(self, nb_zones):
        self.tab_zones = [Zone(i, 0) for i in range(nb_zones)] #tableau de zones
        self.matrice = MatriceProbas(nb_zones) #matrice de probabilités

    @staticmethod
    def nouvellesZones(nb_zones):
        prob = 1 / nb_zones #probabilité de chaque case
        zones_obj = Zones(nb_zones) #création de l'objet zones

        for i in range(nb_zones):
            for j in range(nb_zones):
                zones_obj.matrice.modifier_proba(i, j, prob) #modification de la probabilité de chaque case

        return zones_obj

    def modifierZone(self, n1, n2, proba, action):
        if action == 1:
            self.matrice.modifier_proba(n1, n2, self.matrice.lecture_probas(n1, n2) + proba)
        elif action == 0:
            self.matrice.modifier_proba(n1, n2, self.matrice.lecture_probas(n1, n2) - proba)

    def trouveZone(self, n):
        taille_matrice = self.matrice.getTailleMatrice()
        
        # On vérifie la taille de la matrice
        if taille_matrice == 10:
            # On vérifie si le numéro de zone est valide
            if n < 0 or n > 9:
                print(f"trouveZone : n<0 ou n>9, en effet, n={n}", file=sys.stderr)
                sys.exit(n)
            else:
                for i in range(taille_matrice):
                    if self.tab_zones[i].numero == n:
                        return self.tab_zones[i]
                
                print(f"trouveZone : aucune zone trouvée pour n={n}", file=sys.stderr)
                sys.exit(n)
        else: # Le nombre de zones vaut 11
            # On vérifie si le numéro de zone est valide
            if n < 0 or n > 10:
                print(f"trouveZone : n<0 ou n>11, en effet, n={n}", file=sys.stderr)
                sys.exit(n)
            else:
                for i in range(taille_matrice):
                    if self.tab_zones[i].numero == n:
                        return self.tab_zones[i]
                
                print(f"trouveZone : aucune zone trouvée pour n={n}", file=sys.stderr)
                sys.exit(n)

    def prochaineZone(self, nz):
        taille_matrice = self.matrice.getTailleMatrice()

        # On vérifie la taille de la matrice
        if taille_matrice == 10:
            # On vérifie si le numéro de zone est valide
            if nz < 0 or nz > 9:
                print(f"prochaineZone : nz<0 ou nz>9, en effet, nz={nz}", file=sys.stderr)
                return -1

            x = random.random()  # Générer un nombre aléatoire entre 0 et 1
            somme = 0.0
            prochaine_case = -1

            # Parcourir le tableau des probabilités et accumuler les probabilités
            for i in range(taille_matrice):
                somme += self.matrice.proba[nz][i]
                if somme >= x:
                    prochaine_case = i
                    break

            # Renvoie -1 en cas d'erreur, et le numéro de la prochaine zone sinon
            return prochaine_case

        else:  # Le nombre de zones vaut 11 dans ce cas-là
            # On vérifie si le numéro de la zone est valide
            if nz < 0 or nz > 10:
                print(f"prochaineZone : nz<0 ou nz>10, en effet, nz={nz}", file=sys.stderr)
                return -1

            x = random.random()  # Générer un nombre aléatoire entre 0 et 1
            somme = 0.0
            prochaine_case = -1

            # Parcourir le tableau des probabilités et accumuler les probabilités
            for i in range(taille_matrice):
                somme += self.matrice.proba[nz][i]
                if somme >= x:
                    prochaine_case = i
                    break

            # Renvoie -1 en cas d'erreur, et le numéro de la prochaine zone sinon
            return prochaine_case
        
    def getNumero(self, z):
        return z.numero

    def setNumero(self, z, n):
        z.numero = n

    def getEstAutorise(self, z):
        return z.est_autorise

    def setEstAutorise(self, z, n):
        z.est_autorise = n

    def getTabZones(self):
        return self.tab_zones

    def getMatrice(self):
        return self.matrice

    def setMatrice(self, m):
        self.matrice = m

    def addZone(self):
        taille = len(self.tab_zones)
        self.tab_zones.append(Zone(taille, 0))
        self.matrice.ajouterLigne()
        self.matrice.ajouterColonne()
