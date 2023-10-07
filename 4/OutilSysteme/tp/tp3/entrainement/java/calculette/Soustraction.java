package calculette;
	
public class Soustraction extends Binaire {
		public Soustraction(Expression g, Expression d){
			super(g,d);
	}
	
	public int valeur(){
		return this.gauche.valeur()-this.droite.valeur();
	}
	public String getOperateur(){
		return "*";
		}
}
