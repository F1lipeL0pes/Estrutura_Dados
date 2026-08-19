#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calcula(double n){
    if (n == 1)
        return 2;
    return calcula(n - 1) + ((1 + pow(n, 2))/n);
}

int main()
{
    int n;
    printf("Digite o valor de N: ");
    scanf("%d", &n);

    printf("Soma do algoritmo: %f", calcula(n));
    return 0;
}
