/*
question1: il y a 16 processus générés par le programme si on compte le processus principal.
question2: à moins d'avoir une erreur sur le exec le programme ne fera jamais les appelles aux forks.
    Il y aura donc un seul processus qui va boucler à l'infini.
question3: on aura deux processus qui vont appeler le exec et qui vont recommencer. On a donc comme 
    avant sauf qu'il y a une création exponentielle de processus.
*/
