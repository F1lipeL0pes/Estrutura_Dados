#include <stdio.h>
#include <stdlib.h>

long fibonacci(long n){
    if (n == 0 || n == 1)
        return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

long fibonacciLoop(long n){
    long a = 0;
    long b = 1;
    for (long i = 0; i < n; i++) {
        long proximo = a + b;
        a = b;
        b = proximo;
    }
    return a;
}


int main()
{
    int n;
    printf("Digite um numero: ");
    scanf("%d", &n);

    printf("\nNumero: %d - Numero de Fibonacci: %d", n, fibonacci(n));
    printf("\nNumero: %d - Numero de Fibonacci: %d", n, fibonacciLoop(n));
    return 0;
}
