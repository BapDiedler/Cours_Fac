package glaces;
import geometrie.Point ;

/**
 * Un iceberg rectangulaire
 * @author Martine Gautier, Université de Lorraine
 * @version Février 2014
 */
public class Iceberg2D {

    private Point enBasAGauche ;
    private Point enHautADroite ;

    /**
     * @param g le coin en bas à gauche
     * @param d le coin en haut à droite
     * uniquement en coordonnées positives
     */
    public Iceberg2D(Point g, Point d) {
        this.enBasAGauche = new Point(g);
        this.enHautADroite = new Point(d);
        // A compléter
    }

    /** Construction par fusion de deux icebergs qui se touchent
     * @param i1
     * @param i2
     */
    public Iceberg2D(Iceberg2D i1, Iceberg2D i2) {
        // A compléter
    }

    /**
     * @return le coin en bas à gauche
     */
    public Point coinEnBasAGauche() {
        return this.enBasAGauche;
    }

    /**
     * @return le coin en haut à droite
     */
    public Point coinEnHautADroite() {
        return this.enHautADroite ;
    }


    /**
     * @return hauteur
     */
    public double hauteur() {
        return this.enHautADroite.getOrdonnee() - this.enBasAGauche.getOrdonnee();
    }

    /**
     * @return largeur
     */
    public double largeur() {
        return this.enHautADroite.getAbscisse() - this.enBasAGauche.getAbscisse();
    }

    /**
     * @return surface totale
     */
    public double surface() {
        return this.largeur()*this.hauteur() ;
    }
	
    /**
     * @param i
     * @return vrai si collision entre les deux icebergs
     */
    public boolean collision(Iceberg2D i) {
        if(i.coinEnHautADroite().getAbscisse() >= this.coinEnBasAGauche().getAbscisse())
            return true;
        if(i.coinEnHautADroite().getOrdonnee() >= this.coinEnBasAGauche().getOrdonnee())
            return true;
        return false ;
    }

    /**
     * @param i
     * @return vrai si this est plus volumineux que i
     */
    public boolean estPlusGrosQue(Iceberg2D i) {
        return i.surface() < this.surface() ;
    }

    public String toString() {
        String res = this.enBasAGauche.toString() + " === ";
        res += this.enHautADroite.toString();
        return res ;
    }

    /**
     * @return le point au centre de l'iceberg
     */
    public Point centre() {
        return null ;
    }

    /** Réduction dans les quatre directions ; le centre ne bouge pas
     * @param fr dans ]0..1[ facteur de réduction
     */
    public void fondre(double fr) {
        // A compléter
    }

    /**
     * Casser une partie à droite
     * @param fr dans ]0..1[ facteur de réduction
     */
    public void casserDroite(double fr) {
        // A compléter
    }

    /**
     * Casser une partie à gauche
     * @param fr dans ]0..1[ facteur de réduction
     */
    public void casserGauche(double fr) {
        // A compléter
    }

    /**
     * Casser une partie en haut
     * @param fr dans ]0..1[ facteur de réduction
     */
    public void casserHaut(double fr) {
        // A compléter
    }

    /**
     * Casser une partie en bas
     * @param fr dans ]0..1[ : définit le pourcentage supprimé
     */
    public void casserBas(double fr) {
        // A compléter
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // A compléter
        Point p1 = new Point(0.0,0.0);
        Point p2 = new Point(100.0,100.0);
        Iceberg2D ice = new Iceberg2D(p1,p2);
        System.out.println(ice.surface());
    }
}
