def u(n):
    val = 37
    for _ in range(n):
        val = 3321 * val + 5701
    return val

def cardinal_F(n):
    cpt=0
    F = [False]*n
    for i in range(n):
        if u(i)%n <= n/3:
            F[i] = True
            cpt+=1
    return cpt, F


print(cardinal_F(19));  