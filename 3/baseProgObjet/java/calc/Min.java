package calc;

public class Min extends N_aires{
        public Min(Expression... nb) {
            super(nb);
        }
    
        public int valeur() {
            assert tab.length>0:"on ne peut pas faire la moyenne de rien";
            int m = tab[0].valeur();
            for(Expression ex: tab){
                if(m>ex.valeur()){
                    m=ex.valeur();
                }
            }
            return m;
        }
        public String getOp() {
            return "min" ;
        }
}
