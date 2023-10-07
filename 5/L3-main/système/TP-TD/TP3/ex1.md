# Exercice 1.

1. Une section critique est une section du code qui ne doit pas être interrompue par une interruption.

1. - L’exécution atomique : l’exécution de la section critique doit être atomique, c’est-à-dire que l’exécution de la section critique ne doit pas être interrompue par une interruption.
    - L’exécution exclusive : l’exécution de la section critique ne doit pas être interrompue par une autre section critique.
    - L’exécution rapide : l’exécution de la section critique doit être rapide.

1. Les incovenients du Mutex sont que le thread qui a le lock ne peut pas être interrompu.