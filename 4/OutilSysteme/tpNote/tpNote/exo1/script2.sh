#!/bin/bash

awk -F, '{if($# != 6){print "le nombre de ligne ne vas pas"}else{if(!isnum($4) || !isnum($5) || !isnum($6)){print "les dernières colonne ne sont pas des entiers"}}}' countries.csv
