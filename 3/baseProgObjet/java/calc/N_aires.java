package calc;

public abstract class N_aires implements Expression{
    protected Expression[] tab;

    public N_aires(Expression ... t){
        tab = new Expression[t.length];
        for(int i=0; i<t.length; i++){
            tab[i] = t[i];
        }
    }

    public String toString(){
        StringBuilder builde = new StringBuilder();
        builde.append(getOp()+"(");
        for(Expression ex : tab){
            builde.append(ex+",");
        }
        builde.deleteCharAt(builde.length()-1);
        builde.append(")");
        return builde.toString();
    }

    public abstract String getOp();
}
