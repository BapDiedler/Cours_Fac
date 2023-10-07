package reseau.couches;

import reseau.tables.ARP;
import reseau.Message;
import reseau.adresses.*;

/**
 * @author martine
 */
public class IP extends Reseau {

    static private int compteur = 0;

    protected Adresse masque ;
    protected Adresse adresseIP ;

    private ARP arp = new ARP() ;
    
    /**
     * @param ici la machine où je suis
     * @param masque masque à appliquer
     */
    public IP(Adresse ici, Adresse masque) {
        adresseIP = ici ;
        this.masque = masque;
    }

    /**
     * @param dest adresse destination
     * @param message message à transmettre
     * @return entête du message
     */
    public Message getEntete(Adresse dest, Message message) {
        // Longueur totale (16 bits), Identification (16 bits), Protocole (8 bits)
        // Adresse IP source (32 bits), Adresse IP destination (32 bits)
        Message enTete = new Message();
        enTete.ajouter(2*9+message.size());
        enTete.ajouter(compteur);
        enTete.ajouter((short)17);
        enTete.ajouter(adresseIP);
        enTete.ajouter(dest);
        return enTete ;
    }
    
    /**
     * Utilisation de la table ARP pour retrouver l'adresseMac à partir d'une adresse IP
     * @param adr adresse IP
     * @return adresseMac associée à l'adresse IP
     */
    private AdresseMac getAdresseMac(Adresse adr) {
        return null;
    }
    
    /**
     * @return mon adresse IP
     */
    public Adresse getAdresseIP() {
        return this.adresseIP;
    }
    
    /**
     * @param dest adresse du destinataire
     * @param message message à transmettre
     */
    @Override
    public void sendMessage(Adresse dest, Message message) {
        //throw new UnsupportedOperationException("Not supported yet.");
        Message enTete = new Message(this.getEntete(dest,  message));
        enTete.ajouter(message);
        message = new Message(enTete); 
        System.out.println("Je suis "+getNom()+" et j'envoie "+message.size()+" octets : " +message);
        AdresseMac destMac = new  AdresseMac(arp.get(dest));
        ((Liaison)moinsUn).sendMessage(destMac,  message); 
    } 
  
    @Override
    public void receiveMessage(Message message) {
    	message.supprimer(5);
    	Adresse source = new Adresse(message.extraireAdresse(4));
        message.supprimer(8);
        System.out.println("Je suis "+getNom()+" et j'ai reçu "+message.size()+" octets : " +message);
     	((Transport)plusUn).receiveMessage(source, message);
    }  

}
