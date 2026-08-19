#include <stdio.h>
#include <stdlib.h>

long soma(m, n){
    if (n == m)
        return m;
    return soma(m, n-1) + n;
}

int main()
{
    int a, b;
    printf("Digite a: ");
    scanf("%d", &a);
    printf("Digite b: ");
    scanf("%d", &b);


    printf("Soma do intervalo de %d e %d: %d", a, b, soma(a,b));
    return 0;
}
