from PIL import Image, ImageDraw, ImageFont

largeur_1 = 1024
longueur_1 = 1024
couleurs_texte = [(101, 173, 101), (101, 139, 227), (227, 101, 101)]



for chiffre in range(1, 7):
    image = Image.new("RGBA", (longueur_1, largeur_1), (0, 0, 0, 0))
    draw = ImageDraw.Draw(image)
    font = ImageFont.truetype("C:\\Windows\\fonts\\Impact.ttf", 1000)

    for i in range(3):
        draw.text((0, 0), str(chiffre) + ")", font=font, fill=couleurs_texte[i])
        image.save("images/" + str(chiffre) + "_" + str(i) + ".png", "PNG")


liste_cartes = ["Merabet", "Bannour", "Honoré", "Rioboo", "Goilard", "Bourard", "Munante", "Benezet", "Ligozat", "Mouilleron",
                 "Dembele-Cabot" ,"Pacave", "Huet", "Matias", "Salhab", "Pulido-Nino", "Watel", "Szafranski", "Forest", "Prével"]
largeur_2 = 1024
longueur_2 = 4000

for carte in liste_cartes:
    image = Image.new("RGBA", (longueur_2, largeur_2), (0, 0, 0, 0))
    draw = ImageDraw.Draw(image)
    font = ImageFont.truetype("C:\\Windows\\fonts\\Impact.ttf", 600)

    for i in range(2):
        draw.text((0, 0), carte, font=font, fill=couleurs_texte[i])
        image.save("images/" + carte + "_" + str(i) + ".png", "PNG")


liste_mots = ["En vie", "Mort", "Disparu", "FIPA"]
largeur_3 = 1024
longueur_3 = 2048

for mot in liste_mots:
    image = Image.new("RGBA", (longueur_3, largeur_3), (0, 0, 0, 0))
    draw = ImageDraw.Draw(image)
    font = ImageFont.truetype("C:\\Windows\\fonts\\bradhitc.ttf", 600)

    for i in range(3):
        draw.text((0, 0), mot, font=font, fill=couleurs_texte[i])
        image.save("images/" + mot + "_" + str(i) + ".png", "PNG")
