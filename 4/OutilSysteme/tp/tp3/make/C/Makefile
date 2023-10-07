all: main
FILE=affichage.o jouer.o

%.o : affichage.c affichage.h joueur.c jouer.h ressource.h
	cc -c $@ $^

ressource.h:

main: $(FILE)
	cc $^ main.c -o main

documentation:
	doxygen /*

clean:
	rm -f *.o

compresser: main $(FILE) documentation
	zip dossierCompressee.zip $^ html latex
