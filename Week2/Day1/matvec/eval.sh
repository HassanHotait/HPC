echo 'Default:'
make clean && make mode=default
./matvec 10000 10000
echo "Auto-parallelization:"
make clean && make mode=autopar
./matvec 10000 10000
echo "OpenMP:"
make clean && make mode=openmp 
OMP_NUM_THREADS=4 ./matvec 10000 10000
