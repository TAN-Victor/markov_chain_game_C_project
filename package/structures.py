from carte import *

# Création des constantes 
NB_CARTES_MAIN_JOUEUSE = 5
NB_DE_ZONES = 10

# Classe matrice de probabilités
class MatriceProbas:
    def __init__(self, matrice, taille_matrice):
        self.matrice = matrice
        self.taille_matrice = taille_matrice

    def __init__(self, taille_matrice):
        prob = 1/taille_matrice
        self.matrice = [[prob] * taille_matrice for _ in range(taille_matrice)]
        self.taille_matrice = taille_matrice

    def lecture_probas(self, i, j):
        return self.matrice[i][j]
    
    def modifier_proba(self, i, j, proba):
        self.matrice[i][j] = proba

    def produit_matrice(matrice1, matrice2):
        if matrice1.taille_matrice != matrice2.taille_matrice:
            return None
        
        taille_matrice = matrice1.taille_matrice
        matrice = MatriceProbas(taille_matrice) #on crée une nouvelle matrice de probabilités
        
        for i in range(taille_matrice):
            for j in range(taille_matrice):
                somme = 0
                for k in range(taille_matrice):
                    somme += matrice1.proba[i][k] * matrice2.proba[k][j]
                matrice.proba[i][j] = somme
        
        return matrice

    def getTailleMatrice(self):
        return self.taille_matrice
    
    def setTailleMatrice(self, taille):
        self.taille_matrice = taille

