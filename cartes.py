class Carte:
    def __init__ (self, nom, description):
        self.nom = nom
        self.description = description
    
#getters:
    def getNom(self):
        return self.nom
    
    def getDescription(self):
        return self.description


class Merabet(Carte):
    def __init__(self):
        super().__init__("Merabet", "Pendant vos 3 prochains tours, votre capital augmente de 2.")


class Bannour(Carte):
    def __init__(self):
        super().__init__("Bannour", "Choisissez deux zones, les personnages présents sur ces deux zones sont échangés.")


class Honoré(Carte):
    def __init__(self):
        super().__init__("Honoré", "Chaque monstre se déplace 3 fois. Chaque membre d'école qu'un monstre rencontre est mangé.")


class Riobo(Carte):
    def __init__(self):
        super().__init__("Riobo", "Lors du prochain tour, la joueuse adverse ne choisit pas comment est utilisé son capital. Chaque point de capital est utilisé aléatoirement: pour chaque point, choisissez les trois zones Z1, Z2 et Z3 uniformément parmi les triplets pouvant être choisis.")


class Goilard(Carte):
    def __init__(self):
        super().__init__("Goilard", "Lors du prochain tour et du suivant, c'est vous qui jouez. Lors des deux tours suivant, c'est la joueuse adverse qui joue.")


class Bourard(Carte):
    def __init__(self):
        super().__init__("Bourard", "Lors du prochain déplacement, si deux membres d'écoles adverses se retrouvent sur la même zone, ils se déplacent de nouveau. Si ces deux membres sont sur la zone du monstre avant le second déplacement, ils ne sont pas mangés. On recommence l'opération au plus 100 fois, jusqu'à ce que les membres des écoles adverses soient sur des zones distinctes.")



class Munante(Carte):
    def __init__(self):
        super().__init__("Munante", "Les membres d'écoles présents sur la zone où était un monstre avant son dernier déplacement sont mangés.")


class Benezet(Carte):
    def __init__(self):
        super().__init__("Benezet", "Déplacez un des monstres sur la zone de votre choix. Si un membre d'école se trouve sur la zone du monstre, il n'est pas mangé.")   


class Ligozat(Carte):
    def __init__(self):
        super().__init__("Ligozat", "Choisissez un membre de votre école, il effectue désormais deux déplacements au lieu d'un à chaque tour.")


class Mouilleron(Carte):
    def __init__(self):
        super().__init__("Mouilleron", "Choisissez un membre de l'école de la joueuse adverse. Ce membre devient un membre de votre école.")


class Demebele_Cabot(Carte):
    def __init__(self):
        super().__init__("Demebele_Cabot", "Sacrifiez un membre de votre école de votre choix. Vous avez 15 points de capital en plus à votre prochain tour.")


class Pacave(Carte):
    def __init__(self):
        super().__init__("Pacave", "Créez une nouvelle zone. Les membres de votre école sont les seuls à pouvoir se déplacer sur cette zone. Un membre de l'école de l'autre joueuse qui devrait se déplacer sur cette zone ne se déplace pas. La probabilité d'aller sur cette zone est de 0. Depuis cette zone, la probabilité de rester sur cette zone est 1.")


class Huet(Carte):
    def __init__(self):
        super().__init__("Huet", "Chaque zone effectue une rotation de probabilité. La probabilité d'aller de la zone i à la zone j devient la probabilité d'aller de la zone i à la zone j + 1. La probabilité d'aller de la zone i à la zone 10 devient la probabilité d'aller de la zone i à la zone 1.")


class Matias(Carte):
    def __init__(self):
        super().__init__("Matias", "Chaque monstre disparaît pendant 2 tours. Il réapparaîtra sur la zone d'où il est parti.")


class Salhab(Carte):
    def __init__(self):
        super().__init__("Salhab", "Pendant vos 3 prochains tours, un point de capital permet de déplacer une quantité 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9 ou 1 de probabilité.")


class Pulido_Nino(Carte):
    def __init__(self):
        super().__init__("Pulido_Nino", "Mettez à 0 les probabilités permettant de sortir de la zone de chaque monstre et mettez à 1 la probabilité de rester dans la zone de chaque monstre.")


class Watel(Carte):
    def __init__(self):
        super().__init__("Watel", "Mettez à 0 les probabilités permettant de sortir de la zone de chaque monstre et mettez à 1 la probabilité de rester dans la zone de chaque monstre.")


class Szanfranski(Carte):
    def __init__(self):
        super().__init__("Szanfranski", "Ajoutez un monstre sur la zone 1, un membre de votre école sur la zone 2 et un membre de l'école adverse sur la zone 3. Si un membre d'école se trouve sur la même zone qu'un monstre, il n'est pas mangé.")


class Forest(Carte):
    def __init__(self):
        super().__init__("Forest", "Mettez toutes les probabilités à 0. Puis, pour chaque zone, la probabilité de se déplacer de cette zone vers la zone contenant le monstre passe à 0.5 (s'il y a plusieurs monstres, un des monstres est choisi aléatoirement) ; et la probabilité de se déplacer de cette zone vers une autre zone ne contenant pas de monstre choisie aléatoirement passe également à 0.5.")


class Prével(Carte):
    def __init__(self):
        super().__init__("Prével", "Pendant 4 tours, les membres de votre école ne peuvent être mangés par un monstre. S'ils sont sur sa zone à la fin du tour, rien ne se passe, ils restent sur cette case.")
