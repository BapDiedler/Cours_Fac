#!/bin/bash

#on regarde le nombre d'argument
if [ $# -eq 0 ] ; then
    echo "le nombre d'argument doit être de 1 au minimum"
    exit 1
fi

nom="_"
option="_"
#recolte des variables données en paramètre
if [ $# -eq 1 ] ; then
    nom=$1
else
    nom=$2
    option=$1
fi

#on regarde si le dossier existe bien sinon on stop le programme
if ! [ -d "$nom" ] ; then
    echo "le dossier n'existe pas"
    exit 1
fi

#le dossier de sauvegarde n'existe pas
if ! [ -d $nom"_SAVE" ] && [ "$option" != "-h" ] ; then
    mkdir $nom"_SAVE"
elif [ "$option" == "-h" ] ; then
    mkdir "."$nom"_SAVE"
fi

if [ "$option" != "_" ] ; then
    #gestion de l'option -b
    if [ "$option" == "-b" ] && [ -d $nom"_SAVE" ] ; then
	cp $nom/* $nom"_SAVE"/
    fi
else
    #il n'y a pas d'option
    for fichier in `ls $nom/` ; do
	if [ -e $nom"_SAVE/"$fichier ] ; then
	    if [ $nom"/"$fichier -nt $nom"_SAVE/"$fichier ] ; then
		cp $nom"/"$fichier $nom"_SAVE/"
	    fi
	else
	    cp $nom"/"$fichier $nom"_SAVE/"
	fi
    done
fi

# Demander à l'utilisateur de valider l'action
read -p "Voulez-vous continuer? (yes/no) " answer

# Vérifier la réponse de l'utilisateur
if [[ $answer == "yes" ]]; then
    echo "L'action est confirmée."
elif [[ $answer == "no" ]]; then
    echo "L'action est annulée."
else
    echo "Réponse invalide. Veuillez taper 'yes' ou 'no'."
fi
