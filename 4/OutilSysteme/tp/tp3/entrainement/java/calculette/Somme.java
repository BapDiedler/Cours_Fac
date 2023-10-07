package calculette;
	
public class Somme extends Binaire {
		public Somme(Expression g, Expression d){
			super(g,d);
	}
	
	public int valeur(){
		return this.gauche.valeur()+this.droite.valeur();
	}
	public String getOperateur(){
		return "+";
		}
}
