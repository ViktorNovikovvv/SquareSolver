#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#define ASSERT(condition)                             \
if (!(condition))                                     \
{                                                     \
printf("Error in %s in %d\n", #condition, __LINE__);  \
}                                                     \

int SEquation(double a, double b, double c, double *x1, double *x2);
int LEquation(double b, double c, double *x1);
int TestOfSquareEquation(FILE *fp);

void MainTest();
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
    MainTest();
    input_coefficients(&a, &b, &c);
    nRoots = SEquation(a, b, c, &x1, &x2);
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

int SEquation(double a, double b, double c, double *x1, double *x2)
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

void MainTest()
{
    double a; double b; double c; double x1; double x2; int nRoots;
    const char *FileName = "ForUnitTest.txt";
    FILE *fp = fopen (FileName, "r");

    int NumberOfRightTests = 0;
    int NumberOfAllTests   = 0;
    for (;NumberOfAllTests < 17; NumberOfAllTests++)
    {
    NumberOfRightTests += TestOfSquareEquation(fp);
    }
    printf("Number of all tests - %d\n", NumberOfAllTests);
    printf("Number of passed tests - %d\n", NumberOfRightTests);
}

int TestOfSquareEquation(FILE *fp)
{
    double  a;
    double  b;
    double  c;

    double Right_x1;
    double Right_x2;

    double x1;
    double x2;

    int nRoots;
    int NumberOfRightTests = 0;
    int ExpectedRoots;

    fscanf(fp, "%lg %lg %lg %lg %lg %d", &a, &b, &c, &Right_x1, &Right_x2, &ExpectedRoots);
    nRoots = SEquation(a, b, c, &x1, &x2);

    if(ExpectedRoots == SEquation(a, b, c, &x1, &x2) && Right_x1 == x1 && Right_x2 == x2)
    {
        printf("Test ¹ %d passed", NumberOfRightTests);
        NumberOfRightTests += 1;
        return 1;
    }
    else
    {
        printf("Test ¹ %d failed\n", NumberOfRightTests);
        printf("Expected roots: %lf %lf %d\n", Right_x1, Right_x2, ExpectedRoots);
        printf("Real roots: %lf %lf %d\n", x1, x2, nRoots);
    }
    return 0;
}


