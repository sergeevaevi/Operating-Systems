#include <stdio.h>
#include <math.h>

// описываем функцию f1() как внешнюю
extern int f1();

// описываем функцию f2() как внешнюю
extern int f2();

int main()
{
    int n1, n2;

    n1 = f1();
    n2 = f2();

    printf("f1() = %d\n",n1);
    printf("f2() = %d\n",n2);
    int y = 9;
    double x = sin(y);
    printf("f = %d, %f\n",y, x);
    return 0;
}