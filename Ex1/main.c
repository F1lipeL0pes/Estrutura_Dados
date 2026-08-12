#include <stdio.h>
#include <stdlib.h>

int mdc(x, y){
    if(y == 0)
        return x;
    return mdc(y, x%y);
}

int main()
{
    int a, b;
    printf("Digite a: ");
    scanf("%d", &a);
    printf("Digite b: ");
    scanf("%d", &b);


    printf("MDC de %d e %d: %d", a, b, mdc(a,b));
    return 0;
}
