from personnage import *


class ListePNJ:
    def __init__(self, id, liste_membres, taille, tours_restants_jouer):
        self.id = id #permet d'idendifier la joueuse: 0 si c'est le monstre, 1 si c'est la joueuse 1, 2 si c'est la joueuse 2
        self.liste_membres = liste_membres #une liste de personnages correspondant aux membres de la joueuse (de taille 7 = taille max de l'équipe)
        self.taille = taille #nombre de membres dans la liste de membres (doit être toujours inférieur à 7)
        self.tours_restants_jouer = tours_restants_jouer #tours restants pendant lesquels la joueuse / le monstre peut faire des déplacements (nombres de tours d'affilés)

    #Getters:
    def getMembres(self):
        return self.liste_membres
    
    def getId(self):
        return self.id

    def getTaille(self):
        return self.taille #il faudra modifier la taille en fonction du nombre de membres

    def getToursRestantsJouer(self):
        return self.tours_restants_jouer
    
    #Setters:
    
    def setId(self, id):
        self.id = id
    
    def setTaille(self, taille):
        self.taille = taille

    def setToursRestantsJouer(self, tours_restants_jouer):
        self.tours_restants_jouer = tours_restants_jouer

    #Méthodes:
    def addMembre(self, membre):
        self.liste_membres.append(membre)
        self.taille += 1

    def removeMembre(self, membre):
        self.liste_membres.remove(membre)
        self.taille -= 1


class Joueuse(ListePNJ):
    
    def __init__(self, capital, liste_membres, liste_cartes, id, tour, taille, tour_restants_bonus_capital, tours_restants_invincibilite, tours_restants_jouer, proba_par_capital, bonus_temporaire, tours_restants_bonus_proba_par_capital):
        super().__init__(id, liste_membres, 5, tours_restants_jouer)
        self.capital = 5
        self.liste_cartes = liste_cartes #cartes contenue dans la main de la joueuse
        self.tour = tour #permet de savoir si c'est le tour de la joueuse ou non
        self.tour_restants_bonus_capital = 0 #nombre de tours restants pendant lesquels la joueuse peut recevoir plus de capital
        self.tours_restants_invincibilite = 0 #nombre de tours restants pendant lesquels les membres de la joueuse ne peut pas être mangée par un monstre
        self.proba_par_capital = 0.1 #la valeur de la modification de la probabilitée par une joeuse, par unité de capital (cf Katrin Salhab)
        self.bonus_temporaire = 0 #vaut un entier strctement positif si le bonus est actif, correspond à la valeur du bonus de capital pendant un tour uniquement, et est remis à 0 au tour suivant. Vaut 0 si aucun bonus de capuital n'est actif
        self.tours_restants_bonus_proba_par_capital = 0 #nombre de tours pendant lesquels la probabilité par capital est modifiée



    #Getters:

    def getCartes(self):
        return self.liste_cartes

    def getCapital(self):
        return self.capital
    
    def getTour(self):
        return self.tour

    def getTourRestantsBonusCapital(self):
        return self.tour_restants_bonus_capital

    def getToursRestantsInvincibilite(self):
        return self.tours_restants_invincibilite

    def getInvincibilite(self):
        return self.getToursRestantsInvincibilite() > 0
    
    def getProbaParCapital(self):
        return self.proba_par_capital

    def getBonusTemporaire(self):
        return self.bonus_temporaire
    
    def getToursRestantsBonusProbaParCapital(self):
        return self.tours_restants_bonus_proba_par_capital


    #Setters:

    def setProbaParCapital(self, proba):
        self.proba_par_capital = proba

    def setCapital(self, capital):
        self.capital = capital

    def setTour(self, tour):
        self.tour = tour
    
    def setTourRestantsBonusCapital(self, tour_restants_bonus_capital):
        self.tour_restants_bonus_capital = tour_restants_bonus_capital
    
    def setToursRestantsInvincibilite(self, tours_restants_invincibilite):
        self.tours_restants_invincibilite = tours_restants_invincibilite

    def setBonusTemporaire(self, bonus_temporaire):
        self.bonus_temporaire = bonus_temporaire
    
    def setToursRestantsBonusProbaParCapital(self, tours_restants_bonus_proba_par_capital):
        self.tours_restants_bonus_proba_par_capital = tours_restants_bonus_proba_par_capital

    def setCartes(self, liste_cartes):
        self.liste_cartes = liste_cartes

    #Méthodes:
    def utiliseCapital(self, capital):
        if self.getCapital() >= capital:
            self.setCapital(self.getCapital() - capital)
        else:
            print("La joueuse n'a pas assez de capital pour utiliser cette carte")

    def utiliseCarte(self, carte):
        if carte in self.getCartes():
            self.getCartes().remove(carte)
            carte.use()
        else:
            print("La joueuse ne possède pas cette carte")
    
    def tous_manges(self):
        if self.getTaille() == 0:
            return True
        elif self.getTaille() < 0:
            print("Erreur: la taille de la liste de membres est négative")
            return False
        else:
            manges = 0
            for membre in self.getMembres():
                if membre.statut == 0:
                    manges += 1
            if manges == self.getTaille():
                return True


    


class ListeMonstre(ListePNJ):
    def __init__(self, liste_membres, taille, tours_restants_jouer):
        super().__init__(0, liste_membres, taille, tours_restants_jouer)

