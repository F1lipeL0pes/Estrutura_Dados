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
    struct _Fila *prev;
    struct _Fila *next;
}Fila;

typedef struct _FilaLista{
    Fila *begin;
    Fila *end;
    int contador;

}FilaLista;


Node *Node_Create(int val) {
    Node *d = (Node*) calloc(1, sizeof(Node));
    d->val = val;
    d->next = NULL;
    d->prev = NULL;
    return d;
}

FilaLista *FilaLista_create(){
    FilaLista *FL = (FilaLista *) calloc(1, sizeof(FilaLista));
    FL->begin = NULL;
    FL->contador = 0;
    FL->end = NULL;
    return FL;
}

Fila *Fila_create() {
    Fila *L = (Fila *) calloc(1, sizeof(Fila));
    L->begin = NULL;
    L->end = NULL;
    L->contador = 0;
    L->next = NULL;
    L->prev = NULL;
    return L;
}


Fila* FilaLista_enqueue(FilaLista *L){
    Fila *d = Fila_create();
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
    return d;
}

Fila* FilaLista_dequeue(FilaLista *L){
    Fila *prim = L->begin;
    Fila *p = prim;
    if (L->begin == NULL)
        return NULL;
    if (L->begin == L->end){
        L->begin = NULL;
        L->end = NULL;
        L->contador--;
    }
    else if (L->begin != NULL){
        L->begin = prim->next;
        L->begin->prev = NULL;
        L->contador--;
    }
    return p;
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

int FilaLista_numero_filas(FilaLista *L){
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

void printFila(Fila *FL){
    Node *d = FL->begin;
    for(int i = 1; i <= FL->contador; i++){
        printf("%d - ", d->val);
        d = d->next;
    }
    printf("\n");
}

void printFilaLista(FilaLista *FL){
    Fila *f = FL->begin;
    for(int j = 1; j <= FL->contador; j++){
        printf("%d: ", j);
        printFila(f);
        f = f->next;
    }
}

int FilaLista_numero_elementos(FilaLista *FL){
    Fila *f = FL->begin;
    int c = 0;
    for(int j = 1; j <= FL->contador; j++){
        c += f->contador;
        f = f->next;
    }
    return c;
}

int main()
{
    FilaLista *FL = FilaLista_create();
    Fila *f1 = FilaLista_enqueue(FL);
    Fila_enqueue(f1, 5);
    Fila_enqueue(f1, 10);
    Fila *f2 = FilaLista_enqueue(FL);
    Fila_enqueue(f2, 1);
    Fila_enqueue(f2, 2);
    Fila *f3 = FilaLista_dequeue(FL);
    Fila *f4 = FilaLista_enqueue(FL);
    Fila_enqueue(f4, 7);
    Fila_enqueue(f4, 8);
    Fila_enqueue(f4, 9);

    printFilaLista(FL);
    printf("Numero de elementos totais: %d", FilaLista_numero_elementos(FL));
    return 0;
}
