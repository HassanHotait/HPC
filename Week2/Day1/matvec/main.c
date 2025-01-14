#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
#include <omp.h>
#else
#include <time.h>
#endif

void initialize_matrix(int **matrix, int rows, int cols, int init_val)
{
    *matrix = (int *)malloc(rows * cols * sizeof(int));
    if (*matrix == NULL)
    {
        perror("Failed to allocate memory for matrix");
        exit(EXIT_FAILURE);
    }

    // Fill the matrix with some values (e.g., sequential numbers for simplicity)
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            (*matrix)[i * cols + j] = init_val; // Example initialization
        }
    }
}

void initialize_vector(int **vector, int size, int init_val)
{
    *vector = (int *)malloc(size * sizeof(int));
    if (*vector == NULL)
    {
        perror("Failed to allocate memory for vector");
        exit(EXIT_FAILURE);
    }

    // Fill the vector with some values (e.g., sequential numbers for simplicity)
    for (int i = 0; i < size; ++i)
    {
        (*vector)[i] = init_val; // Example initialization
    }
}

void matrix_vector_multiply(int *matrix, int *vector, int *result, int rows, int cols)

{

#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (int i = 0; i < rows; ++i)
    {
        result[i] = 0;
        for (int j = 0; j < cols; ++j)
        {
            result[i] += matrix[i * cols + j] * vector[j];
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <MATSIZE> <VECSIZE>\n", argv[0]);
        return 1;
    }

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);

    if (rows <= 0 || cols <= 0)
    {
        fprintf(stderr, "Rows & Cols be positive.\n");
        return 1;
    }
    // int rows = 3, cols = 3;
    int *matrix, *vector, result[cols];
    int mat_init_val = 1, vec_init_val = 1;

    // Initialize matrix and vector
    initialize_matrix(&matrix, rows, cols, mat_init_val);
    initialize_vector(&vector, cols, vec_init_val);

    // // Print the matrix
    // printf("Matrix:\n");
    // for (int i = 0; i < rows; ++i)
    // {
    //     for (int j = 0; j < cols; ++j)
    //     {
    //         printf("%d ", matrix[i * cols + j]);
    //     }
    //     printf("\n");
    // }

    // // Print the vector
    // printf("Vector:\n");
    // for (int i = 0; i < cols; ++i)
    // {
    //     printf("%d ", vector[i]);
    // }
    // printf("\n");

// Perform matrix-vector multiplication
#ifdef _OPENMP
    double t1 = omp_get_wtime();
#else
    double t1 = (double)clock() / CLOCKS_PER_SEC;
#endif

    matrix_vector_multiply(matrix, vector, result, rows, cols);

#ifdef _OPENMP
    double t2 = omp_get_wtime();
#else
    double t2 = (double)clock() / CLOCKS_PER_SEC;
#endif

    // Print the result
    // printf("Result:\n");
    // for (int i = 0; i < rows; ++i)
    // {
    //     printf("%d ", result[i]);
    // }
    // printf("\n");

    // Print the time taken
    printf("Time taken: %.20f seconds\n", t2 - t1);

    // Free the allocated memory
    free(matrix);
    free(vector);

    return 0;
}
