#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[])

{
    int num_teams = 114;
    int thread_limit = 4 * 32;
#pragma omp target teams parallel num_teams(num_teams) thread_limit(thread_limit)
    {
        printf("Hello world! I'm thread from %d out of %d in team %d. My global thread id is %d out of %d \n", omp_get_thread_num(), thread_limit, omp_get_team_num(), omp_get_team_num() * thread_limit + omp_get_thread_num(), num_teams * thread_limit);
    } // end target teams parallel
    return 0;
}
