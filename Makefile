all: Flood-It Test_Temps Test_Strategies comp_exo2_exo3

API_Gene_instance.o: API_Gene_instance.c API_Gene_instance.h
	gcc -c API_Gene_instance.c `sdl2-config --cflags`

API_Grille.o: API_Grille.c API_Grille.h
	gcc -c API_Grille.c `sdl2-config --cflags`

Liste_case.o: Liste_case.c Liste_case.h
	gcc -c Liste_case.c `sdl2-config --cflags`

Fonctions_exo1.o: Fonctions_exo1.c Entete_Fonctions.h Liste_case.h API_Grille.h
	gcc -c Fonctions_exo1.c `sdl2-config --cflags`

Flood-It.o: Flood-It.c Entete_Fonctions.h 
	gcc -c Flood-It.c `sdl2-config --cflags`

S_Zsg.o: S_Zsg.c S_Zsg.h Liste_case.h
	gcc -c S_Zsg.c `sdl2-config --cflags`	
Fonctions_exo3.o: Fonctions_exo3.c Entete_Fonctions.h S_Zsg.h API_Grille.h
	gcc -c Fonctions_exo3.c `sdl2-config --cflags`	

Fonctions_exo4.o: Fonctions_exo4.c Entete_Fonctions.h API_Grille.h Liste_case.h
	gcc -c Fonctions_exo4.c -o Fonctions_exo4.o -Wall `sdl2-config --cflags`

Fonctions_exo5.o: Fonctions_exo5.c Entete_Fonctions.h S_Zsg.h API_Grille.h
	gcc -c Fonctions_exo5.c `sdl2-config --cflags`
	
Flood-It: Flood-It.o Liste_case.o API_Grille.o API_Gene_instance.o Fonctions_exo1.o S_Zsg.o Fonctions_exo3.o Fonctions_exo5.o Fonctions_exo4.o
	gcc -o Flood-It Flood-It.o Liste_case.o API_Grille.o API_Gene_instance.o Fonctions_exo1.o Fonctions_exo3.o S_Zsg.o Fonctions_exo5.o Fonctions_exo4.o `sdl2-config --libs` 
Test_Temps.o: Test_Temps.c Entete_Fonctions.h S_Zsg.h API_Gene_instance.h
	gcc -c Test_Temps.c `sdl2-config --cflags`

Test_Temps: Test_Temps.o Liste_case.o API_Grille.o API_Gene_instance.o S_Zsg.o Fonctions_exo1.o Fonctions_exo3.o
	gcc -o Test_Temps Test_Temps.o Liste_case.o API_Grille.o API_Gene_instance.o S_Zsg.o Fonctions_exo1.o Fonctions_exo3.o `sdl2-config --libs`

Test_Strategies.o: Test_Strategies.c Entete_Fonctions.h S_Zsg.h
	gcc -c Test_Strategies.c `sdl2-config --cflags`

Test_Strategies: Test_Strategies.o Liste_case.o API_Grille.o API_Gene_instance.o S_Zsg.o Fonctions_exo3.o Fonctions_exo4.o
	gcc -o Test_Strategies Test_Strategies.o Liste_case.o API_Grille.o API_Gene_instance.o S_Zsg.o Fonctions_exo3.o Fonctions_exo4.o `sdl2-config --libs`

comp_exo2_exo3.o: comp_exo2_exo3.c Entete_Fonctions.h API_Grille.h Liste_case.h
	gcc -c comp_exo2_exo3.c -Wall `sdl2-config --cflags`

comp_exo2_exo3 : comp_exo2_exo3.o API_Grille.o API_Gene_instance.o Liste_case.o S_Zsg.o Fonctions_exo3.o Fonctions_exo1.o
	gcc -o comp_exo2_exo3 comp_exo2_exo3.o API_Grille.o API_Gene_instance.o Liste_case.o S_Zsg.o Fonctions_exo3.o Fonctions_exo1.o `sdl2-config --libs` -lm	

clean:
	rm -f *.o Flood-It Test_Temps Test_Strategies comp_exo2_exo3