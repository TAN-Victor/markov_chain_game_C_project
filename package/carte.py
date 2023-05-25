import random
import sys

class Carte:
    def __init__ (self, nom, description):
        self.nom = nom
        self.description = description
    
#getters:
    def getNom(self):
        return self.nom
    
    def getDescription(self):
        return self.description


