#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

/* Define the function to be integrated */
double f(double x) {
    return x * x;
}

int main(int argc, char *argv[]) {
    int rank, size, n, local_n, i;
    double a, b, h, x, local_sum = 0, total_sum, integral;
    
    /* Initialize MPI */
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    /* Set integration parameters */
    n = 1000000000;
    a = 0;
    b = 12;
    h = fabs(b - a) / n;
    
    /* Calculate local range for each process */
    local_n = n / size;
    int start = rank * local_n + 1;
    int end = (rank == size - 1) ? n - 1 : (rank + 1) * local_n;
    
    /* Compute local sum */
    for(i = start; i <= end; i++) {
        x = a + i * h;
        local_sum += f(x);
    }
    
    /* Reduce all local sums to get total sum */
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    /* Root process computes final result */
    if (rank == 0) {
        integral = (h/2) * (f(a) + f(b) + 2 * total_sum);
        printf("The integral is: %.10f\n", integral);
    }
    
    MPI_Finalize();
    return 0;
}
