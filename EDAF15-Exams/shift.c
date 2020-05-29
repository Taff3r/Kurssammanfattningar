#include <stdio.h>
int div_by_power_of_2(int a, int b){
    int q = a >> b;
    printf("%d\n", (a & ((1 << b) - 1)));
    printf("%d\n", (a & ((1 << b) - 1)) != 0);
    if (a < 0 && (a & ((1 << b) - 1)) != 0){
        printf("l: %d\n", ((1 << b) - 1));
        q++;
    }

    return q;
}
int main(void)
{
    printf("%d\n", div_by_power_of_2(8, -5));
    if((-1 >> 1) < 0) 
        printf("arithmetic\n");
    else
        printf("logical\n");
}
