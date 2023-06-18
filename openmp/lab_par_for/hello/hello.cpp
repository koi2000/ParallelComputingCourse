#include<omp.h>
#include<stdio.h>
int main(){
    #pragma omp parallel
    {
        int ID = omp_get_thread_num();
        printf("Hello(%d)",ID);
        printf(" world(%d)",ID);
    }
    return 0;
}