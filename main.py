##==============================================================================================
# Fichier: interface.py
# Brief: Interface du jeu
# Necessités: effets.py, Python 3.11, Pygame 2.4.0
##==============================================================================================

from package.effets import *



def main():

    liste_cartes_glolbale = ListeCartes()
    liste_cartes_glolbale.ajout_carte(Merabet(), Bannour(), Honore(), Rioboo(), Goilard(), Bourard(), Munante(), Benezet(), Ligozat(), Mouilleron(),
                                      Demebele_Cabot(),  Pacave(), Huet(), Matias(), Salhab(), Pulido_Nino(), Watel(), Szanfranski(), Forest(), Prevel())
    
    joueuse_1 = Joueuse(1, liste_cartes_glolbale)
    joueuse_2 = Joueuse(2, liste_cartes_glolbale)
    monstres = ListeMonstre(liste_cartes_glolbale)

    liste_joueuses = [joueuse_1, joueuse_2, monstres]
    message_generique(1, None, None, None)

    liste_zones = 
