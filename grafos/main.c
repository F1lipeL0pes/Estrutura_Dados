#include <stdio.h>
#include <stdlib.h>

//grafo com lista de adjacência com vetor

#define MAX_VERTICES 100
#define MAX_ARESTAS 500

typedef struct NoAdj{
    struct NoAdj *prox;
    int id;
    int peso;
}NoAdj;

typedef struct grafo{
    int qtdVertices;
    NoAdj** lista;
}grafo;

grafo *criarGrafoComTamanho(int qtdVertices){
    if(qtdVertices <= 0) return NULL;
    grafo *g = calloc(1, sizeof(grafo));
    g->qtdVertices = qtdVertices;
    g->lista = calloc(qtdVertices, sizeof(NoAdj*));

    return g;
}

grafo* criarGrafoSemTamanho(){
    grafo *g = calloc(1, sizeof(grafo));
    g->qtdVertices = MAX_VERTICES;
    g->lista = calloc(MAX_VERTICES, sizeof(NoAdj*));

    return g;
}

//adicionar aresta com peso 1
void adicionarArestaSemPeso(grafo *g, int origem, int destino){
    if(g == NULL || origem < 0 || destino < 0 || origem >= g->qtdVertices || destino >= g->qtdVertices) return;

    NoAdj *no = calloc(1, sizeof(NoAdj));
    no->id = destino;
    no->peso = 1;
    no->prox = g->lista[origem];
    g->lista[origem] = no;

    no = calloc(1, sizeof(NoAdj));
    no->peso = 1;
    no->id = origem;
    no->prox = g->lista[destino];
    g->lista[destino] = no;
}

//adicionar aresta com peso variável
void adicionarArestaComPeso(grafo *g, int origem, int destino, int peso){
    if(g == NULL || origem < 0 || destino < 0 || peso < 1 || origem >= g->qtdVertices || destino >= g->qtdVertices) return;

    NoAdj *no = calloc(1, sizeof(NoAdj));
    no->id = destino;
    no->peso = peso;
    no->prox = g->lista[origem];
    g->lista[origem] = no;

    no = calloc(1, sizeof(NoAdj));
    no->peso = peso;
    no->id = origem;
    no->prox = g->lista[destino];
    g->lista[destino] = no;
}

void excluirAresta(grafo *g, int origem, int destino){
    if(g == NULL || g->qtdVertices == 0 || origem >= g->qtdVertices || origem < 0 || destino < 0 || destino >= g->qtdVertices) return;

    NoAdj *no = g->lista[origem];
    NoAdj *anterior = NULL;

    while(no!=NULL){
        if(no->id == destino){
            if(anterior == NULL){
                g->lista[origem] = no->prox;
            }
            else{
                anterior->prox = no->prox;
            }
            free(no);
            break;
        }
        anterior = no;
        no = no->prox;
    }

    no = g->lista[destino];
    anterior = NULL;
    while(no!=NULL){
        if(no->id == origem){
            if(anterior == NULL){
                g->lista[destino] = no->prox;
            }
            else{
                anterior->prox = no->prox;
            }
            free(no);
            break;
        }
        anterior = no;
        no = no->prox;
    }
}

void excluirGrafo(grafo *g){
    if(g == NULL) return NULL;

    for(int i = 0; i < g->qtdVertices; i++){
        NoAdj *no = g->lista[i];
        while(no != NULL){
            NoAdj *aux = no;
            no = no->prox;
            free(aux);
        }
    }
    free(g);
}


typedef struct noFila{
    int valor;
    struct noFila *prox;
}noFila;

typedef struct fila{
    noFila *inicio;
    noFila *fim;
    int qtd;
}fila;

fila *criarFila(){
    fila* f = calloc(1, sizeof(fila));
    f->inicio = NULL;
    f->fim = NULL;
    f->qtd = 0;
    return f;
}

void enfileirar(fila *f, int valor){
    if(f == NULL || valor < 0) return;

    noFila *no = calloc(1, sizeof(noFila));
    no->prox = NULL;
    no->valor = valor;
    if(f->fim == NULL){
        f->inicio = no;
        f->fim = no;
    }
    else{
        f->fim->prox = no;
        f->fim = no;
    }
    f->qtd++;
}

int desenfileirar(fila* f){
    if(f == NULL || f->inicio == NULL) return 0;

    noFila *no = f->inicio;
    f->inicio = no->prox;
    if(f->inicio == NULL) f->fim = NULL;

    int valor = no->valor;
    free(no);
    f->qtd--;

    return valor;

}

void deletarFila(fila *f){
    noFila *aux;
    while(f->inicio != NULL){
        aux = f->inicio;
        f->inicio = f->inicio->prox;
        free(aux);
    }
    f->fim = NULL;
    free(f);
}

int filaVazia(fila *f){
    if(f->inicio == NULL) return 1;
    return 0;
}

//busca em largura informando o início
void bfs(grafo *g, int inicio){
    if(g == NULL || inicio < 0 || g->qtdVertices == 0 || inicio >= g->qtdVertices) return;
    fila *f = criarFila();
    int qtd = g->qtdVertices;
    int *visitados = calloc(qtd, sizeof(int));

    enfileirar(f, inicio);
    visitados[inicio] = 1;

    while(!filaVazia(f)){
        int atual = desenfileirar(f);
        printf("%d - ", atual);
        NoAdj *aux = g->lista[atual];
        while(aux != NULL){
            int vizinho = aux->id;
            if(visitados[vizinho] == 0){
                visitados[vizinho] = 1;
                enfileirar(f, vizinho);
            }
            aux = aux->prox;
        }
    }

    for(int i = 0; i < g->qtdVertices; i++){
        NoAdj *aux = g->lista[i];
        while(aux != NULL){
            int vizinho = aux->id;
            if(visitados[vizinho] == 0){
                visitados[vizinho] = 1;
                enfileirar(f, vizinho);
            }
            aux = aux->prox;
        }
    }

    deletarFila(f);
    free(visitados);
    printf("\n");

}

//busca em largura sem informar o início
void bfsGeral(grafo *g){
    if(g == NULL|| g->qtdVertices == 0) return;
    int inicio = g->lista[0]->id;
    fila *f = criarFila();
    int qtd = g->qtdVertices;
    int *visitados = calloc(qtd, sizeof(int));
    for(int i = 0; i < qtd; i++){
        if(visitados[i] == 0){
            enfileirar(f, i);
            visitados[i] = 1;
            while(!filaVazia(f)){
                int atual = desenfileirar(f);
                printf("%d - ", atual);
                NoAdj *aux = g->lista[atual];
                while(aux != NULL){
                    int vizinho = aux->id;
                    if(visitados[vizinho] == 0){
                        visitados[vizinho] = 1;
                        enfileirar(f, vizinho);
                    }
                    aux = aux->prox;
                }
            }
        }
    }
    deletarFila(f);
    free(visitados);

    printf("\n");
}

typedef struct noPilha{
    int valor;
    struct noPilha *prox;
}noPilha;

typedef struct pilha{
    noPilha *topo;
    int qtd;
}pilha;

pilha *criarPilha(){
    pilha *p = calloc(1, sizeof(pilha));
    p->qtd = 0;
    p->topo = NULL;

    return p;
}
void push(pilha *p, int valor){
    if(p == NULL) return;
    noPilha *n = calloc(1, sizeof(noPilha));
    n->valor = valor;
    n->prox = p->topo;
    p->topo = n;
    p->qtd++;
}
int pop(pilha *p){
    if(p == NULL || p->topo == NULL) return 0;
    noPilha *aux = p->topo;
    int valor = aux->valor;

    p->topo = aux->prox;
    free(aux);
    p->qtd--;

    return valor;
}
void deletarPilha(pilha *p){
    if(p == NULL) return;
    noPilha *aux;
    while(p->topo != NULL){
        aux = p->topo;
        p->topo = p->topo->prox;
        free(aux);
    }
    free(p);
}

//busca em profundidade com inicio
void dfs(grafo *g, int inicio){
    if(g == NULL || inicio < 0 || inicio >= g->qtdVertices) return;

    pilha *p = criarPilha();
    int *visitados = calloc(g->qtdVertices, sizeof(int));
    push(p, inicio);
    while(p->topo){
        int atual = pop(p);
        if(visitados[atual] == 0){
            printf("%d - ", atual);
            visitados[atual] = 1;
            NoAdj *aux = g->lista[atual];
            while(aux != NULL){
                int vizinho = aux->id;
                if(visitados[vizinho] == 0){
                    push(p, vizinho);
                }
                aux = aux->prox;
            }
        }
    }
    deletarPilha(p);
    free(visitados);
    printf("\n");
}

//busca em profundidade sem inicio
void dfsGeral(grafo *g){
    if(g == NULL || g->qtdVertices == 0) return;

    pilha *p = criarPilha();
    int *visitados = calloc(g->qtdVertices, sizeof(int));
    int inicio = g->lista[0]->id;
    push(p, inicio);
    while(p->topo){
        int atual = pop(p);
        if(visitados[atual] == 0){
            printf("%d - ", atual);
            visitados[atual] = 1;
            NoAdj *aux = g->lista[atual];
            while(aux != NULL){
                int vizinho = aux->id;
                if(visitados[vizinho] == 0){
                    push(p, vizinho);
                }
                aux = aux->prox;
            }
        }
    }
    deletarPilha(p);
    free(visitados);
    printf("\n");
}





//grafo com matriz de adjacência
typedef struct grafoM{
    int qtdVertices;
    int **adjacencias;
}grafoM;

grafoM *criarGrafoMComQtd(int qtd){
    grafoM *g = calloc(1, sizeof(grafoM));
    g->qtdVertices = qtd;
    g->adjacencias = calloc(qtd, sizeof(int));
    for(int i = 0; i < qtd; i++){
        g->adjacencias[i] = calloc(qtd, sizeof(int));
    }
    return g;
}

grafoM *criarGrafoMSemQtd(){
    grafoM *g = calloc(1, sizeof(grafoM));
    g->qtdVertices = MAX_VERTICES;
    g->adjacencias = calloc(MAX_VERTICES, sizeof(int));
    for(int i = 0; i < MAX_VERTICES; i++){
        g->adjacencias[i] = calloc(MAX_VERTICES, sizeof(int));
    }
    return g;
}

void inserirArestaM(grafoM *g, int origem, int destino){
    if(g == NULL || origem < 0 || destino < 0 || origem >= g->qtdVertices || destino >= g->qtdVertices) return;

    g->adjacencias[origem][destino] = 1;
    g->adjacencias[destino][origem] = 1;
}

void excluirArestaM(grafoM *g, int origem, int destino){
    if(g == NULL || origem < 0 || destino < 0 || origem >= g->qtdVertices || destino >= g->qtdVertices) return;

    g->adjacencias[origem][destino] = 0;
    g->adjacencias[destino][origem] = 0;
}


//grafo com matriz de incidência
typedef struct grafoMI{
    int qtdVertices;
    int qtdArestas;
    int **incidencias;
}grafoMI;

grafoMI* criarGrafoMIComTamanho(int vertices){
    if(vertices <= 0) return NULL;

    grafoMI *g = calloc(1, sizeof(grafoMI));
    g->qtdArestas = MAX_ARESTAS;
    g->qtdVertices = vertices;
    g->incidencias = calloc(g->qtdVertices, sizeof(int));
    for(int i = 0; i < g->qtdVertices; i++){
        g->incidencias[i] = calloc(g->qtdArestas, sizeof(int));
    }

    return g;
}




//lista de adjacências como lista de listas
typedef struct Adj{
    int peso;
    int vertice;
    struct Adj *prox;
}Adj;

typedef struct Vertices{
    int id;
    struct Vertices *prox;
    Adj* adjacencias;
}Vertices;

typedef struct grafoLL{
    int qtdVertices;
    Vertices *inicio;
    Vertices *fim;
}grafoLL;

grafoLL *criarGrafoLL(){
    grafoLL *g = calloc(1, sizeof(grafoLL));
    g->qtdVertices = 0;
    g->inicio = NULL;
    g->fim = NULL;
    return g;
}

Vertices *buscarVertice(grafoLL *g, int id){
    if(g == NULL || id < 0) return NULL;

    Vertices *aux = g->inicio;
    while(aux != NULL){
        if(aux->id == id){
            return aux;
        }
        aux = aux->prox;
    }

    return NULL;
}

void inserirVertice(grafoLL *g, int id){
    if(g == NULL || id < 0) return;

    if(buscarVertice(g, id) != NULL) return;

    Vertices *v = calloc(1, sizeof(Vertices));
    v->id = id;
    v->prox = NULL;
    v->adjacencias = NULL;

    if(g->inicio == NULL){
        g->inicio = v;
        g->fim = v;
    }
    else{
         g->fim->prox = v;
         g->fim = v;
    }
    g->qtdVertices++;
}

int arestaExiste(grafoLL *g, int inicio, int fim){
    if(g == NULL || g->qtdVertices == 0 || inicio < 0 || fim < 0) return 0;

    Vertices *origem = buscarVertice(g, inicio);
    if(origem == NULL) return 0;
    Adj *aux = origem->adjacencias;
    while(aux != NULL){
        if(aux->vertice == fim)
            return 1;
        aux = aux->prox;
    }
    return 0;
}

void inserirArestaLL(grafoLL *g, int inicio, int fim){
    if(g == NULL || g->qtdVertices == 0 || inicio < 0 || fimn < 0) return;

    Vertices *origem = buscarVertice(g, inicio);
    Vertices *destino = buscarVertice(g, fim);

    if(origem == NULL || destino == NULL) return;
    if(arestaExiste(g, inicio, fim)) return;


    Adj* a = calloc(1, sizeof(Adj));

    a->peso = 1;
    a->prox = NULL;
    a->vertice = fim;
    if(origem->adjacencias == NULL){
        origem->adjacencias = a;
    }
    else{
        Adj *aux = origem->adjacencias;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = a;
    }

    a = calloc(1, sizeof(Adj));

    a->peso = 1;
    a->prox = NULL;
    a->vertice = inicio;
    if(destino->adjacencias == NULL){
        destino->adjacencias = a;
    }
    else{
        Adj *aux = destino->adjacencias;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = a;
    }
}

void excluirVertice(grafoLL* g, int id){
    if(g == NULL || id < 0 || g->inicio == NULL) return;
    Vertices *aux = buscarVertice(g, id);
    if(!aux) return;

    if(aux == g->inicio){
        if(aux == g->fim){
            g->inicio = NULL;
            g->fim = NULL;
        }
        else{
            g->inicio = aux->prox;
        }
    }
    else{
        Vertices *prev = g->inicio;
        while(prev->prox != aux){
            prev = prev->prox;
        }
        if(aux == g->fim){
            prev->prox = NULL;
            g->fim = prev;
        }
        else{
            prev->prox = aux->prox;
        }
    }

    Adj* ad = aux->adjacencias;
    while(ad != NULL){
        Adj *aux2 = ad->prox;
        free(ad);
        ad = aux2;
    }

    Vertices *v = g->inicio;
    while(v != NULL){
        Adj *a = v->adjacencias;
        Adj *anterior = NULL;
        while(a != NULL){
            if(a->vertice == id){
                Adj *temp = a;

                if(anterior == NULL){
                    v->adjacencias = a->prox;
                }
                else{
                    anterior->prox = a->prox;
                }

                a = a->prox;
                free(temp);
            }
            else{
                anterior = a;
                a = a->prox;
            }
        }

        v = v->prox;
    }

    g->qtdVertices--;
    free(aux);
}

void dijkstra(grafoLL *g, int inicio){
    if(g == NULL || inicio < 0 || buscarVertice(g, inicio) == 0) return;


}


int main()
{
    grafo *g = criarGrafoComTamanho(5);
    adicionarArestaSemPeso(g, 1, 2);
    adicionarArestaSemPeso(g, 1, 3);
    adicionarArestaSemPeso(g, 3, 4);
    adicionarArestaSemPeso(g, 0, 4);

    excluirAresta(g, 1, 3);

    bfs(g, 2);
    bfsGeral(g);

    dfs(g, 1);
    dfsGeral(g);
    return 0;
}
