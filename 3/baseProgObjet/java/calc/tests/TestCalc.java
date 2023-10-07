package calc.tests;

import calc.*;

public class TestCalc {

    //test de somme
    private static void testSomme(){
        Expression n1 = new Nombre(2);
        Expression n2 = new Nombre(3);
        Expression sum = new Somme(n1,n2);
        assert sum.valeur()==5:"le constructeur ne marche pas";
        assert sum.toString().equals("(2+3)"):"la methode toString ne marche pas";
    }
    //test de difference
    private static void testDifference(){
        Expression n1 = new Nombre(2);
        Expression n2 = new Nombre(3);
        Expression dif = new Difference(n2,n1);
        assert dif.valeur()==1:"le constructeur ne marche pas";
        assert dif.toString().equals("(3-2)"):"la methode toString ne marche pas";
    }
    //test de produit
    private static void testProduit(){
        Expression n1 = new Nombre(2);
        Expression n2 = new Nombre(3);
        Expression pro = new Produit(n2,n1);
        assert pro.valeur()==6:"le constructeur ne marche pas";
        assert pro.toString().equals("(3*2)"):"la methode toString ne marche pas";
    }

    //test de quotient
    private static void testQuotient(){
        Expression n1 = new Nombre(9);
        Expression n2 = new Nombre(3);
        Expression quo = new Quotient(n1,n2);
        assert quo.valeur()==3:"le constructeur ne marche pas";
        assert quo.toString().equals("(9/3)"):"la methode toString ne marche pas";
    }

    //test de moyenne
    private static void testMoyenne(){
        Expression n1 = new Nombre(2);
        Expression n2 = new Nombre(2);
        Expression n3 = new Nombre(2);
        Expression n4 = new Nombre(2);
        Expression moy = new Moyenne(n1,n2,n3,n4);
        assert moy.valeur()==2:"le constructeur ne marche pas";
        assert moy.toString().equals("moyenne(2,2,2,2)"):"le toString ne marche pas";
    }

    //test de max
    private static void testMax(){
        Expression n1 = new Nombre(4);
        Expression n2 = new Nombre(2);
        Expression n3 = new Nombre(7);
        Expression n4 = new Nombre(2);
        Expression moy = new Max(n1,n2,n3,n4);
        assert moy.valeur()==7:"le constructeur ne marche pas";
        assert moy.toString().equals("max(4,2,7,2)"):"le toString ne marche pas";
    }

    //test de min
    private static void testMin(){
        Expression n1 = new Nombre(4);
        Expression n2 = new Nombre(1);
        Expression n3 = new Nombre(7);
        Expression n4 = new Nombre(2);
        Expression moy = new Min(n1,n2,n3,n4);
        assert moy.valeur()==1:"le constructeur ne marche pas";
        assert moy.toString().equals("min(4,1,7,2)"):"le toString ne marche pas";
    }

    public static void main(String[] args){
        testSomme();
        testDifference();
        testProduit();
        testQuotient();
        testMoyenne();
        testMax();
        testMin();
    }
}
