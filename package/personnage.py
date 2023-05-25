from zones import *


class Personnage:
    def __init__(self, type_perso, id, zone_courante):
        """
        Crée un nouveau personnage avec les informations fournies.

        Args:
            type_perso (int): Le type du personnage.
            id (int): L'ID du personnage.
            zone_courante (int): La zone courante du personnage.
        """
        self.type = type_perso
        self.id = id
        self.statut = 1  # 1 car vivant
        self.invincible_ce_tour = 0  # N'est pas invincible le tour du début
        self.zone_courante = zone_courante
        self.zone_precedente = -1  # -1 car vient d'être créé
        self.nb_de_pas = 1
        self.tours_restants_bonus_pas = 0
        self.peut_se_deplacer = True
        self.nb_de_tour_disparu_restant = 0

    def deplacer(self, zone):
        """
        Déplace le personnage vers une nouvelle zone.

        Args:
            zone (int): La zone vers laquelle déplacer le personnage.
        """
        self.zone_precedente = self.zone_courante
        self.zone_courante = zone

    def zone_personnage(self):
        """
        Renvoie la zone du personnage.

        Returns:
            int: Le numéro de la zone du personnage. -1 en cas d'erreur.
        """
        if self.zone_courante < 0:
            return -1
        else:
            return self.zone_courante

    def est_mange(self):
        """
        Met à jour le statut du personnage lorsqu'il est mangé.
        """
        self.statut = 0
        self.peut_se_deplacer = False

