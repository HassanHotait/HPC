#include "data.h"

#ifdef ARRAY_OF_STRUCTS
double
distcheck(particle_t *p, int n)
{

    double dist = 0;
    for (int i = 0; i < n; i++)
    {

        double dist_i = p[i].dist;
        dist += dist_i;
    }

    return dist;
}
#else
double
distcheck(particle_t p, int n)
{

    double dist = 0;

    for (int i = 0; i < n; i++)
    {

        double dist_i = p.dist[i];
        dist += dist_i;
    }

    return dist;
}
#endif
