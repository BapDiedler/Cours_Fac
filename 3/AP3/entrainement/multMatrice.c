#include <stdlib.h>
#include <stdio.h>


/**
 * @brief fonction qui multiplie deux matrices
 * 
 * @param Mat1 
 * @param Mat2 
 * @return int[3][3] 
 */
int** multMat(int** Mat1, int** Mat2){
    int matRes[3][3];
    int tmp;
    for(int i=0; i<3; ++i){//colonne de la nouvelle matrice
        for(int j=0; j<3; ++j){//ligne de la nouvelle matrice
            tmp=0;
            for(int k=0; k<3; ++k){//colonne de la matrice 1 et ligne de la matrice 2
                tmp+=Mat1[j][k]*Mat2[k][i];
            }
            matRes[i][j]=tmp;
        }
    }
    return matRes;
}

int main(int argc, char ** argv){
    int Mat1[3][3];
    int** Mat2 = multMat(Mat1,Mat1);
    for(int i=0; i<3; ++i){//colonne de la nouvelle matrice
        for(int j=0; j<3; ++j){//ligne de la nouvelle matrice
            printf("%d",Mat2[j][i]);
        }
    }
    return EXIT_SUCCESS;
}