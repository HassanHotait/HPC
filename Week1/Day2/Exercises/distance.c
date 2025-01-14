#include "data.h"
#include <math.h>

#ifdef ARRAY_OF_STRUCTS
double
distance(particle_t *p, int n)
{

    double dist = 0;
    for (int i = 0; i < n; i++)
    {
        double dx = p[i].x - 0.0;
        double dy = p[i].y - 0.0;
        double dz = p[i].z - 0.0;
        double dist_i = sqrt(dx * dx + dy * dy + dz * dz);
        dist += dist_i;
    }
    return dist;
}
#else
double
distance(particle_t p, int n)
{

    double dist = 0;
    for (int i = 0; i < n; i++)
    {
        double dx = p.x[i] - 0.0;
        double dy = p.y[i] - 0.0;
        double dz = p.z[i] - 0.0;
        double dist_i = sqrt(dx * dx + dy * dy + dz * dz);
        p.dist[i] = dist_i;
        dist += dist_i;
    }
    return dist;
}
#endif
