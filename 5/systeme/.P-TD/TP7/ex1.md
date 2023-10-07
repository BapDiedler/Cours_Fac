# Exercice 1

1. Pour charger le FCB du fichier en mémoire

1. lecture/écriture/repositionnement

1. File Control Block: 
    - strucutre pour stocker les informations sur le fichier pour ça gestion

1. 
|          | avantage                                                       | inconvénients                                                                                                                           |
|----------|----------------------------------------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------|
| Contiguë | - accèse au bloc suivant: facile<br>- Segfault facile          | - Fragmentation<br>- Conaître la taille de fichier à l'avance<br>- Recherche esapce libre coûteurx<br>- Stratégie d'alocation à definir |
| Chaîné   | - Pas de Fragmentation<br>- FCB: courte<br>- Taille quelconque | - Parcours coûteux: Accès sequentiel<br>- Fiabilit<br>- Esapce utilisé par les pointeurs                                                |
| Indexée  | - Parcours rapide<br>- Pas de Fragmentation                    | - 1 bloc de perdu<br>- Taille de fichier limité                                                                                         |