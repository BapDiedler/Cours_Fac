package glaces;

import glaces.Ocean;
import java.util.Scanner;
import glaces.Poisson;

import glaces.ArcticImage;

public class Jeu {
    private Ocean ocean;

    //constructeur
    public Jeu(){
        this.ocean = new Ocean(3,900,900);
    }

    public void jouer(){
        Scanner scan = new Scanner(System.in);
        boolean quit = true;
        int[][] color = this.ocean.getColors();
        ArcticImage image = new ArcticImage(this.ocean.getWidth(),this.ocean.getHeight());
        Pingouin ping = this.ocean.getPingouin();
        int cpt = 0;//compteur de tour
        while(quit){
            System.out.println("d : droite\nq : gauche\nz : haut\ns : bas\nf : quitter");
            color = this.ocean.getColors();
            image.setColors(color);
            String choix = scan.next();
            //differentes actions possible
            switch(choix.toLowerCase()){
                case "q"://déplacer sur l'abscisse
                    if(!((ping.getAbscisse()-ping.getTaille())<0)){
                        ping.deplacerAbscisse(-ping.getTaille());
                    }
                    break;
                case "d":
                    if(!((ping.getAbscisse()+2*ping.getTaille())>this.ocean.getWidth())){
                        ping.deplacerAbscisse(ping.getTaille());
                    }
                    break;
                case "z"://déplacer sur l'ordonnée
                    if(!((ping.getOrdonnee()+2*ping.getTaille())>this.ocean.getHeight())){
                        ping.deplacerOrdonnee(ping.getTaille());
                    }
                    break;
                case "s":
                    if(!((ping.getOrdonnee()-ping.getTaille())<0)){
                        ping.deplacerOrdonnee(-ping.getTaille());
                    }
                    break;
                case "f"://quitter le jeu
                    quit = false;
                    image.fermer();
                    break;
                default:
                    break;
            }
            //cas ou le pingouin se trouve sur un iceberg
            for(int i=0; i<ocean.getCount(); i++){
                ping.onIceberg(ocean.getIceberg2d(i));
            }
            //fonte des icebergs
            ocean.Fondre(0.005);
            //boucle qui cherche les poissons qui sont mangés
            for(int i=0; i<20; i++){
                ocean.getPoisson(i).estMange(ping);
                cpt=0;
            }
            ping.estFatigue(cpt);
            //déplacement des poissons dans l'eau vers la droite
            for(int i=0; i<ocean.getCountPoisson()/4; i++){
                if(!ocean.getPoisson(i).outOfOcean(ocean.getWidth(), ocean.getHeight())){
                    ocean.getPoisson(i).deplacer(ocean.getPoisson(i).getAbscisse()+ocean.getPoisson(i).getLargeur(),ocean.getPoisson(i).getOrdonnee());
                }
                else{
                    ocean.getPoisson(i).deplacer(0, ocean.getPoisson(i).getOrdonnee());
                }
            }
            //déplacement des poissons dans l'eau vers la gauche
            for(int i=ocean.getCountPoisson()/4; i<ocean.getCountPoisson()/2; i++){
                if(!ocean.getPoisson(i).outOfOcean(ocean.getWidth(), ocean.getHeight())){
                    ocean.getPoisson(i).deplacer(ocean.getPoisson(i).getAbscisse()-ocean.getPoisson(i).getLargeur(),ocean.getPoisson(i).getOrdonnee());
                }
                else{
                    ocean.getPoisson(i).deplacer(ocean.getWidth()-ocean.getPoisson(i).getLargeur()-2, ocean.getPoisson(i).getOrdonnee());
                }
            }
            //déplacement des poissons dans l'eau vers le haut
            for(int i=ocean.getCountPoisson()/2; i<3*ocean.getCountPoisson()/4; i++){
                if(!ocean.getPoisson(i).outOfOcean(ocean.getWidth(), ocean.getHeight())){
                    ocean.getPoisson(i).deplacer(ocean.getPoisson(i).getAbscisse(),ocean.getPoisson(i).getHauteur()+ocean.getPoisson(i).getOrdonnee());
                }
                else{
                    ocean.getPoisson(i).deplacer(ocean.getPoisson(i).getAbscisse(),0);
                }
            }
            //déplacement des poissons dans l'eau vers le bas
            for(int i=3*ocean.getCountPoisson()/4; i<ocean.getCountPoisson(); i++){
                if(!ocean.getPoisson(i).outOfOcean(ocean.getWidth(), ocean.getHeight())){
                    ocean.getPoisson(i).deplacer(ocean.getPoisson(i).getAbscisse(),-ocean.getPoisson(i).getHauteur()+ocean.getPoisson(i).getOrdonnee());
                }
                else{
                    ocean.getPoisson(i).deplacer(ocean.getPoisson(i).getAbscisse(), ocean.getHeight()-ocean.getPoisson(i).getHauteur()-2);
                }
            }
            cpt++;
        }
        //scan.close();
    }

    public static void main(String[] args){
        Jeu jeu= new Jeu();
        jeu.jouer();
    }
}
