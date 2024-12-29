#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
void is_correct(int, int);
int main(int argc, char *argv[])
{
 int i, N, solution;
 if(argc != 2)
 {
 printf("Must supply number to sum to, exiting\n");
 exit(-1);
 }
 // else: parse arguement
 N = atoi(argv[1]);
int p, id, global_solution;
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&p);
  MPI_Comm_rank(MPI_COMM_WORLD,&id);
 solution = 0;
 for(i = id; i <= N; i+=p)
 solution += i;
  printf("i: %d\n",i);
}
MPI_Reduce(&solution, &global_solution,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
 //Check if solution is correct
 is_correct(N, solution);
MPI_Finalize();
}
void is_correct(int N, int solution)
{
 int correct;
 correct = (N*(N+1))/2;
 if(solution == correct)
 printf("The solution %d is correct\n", solution);
 else
 printf("The solution is wrong, got %d, should be %d\n", solution, correct);
}
