package glaces;
import java.util.concurrent.CompletableFuture;
import geometrie.Point ;

/**
 * Un iceberg rectangulaire
 * @author Martine Gautier, Université de Lorraine
 */
public class Iceberg2D {

    private Point enBasAGauche ;
    private Point enHautADroite ;

    /**
     * Construction
     * @param g le coin en bas à gauche
     * @param d le coin en haut à droite
     * uniquement en coordonnées positives
     */
    public Iceberg2D(Point g, Point d) {
        this.enBasAGauche = g;
        this.enHautADroite = d;
    }

    /**
     * Construction par fusion de deux icebergs qui se touchent
     * @param i1 premier iceberg à fusionner
     * @param i2 deuxième iceberg à fusionner
     */
    public Iceberg2D(Iceberg2D i1, Iceberg2D i2) {
        //partie pour le point en haut à gauche
        double abscisse = Math.max(i1.coinEnHautADroite().getAbscisse(), i2.coinEnHautADroite().getAbscisse());
        double ordonnee = Math.max(i1.coinEnHautADroite().getOrdonnee(), i2.coinEnHautADroite().getOrdonnee());
        Point hautDroite = new Point(abscisse,ordonnee);
        //partie pour le coin en bas à gauche
        abscisse = Math.min(i1.coinEnBasAGauche().getAbscisse(), i2.coinEnBasAGauche().getAbscisse());
        ordonnee = Math.min(i1.coinEnBasAGauche().getOrdonnee(), i2.coinEnBasAGauche().getOrdonnee());
        Point basGauche = new Point(abscisse,ordonnee);
        //creation du nouvel iceberg
        this.enBasAGauche = basGauche;
        this.enHautADroite = hautDroite;
    }

    /** 
     * Retourne le coin en bas à gauche
     * @return le coin en bas à gauche
     */
    public Point coinEnBasAGauche() {
        return this.enBasAGauche ;
    }

    /**
     * Retourne le coin en haut à droite
     * @return le coin en haut à droite
     */
    public Point coinEnHautADroite() {
        return this.enHautADroite ;
    }


    /**
     * Retourne la hauteur
     * @return hauteur
     */
    public double hauteur() {
        double haut = this.coinEnHautADroite().getOrdonnee() - this.coinEnBasAGauche().getOrdonnee() ;
        return haut;
    }

    /**
     * Retourne la largeur
     * @return largeur
     */
    public double largeur() {
        double larg =  this.coinEnHautADroite().getAbscisse() - this.coinEnBasAGauche().getAbscisse();
        return larg;
    }

    /**
     * Retourne la surface totale
     * @return surface totale
     */
    public double surface() {
        double aire = this.largeur() * this.hauteur();
        return aire ;
    }

    /**
     * Retourne vrai si il y a une collision entre les deux icebergs
     * @param i iceberg potentiellement en collision
     * @return vrai si collision entre les deux icebergs
     */
    public boolean collision(Iceberg2D i) {
        double distanceCentreLargeur = Math.abs(this.centre().getAbscisse() - i.centre().getAbscisse());
        double distanceCentreHauteur = Math.abs(this.centre().getOrdonnee() - i.centre().getOrdonnee());
        double distanceBordureLargeur = (this.largeur()/2)+(i.largeur()/2);
        double distanceBordureHauteur = (this.hauteur()/2)+(i.hauteur()/2);
        if(distanceCentreLargeur - distanceBordureLargeur <= 0. && distanceCentreHauteur - distanceBordureHauteur <= 0.) return true;//si les icebergs se touchent par les cotés
        return false;//si les icebergs ne se touchent pas
    }

    /**
     * Retourne vrai si this est plus volumineux que i
     * @param i iceberg à comparer
     * @return vrai si this est plus volumineux que i
     */
    public boolean estPlusGrosQue(Iceberg2D i) {
        if(this.surface()>i.surface()) return true;
        return false ;
    }

    public String toString() {
        return this.coinEnBasAGauche().toString()+this.coinEnHautADroite().toString() ;
    }

    /**
     * Retourne le point au centre
     * @return le point au centre de l'iceberg
     */
    public Point centre() {
        double middleX = (this.largeur()/2.)+this.coinEnBasAGauche().getAbscisse();
        double middleY = (this.hauteur()/2.)+this.coinEnBasAGauche().getOrdonnee();
        Point middle = new Point(middleX,middleY);
        return middle ;
    }

    /**
     * Réduction dans les quatre directions ; le centre ne bouge pas
     * @param fr dans ]0..1[ facteur de réduction
     */
    public void fondre(double fr) {
        if(fr-1.>=0.){
            this.enHautADroite.deplacer(-this.coinEnHautADroite().getAbscisse(),-this.coinEnHautADroite().getOrdonnee());
            this.enBasAGauche.deplacer(-this.coinEnBasAGauche().getAbscisse(),-this.coinEnBasAGauche().getOrdonnee());
        }
        else{
            double tmp1 = this.hauteur()*((fr)/2);
            double tmp2 = this.largeur()*((fr)/2);
            this.enHautADroite.deplacer(-tmp2,-tmp1);
            this.enBasAGauche.deplacer(tmp2,tmp1);
        }
    }

    /**
     * Casser une partie à droite
     * @param fr dans ]0..1[ facteur de réduction
     */
    public void casserDroite(double fr) {
        double coefLarg = fr * this.largeur();
        this.enHautADroite.deplacer(-coefLarg, 0.);
    }

    /**
     * Casser une partie à gauche
     * @param fr dans ]0..1[ facteur de réduction
     */
    public void casserGauche(double fr) {
        double coefLarg = fr * this.largeur();
        this.enBasAGauche.deplacer(coefLarg, 0.);
    }
    /**
     * Casser une partie en haut
     * @param fr dans ]0..1[ facteur de réduction
     */
    public void casserHaut(double fr) {
        double coefHaut = fr * this.hauteur();
        this.enHautADroite.deplacer(0., -coefHaut);
    }

    /**
     * Casser une partie en bas
     * @param fr dans ]0..1[ : définit le pourcentage supprimé
     */
    public void casserBas(double fr) {
        double coefHaut = fr * this.hauteur();
        this.enBasAGauche.deplacer(0., coefHaut);
    }

}