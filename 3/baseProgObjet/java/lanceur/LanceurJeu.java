import java.lang.reflect.*;
import java.util.Arrays;

/**
 * La classe LanceurJeu permet de démarrer un jeu à deux joueurs, défini par une classe possédant
 *      -un constructeur avec 0,...,k entier en paramètres
 *      -une méthode void unePartie()
 */

public class LanceurJeu {
    
    private Object jeu;

    private Object creatInstance(Constructor<?> co, int[] val) throws ExceptionJeu{
        try {
            Object[] paramCopy = new Object[val.length];
            for(int i=0; i<val.length; i++){
                paramCopy[i] = val[i];
            }
            return co.newInstance(paramCopy);
        } catch (RuntimeException e) {
            throw new ExceptionJeu("les arguments ne sont pas valide");
        } catch (InstantiationException e){
            throw new ExceptionJeu(("instanciation impossible"));
        } catch (IllegalAccessException e){
            throw new ExceptionJeu(("l'accès au constructeur est impossible"));
        } catch (InvocationTargetException e){
            throw new ExceptionJeu((e.getMessage()));
        }
    }

    private Object creatConstructor(Class<?> c, Class<?>[] tp, String[] args) throws ExceptionJeu{
        try {
            Constructor<?> co = c.getConstructor(tp);
            int[] val = new int[args.length - 1];
            for (int i = 0; i < args.length-1; i++) {
                val[i] = Integer.parseInt(args[i+1]);
            }
            return creatInstance(co, val);
        }catch (ExceptionJeu e){
            throw new ExceptionJeu(e.getMessage());
        } catch (NoSuchMethodException e) {
            throw new ExceptionJeu("le constructeur n'est pas valide");
        }
    }

    private Class<?>[] initTabClass(int nbValeurs){
        Class<?>[] tp = new Class[nbValeurs];
        for(int i=0; i<nbValeurs; i++){
            tp[i] = int.class;
        }
        return tp;
    }

    public LanceurJeu(String[] args) throws ExceptionJeu {
        if(args.length != 0){
            try {
                Class<?> c = Class.forName(args[0]);
                Class<?>[] tp = initTabClass(args.length-1);
                this.jeu = creatConstructor(c,tp,args);
            }catch (ClassNotFoundException ex){
                throw new ExceptionJeu("Classe de jeu non trouvée");
            } catch (ExceptionJeu e) {
                throw new ExceptionJeu(e.getMessage());
            }
        }else{
            throw new ExceptionJeu("aucun argument a été entré");
        }
    }

    public void jouer() throws ExceptionJeu{
        try {
            Method m = jeu.getClass().getMethod("unePartie");
            m.invoke(this.jeu) ;
        } catch (NoSuchMethodException e) {
            throw new ExceptionJeu("la méthode demandée n'existe pas");
        } catch (InvocationTargetException | IllegalAccessException e) {
            throw new RuntimeException(e);
        }

    }

    public static void main(String[] args){
        try {
            LanceurJeu j = new LanceurJeu(args);
            j.jouer();
        }catch (ExceptionJeu e){
            System.err.println(e.getMessage());
        }
        System.out.println("Jeu terminé");
    }
}
