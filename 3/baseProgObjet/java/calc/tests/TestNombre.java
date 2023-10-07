package calc.tests;

import calc.Nombre;


public class TestNombre {

    private static void testConstructeur(){
        Nombre nb = new Nombre(4);
        assert nb.valeur()==4;
    }
    public static void main(String[] args){
        testConstructeur();
    }
}
