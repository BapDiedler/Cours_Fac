#!/bin/bash


#cat notes.csv | while read line ; do
#    tmp=$IFS
#    IFS=";"
#    read -ra tableau <<< "$line"
#    sed -e "s/<PRENOM>/${tableau[0]}/g" gabarit.txt | sed -e "s/<NOM>/${tableau[1]}/g" | sed -e "s/<NOTE>/${tableau[3]}/g" | bash mock_mail -s "note outils systeme" ${tableau[2]}
#    IFS=$tmp
#done


tmp=$IFS
IFS=";"
while read prenom nom adresse note ; do
    mail=$(sed -e "s/<PRENOM>/$prenom/g; s/<NOM>/$nom/g; s/<NOTE>/$note/g" gabarit.txt)
    echo $mail | bash mock_mail -s "note outils systeme" $adresse
done < notes.csv
IFS=$tmp
