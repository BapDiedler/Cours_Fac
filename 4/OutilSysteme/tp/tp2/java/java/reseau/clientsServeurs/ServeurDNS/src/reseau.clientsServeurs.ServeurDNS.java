package reseau.clientsServeurs;

import reseau.couches.Application;
import reseau.Message;
import reseau.tables.*;
import reseau.couches.Application;
import reseau.Machine;
/**
 * @author martine
 */
public class ServeurDNS extends Application {
    
    private Machine machDNS;
    private DNS dns;
    private Application client;
    /**
     * @param port le port dans la couche transport
     */
    public ServeurDNS(int port, Machine m, Application clientDNS, DNS dns) {
        super(port);
        machDNS = m;
        client = clientDNS;
        this.dns = dns;
    }

    /**
     * @param message entier à convertir en * 2
     * @return entier * 2
     */
    @Override
    protected Message traiter(Message message) {
        String nom = message.extraireChaine() ;
        System.out.println("Je trouve l'IP de " + nom+" ...");
        return new Message(dns.getAdresse(nom));
    }

}
