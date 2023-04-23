bin/prog: obj/zones.o obj/personnages.o obj/cartes.o obj/joueuses.o obj/interface.o obj/structures.o obj/effets.o obj/main.o
	gcc -Wall -Wextra obj/zones.o obj/personnages.o obj/cartes.o obj/joueuses.o obj/interface.o obj/structures.o obj/effets.o obj/main.o -o bin/prog

obj/zones.o: src/zones.c headers/zones.h
	gcc -Wall -Wextra -c src/zones.c -o obj/zones.o

obj/personnages.o: src/personnages.c headers/personnages.h
	gcc -Wall -Wextra -c src/personnages.c -o obj/personnages.o

obj/cartes.o: src/cartes.c headers/cartes.h
	gcc -Wall -Wextra -c src/cartes.c -o obj/cartes.o

obj/joueuses.o: src/joueuses.c headers/joueuses.h
	gcc -Wall -Wextra -c src/joueuses.c -o obj/joueuses.o

obj/interface.o: src/interface.c headers/interface.h
	gcc -Wall -Wextra -c src/interface.c -o obj/interface.o

obj/structures.o: src/structures.c headers/structures.h
	gcc -Wall -Wextra -c src/structures.c -o obj/structures.o

obj/effets.o: src/effets.c headers/effets.h
	gcc -Wall -Wextra -c src/effets.c -o obj/effets.o

obj/main.o: src/main.c headers/interface.h
	gcc -Wall -Wextra -c src/main.c -o obj/main.o

