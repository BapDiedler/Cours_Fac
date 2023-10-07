module = jouer.o affichage.o

%.o: %.h %.c ressource.h
	gcc $^ -c

main: $(module) main.c ressource.h
	gcc $^ -o $@

documentation: main
	doxygen $<

clean: $(module)
	rm $<

export: main documentation
	zip -r fichierZip.zip $^

.PHONY: clean

ressource.h:
	echo "le fichier ressource.h n'existe pas"
