#!/bin/bash

if [ $# -ne 1 ] ; then
    echo "le nombre d'argument doit etre de 1"
    exit 1
fi

if ! [ -f $1 ] ; then
    echo "le fichier n'existe pas"
fi

#si cpt=1 on a un BEGIN s'il vaut -1 on a un END s'il vaut 0 on est bon
cpt=0

touch trans
while read -ra ligne ; do
    echo ${ligne[*]} > trans
    grep -qi "begin" trans
    if [ $? -eq 0 ] ; then
	if [ $cpt -ge 0 ] ; then
	    let cpt=$cpt+1
	else
	    echo "le fichier est faut"
	    exit 1
	fi
    fi
    grep -qi "end" trans
    if [ $? -eq 0 ] ; then
	if [ $cpt -le 0 ] ; then
	    echo "le fichier est faut"
	    exit 1
	else
	    let cpt=$cpt-1
	fi
    fi
    
done < $1
if [ $cpt -ne 0 ] ; then
    echo "le fichier n'est pas bon"
fi

rm trans
