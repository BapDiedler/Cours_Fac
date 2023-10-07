package testAwaz;

import java.util.Scanner;
import awaz.Awaz;
import awaz.AwazImage;

public class Menu {
    public static void main(String argv[]){
        boolean stop = false;
        Scanner scan = new Scanner(System.in);
        String valScan;
        Awaz melodie = new Awaz();
        do{//affichage de toute les options possibles
            System.out.println("\t ___**Menu principal**___\n");
            System.out.println("___entrez stop pour arreter l'algorithme");
            System.out.println("___entrez add pour ajouter une note");
            System.out.println("___entrez transposer pour transposer la partition");
            System.out.println("___entrez afficher pour afficher la partition");
            System.out.println("___entrez sauvegarde pour sauvegarder sa partition");
            System.out.println("___entrez estVide pour savoir si la partition est vide");
            System.out.println("___entrez lastNote pour avoir la derniere note de la partition");
            System.out.println("___entrez iemeNote pour avoir la ieme note de la partition");
            System.out.println("___entrez lecTitre pour avoir le titre de la partition");
            System.out.println("___entrez ecrTrite pour donner un titre à la partition");
            System.out.println("___entrez nbNotes pour obtenir le nombre de notes de la partition");
            System.out.println("___entrez new pour avoir une nouvelle partition");
            System.out.println("___entrez ouvrir pour utiliser une partition sauvegardee");
            System.out.println("___entrez passABC pour passer en format ABC");
            valScan = scan.next();
            if(valScan.equals("stop")){//pour arreter le programme
                System.out.println("___voulez vous vraiment arreter (o/n) :");
                valScan = scan.next();
                if(valScan.equals("o")){
                    stop = true;
                }
            }
            else if(valScan.equals("add")){//pour ajouter une note
                System.out.println("___entrez la note à ajouter :");
                valScan = scan.next();
                melodie.add(valScan);
                System.out.println("___la note a bien été ajouté");
            }
            else if(valScan.equals("transposer")){//pour transposer la partition
                System.out.println("___entrez le ton");
                int valTmp = scan.nextInt();
                melodie.transposer(valTmp);
                System.out.println("___la partition a bien été transposée");
            }
            else if(valScan.equals("afficher")){//pour afficher la partition
                System.out.print("___la melodie est: "+melodie.toString()+"\n");
            }
            else if(valScan.equals("sauvegarde")){//pour sauvegarder la partition
                melodie.enregistrer(melodie.getTitre());
                System.out.println("___la partition a bien été sauvegarder");
            }
            else if(valScan.equals("estVide")){//pour savoir si la partition est vide
                if(melodie.estVide()){
                    System.out.println("___la partition est bien vide");
                }
                else{
                    System.out.println("___la partition n'est pas vide");
                }
            }
            else if(valScan.equals("lastNote")){//pour voir la derniere des notes
                System.out.println("___la derniere note est :"+melodie.getLast());
            }
            else if(valScan.equals("lecTitre")){//pour voir le titre
                System.out.println("___le titre est :"+melodie.getTitre());
            }
            else if(valScan.equals("iemeNote")){//pour voir la ieme note
                System.out.println("___entrez la position de la note recherchée");
                int valTmp = scan.nextInt();
                System.out.println("___la "+valTmp+"eme note est: "+melodie.ieme(valTmp));
            }
            else if(valScan.equals("ecrTitre")){//changer le titre
                System.out.println("___entrez le nom du fichier :");
                valScan = scan.nextLine();
                melodie.setTitre(valScan);
                System.out.println("___le nom a bien ete modifie");
            }
            else if(valScan.equals("nbNotes")){//afficher le nombre de note
                System.out.println("___le nombre de notes est de :"+melodie.nbNotes());
            }
            else if(valScan.equals("new")){//nouvelle partition
                melodie.nouveau();
                System.out.println("___la nouvelle partion a ete cree");
            }
            else if(valScan.equals("ouvrir")){//utiliser une partition deja sauvegarde
                System.out.println("___entrez le nom du fichier");
                valScan = scan.next();
                melodie.ouvrir(valScan);
                System.out.println("___le fichier est bien ouvert");
            }
            else if(valScan.equals("passABC")){//utiliser pour passer une partition en format ABC
                melodie.toABC();
                System.out.println("___le fichier est transformé");
            }
            else{//utiliser dans le cas où le mot est pas reconnu
                System.out.println("___le mot que vous avez entre n'est pas reconnu");
            }
        }while(!stop);
        scan.close();
        System.out.println("\t ___Le programme a fini d'etre execute ;)___");
    }
}
