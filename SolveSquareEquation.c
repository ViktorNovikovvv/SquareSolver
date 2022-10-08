#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define ASSERT(condition)                             \
if (!(condition))                                     \
{                                                     \
printf("Error in %s in %d\n", #condition, __LINE__);  \
}                                                     \

void UseProgramm         ();
void InputCoefficients   (double *a, double *b, double *c);
int  SolveSquareEquation (double a, double b, double c, double *x1, double *x2);
int  SolveLineEquation   (double b, double c, double *x1);
void OutputCoefficients  (double x1, double x2, int nRoots);

void TestProgramm        ();
int  OneTestProgram      (FILE *fp);

const double ZERO = 2e-5;

enum nRoots
{
    NO_ROOTS  =  0,
    ONE_ROOT  =  1,
    TWO_ROOTS =  2,
    INF_ROOTS = -1,
};

int main()
{
    char Letter = 0;
    int BufClear = 0;

    printf("Choose:\n't'-test the programm\n'u'- use the programm\nother letter - exit\n");

    while(scanf("%c", &Letter) != 1)
    {
        while ((BufClear = getchar()) != '\n' &&  BufClear != EOF)
        {}
        printf("Uncorrectly choise, try again:\n");
    }

    switch(Letter)
    {
        case 'u':
        UseProgramm();
        break;
        case 't':
        TestProgramm();
        break;
        default:
        break;  
        
    }
return 0;
}

void InputCoefficients   (double *a, double *b, double *c)
{
    printf("Enter coefficients:\n");
    while(scanf("%lf %lf %lf", a, b, c)!=3 && scanf("%lf %lf %lf", a, b, c) < 4)
    {
    int BufClear = 0;
       
    while ((BufClear = getchar()) != '\n' &&  BufClear != EOF)
    {}
    printf("Uncorrectly coefficients, please try again:\n");
    }
}

void UseProgramm()
{
    double a = NAN;
    double b = NAN;
    double c = NAN;

    double x1 = NAN;
    double x2 = NAN;

    int nRoots = 3;

             InputCoefficients  (&a, &b, &c);
    nRoots = SolveSquareEquation(a,b,c, &x1, &x2);
             OutputCoefficients (x1,x2,nRoots);
}

int SolveSquareEquation(double a, double b, double c, double *x1, double *x2)
{
    if(fabs(a-0) < ZERO)
    SolveLineEquation(b,c, x1);
    else
    {
        double Discr = b*b - 4*a*c;
        if(Discr > ZERO)
            {
                *x1 = (-b - sqrt(Discr))/2/a;
                *x2 = (-b + sqrt(Discr))/2/a;
                return TWO_ROOTS;
            }
        else if (fabs(Discr-0) < ZERO)
        {
            *x1 = -b/2/a;
            return ONE_ROOT;
        }
        else if (Discr < ZERO)
        return NO_ROOTS;
    }
}

    int SolveLineEquation(double b, double c, double *x1)
    {
        if (fabs(b-0) < ZERO)
        {

        if (fabs(c-0) < ZERO)
        return INF_ROOTS;

        else 
        return NO_ROOTS;

        }
        else
        {
            *x1 = -c/b;
            return ONE_ROOT;
        }
    }

void OutputCoefficients  (double x1, double x2, int nRoots)
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
        ASSERT(nRoots!=-1);
        break;
    }

}



void TestProgramm()
{
    const char *FileName = "ForUnitTest.txt";
    FILE *fp = fopen (FileName, "r");

    int NumberOfAllTests   = 0;
    int NumberOfRightTests = 0;

    for(; NumberOfAllTests < 19; NumberOfAllTests++)
    NumberOfRightTests += OneTestProgram(fp);

    printf("Number of all tests - %d\n", NumberOfAllTests);
    printf("Number of passed tests - %d\n", NumberOfRightTests);
}

int OneTestProgram(FILE *fp)
{
    double a = 0;
    double b = 0;
    double c = 0;

    double x1 = 0;
    double x2 = 0;

    double Right_x1 = 0;
    double Right_x2 = 0;

    int ExpectedRoots = 3;


    fscanf(fp, "%lg %lg %lg %lg %lg %d", &a, &b, &c, &Right_x1, &Right_x2, &ExpectedRoots);
    if (ExpectedRoots == SolveSquareEquation(a, b, c, &x1, &x2) && (Right_x1 == x1 || Right_x1 == x2) && (Right_x2 == x2 || Right_x2 == x1))
    {
    printf("Test passed\n");
    return 1;
    }
    else 
    {
        printf("Test failed\n");
        printf("Expected number of roots:%d\n", ExpectedRoots);
        printf("Expected roots:%lf %lf\n", Right_x1, Right_x2);
        printf("Real number of roots:%d\n", SolveSquareEquation(a, b, c, &x1, &x2)) ;       
        printf("Real roots:%lf %lf\n", x1, x2);
        return 0;
    }
}
