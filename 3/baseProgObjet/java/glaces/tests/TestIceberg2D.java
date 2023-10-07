/**
 * @author Baptiste Diedler
 * 
 * @version 2022 
 */


package glaces.tests;

import glaces.Iceberg2D;
import geometrie.Point ;

public class TestIceberg2D {
    /**
     * @brief fonction qui vérifie la validité des constructeurs
     */
    private static void testConstructeurPrincipal(){
        //test du constructeur principal
        Point p1 = new Point(0.,0.);
        Point p2 = new Point(4.,4.);
        Iceberg2D ice = new Iceberg2D(p1, p2);
        //test d'un iceberg classic
        boolean val = ice.coinEnBasAGauche()==p1 & ice.coinEnHautADroite()==p2;
        assert(val):"Erreur au constructeur principal";
        p2.deplacer(-4.,-4.);
        //test d'un iceberg null
        val = ice.coinEnBasAGauche()==p1 & ice.coinEnHautADroite()==p2;
        assert(val):"Erreur au constructeur principal";
        p1.deplacer(-4.,-4.);
        //test d'un iceberg negatif
        val = ice.coinEnBasAGauche()==p1 & ice.coinEnHautADroite()==p2;
        assert(val):"Erreur au constructeur principal";
    }
    private static void testConstructeurFusion(){
        Point p1 = new Point(0.,0.);
        Point p2 = new Point(4.,4.);
        Iceberg2D ice = new Iceberg2D(p1, p2);
        Point p3 = new Point(0.,4.);
        Point p4 = new Point(6.,7.);
        Iceberg2D ice2 = new Iceberg2D(p3, p4);
        Iceberg2D ice3 = new Iceberg2D(ice, ice2);
        boolean val = ice3.coinEnBasAGauche().getAbscisse()==Math.min(ice.coinEnBasAGauche().getAbscisse(),ice2.coinEnBasAGauche().getAbscisse());
        val = ice3.coinEnBasAGauche().getOrdonnee()==Math.min(ice.coinEnBasAGauche().getOrdonnee(),ice2.coinEnBasAGauche().getOrdonnee()) & val;
        val = ice3.coinEnHautADroite().getOrdonnee()==Math.max(ice.coinEnHautADroite().getOrdonnee(),ice2.coinEnHautADroite().getOrdonnee()) & val;
        val = ice3.coinEnHautADroite().getAbscisse()==Math.max(ice.coinEnHautADroite().getAbscisse(),ice2.coinEnHautADroite().getAbscisse()) & val;
        assert(val):"Erreur au constructeur fusion";
    }

    /**
     * @brief test qui vérifie les fonctions get pour les coins de l'iceberg
     */
    private static void testCoinsIceberg(){
        Point p1 = new Point(0.,0.);
        Point p2 = new Point(4.,4.);
        Iceberg2D ice = new Iceberg2D(p1, p2);
        boolean val = Math.abs(p1-ice.coinEnBasAGauche())==0.001 & Math.abs(p2-ice.coinEnHautADroite())==0.001;
        assert(val):"Erreur pour les fonctions get des points";
    }

    /** 
     * @brief fonction qui test si la collision marche
     */
    private static void testCollisionVrai(){
        Point p1 = new Point(0.,0.);
        Point p2 = new Point(4.,4.);
        Iceberg2D ice = new Iceberg2D(p1, p2);
        Point p3 = new Point(0.,4.);
        Point p4 = new Point(4.,8.);
        Iceberg2D ice2 = new Iceberg2D(p3, p4);
        boolean val = ice.collision(ice2);
        assert(val):"Erreur en cas de collision";
        p3.deplacer(4.,0.);
        p4.deplacer(2.,0.);
        val = ice.collision(ice2);
        assert(val):"Erreur en cas de collision";
        p3.deplacer(-4.,0.);
        p4.deplacer(6.,2.);
        val = ice.collision(ice2);
        assert(val):"Erreur en cas de collision";
    }
    private static void testCollisionFaux(){
        Point p1 = new Point(0.,0.);
        Point p2 = new Point(4.,4.);
        Iceberg2D ice = new Iceberg2D(p1, p2);
        Point p3 = new Point(0.,4.);
        Point p4 = new Point(4.,8.);
        Iceberg2D ice2 = new Iceberg2D(p3, p4);
        p3.deplacer(7.,0.);
        p4.deplacer(5.,1.);
        boolean val = ice.collision(ice2);
        assert(!val):"Erreur en cas de collision";
    }

    /**
     *@brief fonction qui test si la hauteur, la largeur et la surface sont juste
     */
    private static void testHauteurLargeurCentreSurface(){
        Point p1 = new Point(0.,0.);
        Point p2 = new Point(4.,4.);
        Iceberg2D ice = new Iceberg2D(p1, p2);
        boolean val = ice.hauteur() == ice.coinEnHautADroite().getOrdonnee() - ice.coinEnBasAGauche().getOrdonnee();
        assert(val):"Erreur dans la hauteur";
        val = ice.largeur() == ice.coinEnHautADroite().getAbscisse() - ice.coinEnBasAGauche().getAbscisse();
        assert(val):"Erreur dans la largeur";
        val = ice.surface() == ice.hauteur() * ice.largeur();
        assert(val):"Erreur dans la surface";
    }

    /**
     *@brief fonction qui test la fonction estPlusGrosQue
     */
    public static void testEstPlusGrosQueVraie(){
        Point p1 = new Point(0.,0.);
        Point p2 = new Point(4.,5.);
        Iceberg2D ice1 = new Iceberg2D(p1, p2);
        Point p3 = new Point(0.,4.);
        Point p4 = new Point(5.,7.);
        Iceberg2D ice2 = new Iceberg2D(p3, p4);
        boolean val = ice1.estPlusGrosQue(ice2);
        assert(val):"Erreur dans la fonction estPlusGrosQue";
    }
    public static void testEstPlusGrosQueFaux(){
        Point p1 = new Point(0.,0.);
        Point p2 = new Point(4.,5.);
        Iceberg2D ice1 = new Iceberg2D(p1, p2);
        Point p3 = new Point(0.,4.);
        Point p4 = new Point(3.,100.);
        Iceberg2D ice2 = new Iceberg2D(p3, p4);
        boolean val = ice1.estPlusGrosQue(ice2);
        assert(!val):"Erreur dans la fonction estPlusGrosQue";
    }

    /**
     *@brief fonction qui test la fonction fondre
     */
    private static void testFondre(){
        Point p1 = new Point(0.,0.);
        Point p2 = new Point(10.,10.);
        Iceberg2D ice1 = new Iceberg2D(p1, p2);
        Point p3 = new Point(0.,4.);
        Point p4 = new Point(5.,7.);
        Iceberg2D ice2 = new Iceberg2D(p3, p4);
        ice2.fondre(1);
        boolean val = ice2.surface() == 0.;
        assert(val):"Erreur dans la fonction fondre";
        ice1.fondre(0.25);
        val =  ice1.hauteur() == 7.5 & ice1.largeur() == 7.5 ;
        assert(val):"Erreur dans la fonction fondre";
    }

    /**
     * @brief fonction qui test les foncrions cassées
     */
    private static void testCasserHaut(){
        Point p1 = new Point(0.,0.);
        Point p2 = new Point(10.,10.);
        Iceberg2D ice1 = new Iceberg2D(p1, p2);
        ice1.casserHaut(0.5);
        boolean val = ice1.surface() == 50.;
        assert(val):"Erreur dans la fonction casser haut";
    }
    private static void testCasserBas(){
        Point p1 = new Point(0.,0.);
        Point p2 = new Point(10.,10.);
        Iceberg2D ice1 = new Iceberg2D(p1, p2);
        ice1.casserBas(0.5);
        boolean val = ice1.surface() == 50.;
        assert(val):"Erreur dans la fonction casser bas";
    }
    private static void testCasserDroite(){
        Point p1 = new Point(0.,0.);
        Point p2 = new Point(10.,10.);
        Iceberg2D ice1 = new Iceberg2D(p1, p2);
        ice1.casserDroite(0.5);
        boolean val = ice1.surface() == 50.;
        assert(val):"Erreur dans la fonction casser droite";
    }
    private static void testCasserGauche(){
        Point p1 = new Point(0.,0.);
        Point p2 = new Point(10.,10.);
        Iceberg2D ice1 = new Iceberg2D(p1, p2);
        ice1.casserGauche(0.5);
        boolean val = ice1.surface() == 50.;
        assert(val):"Erreur dans la fonction casser gauche";
    }


    public static void main(String[] args) {
        testConstructeurPrincipal();
        testConstructeurFusion();
        testCoinsIceberg();
        testCollisionVrai();
        testCollisionFaux();
        testHauteurLargeurCentreSurface();
        testEstPlusGrosQueVraie();
        testEstPlusGrosQueFaux();
        testFondre();
        testCasserHaut();
        testCasserBas();
        testCasserDroite();
        testCasserGauche();
    }
}
