/**
 * @author Baptiste Diedler
 * 
 * @version 2022 
 */

package glaces;
import glaces.Iceberg2D;
import java.util.Random;
import geometrie.Point ;
import glaces.Pingouin;
import glaces.Poisson;

public class Ocean {
    private Pingouin pingouin;
    private int largeur;
    private int hauteur;
    private Poisson[] tabPoissons;
    private Iceberg2D[] tabIcebergs;

    /**
     * @brief Construction principal
     * 
     * @param int nb
     * @param int largeur
     * @param int hauteur
     */
    public Ocean(int nb, int larg, int haut){
        this.pingouin = new Pingouin(larg-10,0,10);
        this.largeur=larg;
        this.hauteur=haut;
        Random g = new Random();
        //on dit que le nombre de poissons est egal à 20
        this.tabPoissons = new Poisson[20];
        for(int i=0; i<10; i++){
            double x1 = g.nextInt(this.largeur-10);
            double y1 = g.nextInt(this.hauteur-5);
            Poisson poisson = new Poisson(x1, y1, 5, 10);
            this.tabPoissons[i]=poisson;
        }
        for(int i=10; i<20; i++){
            double x1 = g.nextInt(this.largeur-5);
            double y1 = g.nextInt(this.hauteur-10);
            Poisson poisson = new Poisson(x1, y1, 10, 5);
            this.tabPoissons[i]=poisson;
        }
        //creation des icebergs
        this.tabIcebergs = new Iceberg2D[nb];
        for(int i=0;i<nb ; i++){
            Point point1 = new Point(0.,0.);
            Point point2 = new Point(0.,0.);
            double x1 = g.nextInt(largeur);
            double x2 = g.nextInt(largeur);
            double minX = Math.min(x1,x2);
            double maxX = Math.max(x1,x2);
            point1.deplacer(minX,0.);
            point2.deplacer(maxX,0.);
            double y1 = g.nextInt(hauteur);
            double y2 = g.nextInt(hauteur);
            double minY = Math.min(y1,y2);
            double maxY = Math.max(y1,y2);
            point1.deplacer(0.,minY);
            point2.deplacer(0.,maxY);
            Iceberg2D ice = new Iceberg2D(point1, point2);
            this.tabIcebergs[i]=ice;
        } 
    }

    /**
     * @brief Construction
    */
    public Ocean(){
        this(2,300,300);
    }

    /**
     * @brief fonction qui renvoie la largeur
     */
    public int getWidth(){
        return largeur;
    }

    /**
     * @brief fonction qui renvoie la hauteur
     */
    public int getHeight(){
        return hauteur;
    }

    /**
     * @brief fonction qui renvoie le nombre d'icebergs
     */
    public int getCount(){
        return tabIcebergs.length;
    }

    /**
     * @brief fonction qui renvoie le nombre de poissons
     */
    public int getCountPoisson(){
        return tabPoissons.length;
    }

    public Poisson getPoisson(int i){
        return tabPoissons[i];
    }

    /**
     * @brief fonction qui renvoie un iceberg
     */
    public Iceberg2D getIceberg2d(int i){
        return tabIcebergs[i];
    }

    /**
     * @brief fonction qui renvoie le pingouin
     */
    public Pingouin getPingouin(){
        return pingouin;
    }

    /**
     * @brief fonction qui reduit les icebergs de l'ocean
     */
    public void Fondre(double fr){
        for(Iceberg2D ice: this.tabIcebergs){
            ice.fondre(fr);
        }
    }

    /**
     * @brief fonctio qui dessine l'ocean
     * @return int[][]
     */
    public int[][] getColors(){
        int[][] colors = new int[this.hauteur][this.largeur];
        //affichage des poissons
        for(Poisson poisson: tabPoissons){
            if(!poisson.outOfOcean(largeur, hauteur) && poisson.getHauteur()!=0.){
                for(int i=(int)poisson.getAbscisse();i<=(int)poisson.getAbscisse()+poisson.getLargeur(); i++){
                    for(int j=(int)poisson.getOrdonnee(); j<=(int)poisson.getOrdonnee()+poisson.getHauteur(); j++){
                        colors[i][j]=4;
                    }
                }
            }
        }
        //affichage des icebergs
        int xPing = (int)this.pingouin.getAbscisse();
        int yPing = (int)this.pingouin.getOrdonnee();
        for(Iceberg2D ice: this.tabIcebergs){
            for(int i=(int)ice.coinEnBasAGauche().getAbscisse(); i<=(int)ice.coinEnHautADroite().getAbscisse(); i++){
                for(int j=(int)ice.coinEnBasAGauche().getOrdonnee(); j<=(int)ice.coinEnHautADroite().getOrdonnee(); j++){
                    if(ice.largeur()>5 && ice.hauteur()>5)
                        colors[i][j]=1;
                }
            }
        }
        //affichage du pingouin
        for(int i=xPing; i<xPing+(int)this.pingouin.getTaille(); i++){
            for(int j=yPing ; j<yPing+(int)this.pingouin.getTaille(); j++){
                if(pingouin.getFatigue()==0){
                    colors[i][j]=2;
                }
                else if(pingouin.getFatigue()==1){
                    colors[i][j]=3;
                }
            }
        }
        return colors;
    }
}
