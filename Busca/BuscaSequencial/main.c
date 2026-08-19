#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//Busca Sequencial

void buscaSequencial(int vetor[], int tamanho, int num){
    for(int i = 0; i < tamanho; i++){
        if(num == vetor[i]){
            printf("O número %d se encontra no vetor", num);
            return;
        }

    }
    printf("O número %d não se encontra no vetor", num);
}

void buscaBinaria(int vetor[], int tamanho, int num){
    int inicio = 0, fim = tamanho - 1;
    while(inicio <= fim){
        int meio = (inicio + fim)/2;
        if(num == vetor[meio]){
            printf("O número está na lista!");
            return;
        }
        else if (num < vetor[meio]){
            fim = meio-1;
        }
        else{
            inicio = meio + 1;
        }
    }
    printf("O número não está na lista!");
}

void bubbleSort(int vetor[], int tamanho){
    int auxiliar;
    for(int i = 0; i < tamanho; i++){
        for(int j = 0; j < tamanho; j++){
            if (vetor[j] >= vetor[i]){
                auxiliar = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = auxiliar;
            }
        }
    }
}

void exibeVetor(int vetor[], int tamanho){
    for(int i = 0; i < tamanho; i++){
        printf("%d - ", vetor[i]);
    }
}

int main()
{
    setlocale(LC_ALL, "Portuguese");

    int tamanho;
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &tamanho);
    int vetor[tamanho];

    for(int i = 0; i < tamanho; i++){
        vetor[i] = rand() % tamanho;
        printf("%d - ", vetor[i]);
    }

    int num;
    printf("\nDigite o número para busca sequencial: ");
    scanf("%d",&num);

    buscaSequencial(vetor, tamanho, num);
    printf("\n\n");


    bubbleSort(vetor, tamanho);
    printf("\nBubble Sorted:\n");
    exibeVetor(vetor, tamanho);

    printf("\nDigite o número para busca binária: ");
    scanf("%d",&num);
    buscaBinaria(vetor, tamanho, num);

    return 0;
}
