#-------------GRAPHES ORIENTES----------------#
#Avec matrices d'adjacences : la diagonale contient les valeurs des sommets

def Matrice(n):
    #Entrée : un entier
    #Sortie : une matrice de taille nxn avec des 0 partout
    return [[0]*n for i in range(0,n)]

class Graphe:
    def __init__(self, val):
        #Entrée : un entier
        #Sortie : rien
        #Crée un graphe avec un sommet de valeur val définit par une matrice 1x1
        self.matrice = Matrice(1)
        self.matrice[0][0] = val
        self.nb_sommets = 1

    def get_nb_sommets(self):
        #====A FAIRE===#
        return 0

    def get_nb_arete(self):
        #====A FAIRE===#
        return 0

    def get_sommet_num(self, i):
        #Entrée : l'id d'un sommet
        #Sortie : la valeur de ce sommet, un entier
        return self.matrice[i][i]

    def add_sommet(self, val):
        #Entrée : un entier, une valeur
        #Sortie : rien
        #====A FAIRE===#
        #Incide : créer une matrice de taille n+1xn+1, tout recopier puis ajouter le sommet.

    def add_arete(self, v, w):
        #Entrées : deux entiers, les Id des sommets
        #Sortie : rien
        #Ajoute l'arête orienté. Les poids sur les arêtes ne sont pas gérés.
        self.matrice[v][w] = 1

    def succ(self, i):
        #Entrée : l'id d'un sommet, un entier
        #Sortie : la liste des numéros des sommets, un tableau d'entiers
        #====A FAIRE===#
        return []



def DFS(G, v):
    #rien ne doit changer par rapport à la v1
    p = [v]
    n = []
    while len(p)>0:
        v = p.pop()
        print(v)
        for w in G.succ(v):
            if not(w in p) and not(w in n):
                p.append(w)
        n.append(v)
    n
    return n

#ici non plus rien ne doit changer par rapport à la v1
#création du graphe :
#       5
#       |
#       8
#       |
#       5
#     /  \
#    2   6
G = Graphe(5)
G.add_sommet(8)
G.add_sommet(5)
G.add_sommet(2)
G.add_sommet(6)
print("mat : ",G.matrice)
#arête = id
G.add_arete(0,1)
G.add_arete(1,2)
G.add_arete(2,3)
G.add_arete(2,4)
print("Nb sommets : ",G.get_nb_sommets())
print("Nb arrêtes : ", G.get_nb_arete())
print("Valeur sommet num 1 : ", G.get_sommet_num(1))

print("succ de 2 : ")
for w in G.succ(2):
    print(w)

print("===DFS====")
n = DFS(G,0)
print("liste postfixe inversée : ", n)
