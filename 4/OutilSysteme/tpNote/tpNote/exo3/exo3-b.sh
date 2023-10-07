#!/bin/bash

if [ $# -ne 1 ] ; then
    echo "le nombre d'argument doit etre de 1"
    exit 1
fi

if ! [ -f $1 ] ; then
    echo "le fichier n'existe pas"
fi

touch newFichier
    sed -e "s/<ul>/\begin{itemize}/g; s/<\/ul>/\end{itemize}/g" $1 > newFichier
    sed -e "s/<ol>/\begin{enumerate}/g; s/<\/ol>/\end{enumerate}/g" newFichier > $1
    sed -e "s/<li>/\item /g; s/<\/li>//g" $1 > newFichier
    sed -e "s/<p>//g; s/<\/p>//g" newFichier > $1
    sed -e "s/<a href=.*>//g; s/<\/a>//g" $1 > newFichier
    sed -e "s/<img .*>/ /g" newFichier > $1
rm newFichier
