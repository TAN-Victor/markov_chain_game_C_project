
bin/prog: obj/zones.o obj/personnages.o obj/cartes.o obj/joueuses.o obj/interface.o obj/main.o
	gcc -Wall -Wextra -g obj/zones.o obj/personnages.o obj/cartes.o obj/joueuses.o obj/interface.o obj/main.o -o bin/prog

obj/zones.o: src/zones.c headers/zones.h
	gcc -Wall -Wextra -c src/zones.c

obj/personnages.o: src/personnages.c headers/personnages.h
	gcc -Wall -Wextra -c src/personnages.c 

obj/cartes.o: src/cartes.c headers/cartes.h
	gcc -Wall -Wextra -c src/cartes.c

obj/joueuses.o: src/joueuses.c headers/joueuses.h
	gcc -Wall -Wextra -c src/joueuses.c

obj/interface.o: src/interface.c headers/interface.h
	gcc -Wall -Wextra -c src/interface.c

obj/main.o: src/main.c headers/interface.h
	gcc -Wall -Wextra -c src/main.c

