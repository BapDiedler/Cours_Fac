package tests;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public  class EcrireSemaine {
        
	
    public EcrireSemaine(){
    	try {
    		FileWriter flot = new FileWriter("test.txt");
    		BufferedWriter flotFiltre = new BufferedWriter(flot);
    		flotFiltre.write("Lundi");
    		flotFiltre.newLine();flotFiltre.write("Mardi");
    		flotFiltre.newLine();flotFiltre.write("Mercredi");
    		flotFiltre.newLine();flotFiltre.write("Jeudi");
    		flotFiltre.newLine();flotFiltre.write("Vendredi");
    		flotFiltre.newLine();
    		flotFiltre.close();
    		}
    	catch(IOException e){System.out.println("Erreur d'ouverture");}
    }
    
    public static void main(String[] args) {
        new EcrireSemaine();
    }
    
}
         
          
