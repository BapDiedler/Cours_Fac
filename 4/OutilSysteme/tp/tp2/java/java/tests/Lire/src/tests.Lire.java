package tests;

import java.util.Scanner;
import java.io.FileReader;
import java.io.IOException;
import java.io.File;
import java.lang.String;

public  class Lire {
        
	
    public Lire(String nomFichier){
    	try {
    		File f = new File(nomFichier);
    		if(!f.exists()){
    			throw new IOException("Le fichier n'existe pas");
    		}
    		FileReader flot = new FileReader(f);
    		Scanner flotFiltre = new Scanner(flot);
    		int moyenne = 0,nb = 0;
    		while(flotFiltre.hasNext()){
    			moyenne += flotFiltre.nextInt();
    			nb += 1;
    			}
    		System.out.println("Moyenne :"+(moyenne/nb)+" nbr "+nb);
    		}
    	catch(IOException e){System.out.println("Erreur d'ouverture");}
    }
    
    public static void main(String[] args) {
        try{new Lire(args[0]);}
    	catch(ArrayIndexOutOfBoundsException e){System.out.println("Usage : 1 args");}
    }
    
}
         
          
