package calc.tests;

import calc.Expression;
import calc.Nombre;
import calc.Somme;

public class TestSomme {

    private static void testConstructeur(){
        Expression n1 = new Nombre(2);
        Expression n2 = new Nombre(3);
        Expression sum = new Somme(n1,n2);
        assert sum.valeur()==5:"le constructeur ne marche pas";
    }

    private static void testValeur(){
        Expression n1 = new Nombre(2);
        Expression n2 = new Nombre(3);
        Expression sum = new Somme(n1,n2);
        assert sum.valeur()==5:"la methode valeur ne marche pas";
    }

    private static void testString(){
        Expression n1 = new Nombre(2);
        Expression n2 = new Nombre(3);
        Expression sum = new Somme(n1,n2);
        assert sum.toString().equals("(2+3)"):"la methode toString ne marche pas";
    }

    public static void main(String[] args){
        testConstructeur();
        testValeur();
        testString();
    }
}
