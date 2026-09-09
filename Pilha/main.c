#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
    int val;
    struct _Node *next;
    struct _Node *prev;
}Node;

typedef struct _Pilha{
    Node *begin;
    Node *end;
    int contador;

}Pilha;

Pilha *Pilha_create() {

    Pilha *L = (Pilha *) calloc(1, sizeof(Pilha));
    L->begin = NULL;
    L->end = NULL;
    L->contador = 0;
    return L;
}


void Pilha_push(Pilha *L, int val){
    Node *d = Node_Create(val);
    if (L->begin == NULL){//Lista vazia
        L->begin = d;
        L->end = d;
    }
    else{//Lista n o vazia
        L->end->next = d;
        d->prev = L->end;
        L->end = d;
    }
    L->contador++;
}

int Pilha_pop(Pilha *L){
    Node *ult = L->end;
    if (L->begin == NULL)
        return 0;
    int valor = L->end->val;
    if (L->begin == L->end){
        L->begin = NULL;
        L->end = NULL;
        free(ult);
        L->contador--;
    }
    else if (L->begin != NULL){
        L->end = ult->prev;
        L->end->next = NULL;
        free(ult);
        L->contador--;
    }
    return valor;

}

int Pilha_is_empty(Pilha *L){
    if(L->begin == NULL){
        return 1;
    }
    return 0;
}

void Pilha_destroy(Pilha *L){
    while(L->begin != NULL){
        Pilha_pop(L);
    }
}


int Pilha_peekLast(Pilha *L){
    if (L->begin == NULL){
        return -1;
    }
    else{
        return L->end->val;
    }
}

int Pilha_numero_elem(Pilha *L){
    return L->contador;
}

int Pertence(Pilha *p, int x){
    Node *n = p->begin;
    int c = p->contador;
    for(int i = 1; i <= c; i++){
        if(n->val == x){
            free(n);
            return i;
        }
        n = n->next;
    }
    free(n);
    return 0;
}

Pilha* Intercala_Pilhas(Pilha *p1, Pilha *p2){
    Pilha *intercalada = Pilha_create();

    while(p1->contador != 0 && p2->contador != 0){
        Pilha_push(intercalada, Pilha_pop(p1));
        Pilha_push(intercalada, Pilha_pop(p2));
    }
    while(p1->contador != 0){
        Pilha_push(intercalada, Pilha_pop(p1));
    }
    while(p2->contador != 0){
        Pilha_push(intercalada, Pilha_pop(p2));
    }
    return intercalada;
}

void printPilha(Pilha *p){
    Node *n1 = p->begin;
    while(n1 != NULL){
        printf("%d - ", n1->val);
        n1 = n1->next;
    }
}


int main()
{
    Pilha *L = Pilha_create();
    Pilha_push(L, 10);
    Pilha_push(L, 15);
    Pilha_push(L, 20);
    Pilha_push(L, 25);
    printf("%d", Pilha_peekLast(L));
    printf("\nValor removido: %d", Pilha_pop(L));
    printf("\n%d", Pilha_peekLast(L));
    printf("\nEsta vazia: %d\n", Pilha_is_empty(L));
    Pilha_destroy(L);
    printf("\n%d", Pilha_peekLast(L));
    printf("\nEsta vazia: %d", Pilha_is_empty(L));
    Pilha_push(L, 5);
    Pilha_push(L, 10);
    Pilha_push(L, 15);
    printf("\n\n%d\n", Pilha_peekLast(L));
    printPilha(L);

    Pilha *P = Pilha_create();
    Pilha_push(P, 1);
    Pilha_push(P, 2);
    Pilha_push(P, 3);
    printf("\n\n%d\n", Pilha_peekLast(P));
    printPilha(P);


    Pilha *Intercalada = Intercala_Pilhas(L, P);
    printf("\n\n%d\n", Pilha_peekLast(Intercalada));
    printPilha(Intercalada);
    return 0;
}
