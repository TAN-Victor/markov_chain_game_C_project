class Joueuse:
    
    def __init__(self, capital, liste_membres, liste_cartes, id, tour, taille, tour_restants_bonus_capital, tours_restants_invincibilite, tours_restants_jouer, proba_par_capital, bonus_temporaire, tours_restants_bonus_proba_par_capital):
        self.capital = 5
        self.liste_membres = liste_membres #une liste de personnages correspondant aux membres de la joueuse (de taille 7 = taille max de l'équipe)
        self.liste_cartes = liste_cartes #cartes contenue dans la main de la joueuse
        self.id = id #permet d'idendifier la joueuse: 0 si c'est la liste de monstre, 1 si c'est la joueuse 1, 2 si c'est la joueuse 2
        self.tour = tour #permet de savoir si c'est le tour de la joueuse
        self.taille = 5 #nombre de membres dans la liste de membres (doit être toujours inférieur à 7)
        self.tour_restants_bonus_capital = 1 #nombre de tours restants pendant lesquels la joueuse peut recevoir plus de capital
        self.tours_restants_invincibilite = 0 #nombre de tours restants pendant lesquels les membres de la joueuse ne peut pas être mangée par un monstre
        self.tours_restants_jouer = 1 #tours restants pendant lesquels la joueuse peut faire des déplacements (nombres de tours d'affilés)
        self.proba_par_capital = 0.1 #la valeur de la modification de la probabilitée par une joeuse, par unité de capital (cf Katrin Salhab)
        self.bonus_temporaire = 0 #vaut un entier strctement positif si le bonus est actif, correspond à la valeur du bonus de capital pendant un tour uniquement, et est remis à 0 au tour suivant. Vaut 0 si aucun bonus de capuital n'est actif
        self.tours_restants_bonus_proba_par_capital = 0 #nombre de tours pendant lesquels la probabilité par capital est modifiée



 #Getters:

    def getMembres(self):
        return self.liste_membres

    def getCartes(self):
        return self.liste_cartes

    def getCapital(self):
        return self.capital
    
    def getIdJOueuse(self):
        return self.id
    
    def getTour(self):
        return self.tour

    def getTaille(self):
        return self.taille #il faudra modifier la taille en fonction du nombre de membres

    def getTourRestantsBonusCapital(self):
        return self.tour_restants_bonus_capital

    def getToursRestantsInvincibilite(self):
        return self.tours_restants_invincibilite

    def getInvincibilite(self):
        return getToursRestantsInvincibilite() > 0
    
    def getToursRestantsJouer(self):
        return self.tours_restants_jouer
    
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

    def setIdJoueuse(self, id):
        self.id = id

    def setTour(self, tour):
        self.tour = tour

    def setTaille(self, taille):
        self.taille = taille

    def setTourRestantsBonusCapital(self, tour):
        self.tour_restants_bonus_capital = tour

    def setToursRestantsInvincibilite(self, tour):
        self.tours_restants_invincibilite = tour

    def setToursRestantsJouer(self, tour):
        self.tours_restants_jouer = tour

    def setBonusTemporaire(self, bonus):
        self.bonus_temporaire = bonus

    def setToursRestantsBonusProbaParCapital(self, tour):
        self.tours_restants_bonus_proba_par_capital = tour

        
