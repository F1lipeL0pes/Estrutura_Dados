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

int main()
{
    noArvore *raiz = NULL;
    inserirSequencia(&raiz);
    preOrdem(raiz);
    printf("\n");
    buscarElemento(raiz, 10);
    buscarElemento(raiz, 100);
    removerElemento(raiz, 10);
    printf("\n");
    preOrdem(raiz);
    printf("A altura da árvore é de %d", altura(raiz));
    return 0;
}
