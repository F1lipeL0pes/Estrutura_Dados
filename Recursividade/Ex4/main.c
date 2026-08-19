#include <stdio.h>
#include <stdlib.h>

int verificaMenorIterativo(int vetor[], int t){
    int menor;
    for(int i = 0; i < t; i++){
        if(i == 0 || vetor[i] < menor)
            menor = vetor[i];
    }
    return menor;
}

int verificaMenorRecursivo(int vetor[], int t){
    int menor = vetor[t-1];

    if (t == 1)
        return menor;

    if (verificaMenorRecursivo(vetor, t-1) < menor)
        menor = verificaMenorRecursivo(vetor, t-1);

    return menor;
}



int main()
{
    int vetor[] = {10, 9, 5 ,7, 6};


    printf("\nMenor valor do vetor: %d", verificaMenorIterativo(vetor, sizeof(vetor)/4));
    printf("\nMenor valor do vetor: %d", verificaMenorRecursivo(vetor, sizeof(vetor)/4));
    return 0;
}
