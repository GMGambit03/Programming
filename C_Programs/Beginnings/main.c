#include <stdio.h>
#include <stdbool.h>

int main(int argc, char const *argv[])
{
    int weeksAtAIT = 20;
    char name[30];
    bool Active;

    printf("You dirty bumb, how long have you been in ait: ");
    scanf("%d", &weeksAtAIT);

    printf("You dirty bumb, active or nah: ");
    scanf("%d", &Active);

    getchar();
    printf("You dirty bumb, whats you name: ");
    fgets(name, sizeof(name), stdin);

    return 0;
}
