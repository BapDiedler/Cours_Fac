package reseau.tests;


import reseau.*;
import reseau.adresses.Adresse;
import reseau.adresses.Octet;

public class TestMessage {

    private static void testMessage1(){
        Message mes;
        short val, val2;

        val = 66;
        val2 = 44;
        mes = new Message(val,val2);
        assert mes.extraireEntier(0)==66*256+44:"le constructeur ne marche pas";
    }

    private static void testMessage2(){
        Message mes;
        Adresse adr;

        adr = new Adresse("254.254.0.8");
        mes = new Message(adr);
        assert mes.extraireAdresse(4).toString().equals("254.254.0.8"):"le constructeur ne marche pas";
    }

    private static void testAjouter1(){
        Message mes;
        short val, val2;

        val = 66;
        val2 = 44;
        mes = new Message(val);
        mes.ajouter(val2);
        assert mes.extraireEntier(0)==66*256+44:"l'ajout de short ne marche pas";
    }
    
    private static void testAjouter2(){
        Message mes, mes2;
        short val, val2, val3;

        val = 66;
        val2 = 44;
        val3 = 66;
        mes = new Message(val,val2);
        mes2 = new Message(val3);
        mes.ajouter(mes2);
        assert mes.toString().equals("664466"):"l'ajout de message ne marche pas";
    }

    private static void testAjouter3(){
        Message mes;
        int val, val2;

        val = 66;
        val2 = 66;
        mes = new Message(val,val2);
        mes.ajouter(67);
        assert mes.extraireEntier(4)==67;
    }

    private static void testAjouter4(){
        Message mes;
        Octet oc1, oc2;

        oc1 = new Octet(0);
        mes = new Message();
        oc2 = new Octet(0);
        mes.ajouter(oc1);
        mes.ajouter(oc2);
        assert mes.extraireEntier(0)==0;
    }

    private static void testAjouter5(){
        Message mes;
        Adresse ad;

        mes = new Message();
        ad = new Adresse("0.255.0.255");
        mes.ajouter(ad);
        assert mes.extraireEntier(0)==255;
    }

    private static void testMessageString(){
        Message mes;

        mes = new Message("abc");
        assert mes.extraireChaine().equals("abc"):"l'ajout de message ne marche pas";
    }

    private static void testMessage3(){
        Message mes;
        int val = 1025;
        mes = new Message(val);
        assert mes.size()==2:"il n'y a pas le bon nombre d'octet";
        assert mes.extraireEntier(0)==1025;

    }

    private static void testSupprimer1(){
        Message mes;
        int v1 = 10, v2 = 34;

        mes = new Message(v1, v2);
        mes.supprimer(0);
        assert mes.size()==2:"il n'y a pas le bon nombre d'octet";
        assert mes.extraireEntier(0)!=10:"l'octet n'a pas été supprimer";
    }

    private static void testSupprimer2(){
        Message mes;

        mes = new Message(278, 10, 678, 567);
        mes.supprimer(1,2);
        assert mes.extraireEntier(1)!=278:"l'octet n'a pas été supprimer";
    }

    private static void testAugmenter(){
        Message mes;

        mes = new Message(10, 20, 30, 40);
        mes.augmenter(5, 4, 26);
        assert mes.extraireEntier(0)==15:"l'octet n'a pas été augmenter";
        assert mes.extraireEntier(2)==25:"l'octet n'a pas été augmenter";
        assert mes.extraireEntier(4)==30:"l'octet a été augmenter";
    }

    private static void testAjouterAdresse(){
        Message mes;
        Adresse adr;

        adr = new Adresse(16);
        mes = new Message(2,4,5,5);
        mes.ajouter(adr);
        assert mes.extraireEntier(mes.size()-2)==0;
    }

    private static void testExtraireChaine(){
        Message mes;
        short a = 65, b = 66 , c = 10;
        
        mes = new Message(a,b);
        assert mes.extraireChaine().equals("AB"):"les caractères ne sont pas transformés";
        mes = new Message(a,b,c);
        assert mes.extraireChaine() == null :"en cas de non conversion le return n'est pas null";
    }

    private static void testMessage4(){
        Message mes1, mes2;
        short a = 65, b = 66 , c = 10;

        mes1 = new Message(a,b,c);
        mes2 = new Message(mes1);
        assert !mes1.equals(mes2);
        assert mes1.extraireEntier(0) == mes2.extraireEntier(0);
    }

    private static void testMessage5(){
        Message mes;

        mes = new Message();

        assert mes.size()==0;
    }

    private static void testExtraireEntier(){
        Message mes;
        int val = 1025;

        mes = new Message(val);
        assert mes.extraireEntier(0)==1025;
    }

    private static void testExtraireAdresse(){
        Message mes;
        Adresse ad, ad2;

        mes = new Message();
        ad = new Adresse(16);
        mes.ajouter(ad);
        ad2 = new Adresse(mes.extraireAdresse(2));
        assert ad.toString().equals("0.0"):"l'affichage de l'adresse ne marche pas";
        assert ad2.toString().equals("0.0"):"Extraire adresse ne marche pas";
    }


    public static void main(String[] args) {
        testMessage1();
        testMessage2();
        testMessage3();
        testMessage4();
        testMessage5();


        testAjouter1();
        testAjouter2();
        testAjouter3();
        testAjouter4();
        testAjouter5();


        testExtraireChaine();
        testExtraireEntier();
        testExtraireAdresse();

        testMessageString();
        testSupprimer1();
        testSupprimer2();
        testAugmenter();
        testAjouterAdresse();
    }
}
