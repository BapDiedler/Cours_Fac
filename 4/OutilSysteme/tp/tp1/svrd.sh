#!/bin/bash

casH() {
     if [ "-h" = $1 ] ; then #option avec -h
       	mkdir -p ."$2"_SAVE
     fi
}

casB() {
    if [ "-b" = $1 ] ; then #option -b
	if [ -e "$2"_SAVE ] ; then
	    rm -r "$2"_SAVE
	    mkdir -p "$2"_SAVE
	    cp $2/* "$2"_SAVE
	fi
    fi
}

#vérification du nombre d'argument
if [ $# -le 0 ] ; then
    echo "le nombre d'argument doit être de plus de un"
    echo "la commande : svrd [<option>] <nomDossier>"
  fi

if [ $# -eq 2 ] ; then
    if ! [ -e $2 ] ; then #si le dossier n'existe pas
	mkdir $2
    fi
    if [ -d $2 ] ; then
	casB
	casH
    fi
fi # aucun argument en plus
if [ $# -eq 1 ] ; then
    if ! [ -e $1 ] ; then #le dossier n'existe pas
	mkdir -p "$1"
    fi
    if ! [ -e "$1"_SAVE ] ; then #le dossier de sauvegarde n'existe pas
	mkdir -p "$1"_SAVE
    fi
    for fichier in `ls $1` ; do #parcours de tous les fichiers présents
	if [ -e "$1"_SAVE/"$fichier" ] ; then
	    if [ $fichier -nt "$1"_SAVE/"$fichier" ] ; then # on regarde les fichiers plus récents
		val=$(stat -c %s $fichier)
		if [ $val -eq 1000000 ] ; then
		    cp -r $fichier "$1"_SAVE
		fi
	    fi
	else
	    val=$(stat -c %s $fichier)
                if [ $val -eq 1000000 ] ; then
                    cp -r $fichier "$1"_SAVE
                fi

	fi
    done
fi


