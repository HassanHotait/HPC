#include <stdio.h>
#include <stdlib.h>
#include "mandel_offload.h"
#include "writepng.h"

#ifdef _OPENMP
#include <omp.h>
#else
#include <time.h>
#endif

int main(int argc, char *argv[])
{

    int width, height;
    int max_iter;
    int *image;

    width = 4601;
    height = 4601;
    max_iter = 400;

    // command line argument sets the dimensions of the image
    if (argc == 2)
        width = height = atoi(argv[1]);

    image = (int *)malloc(width * height * sizeof(int));
    if (image == NULL)
    {
        fprintf(stderr, "memory allocation failed!\n");
        return (1);
    }

#ifdef _OPENMP
    double start_time = omp_get_wtime();
#else
    double start_time = clock() / (CLOCKS_PER_SEC);
#endif
    mandel_offload(width, height, image, max_iter);
#ifdef _OPENMP
    double end_time = omp_get_wtime();
#else
    double end_time = clock() / (CLOCKS_PER_SEC);
#endif

    printf("Mandelbrot created in %f seconds\n", end_time - start_time);

    writepng("mandelbrot.png", image, width, height);

    return (0);
}
