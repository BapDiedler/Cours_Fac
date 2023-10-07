#include <stdio.h>
#include <stdlib.h>

int v(int i){
    if(i==0){
        return 42;
    }
    int val=42;
    int tmp;
    for(int j = 0; j<i; j++){
        tmp = val;
        val = (101833*tmp + 1000000000007)%1000000000007;
    }
    return val;
}

int u(int t){
    return v(t%1000003);
}

int nb(int L, int Q){
    int cpt=0;
    for(int q=0; q<Q; q++){
        for(int c=0; c<L; c++){
             if(u(Q*L+u(q*L+c))%2 == 1){
                cpt++;
            }
        }
    }
    return cpt;
}

int main(void){
    for(int i=0; i<50; i++){
        printf("%d\n",u(i)%1000);
    }
    return 0;
}