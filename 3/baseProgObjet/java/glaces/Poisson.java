package glaces;

import java.util.Random;

public class Poisson {
    private double abscisse;
    private double ordonnee;
    private double hauteur;
    private double largeur;
    

    /**
     * @brief Construction principal
     * 
     * @param double abs
     * @param double ord
     * @param double haut
     * @param double larg
     */
    public Poisson(double abs, double ord, double haut, double larg){
        this.abscisse=abs;
        this.ordonnee=ord;
        this.hauteur=haut;
        this.largeur=larg;
    }
    
    /**
     * @brief fonction qui renvoie l'abscisse
     */
    public double getAbscisse(){
        return abscisse;
    }

    /**
     * @brief fonction qui renvoie l'ordonnee
     */
    public double getOrdonnee(){
        return ordonnee;
    }

    /**
     * @brief fonction qui renvoie la hauteur
     */
    public double getHauteur(){
        return hauteur;
    }

    /**
     * @brief fonction qui renvoie la largeur
     */
    public double getLargeur(){
        return largeur;
    }

    /**
     * @brief fonction qui détruit le poisson s'il est mangé
     */
    public void estMange(Pingouin ping){
        double distanceCentreLargeur = Math.abs(this.getAbscisse()+(0.5*this.getLargeur()) - ping.getAbscisse()-(0.5*ping.getTaille()));
        double distanceCentreHauteur = Math.abs(this.getOrdonnee()+(0.5*this.getHauteur()) - ping.getOrdonnee()-(0.5*ping.getTaille()));
        double distanceBordureLargeur = (this.getLargeur()/2)+(ping.getTaille()/2);
        double distanceBordureHauteur = (this.getHauteur()/2)+(ping.getTaille()/2);
        if(distanceCentreLargeur - distanceBordureLargeur <= 0. && distanceCentreHauteur - distanceBordureHauteur <= 0.){
            this.hauteur=0.;
            this.largeur=0.;
        }
    }

    /**
     * @brief fonction qui détermine si un poisson est fatigué
     */
    public boolean estFatigue(){
        Random g = new Random();
        int val = g.nextInt(3);
        return(val==2);
    }

    /**
     * @brief fonction qui dit si un poisson est sorti
     */
    public boolean outOfOcean(double largOcean, double hautOcean){
        boolean valAbscisse = (int)abscisse+(int)largeur>(int)largOcean-1 || (int)abscisse<0.;
        boolean valOrdonnee = (int)ordonnee+(int)hauteur>(int)hautOcean-1 || (int)ordonnee<0.;
        return(valAbscisse || valOrdonnee);
    }

    /**
     * @brief fonction qui deplace le poisson de sa largeur vers la droite
     */
    public void deplacer(double x, double y){
        abscisse=x;
        ordonnee=y;
    }
}
