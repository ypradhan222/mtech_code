#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#define INF 1000000

int main(int argc, char **argv) {
  int n; // Number of vertices
  int my_rank; // Rank of the current process
  int p; // Number of processes

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &p);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  // Read the adjacency matrix
  if (my_rank == 0) {
    scanf("%d", &n);
    int adj_matrix[n][n];
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        scanf("%d", &adj_matrix[i][j]);
        if (adj_matrix[i][j] == 0) {
          adj_matrix[i][j] = INF;
        }
      }
    }

    // Distribute the adjacency matrix to all processes
    for (int i = 1; i < p; i++) {
      MPI_Send(&adj_matrix[i * n / p][0], n * n / p, MPI_INT, i, 0, MPI_COMM_WORLD);
    }
  } else {
    int *adj_matrix_local = malloc(n * n / p * sizeof(int));
    MPI_Recv(adj_matrix_local, n * n / p, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // Run Floyd's algorithm
    for (int k = 0; k < n; k++) {
      for (int i = 0; i < n / p; i++) {
        for (int j = 0; j < n; j++) {
          adj_matrix_local[i * n + j] = math.min(adj_matrix_local[i * n + j], adj_matrix_local[i * n + k] + adj_matrix_local[k * n + j]);
        }
      }

      // Gather the updated adjacency matrix from all processes
      if (my_rank == 0) {
        for (int i = 1; i < p; i++) {
          MPI_Recv(&adj_matrix[i * n / p][0], n * n / p, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
      } else {
        MPI_Send(adj_matrix_local, n * n / p, MPI_INT, 0, 0, MPI_COMM_WORLD);
      }
    }

    free(adj_matrix_local);
  }

  // Print the shortest path matrix
  if (my_rank == 0) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        printf("%d ", adj_matrix[i][j]);
      }
      printf("\n");
    }
  }

  MPI_Finalize();

  return 0;
}
