package reseau.tests;

import reseau.adresses.*;

public class TestAdresse {
    public static void main(String[] args) {
        testGetNbreOctetsAdresse() ;
        testAdresse1();
        testAdresse2();
        testSetOctet1();
        testSetOctet2();
        testToString();
        testInverser();
        testMasque();
        testAdresse3();
    }

    private static void testAdresse3(){
        Adresse a;
        String ad = "211.0.2.123";

        a = new Adresse(ad);
        assert a.toString().equals(ad) :"l'adresse avec le string ne marche pas";
    }

    private static void testToString(){
        Adresse a;

        a = new Adresse(16, 10);
        assert a.toString().equals("255.192"):"le toString ne marche pas";
    }

    private static void testInverser(){
        Adresse a;
        Octet oc;

        a = new Adresse(16, 8);
        a.inverser();
        assert a.toString().equals("0.255"):"les bits ne se sont pas inversé";
    }

    private static void testMasque(){
        Adresse a, a2, a3;
        Octet oc, oc2;


        oc = new Octet(128);
        oc2 = new Octet(3);
        a = new Adresse(oc);
        a2 = new Adresse(oc2);
        a3 = new Adresse(new Octet(128));
        a.masquer(a2);
        assert !a.toString().equals(a3.toString()):"la fonction ne marche pas";
    }

    private static void testAdresse1(){
        Octet oc, oc2;
        Adresse a;

        oc = new Octet();
        oc2 = new Octet();
        a = new Adresse(oc);
        int nbOct = a.getNbreOctets();
        assert nbOct==1:"le nombre d'octet est incorrect";
        a = new Adresse(oc, oc2);
        nbOct = a.getNbreOctets();
        assert nbOct==2:"le nombre d'octet est incorrect";
    }

    private static void testGetNbreOctetsAdresse() {
        Adresse a ;
        int res ;

        // adresse créée vide
        a = new Adresse(16) ;
        res = a.getNbreOctets() ;
        assert res==2 :"Nombre d'octets incorrect" ;
    }

    private static void testAdresse2(){
        Adresse a;
        int nbOct;
        Octet oc;

        a = new Adresse(16, 1);
        nbOct = a.getNbreOctets();
        oc = a.getOctet(0);
        assert oc.getValue()==128:"la valeur du première octet est fausse";
        assert nbOct==2:"le nombre d'octet est incorrect";
        a= new Adresse(16,10);
        nbOct = a.getNbreOctets();
        oc = a.getOctet(0);
        assert oc.getValue()==255:"la valeur du première octet est fausse";
        assert nbOct==2:"le nombre d'octet est incorrect";
    }

    private static void testSetOctet1(){
        Adresse a;
        Octet oc;

        a = new Adresse(16) ;
        oc = new Octet(10);
        a.setOctet(oc, 0);
        assert oc.getValue()==a.getOctet(0).getValue():"l'octet n'a pas ete changé";
    }

    private static void testSetOctet2(){
        Adresse a;
        int nbOct;
        Octet oc, oc2;

        //test numero 1
        a = new Adresse(16) ;
        oc = new Octet(10);
        a.setOctets(oc);
        assert oc.getValue()==a.getOctet(0).getValue():"l'octet n'a pas ete changé";

        //test numero 2
        a = new Adresse(16) ;
        oc = new Octet(10);
        oc2 = new Octet(12);
        a.setOctets(oc, oc2);
        assert oc.getValue()==a.getOctet(0).getValue():"l'octet n'a pas ete changé";
        assert oc2.getValue()==a.getOctet(1).getValue():"l'octet n'a pas ete changé";
    }
}
