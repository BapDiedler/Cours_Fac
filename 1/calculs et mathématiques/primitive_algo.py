#algo qui donne les primitives de bases
def derivee(fonction):
    if fonction=='x':
        return '1'
    elif fonction=='x**n':
        return 'n(x**(n-1))'
    elif fonction=='sqrt(x)':
        return '1/(2sqrt(x))'
    elif fonction== '1/x':
        return '-1/(x**2)'
    elif fonction=='cos(x)':
        return '-sin(x)'
    elif fonction=='sin(x)':
        return 'cos(x)'

fonction=str(input("entrer un primitive de base: "))
print("Sa primitive est: ",derivee(fonction))