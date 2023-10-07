package calc;

public class Difference extends Binaire{
    public Difference (Expression g, Expression d) {
        super(g, d);
    }
    public int valeur() {
        return gauche.valeur() - droit.valeur() ;
    }
    public String getOperateur() {
        return "-" ;
    }
}
