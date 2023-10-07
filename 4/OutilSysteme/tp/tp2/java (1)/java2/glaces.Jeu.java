package glaces;
import glaces.Ocean ;
import java.util.Scanner;
	
public class Jeu {

	private Ocean ocean;
	
    public Jeu() {
    	this.ocean = new Ocean(300,40);	
    }
    
    public void jouer(){
    	this.ocean.rafraichissementCoul();
    	this.ocean.afficher();
    	int nbrCoup = 10;
    	Scanner reader = new Scanner(System.in);
    	int n = -1;
    	while(n != 0){
    		System.out.println("Enter a number: ");
			n = reader.nextInt();
			if(n > 0){
				this.ocean.deplacerH(n);
				this.ocean.rafraichissementCoul();
    			this.ocean.afficher();
    		}
    	}
    	this.ocean.fermer();
    	reader.close();
    }
    
    
    public static void main(String[] args){
    	Jeu j = new Jeu();
    	j.jouer();
    	
    }
}
