package calculette.tests;

import calculette.Soustraction;
import calculette.Nombre;

public class TestSoustraction {
	
	public TestSoustraction(){
		Nombre n1 = new Nombre(4);
		Nombre n2 = new Nombre(-1);
		Soustraction s1 = new Soustraction(n1,n2);
		assert(s1.valeur()==5):"Problème avec la somme de deux nombres";
		Soustraction s2 = new Soustraction(s1,s1);
		assert(s2.valeur()==0):"Problème avec la somme de deux sommes";
		Soustraction s3 = new Soustraction(s1,n1);
		assert(s3.valeur()==1):"Problème avec la somme d'une somme et d'un nombre";
	}
	
	public static void main(String[] args){
		TestSomme ts =  new TestSomme();
	}
}
