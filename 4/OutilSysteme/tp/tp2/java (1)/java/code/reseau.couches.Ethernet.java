package reseau.couches;

import reseau.Message;
import reseau.adresses.AdresseMac;

/**
 * @author martine
 */
public class Ethernet extends Liaison {
    
    public Ethernet(AdresseMac am ) {
        super(am); 
    }
        
    @Override
    public void sendMessage(AdresseMac dest, Message message) {
    	//throw new UnsupportedOperationException("Not supported yet.");
        Message enTete = new Message(this.getEntete(dest,  message));
        enTete.ajouter(message);
        message = new Message(enTete); 
        System.out.println("Je suis "+getNom()+" et j'envoie "+message.size()+" octets : " +message);
     	//voisin.receiveMessage(message);
     	lan.sendTrame(message);
    }
  
    /**
     * Je reçois un message de la couche moinsUn
     * @param message le message reçu
     */
    @Override
    public void receiveMessage(Message message) {
        //throw new UnsupportedOperationException("Not supported yet.");  
        AdresseMac dest = message.extraireAdresseMac();
        if(!dest.equals( adrMac)){
        	throw new UnsupportedOperationException("Bad macAdresse.");
        	}
        message.supprimer(6);
        message.supprimer(6);
        System.out.println("Je suis "+getNom()+" et j'ai reçu "+message.size()+" octets : " +message);
     	((Reseau)plusUn).receiveMessage(message);
    }

    @Override
    protected Message getEntete(AdresseMac dest, Message message) {
        // Adresse Mac destination (48 bits), adresse Mac source (48 bits)
        Message enTete = new Message();
        enTete.ajouter(dest);
        enTete.ajouter(adrMac);
        return enTete;
    }

}
