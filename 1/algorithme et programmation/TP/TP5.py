def est_la(tab,t):
    for ele in tab:
        if(ele==t):
            print("vrai")
            return 1
    print("faux")
    return 1

def prem_rec(tab,t):
    index=0
    for i in tab:
        if i==t:
            return index
        index+=1
    return -1

def seq(tab):
    tmp=min(tab)
    long=0
    for ele in tab:
        if ele>=tmp:
            long+=1
            tmp=ele
        else:
            long=0
            tmp=min(tab)
            


def test_est_la(tab):
    est_la(tab,2)

def test_prem_rec(tab):
    print("la valeur est :",prem_rec(tab,2))

nb_case=int (input("entrez un nombre de cases pour le tableau entre 0 et 100: "))
if(nb_case>0 and nb_case<100):
    tab=[None]*(nb_case-1)
else:
    print("le nombre de cases ne correspond pas !!")
n=0
while n-1!=nb_case:
    tab[n]=input("entrez la valeur de la case")
    n+=1
#test_est_la(tab)
test_prem_rec(tab)