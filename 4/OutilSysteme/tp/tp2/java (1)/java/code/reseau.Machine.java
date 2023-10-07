package reseau;

import reseau.Message;
import reseau.adresses.*;
import reseau.couches.*;
import reseau.tables.*;
/**
 * @author martine
 */
public  class Machine {
	private String nom;
	private Adresse adresseIP;
	private AdresseMac adresseMac;
	private Adresse masque;
	private Liaison ethernet;
    private Reseau ip;
    private Transport udp;
        
	
    public Machine(String nomMachine, Adresse adrIP,  Adresse masq){
    	ARP arp = new ARP();
       
    	nom = nomMachine;
    	adresseIP = new Adresse(adrIP);
    	adresseMac = new AdresseMac(arp.get(adrIP));
    	masque = new Adresse(masq);
    	ethernet = new Ethernet(adresseMac);
        ip = new IP(adrIP, masq);
        udp = new UDP();
       
        // Création des liaisons entre les couches
        ethernet.setCoucheSuperieure(ip);
        ip.setCouches(udp,ethernet);
        udp.setCoucheInferieure(ip);
    }
    
    public void ajouter(int port, Application appli){
    	appli.setCoucheInferieure(udp);
    	udp.ajouter(port,appli);
        
    }
    
    public AdresseMac getAdresseMac(){
    	return adresseMac;
    }
    public String getNom(){
    	return nom;
    	}
    
    public Liaison getCoucheLiaison(){
    	return ethernet;
    }
}
         
          
