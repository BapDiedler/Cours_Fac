package calculette.tests;

import calculette.Somme;
import calculette.Nombre;

public class TestSomme {
	
	public TestSomme(){
		Nombre n1 = new Nombre(4);
		Nombre n2 = new Nombre(-1);
		Somme s1 = new Somme(n1,n2);
		assert(s1.valeur()==3):"Problème avec la somme de deux nombres";
		Somme s2 = new Somme(s1,s1);
		assert(s2.valeur()==6):"Problème avec la somme de deux sommes";
		Somme s3 = new Somme(s2,n1);
		assert(s3.valeur()==10):"Problème avec la somme d'une somme et d'un nombre";
	}
	
	public static void main(String[] args){
		TestSomme ts =  new TestSomme();
	}
}
