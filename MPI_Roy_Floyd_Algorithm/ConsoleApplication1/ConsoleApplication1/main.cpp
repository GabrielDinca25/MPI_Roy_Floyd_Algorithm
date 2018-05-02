/*#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
	// Initialize the MPI environment
	MPI_Init(NULL, NULL);

	// Get the number of processes
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	// Get the rank of the process
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	// Get the name of the processor
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int name_len;
	MPI_Get_processor_name(processor_name, &name_len);


	// Finalize the MPI environment.
	MPI_Finalize();
}*/

#include<stdio.h>
#include<conio.h>
#define pinf 10000 
int a[20][20], n, m;

void init_cost_mat()
{
	FILE *f;
	errno_t err;
	int i, j, x, y, c;
	err = fopen_s(&f, "roy_in.txt", "rt");
	if (err)
		printf("File failed to open");

	printf("\n");
	fscanf_s(f, "%d", &n);
	fscanf_s(f, "%d\n", &m);
	//initializare matrice
	for (i = 1;i <= n;i++)
		for (j = 1;j <= n;j++)
			if (i == j)
				a[i][j] = 0;
			else
				a[i][j] = pinf;

	for (i = 1;i <= m;i++)
	{
		fscanf_s(f, "%d %d %d\n", &x, &y, &c);
		a[x][y] = a[y][x] = c;
	}
	fclose(f);
}

void print_mat()
{
	for (int i = 1;i <= n;i++)
	{
		for (int j = 1;j <= n;j++)
			if (a[i][j] == pinf)
				printf(" - ");
			else
				printf("%4d ", a[i][j]);
		printf("\n");
	}
}

void RoyFloyd() // roy floyd
{
	for (int k = 1;k <= n;k++)
		for (int i = 1;i <= n;i++)
			for (int j = 1;j <= n;j++)
				if (a[i][j]>a[i][k] + a[k][j])
				{
					a[i][j] = a[i][k] + a[k][j];
				}
}

void descompun_drum(int i, int j)
{
	int ok = 0, k = 1;

	while (k <= n && !ok)
	{
		if (i != k&&j != k)
			if (a[i][j] == a[i][k] + a[k][j])
			{
				descompun_drum(i, k);
				descompun_drum(k, j);

				ok = 1;
			}
			k++;
	}
	if (!ok)
	{
		printf(" %d ", j);
	}

}

void scriu_drum(int nod_initial, int nod_final)
{
	if (a[nod_initial][nod_final]<pinf)
	{
		printf("Path from %d to %d has the cost: %d",nod_initial,nod_final,a[nod_initial][nod_final]);
		printf("\n Best path is: %d ", nod_initial);
		descompun_drum(nod_initial, nod_final); 
	}
	else
		printf("There's no path between %d and %d ", nod_initial, nod_final);

}


void main()
{
	int x, y;
	init_cost_mat();
	printf("\nThe cost matrix: \n");
	print_mat();
	RoyFloyd();
	printf("\nOptim cost matrix\n");
	print_mat();
	printf("\nFind the best path between x and y \n");
	printf("x=");
	scanf_s("%d", &x);
	printf("y=");
	scanf_s("%d", &y);
	scriu_drum(x, y);
	_getch();
}