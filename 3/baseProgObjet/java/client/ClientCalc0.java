package client ;

import calc.* ;

public class ClientCalc0 {

     public static void main (String [] args) {
	    Expression e = new Somme(new Nombre(5), new Difference(new Nombre(6),new Nombre(9))); 
        System.out.println(e.valeur()) ;
     }

}