#!/bin/bash

if [ $# -ne 1 ] ; then
    echo "le nombre d'argument doit etre de 1"
    exit 1
fi

if ! [ -f $1 ] ; then
    echo "le fichier n'existe pas"
fi

# le fichier est valide

tmp="1"
touch newFichier
touch tmpFichier
while read ligne ; do
    if [ "$tmp" == "1" ] ; then
	echo $ligne > tmpFichier
	grep -qi "<div id=.*>" tmpFichier
	if [ $? -eq 0 ] ; then
	    tmp="0"
	fi
    else
	echo $ligne >> newFichier
    fi
done < $1
cat newFichier > $1
rm newFichier
rm tmpFichier
