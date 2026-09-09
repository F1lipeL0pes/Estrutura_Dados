#include <stdio.h>
#include <stdlib.h>

typedef struct _dNode{
    int val;
    struct _dNode *next;
    struct _dNode *prev;
}dNode;

typedef struct _linkedList{
    dNode *begin;
    dNode *end;
    int contador;

}LinkedList;

dNode *dNode_Create(int val) {
    dNode *d = (dNode*) calloc(1, sizeof(dNode));
    d->val = val;
    d->next = NULL;
    d->prev = NULL;
    return d;
}

LinkedList *LinkedList_create() {

    LinkedList *L = (LinkedList *) calloc(1, sizeof(LinkedList));
    L->begin = NULL;
    L->end = NULL;
    L->contador = 0;
    return L;
}

void LinkedList_add_first(LinkedList *L, int val) {

    dNode *p = dNode_Create(val);

    if (L->begin == NULL){
        L->begin = p;
        L->end = p;

    } else {
        p->next = L->begin;
        L->begin->prev = p;
        L->begin = p;
    }
    L->contador++;

}

void LinkedList_add_last(LinkedList *L, int val){
    dNode *d = dNode_Create(val);
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

void LinkedList_remove(LinkedList *L, int valor){
    dNode *prev = NULL;
    dNode *pos = NULL;

    if (L->begin != NULL){
        if (L->begin->val == valor){//1o  valor
            if(L->begin->next == NULL){//só 1 elemento na lista
                pos = L->begin;
                free(pos);
                L->begin = NULL;
                L->end = NULL;
            }
            else{//primeiro elemento
                pos = L->begin;
                L->begin = pos->next;
                L->begin->prev = NULL;
                free(pos);
            }
            L->contador--;
        }
        else{//no meio ou final
            prev = L->begin;
            pos = L->begin->next;
            while (pos != NULL && pos->val != valor) {
                prev = pos;
                pos = pos->next;
            }
            if(pos != NULL){
                if (pos->next != NULL){//verifica se n e- o ultimo
                prev->next = pos->next;
                prev->next->prev = prev;
                free(pos);
                L->contador--;
                }
                else{//  e- o ultimo
                    L->end = prev;
                    prev->next = NULL;
                    free(pos);
                    L->contador--;
                }
            }
        }
    }

}

void LinkedList_print(LinkedList *L){
    printf("\n");
    dNode *d = L->begin;
    for(int i = 1; i <= L->contador; i++){
        printf("%d - ", d->val);
        d = d->next;
    }
}

void LinkedList_print_reverse(LinkedList *L){
    printf("\n");
    dNode *d = L->end;
    int contador = 0;
    for(int i = 1; i <= L->contador; i++){
        printf("%d - ", d->val);
        d = d->prev;
    }
}


int Linked_list_prim(LinkedList *L){

    if (L->begin == NULL){
        return -1;
    }
    else{
        return L->begin->val;
    }
}

int Linked_list_ult(LinkedList *L){
    if (L->begin == NULL){
        return -1;
    }
    else{
        return L->end->val;
    }
}

int LinkedList_numero_elem(LinkedList *L){
    return L->contador;
}

void Linked_copia(LinkedList *La, LinkedList *Lb){
    dNode *p = La->begin;
    for(int contador = 0; contador < La->contador; contador++){
        LinkedList_add_last(Lb, p->val);
        p = p->next;
    }
}

void Linked_copia_inverte(LinkedList *La, LinkedList *Lb){
    dNode *p = La->begin;
    for(int contador = 0; contador < La->contador; contador++){
        LinkedList_add_first(Lb, p->val);
        p = p->next;
    }
}

void Linked_append(LinkedList *La, LinkedList *Lb){
    dNode *p = La->begin;
    int contador = 0;
    while(contador < La->contador){
        LinkedList_add_last(Lb, p->val);
        p = p->next;
        contador++;
    }
}

void Linked_concat(LinkedList *La, LinkedList *Lb, LinkedList *Lc){
    dNode *pa = La->begin;
    dNode *pb = Lb->begin;
    int contador = 0;
    while(contador < La->contador){
        LinkedList_add_last(Lc, pa->val);
        pa = pa->next;
        contador++;
    }
    contador = 0;
    while(contador < Lb->contador){
        LinkedList_add_last(Lc, pb->val);
        pb = pb->next;
        contador++;
    }
}

void Linked_transform(LinkedList * La, LinkedList * Lb, LinkedList * Lc){
    dNode *pa = La->begin;
    dNode *pb = Lb->begin;
    int contador = 0;
    while(contador < La->contador){
        LinkedList_add_last(Lc, pa->val);
        pa = pa->next;
        contador++;
    }
    contador = 0;
    while(contador < Lb->contador){
        LinkedList_add_last(Lc, pb->val);
        pb = pb->next;
        contador++;
    }
    dNode *pc = Lc->begin;
    while (pc!= NULL){
        LinkedList_remove(La, pc->val);
        LinkedList_remove(Lb, pc->val);
        pc = pc->next;
    }

}

void Linked_merge(LinkedList * La, LinkedList * Lb, LinkedList * Lc){
    dNode *pa = La->begin;
    dNode *pb = Lb->begin;
    while(pa!= NULL && pb!= NULL){
        LinkedList_add_last(Lc, pa->val);
        LinkedList_add_last(Lc, pb->val);
        pa = pa->next;
        pb = pb->next;
    }
    while(pa!= NULL){
        LinkedList_add_last(Lc, pa->val);
        pa = pa->next;
    }
    while(pb!= NULL){
        LinkedList_add_last(Lc, pb->val);
        pb = pb->next;
    }
}


int main()
{
    printf("Hello world!\n");
    LinkedList *L = LinkedList_create();
    LinkedList_add_first(L, 5);
    LinkedList_add_last(L, 9);
    LinkedList_add_last(L, 10);
    LinkedList_add_last(L, 12);
    LinkedList_print(L);
    LinkedList_remove(L, 10);
    LinkedList_print(L);
    LinkedList_print_reverse(L);

    printf("\n\nCopia");
    LinkedList *LCopia = LinkedList_create();
    Linked_copia(L, LCopia);
    LinkedList_print(LCopia);

    printf("\n\nCopia Inverte");
    LinkedList *LCopiaI = LinkedList_create();
    Linked_copia_inverte(L, LCopiaI);
    LinkedList_print(LCopiaI);

    printf("\n\nAppend");
    Linked_append(LCopia, LCopiaI);
    LinkedList_print(LCopiaI);

    printf("\n\nConcat");
    LinkedList *LConcat = LinkedList_create();
    Linked_concat(L, LCopia, LConcat);
    LinkedList_print(LConcat);

    printf("\n\nTransform");
    LinkedList *LTransform = LinkedList_create();
    Linked_transform(LCopiaI, LConcat, LTransform);
    LinkedList_print(LTransform);

    printf("\n\nMerge");
    LinkedList *LMerge = LinkedList_create();
    Linked_merge(L, LTransform, LMerge);
    LinkedList_print(LMerge);
    return 0;
}
