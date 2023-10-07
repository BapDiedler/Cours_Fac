package reseau.adresses;


/**
 * @author martine
 * @version 20 nov. 2014
 */

public class Adresse {

    //champs de la class adresse
    private Octet[] octets;

    /**
     * Constructeur de copie (copie profonde)
     * @param a adresse à copier
     * @exception AssertionError si a est null
     */
    public Adresse(Adresse a) {
        this(a.octets);
    }

    /**
     * Constructeur à partir du tableau d'octets (copie profonde)
     * @param al octets
     * @exception AssertionError si al est null
     */
    public Adresse(Octet... al) {
        assert al.length>=1:"Le nombre d'octet doit être supérieur à 1";
        assert al!=null:"le tableau d'octet doit être initialisé";

        octets = new Octet[al.length];
        int cpt = 0;
        for(Octet oc : al){
            octets[cpt] = oc;
            cpt++;
        }
    }

    /**
     * Adresse 0
     * @param nbBits nombre de bits
     * @exception AssertionError si le nombre total de bits n'est pas un multiple de 8 supérieur ou égal à 8
     */
    public Adresse(int nbBits) {
        this(nbBits,0);
    }

    /**
     * Adresse masque composée de nbBitsUn bits à 1 suivis de 0 pour compléter.
     * @param nbBits nombre de bits total
     * @param nbBitsUn nombre de bits à 1
     * @exception AssertionError si le nombre total de bits n'est pas un multiple de 8 supérieur ou égal à 8
     * @exception AssertionError si le nombre total de 1 est incorrect (négatif ou supérieur à nbBits)
     */
    public Adresse(int nbBits, int nbBitsUn) {
        assert nbBits>=1:"le nombre de bits rentré est incorrect";
        assert nbBits%8==0:"le nombre de bits rentré est incorrect";
        assert nbBitsUn>=0:"le nombre de bits à un est incorrect";
        assert nbBits>=nbBitsUn:"le nombre de bits à un est trop grand";

        octets = new Octet[nbBits/8];
        for(int i = 0; i<nbBits/8; i++){
            octets[i] = new Octet();
        }
        for(Octet oc : octets){
            if(8<=nbBitsUn){
                oc.setUn();
                nbBitsUn-=8;
            }
            else if(nbBitsUn > 0){
                oc.setUn(nbBitsUn);
                nbBitsUn-=8;
            }
        }
    }

    /**
     * Constructeur à partir d'une adresse écrite sous forme de notation décimale pointée (par ex : 245.156.0.0)
     * @param s notation décimale pointée d'une adresse (par ex : 245.156.0.0)
     * @exception AssertionError si le nombre d'octets est différent de 4, 6, 8 ou si un entier est trop grand
     */
    public Adresse(String s) {
        String[] tab = s.split("\\.");
        assert tab.length==4 || tab.length==8 || tab.length==6 :"le nombre d'octets ne correspond pas à une adresse";
        octets = new Octet[tab.length];
        int val;
        for(int i = 0; i<tab.length; i++){
            val = Integer.parseInt(tab[i]);
            assert val<256:"un des entiers entrés est trop grand";
            octets[i] = new Octet(val);
        }
    }

    /**
     * Retourne le nombre de bits
     * @return le nombre de bits
     */
    public int size() {
        return octets.length*8 ;
    }

    /**
     * Retourne le nombre d'octets
     * @return le nombre d'octets
     */
    public int getNbreOctets() {
        return octets.length;
    }

    /**
     * Appliquer un masque
     * @param masque masque à appliquer
     * @exception AssertionError si le masque et le receveur ne sont pas de la même taille
     */
    public void masquer(Adresse masque) {
        for(int i = 0; i<masque.octets.length; i++){
            octets[i].masquer(masque.octets[i]);
        }
    }

    /**
     * Inverser les octets : complément à 1 de chaque octet (0 &rarr; 1, 1 &rarr; 0)
     */
    public void inverser() {
        for(Octet oc : octets){
            oc.inverser();
        }
    }

    /**
     * Fixer les octets
     * @param alo octets
     * @exception AssertionError si alo est null
     */
    public void setOctets(Octet... alo)  {
        assert alo != null :"les octets doivent être organisé";
        assert alo.length >0 :"le tableau doit être remplit";

        for(int i = 0; i<alo.length; i++){
            octets[i] = alo[i];
        }
    }

    /**
     * Fixer un des octets de l'adresse, k est le rang de l'octet, k &ge; 0
     * @param o octet
     * @param k rang de l'octet
     * @exception AssertionError si k n'est pas entre 0 et le nombre d'octets
     */
    public void setOctet(Octet o, int k)  {
        assert k>=0 && k<octets.length:"k n'est pas entre 0 et le nombre d'octets";

        octets[k] = new Octet(o);
    }

    /**
     * Consulter un des octets de l'adresse, k est le rang de l'octet, k &ge; 0
     * @param k rang de l'octet
     * @return l'octet de rang k de l'adresse
     * @exception AssertionError si k n'est pas entre 0 et le nombre d'octets
     */
    public Octet getOctet(int k) {
        assert k>=0 && k<octets.length:"k n'est pas entre 0 et le nombre d'octets";
        return octets[k] ;
    }

    /**
     * Construit la chaîne de caractères où la valeur de chaque octet est séparé du suivant par un point.
     * Par exemple 192.45.43.100
     * @return la chaîne de caractères construite
     */
    public String toString() {
        StringBuilder builde = new StringBuilder();
        for(Octet oc : octets){
            builde.append(oc.toString()+'.');
        }
        builde.deleteCharAt(builde.length()-1);
        return builde.toString() ;
    }
}
