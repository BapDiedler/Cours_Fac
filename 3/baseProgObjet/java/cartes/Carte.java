package cartes;

public class Carte {

    private int valeur ;

    private Couleur couleur ;

    public Carte(int valeur, Couleur couleur) {
        assert(valeur<=8 && valeur>=1):"La valeur des cartes est comprise entre 1 et 8";
        this.valeur = valeur;
        assert(couleur!=null):"La couleur des cartets doit être initialisé";
        this.couleur = couleur;
    }

    public int getValeur() {
        return valeur;
    }

    public void setValeur(int valeur) {
        assert(valeur<=8 && valeur>=1):"La valeur des cartes est comprise entre 1 et 8";
        this.valeur = valeur;
    }

    public Couleur getCouleur() {
        return couleur;
    }

    public void setCouleur(Couleur couleur) {
        assert(couleur!=null):"La couleur des cartets doit être initialisé";
        this.couleur = couleur;
    }

    public String toString() {
        return "Carte{" +
                "valeur=" + valeur +
                ", couleur=" + couleur +
                '}';
    }

}