echo 'Default:'
make clean && make
./mandelbrot
echo 'OpenMP:'
make clean && make mode=openmp
OMP_NUM_THREADS=12 ./mandelbrot


