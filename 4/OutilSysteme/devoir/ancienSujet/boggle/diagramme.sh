#!/bin/bash
cd boggle
for path in `find ./*` ; do
    if [ -f $path ] ; then
	nom=$(basename -s ".java" "$path")
	echo -n "$nom : "
	for new_path in `find ./*` ; do
	    if [ -f $new_path ] ; then
		new_nom=$(basename -s ".java" "$new_path")
		if [ "$new_nom" != "$nom" ] ; then
		    grep -Fq $nom $new_path
		    if [ $? -eq 0 ] ; then
			echo -n "$new_nom "
		    fi
		fi
	    fi
	done
	echo
    fi    
done
