package reseau.couches;

import java.util.HashMap;
import reseau.Message;
 
import reseau.adresses.Adresse;

/**
 * @author martine
 * @version 19 nov. 2014
 */

public abstract class Transport extends Couche {
    
    private HashMap<Integer, Application> lesApplications ;     // Accès aux applications via le port
    
    public Transport() {
        lesApplications = new HashMap<>();
    }

    /**
     * Ajouter une nouvelle application avec son no de port
     * @param port port de l'application
     * @param appli  application associée au port
     */
    public void ajouter(int port, Application appli) {
        lesApplications.put(port, appli) ;
    }
    
    /**
     * @param port port de l'application
     * @return l'application liée au port donné
     */
    public Application getApplication(int port) {
        Application a = lesApplications.get(port) ;
        if (a==null) throw new IllegalArgumentException("Port inconnu "+port);
        return a;
    }
   
    /**
     * Envoyer un message à un destinataire précis
     * @param portSource port source de l'application
     * @param dest adresse destination
     * @param portDest port destination de l'application
     * @param message message à transmettre
     */
    public void sendMessage(int portSource, Adresse dest, int portDest, Message message) {
        //throw new UnsupportedOperationException("Not supported yet.");
        Message enTete = new Message(this.getEntete(portSource,dest,  portDest,  message));
        enTete.ajouter(message);
        message = new Message(enTete); 
        System.out.println("Je suis "+getNom()+" et j'envoie "+message.size()+" octets : " +message);
        ((Reseau)moinsUn).sendMessage(dest,  message);
        
    }
 
    public void receiveMessage(Adresse source, Message message) {
        int portSource, portDest;
        portSource = message.extraireEntier(2);
        portDest = message.extraireEntier(2);
        message.supprimer(4);
        System.out.println("Je suis "+getNom()+" et j'ai reçu "+message.size()+" octets : " +message);
     	Application appli = getApplication(portDest);
     	appli.receiveMessage(source,portSource,message);
    }

    /**
     * Construit l'entête du message
     * @param portSource port source de l'application
     * @param dest adresse destination
     * @param portDest port destination de l'application
     * @param message message à transmettre
     * @return entête construite
     */
    protected abstract Message getEntete(int portSource, Adresse dest, int portDest, Message message) ;
    
}
