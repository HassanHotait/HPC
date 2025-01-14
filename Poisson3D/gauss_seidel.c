/* gauss_seidel.c - Poisson problem in 3d
 *
 */
#include <math.h>
#include <stdio.h>

int gauss_seidel(double ***u, double ***f, int N, int iter_max, double *tolerance)
{
    int iter = 0;
    double max_diff = 0.0;

    do
    {
        max_diff = 0.0;

        // Iterate through the grid, excluding boundary points
        for (int i = 1; i < N - 1; i++)
        {
            for (int j = 1; j < N - 1; j++)
            {
                for (int k = 1; k < N - 1; k++)
                {
                    double u_old = u[i][j][k];
                    u[i][j][k] = 0.16666666667 * (u[i - 1][j][k] + u[i + 1][j][k] + // x-direction
                                                  u[i][j - 1][k] + u[i][j + 1][k] + // y-direction
                                                  u[i][j][k - 1] + u[i][j][k + 1] + // z-direction
                                                  f[i][j][k]);

                    // Update maximum difference for convergence check
                    double diff = fabs(u[i][j][k] - u_old);
                    if (diff > max_diff)
                    {
                        max_diff = diff;
                    }
                }
            }
        }

        iter++;

        // Print the iteration and max_diff for tracking
        printf("Iteration %d: max_diff = %e\n", iter, max_diff);

        // Stop if the maximum difference is less than the tolerance
        if (max_diff < *tolerance)
        {
            break;
        }
    } while (iter < iter_max);

    // Update the tolerance to the final maximum difference
    *tolerance = max_diff;

    return iter; // Return the number of iterations performed
}
