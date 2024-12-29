#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
int NUM_SIMS = 1000000;
int main(int argc, char *argv[])
{
 int i, totalin;
 double x, y, area;
int p, id;
int globalin;
MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD, &p);
MPI_Comm_rank(MPI_COMM_WORLD, &id);
 // perform NUM_SIMS ops to estimate 1/4 area of circle
 totalin = 0;
 srand(0);
 for(i = id; i < NUM_SIMS; i+=p)
 {
 x = (double) rand()/RAND_MAX;
 y = (double) rand()/RAND_MAX;
 // if x*x+y*y <= 1, then random pt is inside of circle
 if(x*x+y*y <= 1){
 totalin++;}
 }
MPI_Reduce(&totalin,&globalin,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
 //Find Total Area. Area = pi*r*r = pi
 // Area = 4*totalin/(NUM_SIMS*nprocs)
 area = (double) 4*(double)globalin/(double)(NUM_SIMS);
printf("pi is: %f\n", area);
  MPI_Finalize();
}
