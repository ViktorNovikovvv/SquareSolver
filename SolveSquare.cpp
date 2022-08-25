#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

double QEquation(double a, double b, double c, double *x1, double *x2, int *nRoots);
double LEquation(double b, double c, double *x1, int *nRoots);
double input_coefficients(double *a, double *b, double *c);

void output_coefficients(double x1, double x2, int nRoots);

int main()
{
    double  a = 0;
    double  b = 0;
    double  c = 0;

    double x1 = 0;
    double x2 = 0;

    int nRoots = 0;

    input_coefficients(&a, &b, &c);
    QEquation(a, b, c, &x1, &x2, &nRoots);
    output_coefficients(x1, x2, nRoots);

    return 0;
}

double input_coefficients (double *a, double *b, double *c)
{
    printf ("Enter coefficients a, b, c\n");

    if (scanf("%lg %lg %lg", a, b, c) != 3)
    {
        printf("Uncorrectly entered");
        abort();
    }
    return 0;
}

double LEquation(double b, double c, double* x1, int *nRoots)
{
    if (b == 0)
    {
        if (c == 0)
        {
            *nRoots = 3;
            return 0;
        }
        else
        {
            *nRoots = 0;
            return 0;
        }
    }
    else
    {
        *x1 = -c/b;
        *nRoots = 1;
        return 0;
    }
    return 0;
}

double QEquation(double a, double b, double c, double *x1, double *x2, int *nRoots)
{
    if (a == 0)
    {
        LEquation(b, c, x1, nRoots);

        return 0;
    }
    else
    {
        if (b*b - 4*a*c >= 0)
        {
            if(b*b - 4*a*c > 0)
            {
                double sqrt_Discr;
                *x1 = (-b - sqrt(b*b - 4*a*c))/2/a;
                *x2 = (-b + sqrt(b*b - 4*a*c))/2/a;
                *nRoots = 2;
                return 0;
            }
            else
            {
                *x1 = -b/2/a;
                *nRoots = 1;
                return 0;
            }
            return 0;
        }
        else
        {
            *nRoots = 0;
            return 0;
        }
    }
    return 0;
}

void output_coefficients(double x1, double x2, int nRoots)
{
    switch(nRoots)
    {
        case 0:
        printf("No roots");
        break;

        case 1:
        printf("One root:%lf", x1);
        break;

        case 2:
        printf("Two roots:%lf %lf", x1, x2);
        break;

        case 3:
        printf("Infinity roots");
        break;

        default:
        assert (0);
        break;
    }
}
