#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

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

void insertSort(int vetor[], int tamanho){
    for(int i = 1; i < tamanho; i++){
        int guarda = vetor[i], j = i - 1;
        while(j >= 0 && vetor[j] > guarda){
            vetor[j+1] = vetor[j];
            j--;
        }
        vetor[j+1] = guarda;
    }
}

void selectionSort(int vetor[], int tamanho){
    for(int i = 0; i < tamanho; i++){
        int menor = i;

        for(int j = i + 1; j < tamanho; j++){
            if(vetor[j] < vetor[menor]){
                menor = j;
            }
        }
        if (menor != i){
            int temp = vetor[i];
            vetor[i] = vetor[menor];
            vetor[menor] = temp;
        }
    }
}

void merge(int v[], int inicio, int meio, int fim) {
    int i = inicio;
    int j = meio + 1;
    int k = 0;
    int tamanho = fim - inicio + 1;
    int aux[tamanho];

    while (i <= meio && j <= fim) {
        if (v[i] <= v[j]) {
            aux[k] = v[i];
            i++;
        } else {
            aux[k] = v[j];
            j++;
        }

        k++;
    }
    while (i <= meio) {
        aux[k] = v[i];
        i++;
        k++;
    }
    while (j <= fim) {
        aux[k] = v[j];
        j++;
        k++;
    }
    for (i = inicio, k = 0; i <= fim; i++, k++) {
        v[i] = aux[k];
    }
}
void mergeSortRec(int v[], int inicio, int fim) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        mergeSortRec(v, inicio  , meio);
        mergeSortRec(v, meio + 1, fim);
        merge(v, inicio, meio, fim);
    }
}
void mergeSort(int v[], int tamanho) {
    mergeSortRec(v, 0, tamanho - 1);
}

int particiona(int vetor[], int inicio, int fim) {
    int pivo = vetor[fim];
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        if (vetor[j] <= pivo) {
            i++;

            int temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
        }
    }
    int temp = vetor[i + 1];
    vetor[i + 1] = vetor[fim];
    vetor[fim] = temp;

    return i + 1;
}

void quickSort(int vetor[], int inicio, int fim) {
    if (inicio < fim) {
        int posicaoPivo = particiona(vetor, inicio, fim);
        quickSort(vetor, inicio, posicaoPivo - 1);
        quickSort(vetor, posicaoPivo + 1, fim);
    }
}

void exibeVetor(int vetor[], int tamanho){
    printf("\n");
    for(int i = 0; i < tamanho; i++){
        printf("%d - ", vetor[i]);
    }
}

void geraVetor(int vetor[], int tamanho){
    printf("\n");
    for(int i = 0; i < tamanho; i++){
        vetor[i] = rand() % tamanho;
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
    geraVetor(vetor, tamanho);

    int num;
    printf("\nDigite o número para busca sequencial: ");
    scanf("%d",&num);

    buscaSequencial(vetor, tamanho, num);
    printf("\n\n");


    bubbleSort(vetor, tamanho);
    printf("\nBubble Sorted:");
    exibeVetor(vetor, tamanho);

    printf("\nDigite o número para busca binária: ");
    scanf("%d",&num);
    buscaBinaria(vetor, tamanho, num);
    printf("\n\n");

    geraVetor(vetor, tamanho);
    insertSort(vetor, tamanho);
    printf("\nInsert Sorted:");
    exibeVetor(vetor, tamanho);
    printf("\n\n");

    geraVetor(vetor, tamanho);
    selectionSort(vetor, tamanho);
    printf("\nSelection Sorted:");
    exibeVetor(vetor, tamanho);
    printf("\n\n");

    geraVetor(vetor, tamanho);
    mergeSort(vetor, tamanho);
    printf("\nMerge Sorted:");
    exibeVetor(vetor, tamanho);
    printf("\n\n");

    geraVetor(vetor, tamanho);
    quickSort(vetor, 0, tamanho);
    printf("\nQuick Sorted:");
    exibeVetor(vetor, tamanho);


    return 0;
}
