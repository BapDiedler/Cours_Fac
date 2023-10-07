package glaces;
import glaces.Iceberg2D ;
import geometrie.Point;
import java.util.Random;
import glaces.Pingouin;
import glaces.ArcticImage;

    	
public class Ocean {

    private int largeur ;
    private int hauteur ;
    private Iceberg2D[] icebergs;
    private Pingouin pin;
    private int[][] couleur;
	static int imgW = 300;
	static int imgH = 300;
	ArcticImage img;
	
    /**
     * @param l la largeur de l'océan
     * @param h la hauteur de l'océan
     * uniquement des entiers positifs
     */
    public Ocean(int l, int h) {
    	
    	
    	Random g = new Random() ;
        this.largeur = l;
        this.hauteur = h;
        
        //Création et placement des icebergs
        this.icebergs = new Iceberg2D[2];
        for(int i = 0; i <this.icebergs.length; i++){
        	int IceLen = g.nextInt(100);//largeur aléatoire
        	int IceHei = g.nextInt(100);//hauteur aléatoire
	        int IceX = g.nextInt(imgW-IceLen);//position aléatoire
	        this.icebergs[i] = new Iceberg2D(new Point(IceX,h),new Point(IceX+IceLen,h+IceHei ));
    	}
    	this.img = new ArcticImage(300,300);
    	
    	//Création et placement du pingoin
    	this.pin = new Pingouin(new Point(0,h),10);
    }
    
    public void deplacerH(double dep){
    	this.pin.deplacerH(dep);
    }
	 public void deplacerV(double dep){
    	this.pin.deplacerV(dep);
    }

    
    public void rafraichissementCoul(){
    //Création de la grille de couleur
    	//Pour l'océan
    	this.couleur = new int[imgW][imgH];
    	for(int i = 0; i < imgW; i++){
    		for(int j = 0; j < imgH; j++){
    			if(j < this.hauteur)
	    			this.couleur[i][j] = 0;
    			else
    				this.couleur[i][j] = 1;
    		}
    	}
    	
    	//Pour les icebergs
    	for(int i = 0; i <this.icebergs.length; i++){
    		int x = (int) this.icebergs[i].coinEnBasAGauche().getAbscisse();
    		int y = (int) this.icebergs[i].coinEnBasAGauche().getOrdonnee();
    		int lI = (int) this.icebergs[i].largeur();
    		int hI = (int) this.icebergs[i].hauteur();
    		for(int j = x; j <= x+lI; j++){
    			for(int k = y; k <= y+hI; k++){
    				this.couleur[j][k] = 2;
    			}
    		}
    	}
    	
    	//Pour le pingoin
    	int pinAbs = (int) this.pin.getPosition().getAbscisse();
    	int pinOrd = (int) this.pin.getPosition().getOrdonnee();
    	int pinLar = this.pin.getTaille();
    	for(int j = pinAbs; j <= pinAbs+pinLar; j++){
    			for(int k = pinOrd; k <= pinOrd + pinLar; k++){
    				this.couleur[j][k] = 3;
    			}
    		}
    	}

	public void fermer(){
		this.img.fermer();
		System.exit(0);
	}
    /**
     * @return la largeur de l'océan
     */
    public int getLargeur() {
        return this.largeur;
    }

    /**
     * @return la hauteur de l'océan
     */
    public int getHauteur() {
        return this.hauteur ;
    }
    
    
    /**
    * @param i le ième iceberg
    * @return point en haut à droite du  ième iceberg
    */
    public Point getHD(int i){
    	assert(i<this.icebergs.length):"array out of bound : pas assez d'iceberg";
    	return this.icebergs[i].coinEnHautADroite();
    }
    
    public void afficher(){
    	
    	img.setColors(this.couleur);
    }
    
    public static void main(String[] args){
    	Ocean o = new Ocean(300,50);
    	o.rafraichissementCoul();	
    	o.deplacerH(40);
    	
    	o.rafraichissementCoul();
    	
    	System.out.println(o.getHD(0).toString());
    	o.afficher();
    }
}
