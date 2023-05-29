import random
import sys
import os


from interface import *



class Merabet(Carte):
    def __init__(self):
        super().__init__("Merabet", "Pendant vos 3 prochains tours, votre capital augmente de 2.")
    def use(self, joueuse):
        joueuse.setToursRestantsBonusCapital(3)
        joueuse.setBonusTemporaire(2)




class Bannour(Carte):
    def __init__(self):
        super().__init__("Bannour", "Choisissez deux zones, les personnages présents sur ces deux zones sont échangés.")

    def use(self, nb_zones):
        demander_zone(map_boutons, nb_zones, 2)

    def use2(self, liste_des_joueuses, zone1, zone2):
        for joueuse in liste_des_joueuses:
            for membre in joueuse.getMembres():
                if membre.zone_courante == zone1:
                    membre.deplacer(zone2)
                    message_generique(202, joueuse, [membre.id, zone1.numero, zone2.numero], None, console_phrase)
                elif membre.zone_courante == zone2:
                    membre.deplacer(zone1)
                    message_generique(202, joueuse, [membre.id, zone2.numero, zone1.numero], None, console_phrase)






class Honore(Carte):
    def __init__(self):
        super().__init__("Honoré", "Chaque monstre se déplace 3 fois. Chaque membre d'école qu'un monstre rencontre est mangé.")

    def use(self, liste_des_joueuses,liste_des_monstres, liste_des_zones):
        liste_des_monstres.setToursRestantsJouer(3)
        for i in range(3):
            for monstre in liste_des_monstres:
                for joueuse in liste_des_joueuses:
                    for membre in joueuse.getMembres():
                        if membre.zone == monstre.zone:
                            membre.statut=0
    





class Rioboo(Carte):
    def __init__(self):
        super().__init__("Rioboo", "Lors du prochain tour, la joueuse adverse ne choisit pas comment est utilisé son capital. Chaque point de capital est utilisé aléatoirement: pour chaque point, choisissez les trois zones Z1, Z2 et Z3 uniformément parmi les triplets pouvant être choisis.")

    def use(self, adversaire, zones):
        capital  = adversaire.getCapital()
        if capital<0 or capital>adversaire.getCapital:
            print("veuiilez entrer un nombre valide")
        else:
            proba_par_capital = adversaire.getProbaParCapital()
            zone1 = random.choice(zones.getTabZones())
            zone2 = random.choice(zones.getTabZones())
            zone3 = random.choice(zones.getTabZones())
            while (zone2.numero == zone3.numero or zones.getMatrice().lecture_probas(zone1.numero, zone2.numero) + proba_par_capital > 1 or zones.getMatrice().lecture_probas(zone1.numero, zone3.numero) - proba_par_capital < 0):
                zone1 = random.choice(zones.getTabZones())
                zone2 = random.choice(zones.getTabZones())
                zone3 = random.choice(zones.getTabZones())
            zones.modifierZone(zone1.numero, zone2.numero, adversaire.getProbaParCapital(),1)
            zones.modifierZone(zone1.numero, zone3.numero, adversaire.getProbaParCapital(),0)
            adversaire.setCapital(adversaire.getCapital()-capital)
        



class Goilard(Carte):
    def __init__(self):
        super().__init__("Goilard", "Lors du prochain tour et du suivant, c'est vous qui jouez. Lors des deux tours suivant, c'est la joueuse adverse qui joue.")

    def use(self, joueuse, adversaire):
        joueuse.setToursRestantsJouer(2)
        adversaire.setToursRestantsJouer(2)



class Bourard(Carte):
    def __init__(self):
        super().__init__("Bourard", "Lors du prochain déplacement, si deux membres d'écoles adverses se retrouvent sur la même zone, ils se déplacent de nouveau. Si ces deux membres sont sur la zone du monstre avant le second déplacement, ils ne sont pas mangés. On recommence l'opération au plus 100 fois, jusqu'à ce que les membres des écoles adverses soient sur des zones distinctes.")

    def use(self, liste_monstres, liste_des_joueuses, liste_zones):
        nb_monstre = liste_monstres.getTaille()
        for i in range(nb_monstre):
            if liste_monstres.getMembres()[i].peut_se_deplacer and liste_monstres.getMembres()[i].statut == 1:
                for k in range(liste_des_joueuses.getMembres()[i].nb_de_pas):
                    liste_monstres.getMembres()[i].deplacer(liste_zones.trouveZone(liste_zones.prochaineZone(liste_monstres.getMembres()[i].zone_courante)))
                liste_monstres.getMembres()[i].peut_se_deplacer = False
        
        for i in range(2):
            nb_membres = liste_des_joueuses[i].getTaille()
            for j in range(nb_membres):
                if liste_des_joueuses[i].peut_se_deplacer and liste_des_joueuses[i].getMembres()[j].statut == 1:
                    for k in range(liste_des_joueuses[i].getMembres()[j].nb_de_pas):
                        liste_des_joueuses[i].getMembres()[j].deplacer(liste_zones.trouveZone(liste_zones.prochaineZone(liste_des_joueuses[i].getMembres()[j].zone_courante)))

        continuer = True
        nb_tour = 0
        while continuer and nb_tour < 100:
            for i in range(liste_des_joueuses[0].getTaille()):
                for j in range(liste_des_joueuses[1].getTaille()):
                    if liste_des_joueuses[0].getMembres()[i].zone_courante == liste_des_joueuses[1].getMembres()[j].zone_courante:
                        continuer = True
                        nb_tour += 1
                        liste_des_joueuses[0].getMembres()[i].deplacer(liste_zones.trouveZone(liste_zones.prochaineZone(liste_des_joueuses[0].getMembres()[i].zone_courante)))
                        liste_des_joueuses[1].getMembres()[j].deplacer(liste_zones.trouveZone(liste_zones.prochaineZone(liste_des_joueuses[1].getMembres()[j].zone_courante)))
        
        for i in range(2):
            for j in range(liste_des_joueuses[i].getTaille()):
                liste_des_joueuses[i].getMembres()[j].peut_se_deplacer = False



class Munante(Carte):
    def __init__(self):
        super().__init__("Munante", "Les membres d'écoles présents sur la zone où était un monstre avant son dernier déplacement sont mangés.")

    def use(self, liste_des_joueuses, liste_des_monstres):
        for monstre in liste_des_monstres:
            for joueuse in liste_des_joueuses:
                for membre in joueuse.getMembres():
                    if membre.zone == monstre.zone:
                        membre.statut = 0

class Benezet(Carte):
    def __init__(self):
        super().__init__("Benezet", "Déplacez un des monstres sur la zone de votre choix. Si un membre d'école se trouve sur la zone du monstre, il n'est pas mangé.")   

    def use(self):
        demander_monstre()
        demander_zone()

    def use2(self, num_monstre, zone):
        monstres[num_monstre].deplacer(num_zone)



class Ligozat(Carte):
    def __init__(self):
        super().__init__("Ligozat", "Choisissez un membre de votre école, il effectue désormais deux déplacements au lieu d'un à chaque tour.")

    def use(self):
        demander_membre()
    
    def use2(self, joueuse, num_membre):
        joueuse.getMembres()[num_membre].nb_de_pas = 2



class Mouilleron(Carte):
    def __init__(self):
        super().__init__("Mouilleron", "Choisissez un membre de l'école de la joueuse adverse. Ce membre devient un membre de votre école.")

    def use(self):
        demander_membre()
    
    def use2(self,adversaire, joueuse, num_membre):
        if joueuse.getTaille()<=6:
            joueuse.addMembre(adversaire.liste_membres[num_membre])
            adversaire.removeMembre(adversaire.liste_membres[num_membre])
        else:
            print("Vous ne pouvez pas avoir plus de 7 membres dans votre école")



class Dembele_Cabot(Carte):
    def __init__(self):
        super().__init__("Dembele-Cabot", "Sacrifiez un membre de votre école de votre choix. Vous avez 15 points de capital en plus à votre prochain tour.")
    
    def use(self):
        demander_membre()

    def use(self, joueuse, num_membre):
        joueuse.liste_membres.remove(joueuse.liste_membres[num_membre])
        joueuse.setCapital(joueuse.getCapital()+15)



class Pacave(Carte):
    def __init__(self):
        super().__init__("Pacave", "Créez une nouvelle zone. Les membres de votre école sont les seuls à pouvoir se déplacer sur cette zone. Un membre de l'école de l'autre joueuse qui devrait se déplacer sur cette zone ne se déplace pas. La probabilité d'aller sur cette zone est de 0. Depuis cette zone, la probabilité de rester sur cette zone est 1.")

    def use(self, joueuse, zones):
        zones.addZone()
        zones.setEstAutorise(zones.getTabZones()[zones.getMatrice().getTailleMatrice()-1], joueuse.getId())
        zones.getMatrice().modifier_proba(zones.getTabZones()[zones.getMatrice().getTailleMatrice()-1], zones.getTabZones()[zones.getMatrice().getTailleMatrice()-1], 1)



class Huet(Carte):
    def __init__(self):
        super().__init__("Huet", "Chaque zone effectue une rotation de probabilité. La probabilité d'aller de la zone i à la zone j devient la probabilité d'aller de la zone i à la zone j + 1. La probabilité d'aller de la zone i à la zone 10 devient la probabilité d'aller de la zone i à la zone 1.")

    def use(self, zones):
        taille = zones.getMatrice().getTailleMatrice()
        matrice = zones.getMatrice()
        for i in range(taille):
            proba = matrice[i][i]
            for j in range(taille - 1):
                matrice[i][j] = matrice[i][j+1]
            matrice[i][taille - 1] = proba
    



class Matias(Carte):
    def __init__(self):
        super().__init__("Matias", "Chaque monstre disparaît pendant 2 tours. Il réapparaîtra sur la zone d'où il est parti.")

    def use(self, liste_des_monstres):
        for monstre in liste_des_monstres:
            monstre.nb_de_tour_disparu_restant = 3  #Les 2 prochains tours + le tour où la carte est jouée



class Salhab(Carte):
    def __init__(self):
        super().__init__("Salhab", "Pendant vos 3 prochains tours, un point de capital permet de déplacer une quantité 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9 ou 1 de probabilité.")

    def use(self):
        demander_proba()

    def use2(self, joueuse, proba_par_capital):
        joueuse.setToursRestantsBonusProbaParCapital(4) #Les 3 prochains tours + le tour où la carte est jouée
        joueuse.setProbaParCapital(proba_par_capital)



class Pulido_Nino(Carte):
    def __init__(self):
        super().__init__("Pulido-Nino", "Mettez à 0 les probabilités permettant de sortir de la zone de chaque monstre et mettez à 1 la probabilité de rester dans la zone de chaque monstre.")

    def use(self, zones, liste_des_monstres):
        matrice = zones.getMatrice()
        for monstre in liste_des_monstres:
            for i in range(matrice.getTailleMatrice()):
                matrice.modifier_proba(monstre.zone_courante.numero, i, 0)
            matrice.modifier_proba(i,i,1)




class Watel(Carte):
    def __init__(self):
        super().__init__("Watel", "Choisissez un membre de votre école, il devient FISA et effectue désormais son déplacement un tour sur deux.")
    
    def use(self):
        demander_membre()
    
    def use2(self, joueuse, num_membre):
        joueuse.liste_membres[num_membre].statut = 3



class Szafranski(Carte):
    def __init__(self):
        super().__init__("Szafranski", "Ajoutez un monstre sur la zone 1, un membre de votre école sur la zone 2 et un membre de l'école adverse sur la zone 3. Si un membre d'école se trouve sur la même zone qu'un monstre, il n'est pas mangé.")

    def use(self, joueuse, adversaire, liste_des_monstres):
        liste_des_monstres.addMembre(Personnage(0,liste_des_monstres.getTaille()+1,1))
        joueuse.addMembre(Personnage(joueuse.getId(),joueuse.getTaille()+1, 2))
        adversaire.addMembre(Personnage(adversaire.getId(),adversaire.getTaille()+1, 3))



class Forest(Carte):
    def __init__(self):
        super().__init__("Forest", "Mettez toutes les probabilités à 0. Puis, pour chaque zone, la probabilité de se déplacer de cette zone vers la zone contenant le monstre passe à 0.5 (s'il y a plusieurs monstres, un des monstres est choisi aléatoirement) ; et la probabilité de se déplacer de cette zone vers une autre zone ne contenant pas de monstre choisie aléatoirement passe également à 0.5.")

    def use(self, zones, liste_des_monstres):
        matrice = zones.getMatrice()
        for i in range(matrice.getTailleMatrice()):
            for j in range(matrice.getTailleMatrice()):
                matrice.modifier_proba(i,j,0)
        monstre = liste_des_monstres.getMembres()[random.randint(0, liste_des_monstres.getTaille() -1)]
        for i in range(matrice.getTailleMatrice()):
            matrice.modifier_proba(i,monstre.zone_courante.numero,0.5)
            random2 = random.randint(0, matrice.getTailleMatrice())
            while random2 == monstre.zone_courante.numero:
                random2 = random.randint(0, matrice.getTailleMatrice())
            matrice.modifier_proba(i,random2,0.5)





class Prevel(Carte):
    def __init__(self):
        super().__init__("Prével", "Pendant 4 tours, les membres de votre école ne peuvent être mangés par un monstre. S'ils sont sur sa zone à la fin du tour, rien ne se passe, ils restent sur cette case.")

    def use(self, joueuse):
        joueuse.setToursRestantsImmune(4)

