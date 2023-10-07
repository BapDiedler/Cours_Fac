package calc;

public class Somme extends Binaire{
    public Somme (Expression g, Expression d) {
        super(g, d);
    }
    public int valeur() {
        return gauche.valeur() + droit.valeur() ;
    }
    public String getOperateur() {
        return "+" ;
    }
}
