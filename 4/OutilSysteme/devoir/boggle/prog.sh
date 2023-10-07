#!/bin/bash

for fichier in `find boggle/*` ; do
    if ! [ -d $fichier ] ; then
	nom=$(basename -s ".java" $fichier)
	echo -n "$nom : "
	for newFichier in `find boggle/*` ; do
	    if [ "$fichier" != "$newFichier" ] ; then
		if ! [ -d $newFichier ] ; then
		    newNom=$(basename -s ".java" $newFichier)
		    grep -qE "$nom" $newFichier
		    if [ $? == 0 ] ; then
			echo -n "$newNom "
		    fi
		fi
	    fi
	done
	echo
    fi    
done
