
prog: zones.o personnages.o cartes.o joueuses.o interface.o main.o
	gcc -Wall -Wextra -g zones.o personnages.o cartes.o joueuses.o interface.o main.o -o prog

zones.o: zones.c zones.h
	gcc -Wall -Wextra -c zones.c

personnages.o: personnages.c personnages.h
	gcc -Wall -Wextra -c personnages.c 

cartes.o: cartes.c cartes.h
	gcc -Wall -Wextra -c cartes.c

joueuses.o: joueuses.c joueuses.h
	gcc -Wall -Wextra -c joueuses.c

interface.o: interface.c interface.h
	gcc -Wall -Wextra -c interface.c

main.o: main.c interface.h
	gcc -Wall -Wextra -c main.c

