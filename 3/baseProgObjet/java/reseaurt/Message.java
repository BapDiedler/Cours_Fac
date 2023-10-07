package reseau;

import java.util.ArrayList;

import reseau.adresses.*;

/**
 * @author martine
 * @version 4 déc. 2014
 */
public class Message {

    private ArrayList<Octet> mes;

    /**
     * Constructeur d'un message vide
     */
    public Message() {
        mes = new ArrayList<>();
    }

    /**
     * Constructeur de copie (copie profonde)
     * @param mess nombre d'éléments à copier
     * @exception AssertionError si mess est null
     */
    public Message(Message mess) {
        mes = new ArrayList<>();
        for(int i=0; i<mess.size(); i++){
            mes.add(new Octet(mess.mes.get(i)));
        }
    }

    /**
     * Constructeur d'un message à partir des petits entiers (1 petit entier est codé sur un seul octet)
     * @param v des petits entiers qui constituent le message
     * @exception AssertionError si v est null
     */
    public Message(short... v) {
        assert v!=null : "les shorts doivent être initialisé";
        mes = new ArrayList<>();
        for(int i=0; i<v.length; i++){
            mes.add(new Octet(v[i]));
        }
    }

    /**
     * Constructeur d'un message à partir des entiers (1 entier est codé sur 2 octets)
     * @param v des entiers qui constituent le message
     * @exception AssertionError si v est null
     */
    public Message(int... v) {
        assert v!=null : "les ints doivent être initialisé";
        mes = new ArrayList<>();
        for(int i = 0; i<v.length; i++){
            mes.add(new Octet(v[i]/256));
            mes.add(new Octet(v[i]%256));
        }
    }

    /**
     * Constructeur d'un message à partir de la chaîne de caractères
     * @param mot chaîne de caractères qui constitue le message
     * @exception AssertionError si mot est null
     */
    public Message(String mot) {
        assert mot!=null : "le String doit être initialisé";
        mes = new ArrayList<>();
        char val;
        int tmp;
        for(int i = 0; i<mot.length(); i++){
            val = mot.charAt(i);
            tmp = val;
            mes.add(new Octet(tmp));
        }
    }

    /**
     * Constructeur d'un message à partir de l'adresse
     * @param adr adresse à placer dans le message
     * @exception AssertionError si adr est null
     */
    public Message(Adresse adr) {
        assert adr!=null:"l'adresse ne peut pas être null";
        mes = new ArrayList<>();
        Octet val;
        for(int i=0; i<adr.size()/8; i++){
            val = adr.getOctet(i);
            mes.add(val);
        }
    }

    /**
     * Retourne le nombre d'octets
     * @return le nombre d'octets
     */
    public int size() {
        return mes.size();
    }

    /**
     * Ajouter un petit entier à la fin, entier &ge; 0
     * @param x entier à ajouter
     */
    public void ajouter(short x) {
        mes.add(new Octet(x));
    }

    /**
     * Ajouter un entier à la fin, entier &ge; 0
     * @param x entier à ajouter
     */
    public void ajouter(int x) {
        mes.add(new Octet(x/256));
        mes.add(new Octet(x%256));
    }

    /**
     * Ajouter un octet à la fin
     * @param o octet à ajouter
     * @exception AssertionError si o est null
     */
    public void ajouter(Octet o) {
        assert o!=null:"l'octet doit être initialisé";
        mes.add(o);
    }

    /**
     * Concaténer un autre message
     * @param mess message à ajouter à la fin
     * @exception AssertionError si mess est null
     */
    public void ajouter(Message mess) {
        assert mess!=null:"le message doit être initialisé";
        for(Octet oc : mess.mes){
            mes.add(oc);
        }
    }

    /**
     * Ajouter les octets d'une adresse à la fin
     * @param adr adresse à ajouter
     * @exception AssertionError si adr est null
     */
    public void ajouter(Adresse adr) {
        assert adr!=null:"l'adresse' doit être initialisé";
        for(int i=0; i<adr.getNbreOctets(); i++){
            mes.add(adr.getOctet(i));
        }
    }
    
    @Override
    public String toString() {
        StringBuilder builde = new StringBuilder();
        for(Octet oc : mes){
            builde.append(oc);
        }
        return builde.toString() ;
    }

    /**
     * Extraire les 2 octets situés en index et index+1 pour en faire un entier
     * octets forts puis faibles (big endian)
     * @param index index du premier octet
     * @exception AssertionError si index ou index+1 n'est pas dans le domaine du tableau
     * @return un entier
     */
    public int extraireEntier(int index) {
        assert index>=0 && index+1<mes.size():"l'index est en dehors de la liste";
        int val = mes.get(index).getValue()*256;
        return val + mes.get(index+1).getValue();
    }

    /**
     * Extraire les nbOctets premiers octets pour en faire une adresse
     * @param nbOctets nombre d'octets à extraire
     * @exception AssertionError si nbOctets &gt; longueur du message
     * @return une adresse
     */
    public Adresse extraireAdresse(int nbOctets) {
        assert nbOctets-1<mes.size():"le nombre d'octet est rop grand";
        Octet[] oc = new Octet[nbOctets];
        for(int i=0; i<nbOctets; i++){
            oc[i] = new Octet(mes.get(i));
        }
        return new Adresse(oc) ;
    }

    /**
     * Transformer le message en une suite de lettres, si possible 
     * @return null si l'un des octets n'est pas une lettre (maj ou min)
     */
    public String extraireChaine() {
        StringBuilder builde = new StringBuilder();
        for(Octet oc : mes){
            if(!oc.estUneLettre() && !oc.estUnPoint()){
                return null;
            }
            else{
                builde.append((char)oc.getValue());
            }
        }
        return builde.toString() ;
    }

    /**
     * Augmenter de i chaque octet dont la valeur est comprise entre bi et bs
     * @param i valeur à ajouter
     * @param bi borne inférieure
     * @param bs borne supérieure
     */
    public void augmenter(int i, int bi, int bs) {
        int tmp = 0;
        for(Octet oc : mes){
            if(oc.plusPetitQue(bs) && oc.getValue()>bi){
                oc.ajouter(i);
            }
        }
    }

    /**
     * On enlève les i premiers éléments
     * @param i nombre d'éléments à enlever
     * @exception AssertionError si i n'est pas dans le domaine du tableau
     */
    public void supprimer(int i) {
        assert i>=0 && i<mes.size():"l'indice est en dehors de la liste";
        mes.remove(i);
        mes.remove(i);
    }

    /**
     * On enlève les éléments entre debut et fin inclus
     * @param debut borne inférieure
     * @param fin borne supérieure
     * @exception AssertionError si on n'a pas 0 &le; debut &le; fin &lt; size()
     */
    public void supprimer(int debut, int fin) {
        assert mes.size()!=0:"le message doit contenir des caractères";
        assert debut>=0 && debut<mes.size():"l'indice est en dehors de la liste";
        assert fin>=0 && fin<mes.size():"l'indice est en dehors de la liste";
        while(debut <= fin){
            mes.remove(debut);
            mes.remove(debut);
            debut++;
        }
    }

}
