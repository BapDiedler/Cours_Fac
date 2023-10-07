package bib;

import java.util.ArrayList;
import bib.exceptions.*;
import java.util.Iterator;

public class Lexique implements Iterable<String> {
	private int nbMots;
	private String[] lexique;
	private int sommet;

    public Lexique(int nbMotsMax) {
    	nbMots = nbMotsMax;
    	lexique = new String[nbMots];
    	sommet =0;
    }
    
    public Iterator<String> iterator(){
    	IteratorLexique iLex = new IteratorLexique(lexique, sommet);
    	return iLex;
    }

    
    public void ajout(String mot){
    	try{
    		if(nbMots <= sommet){
    		 	throw 	new FullException("Taille maximale du lexique atteinte");
    		 	}
	    	lexique[sommet] = mot;
	    	sommet++;
	    	}catch(FullException e){System.out.println(e);}
    }
    
    public int nbMots(){
    	return sommet;
    }
    
    public int getCapacite(){
    	return nbMots;
    	}
    
    public String toString(){
    	String res = "";
    	for(int i = 0; i < sommet; i++){
    		res += lexique[i]+ "\n";
    		}
    	return res;
    }

    
}