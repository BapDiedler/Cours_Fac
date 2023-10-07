package calc;

public class Moyenne extends N_aires{
    public Moyenne(Expression... nb) {
        super(nb);
    }

    public int valeur() {
        assert tab.length>0:"on ne peut pas faire la moyenne de rien";
        int val = 0;
        int tmp = 0;
        for(Expression ex: tab){
            val+=ex.valeur();
            tmp++;
        }
        return val/tmp;
    }
    public String getOp() {
        return "moyenne" ;
    }
}