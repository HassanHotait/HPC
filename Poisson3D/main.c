/* main.c - Poisson problem in 3D
 */
#include <stdio.h>
#include <stdlib.h>
#include "alloc3d.h"
#include "print.h"

#ifdef _JACOBI
#include "jacobi.h"
#endif

#ifdef _GAUSS_SEIDEL
#include "gauss_seidel.h"
#endif

#define N_DEFAULT 100

int main(int argc, char *argv[])
{
    int N = N_DEFAULT;
    int iter_max = 1000;
    double tolerance;
    double start_T;
    int output_type = 0;
    char *output_prefix = "poisson_res";
    char *output_ext = "";
    char output_filename[FILENAME_MAX];
    double ***u = NULL, ***u_new = NULL, ***f = NULL;

    /* Get the parameters from the command line */
    if (argc < 5)
    {
        fprintf(stderr, "Usage: %s <grid size> <max iterations> <tolerance> <start temperature> [output type]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    N = atoi(argv[1]);         // Grid size
    iter_max = atoi(argv[2]);  // Maximum number of iterations
    tolerance = atof(argv[3]); // Tolerance
    start_T = atof(argv[4]);   // Start temperature for all inner grid points
    if (argc == 6)
    {
        output_type = atoi(argv[5]); // Output type
    }

    // Allocate memory for grids
    if ((u = malloc_3d(N, N, N)) == NULL)
    {
        perror("Array u: allocation failed");
        exit(EXIT_FAILURE);
    }

    if ((u_new = malloc_3d(N, N, N)) == NULL)
    {
        perror("Array u_new: allocation failed");
        free_3d(u);
        exit(EXIT_FAILURE);
    }

    if ((f = malloc_3d(N, N, N)) == NULL)
    {
        perror("Array f: allocation failed");
        free_3d(u);
        free_3d(u_new);
        exit(EXIT_FAILURE);
    }

    // Initialize grids
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                if (i == 0 || i == N - 1 || j == 0 || j == N - 1 || k == 0 || k == N - 1)
                {
                    u[i][j][k] = 0.0; // Boundary conditions
                }
                else
                {
                    u[i][j][k] = start_T; // Initial guess for the interior
                }
                u_new[i][j][k] = u[i][j][k];
                f[i][j][k] = 0.0; // Source term (homogeneous case)
            }
        }
    }

    // Call the solver
#ifdef _JACOBI
    int iterations = jacobi(u, u_new, f, N, iter_max, &tolerance);
    printf("Jacobi method completed in %d iterations with final tolerance = %e\n", iterations, tolerance);
#endif

#ifdef _GAUSS_SEIDEL
    int iterations = gauss_seidel(u, f, N, iter_max, &tolerance);
    printf("Gauss-Seidel method completed in %d iterations with final tolerance = %e\n", iterations, tolerance);
#endif

    // Output results if requested
    switch (output_type)
    {
    case 0:
        // No output
        break;
    case 3:
        output_ext = ".bin";
        sprintf(output_filename, "%s_%d%s", output_prefix, N, output_ext);
        fprintf(stderr, "Writing binary dump to %s: ", output_filename);
        print_binary(output_filename, N, u);
        break;
    case 4:
        output_ext = ".vtk";
        sprintf(output_filename, "%s_%d%s", output_prefix, N, output_ext);
        fprintf(stderr, "Writing VTK file to %s: ", output_filename);
        print_vtk(output_filename, N, u);
        break;
    default:
        fprintf(stderr, "Unsupported output type!\n");
        break;
    }

    // Deallocate memory
    free_3d(u);
    free_3d(u_new);
    free_3d(f);

    return 0;
}
