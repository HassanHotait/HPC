/* jacobi.c - Poisson problem in 3d
 */
#include <math.h>
#include <stdio.h>

/**
 * Jacobi method for solving the 3D Poisson problem.
 *
 * @param u         Current grid values
 * @param u_new     Updated grid values
 * @param f         Right-hand side values (source term)
 * @param N         Grid size
 * @param iter_max  Maximum number of iterations
 * @param tolerance Pointer to the tolerance value; updated with the final max difference
 * @return          Number of iterations performed
 */
int jacobi(double ***u, double ***u_new, double ***f, int N, int iter_max, double *tolerance)
{
    int iter = 0;
    double diff, max_diff;

    do
    {
        max_diff = 0.0;

        // Update grid points using the Jacobi formula
        for (int i = 1; i < N - 1; i++)
        {
            for (int j = 1; j < N - 1; j++)
            {
                for (int k = 1; k < N - 1; k++)
                {
                    u_new[i][j][k] = (1.0 / 6.0) * (u[i + 1][j][k] + u[i - 1][j][k] +
                                                    u[i][j + 1][k] + u[i][j - 1][k] +
                                                    u[i][j][k + 1] + u[i][j][k - 1] -
                                                    f[i][j][k]);

                    diff = fabs(u_new[i][j][k] - u[i][j][k]);
                    if (diff > max_diff)
                    {
                        max_diff = diff;
                    }
                }
            }
        }

        // Copy u_new to u
        for (int i = 1; i < N - 1; i++)
        {
            for (int j = 1; j < N - 1; j++)
            {
                for (int k = 1; k < N - 1; k++)
                {
                    u[i][j][k] = u_new[i][j][k];
                }
            }
        }

        iter++;
        printf("Iteration %d: max_diff = %e\n", iter, max_diff);
    } while (iter < iter_max && max_diff > *tolerance);

    *tolerance = max_diff;
    return iter;
}
