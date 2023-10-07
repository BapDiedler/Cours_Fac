for dos in `ls`
do
	if [ -d $dos ]
	then
		for fich in `ls $dos/`
		do
			if [ ! -d $dos/$fich ]
			then
				fichBis="$dos.$fich"
				#cp $dos/$fich $fichBis
			else
				for f in `ls $dos/$fich`
				do
					fichBis="$dos.$fich.$f"
					echo $fichBis
					cp $dos/$fich/$f $fichBis
				done
			fi
		done 
	fi
done
