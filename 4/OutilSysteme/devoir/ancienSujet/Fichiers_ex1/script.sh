#!/bin/bash

tmp=$IFS
IFS=";"
cat notes.csv | while read prenom nom email note ; do
    newTexte=$(sed -e "s/<PRENOM>/$prenom/g; s/<NOM>/$nom/g; s/<NOTE>/$note/g" gabarit.txt)
    echo $newTexte | bash mock_mail -s "note outils systeme" email
done
IFS=$tmp


