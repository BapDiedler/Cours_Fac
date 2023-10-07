package reseau.clientsServeurs;

import reseau.couches.Application;
import reseau.Message;
import reseau.adresses.Adresse;
import reseau.*;
import reseau.couches.Transport;

/**
 * @author martine
 */
public class ClientDNS extends Application {

	private Adresse adrDNS;
	private Machine mach;
	
    public ClientDNS(int port, Machine m, Adresse adr) {
        super(port) ;
    	mach = m;
    	adrDNS = adr;
    }
   
    /**
     * Je reçois un message de la couche inférieure 
     * @param source adresse de la source
     * @param portSource port de la source
     * @param message message reçu
     */
    //@Override
    public void sendMessage(String nomDest, int portDest, Message message) {
        resultat = null ;
        message = new Message(nomDest);
        // Afficher une trace de l'envoi
        System.out.println("Je suis "+getNom()+" et j'envoie "+message.size()+" octets : " +message);
        // Transmettre à la couche Transport
        ((Transport)moinsUn).sendMessage(port, adrDNS, portDest, message);
    }
}