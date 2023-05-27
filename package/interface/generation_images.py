from PIL import Image, ImageDraw, ImageFont
import os
import sys

largeur_1 = 1024
longueur_1 = 1024
couleurs_texte = [(101, 173, 101), (101, 139, 227), (227, 101, 101)]

current_dir = os.path.dirname(os.path.abspath(sys.argv[0]))
os.chdir(current_dir)

for chiffre in range(1, 8):
    image = Image.new("RGBA", (longueur_1, largeur_1), (0, 0, 0, 0))
    draw = ImageDraw.Draw(image)
    font = ImageFont.truetype("C:\\Windows\\fonts\\Impact.ttf", 1000)

    for i in range(3):
        draw.text((0, 0), str(chiffre) + ")", font=font, fill=couleurs_texte[i])
        image.save("images/" + str(i) + "_" + str(chiffre) + ".png", "PNG")


liste_cartes = ["Merabet", "Bannour", "Honoré", "Rioboo", "Goilard", "Bourard", "Munante", "Benezet", "Ligozat", "Mouilleron",
                 "Dembele-Cabot" ,"Pacave", "Huet", "Matias", "Salhab", "Pulido-Nino", "Watel", "Szafranski", "Forest", "Prével"]
largeur_2 = 700
longueur_2 = 1

for carte in liste_cartes:
    longueur_2 = len(carte) * 310
    image = Image.new("RGBA", (longueur_2, largeur_2), (0, 0, 0, 0))
    draw = ImageDraw.Draw(image)
    font = ImageFont.truetype("C:\\Windows\\fonts\\Impact.ttf", 600)

    for i in range(2):
        draw.text((0, 0), carte, font=font, fill=couleurs_texte[i])
        image.save("images/" + carte + "_" + str(i) + ".png", "PNG")


liste_mots = ["En vie", "Mort", "Disparu", "FIPA"]
largeur_3 = 700
longueur_3 = 1

for mot in liste_mots:
    longueur_3 = len(mot) * 340
    image = Image.new("RGBA", (longueur_3, largeur_3), (0, 0, 0, 0))
    draw = ImageDraw.Draw(image)
    font = ImageFont.truetype("C:\\Windows\\fonts\\segoepr.ttf", 550)

    for i in range(3):
        draw.text((0, -75), mot, font=font, fill=couleurs_texte[i])
        image.save("images/" + mot + "_" + str(i) + ".png", "PNG")
