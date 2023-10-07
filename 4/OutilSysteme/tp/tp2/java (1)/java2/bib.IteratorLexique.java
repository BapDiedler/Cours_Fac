package bib;

import java.util.ArrayList;
import bib.exceptions.*;
import bib.Lexique;
import java.util.ListIterator;

public class IteratorLexique implements ListIterator<String> {
	private Iterator<String> ite;

    public IteratorLexique(String[] lexique, int sommet) {
    	/*ArrayList<String> liste = new ArrayList<>();
    	for(int i = 0; i < sommet; i++){
    		liste.add(lexique[i]);
    		}
    	ite = liste.iterator();*/
    	for(int i = 0; i < sommet; i++){
    		ite.add(lexique[i]);
    		}
    }
    
    public boolean hasNext(){
    	return ite.hasNext();
    	}
    public String next(){
    	return ite.next();
    	}
    public void remove(){
    	 ite.remove();
    	}

    
}