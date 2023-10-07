package calc;

public class Produit extends Binaire{
    public Produit (Expression g, Expression d) {
        super(g, d);
    }
    public int valeur() {
        return gauche.valeur() * droit.valeur() ;
    }
    public String getOperateur() {
        return "*" ;
    }
}
