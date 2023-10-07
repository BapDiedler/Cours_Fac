package tests;

import java.io.PrintWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.File;
import java.util.Random;
import java.lang.ArrayIndexOutOfBoundsException;
public  class Ecrire {
        
	
    public Ecrire(String nomFichier){
    	try {
    		File f = new File(nomFichier);
    		if(f.exists()){
    			throw new IOException("Le fichier existe déjà");
    		}
    		FileWriter flot = new FileWriter(f);
    		PrintWriter flotFiltre = new PrintWriter(flot);
    		Random randGen = new Random();
    		int maxValue = 500;
    		
    		for(int i = 0; i < randGen.nextInt(maxValue)+500; i++){	
	    		flotFiltre.println(randGen.nextInt(maxValue));
				}
    		flotFiltre.close();
    		}
    	catch(IOException e){System.out.println(e);}
    }
    
    public static void main(String[] args) {
    	try{new Ecrire(args[0]);}
    	catch(ArrayIndexOutOfBoundsException e){System.out.println("Usage : 1 args");}
    
	}     
}
         
          
