#include <mpi.h>
#include<stdio.h>
#include<conio.h>

#define inf 10000
#define SIZE 5

void main()
{
	int cost_matrix[SIZE][SIZE] = {
		{0, 2, inf, 2, inf},
		{2, 0, 3, inf, inf}, 
		{inf, 3, 0, 1, 8},
		{10, inf, 1, 0, inf},
		{inf, inf, 8, inf, 0} 
	};

	int optimal_cost_matrix[SIZE][SIZE];

	int numprocs, procid, len, partner, message;
	char hostname[MPI_MAX_PROCESSOR_NAME];
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &procid);
	MPI_Get_processor_name(hostname, &len);
	MPI_Status status;

	for (int i = 0;i < SIZE;i++)
	{
		for (int j = 1;j < SIZE;j++)
		{
			if (cost_matrix[i][j] > cost_matrix[i][procid] + cost_matrix[procid][j])
			{
				cost_matrix[i][j] = cost_matrix[i][procid] + cost_matrix[procid][j];
			}
		}
	}

	MPI_Gather(cost_matrix, SIZE*SIZE, MPI_INT, optimal_cost_matrix, SIZE*SIZE, MPI_INT, 0, MPI_COMM_WORLD);

	if (procid == 0)
	{
		for (int i = 0;i < SIZE;i++)
		{
			for (int j = 1;j < SIZE;j++)
			{
				cost_matrix[i][j] = optimal_cost_matrix[i][j];
			}
		}

		printf("Optimal cost matrix is: ");

		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				printf("%d ", cost_matrix[i][j]);
			}
			printf("\n");
		}

	}

	
	MPI_Finalize();
}