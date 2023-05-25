##==============================================================================================
# Fichier: interface.py
# Brief: Interface du jeu
# Necessités: effets.py, Python 3.11, Pygame 2.4.0
##==============================================================================================

import sys
import os

current_dir = os.path.dirname(os.path.abspath(sys.argv[0]))+"\package"
sys.path.insert(0, current_dir)
print(current_dir)
os.chdir(current_dir)

from package.effets import *







def main():

    liste_cartes_globale = [Merabet(), Bannour(), Honore(), Rioboo(), Goilard(), Bourard(), Munante(), Benezet(), Ligozat(), Mouilleron(),
                                      Demebele_Cabot(),  Pacave(), Huet(), Matias(), Salhab(), Pulido_Nino(), Watel(), Szanfranski(), Forest(), Prevel()]


    joueuse_1 = Joueuse(1, liste_cartes_globale)
    joueuse_2 = Joueuse(2, liste_cartes_globale)
    monstres = ListeMonstre()

    liste_joueuses = [joueuse_1, joueuse_2, monstres]
    message_generique(1, None, None, None)


main()