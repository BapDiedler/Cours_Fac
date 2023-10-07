package calc;

public class Max extends N_aires{
        public Max(Expression... nb) {
            super(nb);
        }
    
        public int valeur() {
            assert tab.length>0:"on ne peut pas faire la moyenne de rien";
            int m = tab[0].valeur();
            for(Expression ex: tab){
                if(m<ex.valeur()){
                    m=ex.valeur();
                }
            }
            return m;
        }
        public String getOp() {
            return "max" ;
        }
}
