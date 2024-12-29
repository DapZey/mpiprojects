#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

double f(double x) {
    return x * x;
}

int main(int argc, char *argv[]) {
    int p, id, n, local_index, i;
    double a, b, h, x, local_sum = 0, total_sum, integral;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    n = 1000000000;
    a = 0;
    b = 12;
    h = fabs(b - a) / n;
    local_index = n / id;
    int start_index = p * local_index + 1;
    int end_index = (p == id - 1) ? n - 1 : (p + 1) * local_index;
    
    for(i = start_index; i <= end_index; i++) {
        x = a + i * h;
        local_sum += f(x);
    }
    
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if (p == 0) {
        integral = (h/2) * (f(a) + f(b) + 2 * total_sum);
        printf("The integral is: %.10f\n", integral);
    }
    
    MPI_Finalize();
    return 0;
}
