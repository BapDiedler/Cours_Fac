package glaces;

import glaces.Iceberg2D;

public class Pingouin {
    private double abscisse;
    private double ordonnee;
    private double taille;
    private int fatigue;

    /**
     * @brief Construction principal
     * 
     * @param double x
     * @param double y
     * @param double taille
     */
    public Pingouin(double x, double y, double taille){
        this.abscisse= x;
        this.ordonnee= y;
        this.taille= taille;
        fatigue=0;
    }

    /**
     * @brief fonction qui dit si le pingouin est sur un iceberg
     */
    public void onIceberg(Iceberg2D ice){
        //cas où il vient du  haut
        boolean val = (int)ordonnee-(int)ice.coinEnHautADroite().getOrdonnee() < 0. 
        && abscisse+taille <  ice.coinEnHautADroite().getAbscisse() 
        && abscisse>ice.coinEnBasAGauche().getAbscisse()
        && (int)ordonnee>ice.centre().getOrdonnee();
        if(val){
            if(ice.hauteur()>12){
                ice.casserHaut(0.01);
                this.onIceberg(ice);
            }
            else{
                ice.casserHaut(1);
            }
        }
        //cas où il vient du bas
        val = (int)ice.coinEnBasAGauche().getOrdonnee() - (int)ordonnee-taille < 0. 
        && abscisse+taille <  ice.coinEnHautADroite().getAbscisse() 
        && abscisse>ice.coinEnBasAGauche().getAbscisse()
        && (int)ordonnee<(int)ice.centre().getOrdonnee();
        if(val){
            if(ice.hauteur()>12){
                ice.casserBas(0.01);
                this.onIceberg(ice);
            }
            else{
                ice.casserBas(1);
            }
        }
        //cas où il vient de la droite
        val = (int)abscisse-(int)ice.coinEnHautADroite().getAbscisse()<0.
        && (int)ordonnee>(int)ice.coinEnBasAGauche().getOrdonnee()
        && (int)ordonnee+taille<(int)ice.coinEnHautADroite().getOrdonnee()
        && (int)abscisse>ice.centre().getAbscisse();
        if(val){
            if(ice.largeur()>12){
                ice.casserDroite(0.01);
                this.onIceberg(ice);
            }
            else{
                ice.casserDroite(1);
            }
        }
        //cas où il vient de la gauche
        val = (int)ice.coinEnBasAGauche().getAbscisse()-(int)abscisse-taille<0.
        && (int)ordonnee>(int)ice.coinEnBasAGauche().getOrdonnee()
        && (int)ordonnee+taille<(int)ice.coinEnHautADroite().getOrdonnee()
        && (int)abscisse<ice.centre().getAbscisse();
        if(val){
            if(ice.largeur()>12){
                ice.casserGauche(0.01);
                this.onIceberg(ice);
            }
            else{
                ice.casserGauche(1);
            }
        }
    }

    /**
     * @brief fonction qui renvoie l'abscisse
     */
    public double getAbscisse(){
        return this.abscisse;
    }

    /**
     * @brief fonction qui renvoie l'ordonnee
     */
    public double getOrdonnee(){
        return this.ordonnee;
    }

    /**
     * @brief fonction qui renvoie la taille 
     */
    public double getTaille(){
        return this.taille;
    }

    /**
     * @brief fonction qui deplace le pingouin de son abscisse
     */
    public void deplacerAbscisse(double dist){
        this.abscisse+=dist;
    }

    /**
     * @brief fonction qui deplace le pingouin de son ordonnee
     */
    public void deplacerOrdonnee(double dist){
        this.ordonnee+=dist;
    }

    /**
     * @brief fonction qui détermine si le pingouin est fatigué
     */
    public void estFatigue(int i){
        if(i>30){
            fatigue = 2;
        }
        if(i>10){
            fatigue = 1;
        }
        fatigue = 0;
    }

    /**
     * @brief getter qui dit si un pingouin est fatigué
     */
    public int getFatigue(){
        return fatigue;
    }

}
