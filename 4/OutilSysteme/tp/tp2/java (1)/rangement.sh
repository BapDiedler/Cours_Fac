#!/bin/bash

cd java

#création des répertoires ressource sujet ...

mkdir -p code
mv *.java code
mv *.class code

mkdir -p sujet
mv *.pdf sujet/

mkdir -p data
mv DATA*.png data/
mv DATA*.jpg data/

mkdir -p ressource
mv -f *.zip ressource/
mv -f *.png ressource/

mkdir -p bash
mv -f *.bash bash/

cd code

for fichier in `ls` ; do
    tmp=$IFS
    IFS="."
    #fichier=$(basename -s .java $fichier)
    #    echo $fichier
    read -ra tableau <<< $fichier
    mkdir -p ${tableau[0]}
    if [ -f "$" ] ; then
	mv $fichier ${tableau[0]}
    fi
    
done
