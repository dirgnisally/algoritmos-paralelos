#include <iostream>
#define MAX 4
#include <time.h>
#include <stdio.h>
#include <dos.h>

using namespace std;

int main()
{
    double A[MAX][MAX];
    double x[MAX];
    double y[MAX];
    int i, j;
   // cout<<"hello"<<endl;
   clock_t start, end;
   start = clock();
    /* First loop */
       for (i=0; i<MAX; i++)
            for (j=0; j<MAX; j++){
                 //cout<< A[i][j]<<endl;
                 y[i] += A[i][j] * x[j];

            }

    end = clock();
    printf("The time was: %f\n", (end - start) / CLK_TCK);


         for (j=0; j<MAX; j++)
            for (i=0; i<MAX; i++)
                y[i] +=A[i][j] * x[j];
    cout << "Hello world!" << endl;
    return 0;
}
