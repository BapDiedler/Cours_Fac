package calculette;

public abstract class Binaire implements Expression {
	protected Expression gauche;
	protected Expression droite;
	
	public Binaire(Expression g, Expression d){
		this.gauche = g;
		this.droite = d;
	}
	
	public String toString(){
		return "("+this.gauche.valeur()+getOperateur()+this.droite.valeur()+")";
	}
	
	public abstract String getOperateur();
}
