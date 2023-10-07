#!/bin/bash

fichIngredient() {
    cd recettes
    #je n'arrive pas à recupérer les éléments en paramètre                                                                            
    cd recettes
    while [ $OPTIND -ne 1 ] ; do
              TAB[$i]=$1
              shift $((OPTIND-1))
              i=$(($i+1))
          done

    for fichier in `ls` ; do
	echo -n "$fichier : "
        for ele in $TAB ; do
                    grep -Fqi "$ele" $fichier
                    if [ $? -eq 0 ] ; then
                        echo -n $ele
                    fi
                done
    done

}


unIngredient () {
    #je n'arrive pas à recupérer les éléments en paramètre
    cd recettes
    while [ $OPTIND -ne 1 ] ; do
	      TAB[$i]=$1
	      shift $((OPTIND-1))
	      i=$(($i+1))
	  done

    for fichier in `ls` ; do
	for ele in $TAB ; do
		    grep -Fqi "$ele" $fichier
		    if [ $? -eq 0 ] ; then
			echo $ficher
		    fi
		    
		done
		   
    done
    
}

unIngredient carotte
