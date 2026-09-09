#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
    int val;
    struct _Node *next;
    struct _Node *prev;
}Node;

typedef struct _Fila{
    Node *begin;
    Node *end;
    int contador;

}Fila;

Node *Node_Create(int val) {
    Node *d = (Node*) calloc(1, sizeof(Node));
    d->val = val;
    d->next = NULL;
    d->prev = NULL;
    return d;
}

Fila *Fila_create() {

    Fila *L = (Fila *) calloc(1, sizeof(Fila));
    L->begin = NULL;
    L->end = NULL;
    L->contador = 0;
    return L;
}


void Fila_enqueue(Fila *L, int val){
    Node *d = Node_Create(val);
    if (L->begin == NULL){//Lista vazia
        L->begin = d;
        L->end = d;
    }
    else{//Lista n o vazia
        L->end->next = d;
        d->prev = L->end;
        L->end = d;
        d->next = NULL;
    }
    L->contador++;
}

int Fila_dequeue(Fila *L){
    Node *prim = L->begin;
    int valor;
    if (L->begin == NULL)
        return 0;
    valor = L->begin->val;
    if (L->begin == L->end){
        L->begin = NULL;
        L->end = NULL;
        free(prim);
        L->contador--;
    }
    else if (L->begin != NULL){
        L->begin = prim->next;
        L->begin->prev = NULL;
        free(prim);
        L->contador--;
    }
    return valor;


}
int Fila_is_empty(Fila *L){
    if(L->begin == NULL){
        return 1;
    }
    return 0;
}

int Fila_peekFirst(Fila *L){

    if (L->begin == NULL){
        return -1;
    }
    else{
        return L->begin->val;
    }
}

int Fila_numero_elem(Fila *L){
    return L->contador;
}

void esvazia_Fila(Fila *L){
    while(L->begin != NULL){
        Fila_dequeue(L);
    }
}

Fila* inverte_Fila(Fila *L){
    if (Fila_is_empty(L) == 1)
        return L;
    Fila *M = Fila_create();
    int cont = L->contador;
    Node *f = L->end;
    for(int i = 1;i <= cont;i++){
        Fila_enqueue(M, f->val);
        f = f->prev;
    }
    return M;
}

int main()
{
    Fila *L = Fila_create();
    Fila_enqueue(L, 10);
    Fila_enqueue(L, 15);
    Fila_enqueue(L, 20);
    Fila_enqueue(L, 25);
    printf("%d\n", Fila_peekFirst(L));//10-15-20-25
    Fila_dequeue(L);
    printf("%d\n\n", Fila_peekFirst(L)); //15-20-25

    Fila *M = inverte_Fila(L);
    printf("%d\n", Fila_peekFirst(M));//25-20-15
    Fila_dequeue(M);
    printf("%d\n\n", Fila_peekFirst(M)); //20-15
    return 0;
}
