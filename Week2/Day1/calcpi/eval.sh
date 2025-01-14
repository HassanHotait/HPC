echo 'Default:'
make clean && make mode=default
./calcpi 1000000000
echo "Auto-parallelization:"
make clean && make mode=autopar
./calcpi 1000000000
echo "OpenMP:"
make clean && make mode=openmp 
OMP_NUM_THREADS=4 ./calcpi 1000000000
