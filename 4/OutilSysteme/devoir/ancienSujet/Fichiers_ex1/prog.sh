#!/bin/bash

tmp=$IFS
IFS=";"
cat notes.csv | while read prenom nom mail note ; do
    message=$(sed "s/<NOM>/$nom/g; s/<PRENOM>/$prenom/g; s/<NOTE>/note/g;" gabarit.txt)
    echo $message | bash mock_mail -s "note outils systeme" $mail
done
