#!/bin/bash

#le nombre d'argument doit etre de 2
if ! [ $# -eq 2 ] ; then
    echo "le nombre d'arguments doit être de 2 ( nomFichier, langage )"
    exit 1
fi

#creation du fichier demandé
touch $1


if [ $2 = "c" ] ; then #gestion du langage C
    cd C
    make
elif [ $2 = "java" ] ; then #gestion de langage java
    cd java
    make
else
    echo "le langage n'est pas reconnu"
fi

