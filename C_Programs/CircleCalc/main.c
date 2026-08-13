#include <stdio.h>
#include <math.h>

float PI = 3.1415927;

float solveRadius(float circ)
{
    return circ / (2 * PI);
}

float solveCircumRad(float radius)
{
    return (2 * PI * radius);
}

float solveCircumDiam(float diam)
{
    return (PI * diam);
}

float solveDiamRadius(float radius)
{
    return (2*radius);
}

float solveDiamCirc(float circ)
{
    return (circ/PI);
}

int main(int argc, char const *argv[])
{
    char input;
    float circ;
    float radius;
    float diam;

    while (input != 'e')
    {
        printf("\n\nDo you need to calculate the Radius(r), the Diameter(d), or the Circumference(c):\n");
        scanf("%c", &input);

        if (input == 'r'){
            printf("Please provide the circumference:\n");
            scanf("%f", &circ);
            printf("The Radius is ");
            printf("%f", solveRadius(circ));
            getchar();
        }
        else if (input == 'c'){
            char radOrDiam;
            printf("Do you have the radius(r) or diameter(d):\n");
            getchar();
            scanf("%c", &radOrDiam);
            if(radOrDiam == 'r'){
                getchar();
                printf("Please provide the radius:\n");
                scanf("%f", &radius);
                printf("The Circumference is ");
                printf("%f", solveCircumRad(radius));
                getchar();
            }
            else if(radOrDiam == 'd'){
                printf("Please provide the diameter:\n");
                scanf("%f", &diam);
                printf("The Circumference is ");
                printf("%f", solveCircumDiam(diam));
                getchar();
            }
        }
        else if(input == 'd'){
            char radOrCirc;
            printf("Do you have the radius(r) or circumference(d):\n");
            getchar();
            scanf("%c", &radOrCirc);

            if(radOrCirc == 'r'){
                printf("Please provide the radius:\n");
                scanf("%f", &radius);
                printf("The Diameter is ");
                printf("%f", solveDiamRadius(radius));
                getchar();
            }
                else if(radOrCirc == 'c'){
                printf("Please provide the circumference:\n");
                scanf("%f", &circ);
                printf("The Diameter is ");
                printf("%f", solveDiamCirc(circ));
                getchar();
            }
        }
        else if(input == 'e'){
            return 0;
        }
    }
    

    

    getchar();
    return 0;
}
