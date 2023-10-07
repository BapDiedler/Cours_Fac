/**
1: Une section critique est un passage dans le code celui-ci ne peut pas être interrompu. Que se soit par des interruption ou des exceptions.
                                  C'est une zone de code où plusieurs threads peuvent accéder en même temps à la même zone de mémoire partagée.
                                  Un seul thread à la fois peut y accéder.
2: Les propriétés attendues sont: exclusion mutuelle: un seul thread à la fois dans la section critique.
                                  déroulement: Un thread n’a pas d’influence sur le choix de qui peut entrer dans la section critique.
                                  vivacité: Un thread entre en section critique après un temps borné.
3: Les inconvéniants du Mutex sont : il doit connaître en avance le nombre de threads.
                                  Et de plus les threads en attente font de l'attente active.
*/