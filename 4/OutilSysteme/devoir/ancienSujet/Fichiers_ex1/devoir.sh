#!/bin/bash

tmp=$IFS
IFS=";"
while read prenom nom adresse note ; do
    cat gabarit.txt | sed -E "s/<PRENOM>/$prenom/g; s/<NOM>/$nom/g; s/<NOTE>/$note/g" | bash mock_mail -s "note outils systeme" $adresse
done < notes.csv
