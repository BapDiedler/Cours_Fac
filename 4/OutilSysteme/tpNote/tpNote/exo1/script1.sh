#!/bin/bash

awk -F, 'BEGIN{cpt=0; continent="_";NR=1} {if($1 == continent){cpt+=$5}else{if(continent != "_"){print $1" : "cpt ; continent=$1}else{continent=$1}}}' countries.csv
