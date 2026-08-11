#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


typedef struct ContaBancaria{
    int num;
    float saldo;
    struct ContaBancaria *next;
}ContaBancaria;

typedef struct listaContas{
    ContaBancaria *begin;
    ContaBancaria *end;
    int contador;
}listaContas;

listaContas *criarLista(){
    listaContas *L = (listaContas *) calloc(1, sizeof(listaContas));
    L->begin = NULL;
    L->end = NULL;
    L->contador = 0;
    return L;
}

ContaBancaria *encontrarContaPorNumero(listaContas *L, int num){
    ContaBancaria *cb = L->begin;
    while(cb != NULL && cb->num != num){
        cb = cb->next;
    }
    if(cb != NULL){
        return cb;
    }
    return NULL;
}

ContaBancaria *criarConta(listaContas *L, int num){
    ContaBancaria *cb = (ContaBancaria*) calloc(1, sizeof(ContaBancaria));
    while (encontrarContaPorNumero(L, num) != NULL){
        printf("Número já existente! Digite um novo valor para a conta: ");
        scanf("%d", &num);
    }
    cb->num = num;
    cb->saldo = 0;
    cb->next = NULL;
    return cb;
}

void adicionarContaNova(listaContas *L, int num){
    ContaBancaria *cb = criarConta(L, num);
    if (L->begin == NULL){
        L->begin = cb;
        L->end = cb;
    }
    else{
        L->end->next = cb;
        L->end = cb;
    }
    L->contador++;
    printf("Conta criada!");
}

void depositar(listaContas *L, int num, float saldo){
    ContaBancaria *cb = encontrarContaPorNumero(L, num);
    if(cb != NULL){
        cb->saldo += saldo;
        printf("Saldo depositado");
    }
    else{
        printf("Conta inexistente!");
    }
}

void sacar(listaContas *L, int num, float saldo){
    ContaBancaria *cb = encontrarContaPorNumero(L, num);
    if(cb != NULL){
        if(saldo > cb->saldo){
            printf("Saque maior que o existente da conta!");
        }
        else{
            cb->saldo -= saldo;
            printf("Saque realizado!");
        }
    }
    else{
        printf("Conta inexistente!");
    }
}

void exibeDados(listaContas *L, int num){
    ContaBancaria *cb = encontrarContaPorNumero(L, num);
    if(cb != NULL){
        printf("\nNúmero da Conta: %d - Saldo: %.2f", cb->num, cb->saldo);
    }
    else{
        printf("Conta inexistente!");
    }

}

void exibirLista(listaContas *L){
    ContaBancaria *cb = L->begin;
    while(cb != NULL){
        exibeDados(L, cb->num);
        cb = cb->next;
    }
}

void excluirConta(listaContas *L, int num){
    ContaBancaria *cb = encontrarContaPorNumero(L, num);
    if (cb == NULL){
        printf("Conta inexistente na lista!");
        return;
    }
    else if(cb->saldo > 0){
        printf("Conta possui saldo, impossível excluir!");
    }
    else{
        ContaBancaria *ce = L->begin;
        while(ce != NULL && ce != cb){
            ce = ce->next;
        }
        if(ce == NULL){
            printf("Conta inexistente na lista!");
        }
        else{
            //lista só tem 1 elemento
            if(L->begin == cb){
                if(L->end == cb){
                    free(cb);
                    L->begin = NULL;
                    L->end = NULL;
                }
            //conta é a primeira da lista
                else{
                    L->begin = L->begin->next;
                    free(cb);
                }
            }
            else{
                ce = L->begin;
                while(ce->next != cb){
                    ce = ce->next;
                }
            //conta está no final da lista
                if(L->end == cb){
                    ce->next = NULL;
                    L->end = ce;
                    free(cb);
                }
            //conta está no meio da lista
                else{
                    ce->next = cb->next;
                    free(cb);
                }
            }
            L->contador--;
            cb = NULL;
            printf("Conta excluída!");
        }
    }
}



int main()
{
    setlocale(LC_ALL, "Portuguese");
    listaContas *L = criarLista();
    int resp, num;
    float saldo;
    do{
        printf("\n\n1- Criar Conta\n"
               "2- Consultar Saldo\n"
               "3- Sacar\n"
               "4- Depositar\n"
               "5- Excluir Conta\n"
               "6- Exibir Lista de Contas\n"
               "7- Sair\n\n"
               "Digite a ação desejada: ");
        scanf("%d", &resp);
        switch(resp){
            case 1:
                printf("Digite o número da conta: ");
                scanf("%d", &num);
                adicionarContaNova(L, num);
                break;
            case 2:
                printf("Digite o número da conta: ");
                scanf("%d", &num);
                exibeDados(L, num);
                break;
            case 3:
                printf("Digite o número da conta: ");
                scanf("%d", &num);
                printf("Digite o saldo a ser sacado: ");
                scanf("%f", &saldo);
                sacar(L, num, saldo);
                break;
            case 4:
                printf("Digite o número da conta: ");
                scanf("%d", &num);
                printf("Digite o saldo a ser depositado: ");
                scanf("%f", &saldo);
                depositar(L, num, saldo);
                break;
            case 5:
                printf("Digite o número da conta: ");
                scanf("%d", &num);
                excluirConta(L, num);
                break;
            case 6:
                exibirLista(L);
                break;
            case 7:
                printf("Tchau! :D");
                break;
        }
    }while(resp != 7);
    return 0;
}
