#!/bin/bash

awk -F, 'BEGIN{printf("# BEGIN #\n")} \
{if(NR==1){print $0",difference 2020 et 2000"}else{cpt=($6-$4);print $0","cpt}}  \
END{printf("# END #\n")}' countries.csv
