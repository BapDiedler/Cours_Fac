module = affichage.o jouer.o

all: main

%.o: %.c %.h ressource.h
	cc -c $<

main: main.c $(module)
	cc $^ -o $@

documentation: main
	doxygen $^

export: documentation
	zip -r projetC.zip .

clean:
	rm -f $(module)

.PHONY: clean
