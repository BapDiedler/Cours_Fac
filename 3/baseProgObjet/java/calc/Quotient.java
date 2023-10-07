package calc;

public class Quotient extends Binaire{
    public Quotient (Expression g, Expression d) {
        super(g, d);
    }
    public int valeur() {
        assert droit.valeur()!=0:"on ne peut pas diviser par zero";
        return gauche.valeur() / droit.valeur() ;
    }
    public String getOperateur() {
        return "/" ;
    }
}
