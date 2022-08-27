#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#define ASSERT(condition)                             \
if (!(condition))                                     \
{                                                     \
printf("Error in %s in %d\n", #condition, __LINE__);  \
}                                                     \

int QEquation(double a, double b, double c, double *x1, double *x2);
int LEquation(double b, double c, double *x1);

void Test(int *nTests);
void input_coefficients(double *a, double *b, double *c);
void output_coefficients(double x1, double x2, int nRoots);

enum nRoots
{
NO_ROOTS  =  0,
ONE_ROOT  =  1,
TWO_ROOTS =  2,
INF_ROOTS =  3,
};

int main()
{
    double  a = 0;
    double  b = 0;
    double  c = 0;

    double x1 = 0;
    double x2 = 0;

    int nRoots = 0;
    int nTests = 0;

    Test(&nTests);
    input_coefficients(&a, &b, &c);
    nRoots = QEquation(a, b, c, &x1, &x2);
    output_coefficients(x1, x2, nRoots);

    return 0;
}

void input_coefficients(double *a, double *b, double *c)
{
    printf("Enter coefficients\n");
    while (scanf("%lg %lg %lg", a, b, c) != 3)
    {
        while(int i = getchar() != '\n' && i != EOF)
        {}
        printf("Try again:\n");
    }

}

int QEquation(double a, double b, double c, double *x1, double *x2)
{
    int nRoots = 0;
    if (a == 0)
    {
        LEquation(b, c, x1);

    }
    else
    {
        if (b*b - 4*a*c >= 0)
        {
            if(b*b - 4*a*c > 0)
            {
            *x1 = (-b - sqrt(b*b - 4*a*c))/2/a;
            *x2 = (-b + sqrt(b*b - 4*a*c))/2/a;
            nRoots = TWO_ROOTS;
            }
            else
            {
            *x1 = -b/2/a;
            nRoots = ONE_ROOT;
            }
        }
        else
        nRoots = NO_ROOTS;
    }
    return nRoots;
}

int LEquation(double b, double c, double* x1)
{
    int nRoots = 0;
    if (b == 0)
    {
        if (c == 0)
        nRoots = INF_ROOTS;

        else
        nRoots = NO_ROOTS;
    }
    else
    {
    *x1 = -c/b;
    nRoots = ONE_ROOT;
    }
    return nRoots;
}

void output_coefficients(double x1, double x2, int nRoots)
{
    switch(nRoots)
    {
        case NO_ROOTS:
        printf("No roots");
        break;

        case ONE_ROOT:
        printf("One root:%lf", x1);
        break;

        case TWO_ROOTS:
        printf("Two roots:%lf %lf", x1, x2);
        break;

        case INF_ROOTS:
        printf("Infinity roots");
        break;

        default:
        ASSERT(0);
        break;
    }
}

void Test(int *nTests)
{

    double x1 = 0;
    double x2 = 0;

int nRoots = QEquation(0, 0, 0, &x1, &x2);
    if (nRoots != INF_ROOTS)
    {
    printf ("FAILED! nRoots = %d, expected nRoots = %d\n", nRoots, INF_ROOTS);
    }
    else
    {
    *nTests += 1;
    printf("Test № %d past completely\n", nTests);
    }
}
