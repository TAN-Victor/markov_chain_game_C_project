# README - Group_8_project_1A

\
Description: Vous trouverez dans ce git, à la branche lot_c :
* le dossier *package* qui contiendra les fichiers nécessaires,
    * le dossier *interface* qui contiendra les images / sprites et fichiers.py qui les génèrent,
    * les fichiers *carte.py*, *effets.py*, *joueuses.py*, *personnage.py*, *structures.py*, *zones.py* qui sont recopiés depuis le lot_b
    * le fichier *interface.py* qui crée les différents widgets comme les boutons ou les sprites,
* le fichier *main.py* qui contient la boucle de jeu principale,
* un fichier exécutable pour linux *main* (voir remarque plus bas),
* un fichier exécutable pour windows *main.exe* (voir remarque plus bas),
* ce fichier *readme.md*.



***

## Execution du programme

ATTENTION: Le jeu a été principalement codé pour des écrans 1920 x 1080.
Il détecte la taille de votre écran _principal_ si vous avez plusieurs écrans, pas celui actif.
Il y a quelques problèmes de taille d'affichage pour les tailles d'écran upscalé (Dans les paramètres de la machine, il faut être à 100% et pas 125% ou 150%).


Il suffit de lancer le main.py sans argument si vous possédez la librairie pygame.
Par contre, à chaque lancement du main.py, des fichiers dans \_pycache\_ sont modifiés.
Sinon, le jeu a été compilé avec pyinstaller pour ne plus avoir besoin de pygame.

### Sous Windows

Il est possible de lancer le main.exe, mais beaucoup d'antivirus peuvent bloquer l'application.
Dans ce cas, un rendez-vous et une démonstration par visio serait peut-être plus pertinent.
Lancer en mode administrateur marche parfois.

### Sous Linux

Il faut avoir Glibc (ldd) en version 2.35. Les machines de l'école ne l'ont qu'en 2.31 et ne marcheront donc pas.

## Remarque

Le jeu a été fait avec Pygame.

