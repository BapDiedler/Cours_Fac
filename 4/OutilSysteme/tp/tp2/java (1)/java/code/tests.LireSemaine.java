package tests;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.lang.String;

public  class LireSemaine {
        
	
    public LireSemaine(){
    	try {
    		FileReader flot = new FileReader("test.txt");
    		BufferedReader flotFiltre = new BufferedReader(flot);
    		String ligne = flotFiltre.readLine();
    		while(ligne != null){
    			System.out.println("nbr caractères de la ligne : "+ligne.length());
    			ligne = flotFiltre.readLine();
    			}
    		}
    	catch(IOException e){System.out.println("Erreur d'ouverture");}
    }
    
    public static void main(String[] args) {
        new LireSemaine();
    }
    
}
         
          
