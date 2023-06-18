#include<omp.h>
#include<stdio.h>
int main(){
    double A[1000];
    omp_set_num_threads(4);
    #pragma omp parallel
    {
        int ID = omp_get_thread_num();
        pooh(ID,A);
    }
    printf("all down\n");
    return 0;
}