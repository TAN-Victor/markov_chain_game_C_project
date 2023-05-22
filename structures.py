class MatriceProbas:
    def __init__(self, matrice, taille_matrice):
        self.matrice = matrice
        self.taille_matrice = taille_matrice

    def __init__(self, taille_matrice):
        prob = 1/taille_matrice
        self.matrice = [[prob] * taille_matrice for _ in range(taille_matrice)]

    def lecture_probas(self, i, j):
        return self.matrice[i][j]
    
    def modifier_proba(self, i, j, proba):
        self.matrice[i][j] = proba
