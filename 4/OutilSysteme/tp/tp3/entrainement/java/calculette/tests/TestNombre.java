package calculette.tests;

import calculette.Nombre;

public class TestNombre {
	public TestNombre(){
		
		Nombre n = new Nombre(4);
		assert(n.valeur() == 4):"Bug valeur() dans Nombre";
		assert(n.toString().equals("4")):"Bug toString() dans Nombre";
		
	}
	
	public static void main(String[] args){
		TestNombre t = new TestNombre();	
	}
}
