import math

def u_bare(n):
    M = (2**31) - 1
    val = 42
    for _ in range(n):
        val = (16807 * val + 17 ) % M
    return val

def u(n):
    return u_bare(n%999983)


def C_aux(a,b):
    return (2*a + b)%997

def C(liste):
    val = 0
    for num in liste:
        val = C_aux(val,num)
    return val

def D(m,n):
    liste = [0]*m
    for i in range(1,m):
        if u(n+i-1)%2 == 0:
            liste[i] = liste[i-1] - 1
        else:
            liste[i] = liste[i-1] + 1
    return liste

def I(liste):
    val = 0
    for i in range(len(liste)-2):
        val+=((liste[i+1]-liste[i] +1)/2) * 2**i
    return val%997

def T_aux(m,n,i):
    arbre = []
    if m == 1 :
        return arbre
    elif m == 2 or u(n)%3 == 0 :
        arbre.append([m-1,n+1,i+1])
        arbre.extend(T_aux(m-1,n+1,i+1))
        return arbre
    arbre.append([math.floor((m-1)/2),n+1,i+1])
    arbre.extend(T_aux(math.floor((m-1)/2),n+1,i+1))
    arbre.append([math.ceil((m-1)/2),math.floor(n+1+(m-1)/2),math.floor(i+1+(m-1)/2)])
    arbre.extend(T_aux(math.ceil((m-1)/2),math.floor(n+1+(m-1)/2),math.floor(i+1+(m-1)/2)))
    return arbre


def T(m,n):
    arbre = [[m,n,0]]
    arbre.extend(T_aux(m,n,0))
    return arbre


print(T(4,17))