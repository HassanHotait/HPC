#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _OPENMP
#include <omp.h>
#endif

double integrand(double x)
{
    return 4.0 / (1.0 + x * x);
}

double calculate_pi(int num_intervals)
{
    double sum = 0.0;
    double step = 1.0 / (double)num_intervals;

#ifdef _OPENMP
#pragma omp parallel for reduction(+ : sum)
#endif
    for (int i = 0; i < num_intervals; i++)
    {
        double x = (i + 0.5) * step;
        sum += integrand(x);
    }

    return sum * step;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <num_intervals>\n", argv[0]);
        return 1;
    }

    int num_intervals = atoi(argv[1]);
    if (num_intervals <= 0)
    {
        fprintf(stderr, "Number of intervals must be positive.\n");
        return 1;
    }

    double start_time, end_time;

#ifdef _OPENMP
    start_time = omp_get_wtime(); // Use OpenMP timer if OpenMP is enabled
#else
    start_time = (double)clock() / CLOCKS_PER_SEC; // Use clock() for default mode
#endif

    double pi = calculate_pi(num_intervals);

#ifdef _OPENMP
    end_time = omp_get_wtime(); // Use OpenMP timer
#else
    end_time = (double)clock() / CLOCKS_PER_SEC; // Use clock() for default mode
#endif

    printf("Calculated Pi: %.15f\n", pi);
    printf("Time taken: %.6f seconds\n", end_time - start_time);

    return 0;
}
