class Personnage:
    def __init__(self, type_perso, id, zone_courante):
        """Crée un nouveau personnage avec les informations fournies.
        
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
        self.peut_se_deplacer = 1
        self.nb_de_tour_disparu_restant = 0

    # Getters
    def get_type(self):
        """Renvoie le type du personnage."""
        return self.type

    def get_id(self):
        """Renvoie l'ID du personnage."""
        return self.id

    def get_statut(self):
        """Renvoie le statut du personnage."""
        return self.statut

    def get_zone_courante(self):
        """Renvoie la zone courante du personnage."""
        return self.zone_courante

    def get_zone_precedente(self):
        """Renvoie la zone précédente du personnage."""
        return self.zone_precedente

    def get_nb_de_pas(self):
        """Renvoie le nombre de pas restant du personnage."""
        return self.nb_de_pas

    def get_nb_tour_disparu_restant(self):
        """Renvoie le nombre de tours restant avant que le personnage ne réapparaisse."""
        return self.nb_de_tour_disparu_restant

    def get_peut_se_deplacer(self):
        """Renvoie un booléen indiquant si le personnage peut se déplacer ou non."""
        return self.peut_se_deplacer

    def get_invincible_ce_tour(self):
        """Renvoie un booléen indiquant si le personnage est invincible ce tour ou non."""
        return self.invincible_ce_tour

    def get_tours_restants_bonus_pas(self):
        """Renvoie le nombre de tours restant avant que le bonus de pas ne disparaisse."""
        return self.tours_restants_bonus_pas

    # Setters
    def set_type(self, type_perso):
        """Modifie le type du personnage."""
        self.type = type_perso

    def set_id(self, id):
        """Modifie l'ID du personnage."""
        self.id = id

    def set_statut(self, statut):
        """Modifie le statut du personnage."""
        self.statut = statut

    def set_zone_courante(self, zone_courante):
        """Modifie la zone courante du personnage."""
        self.zone_courante = zone_courante

    def set_zone_precedente(self, zone_precedente):
        """Modifie la zone précédente du personnage."""
        self.zone_precedente = zone_precedente

    def set_nb_de_pas(self, nb_de_pas):
        """Modifie le nombre de pas restant du personnage."""
        self.nb_de_pas = nb_de_pas

    def set_nb_tour_disparu_restant(self, nb_tour_disparu):
        """Modifie le nombre de tours restant avant que le personnage ne réapparaisse."""
        self.nb_de_tour_disparu_restant = nb_tour_disparu

    def set_peut_se_deplacer(self, peut_se_deplacer):
        """Modifie si le personnage peut se déplacer ou non."""
        self.peut_se_deplacer = peut_se_deplacer

    def set_invincible_ce_tour(self, invincible):
        """Modifie si le personnage est invincible ce tour ou non."""
        self.invincible_ce_tour = invincible

    def set_tours_restants_bonus_pas(self, tours_restants_bonus_pas):
        """Modifie le nombre de tours restant avant que le bonus de pas ne disparaisse."""
        self.tours_restants_bonus_pas = tours_restants_bonus_pas

    # Autres méthodes
    def deplacer(self, zone):
        """Déplace le personnage vers une nouvelle zone.
        
        Args:
            zone (int): La zone vers laquelle déplacer le personnage.
        """
        self.set_zone_precedente(self.get_zone_courante())
        self.set_zone_courante(zone)

    def zone_personnage(self):
        """Renvoie la zone du personnage. Renvoie -1 si le personnage n'a pas de zone."""
        if self.get_zone_courante() < 0:
            return -1
        else:
            return self.get_zone_courante()

    def est_mange(self):
        """Change le statut du personnage à 'mangé' et le rend incapable de se déplacer."""
        self.set_statut(0)
        self.set_peut_se_deplacer(0)

