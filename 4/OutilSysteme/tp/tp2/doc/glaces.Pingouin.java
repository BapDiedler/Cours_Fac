package glaces;
import geometrie.Point;

public class Pingouin {
	///BIBLIO A FAIRE
	
    private Point position ;
    private int taille ;

    /**
     * @param g le coin en bas à gauche
     * @param d le coin en haut à droite
     * uniquement en coordonnées positives
     */
    public Pingouin(Point pos, int tail) {
        this.position = new Point(pos);
        this.taille = tail;
    }

   
    /**
     * @return le coin en bas à gauche
     */
    public int getTaille() {
        return this.taille;
    }

    /**
     * @return le coin en haut à droite
     */
    public Point getPosition() {
        return this.position ;
    }
    
    public void deplacerH(double dep){
    	this.position.deplacer(dep,0);
    }
	 public void deplacerV(double dep){
    	this.position.deplacer(0,dep);
    }


    public String toString() {
        String res = this.position.toString() + " === ";
        ///ACOMPLETER
        return res ;
    }


    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // A compléter
        Point p1 = new Point(0.0,0.0);
        
    }
}
