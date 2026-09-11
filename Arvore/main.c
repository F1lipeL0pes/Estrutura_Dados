#include <stdio.h>
#include <stdlib.h>

typedef struct noArvore{
    int conteudo;
    struct noArvore *esq;
    struct noArvore *dir;
}noArvore;

noArvore *criarNo(int conteudo){
    noArvore *no = calloc(1, sizeof(noArvore));
    no->conteudo = conteudo;
    no->dir = NULL;
    no->esq = NULL;
    return no;
}

noArvore *inserirNo(noArvore *raiz, int conteudo){
    if(raiz == NULL){
        return criarNo(conteudo);
    }
    if(conteudo < raiz->conteudo){
        raiz->esq = inserirNo(raiz->esq, conteudo);
    }
    else if(conteudo > raiz->conteudo){
        raiz->dir = inserirNo(raiz->dir, conteudo);
    }
    return raiz;
}

void preOrdem(noArvore *raiz){
    if(raiz != NULL){
        printf("%d ", raiz->conteudo);
        preOrdem(raiz->esq);
        preOrdem(raiz->dir);
    }
}

void inOrdem(noArvore *raiz){
    if(raiz != NULL){
        inOrdem(raiz->esq);
        printf("%d ", raiz->conteudo);
        inOrdem(raiz->dir);
    }
}

void posOrdem(noArvore *raiz){
    if(raiz != NULL){
        posOrdem(raiz->esq);
        posOrdem(raiz->dir);
        printf("%d ", raiz->conteudo);
    }
}

void inserirSequencia(noArvore **raiz) {
    int valor;
    do {
        printf("Digite o valor para a árvore (0 para terminar): ");
        scanf("%d", &valor);
        if (valor > 0) {
            *raiz = inserirNo(*raiz, valor);
        }
    } while (valor != 0);
}

void buscarElemento(noArvore *raiz, int conteudo){
    if (raiz != NULL){
        if(conteudo == raiz->conteudo){
            printf("\nO número %d está na árvore", conteudo);
            return;
        }
        if (conteudo < raiz->conteudo){
            return buscarElemento(raiz->esq, conteudo);
        }
        if (conteudo > raiz->conteudo){
            return buscarElemento(raiz->dir, conteudo);
        }
    }
    else{
        printf("\nO número %d não está na árvore", conteudo);
    }
}


noArvore *removerElemento(noArvore *raiz, int conteudo){
    if(raiz == NULL){
        return NULL;
    }

    if(conteudo < raiz->conteudo){
        raiz->esq = removerElemento(raiz->esq, conteudo);
    }
    else if(conteudo > raiz->conteudo){
        raiz->dir = removerElemento(raiz->dir, conteudo);
    }
    else{
        if(raiz->esq == NULL && raiz->dir == NULL){
            free(raiz);
            return NULL;
        }

        else if(raiz->esq == NULL){
            noArvore *aux = raiz->dir;
            free(raiz);
            return aux;
        }

        else if(raiz->dir == NULL){
            noArvore *aux = raiz->esq;
            free(raiz);
            return aux;
        }

        else{
            noArvore *aux = raiz->dir;
            while(aux->esq != NULL){
                aux = aux->esq;
            }
            raiz->conteudo = aux->conteudo;
            raiz->dir = removerElemento(raiz->dir, aux->conteudo);
        }
    }
    return raiz;
}


int altura(noArvore *raiz){
    if(raiz == NULL){
        return -1;
    }

    int esquerda = altura(raiz->esq);
    int direita = altura(raiz->dir);

    if(esquerda > direita){
        return esquerda + 1;
    }
    else{
        return direita + 1;
    }
}

int profundidade(noArvore *raiz, int valor, int nivel) {
    if (raiz == NULL) {
        return -1;
    }

    if (raiz->conteudo == valor) {
        return nivel;
    }

    int esquerda = profundidade(raiz->esq, valor, nivel + 1);

    if (esquerda != -1) {
        return esquerda;
    }

    return profundidade(raiz->dir, valor, nivel + 1);
}


int quantidadeNos(noArvore *raiz) {
    if (raiz == NULL)
        return 0;

    return 1 + quantidadeNos(raiz->esq)
             + quantidadeNos(raiz->dir);
}

void imprimirPorNivel(noArvore *raiz) {
    if (raiz == NULL)
        return;

    noArvore *fila[quantidadeNos(raiz)];
    int inicio = 0;
    int fim = 0;

    fila[fim++] = raiz;

    int nivel = 0;

    printf("\n");
    while (inicio < fim) {
        int quantidade = fim - inicio;

        printf("Nivel %d: ", nivel);

        for (int i = 0; i < quantidade; i++) {
            noArvore *atual = fila[inicio++];

            printf("%d ", atual->conteudo);

            if (atual->esq != NULL)
                fila[fim++] = atual->esq;

            if (atual->dir != NULL)
                fila[fim++] = atual->dir;
        }

        printf("\n");
        nivel++;
    }
}

void inverterArvore(noArvore *raiz){
    if (raiz == NULL)
        return;
    noArvore *aux = raiz->esq;
    raiz->esq = raiz->dir;
    raiz->dir = aux;

    inverterArvore(raiz->esq);
    inverterArvore(raiz->dir);
}

int main()
{
    noArvore *raiz = NULL;
    inserirSequencia(&raiz);
    /*preOrdem(raiz);
    printf("\n");
    buscarElemento(raiz, 10);
    buscarElemento(raiz, 100);
    removerElemento(raiz, 10);
    noArvore *n = inserirNo(raiz, 100);
    noArvore *n2 = inserirNo(raiz, 1000);
    printf("\n");
    preOrdem(raiz);
    printf("A altura da árvore é de %d", altura(raiz));
    imprimirPorNivel(raiz);
    preOrdem(raiz);
    printf("\n");
    inOrdem(raiz);
    printf("\n");
    posOrdem(raiz)*/

    imprimirPorNivel(raiz);
    inverterArvore(raiz);
    imprimirPorNivel(raiz);
    printf("\n%d", altura(raiz));
    return 0;
}
