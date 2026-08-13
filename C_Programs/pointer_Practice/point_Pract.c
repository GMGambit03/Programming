#include <stdio.h>

int main(int argc, char const *argv[])
{
    int i;
    int *p = &i;
    char hello[6] = "hello";
    char *h = &hello[0];

    i = 30;
    

    printf("-- Integer i and Integer pointer p --\n");
    printf("The address of i from p: %d\n", p);
    printf("The address of i from i: %d\n", &i);
    printf("The value of i: %d\n", *p);
    printf("The address of p: %d\n", &p);

    printf(" -- Character hello and Character pointer h -- \n");
    printf("The address of hello from h %d\n", h);
    printf("The address of hello from hello %d\n", &hello);
    printf("The value of hello[0] from h %c\n", *h);
    printf("The address of h from h %c\n", &h);

    printf("%d", &h);

    getchar();
    return 0;
}
