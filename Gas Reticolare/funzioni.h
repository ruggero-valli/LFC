#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define Dim 2   // Number of dimensions

typedef struct t_pos {
    int x;
    int y;
} t_pos;

double INVRANDMAX=1/(RAND_MAX + 1.);

void* mycalloc(int N, int size);
double randrange(double a, double b);
int randbool(double p);
double mod(double x, double m);
void print_matrix(int **matrix, int L);
void print_array(t_pos *array, int N);
int** init_matrix(int L);
void populate_matrix(int **matrix, double ro, int L, int N);
void populate_array(int** matrix, t_pos* pos, t_pos* abs_pos, int L, int N);
void update(int **matrix, t_pos *pos, t_pos *abs_pos, int L, int N);

double R2(t_pos *abs_pos, int N);
double D(int** matrix, t_pos *pos, t_pos *abs_pos, int L, int N, double ro, int NSIM, int tmax);
double*A(int** matrix, t_pos *pos, t_pos *abs_pos, int L, int N, double ro, int NSIM, int tmax);


void* mycalloc(int N, int size){
    // Like calloc, but raises an error if fails to allocate
    void* ptr = calloc(N, size);
    if (ptr == NULL){
        fprintf(stderr, "Memory Error: allocation failed\n");
        exit(2);
    }
}

double randrange(double a, double b){
    // Generate a random double number in [a,b)
    return rand()*INVRANDMAX*(b-a)+a;
}

int randbool(double p){
    // Generate a random number either 0 or 1
    // with probability p that it is 1
    return rand()*INVRANDMAX < p;
}

double mod(double x, double m){
    // Compute x mod. m. Result is in [0,m)
    return fmod(fmod(x, m) + m, m);
}

void print_matrix(int **matrix, int L){
    // Print the matrix as a nice table on stdout
    // For debug purposes
    int i, j;
    for (i=0; i<L; i++){
        for(j=0; j<L; j++){
            printf("%5d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void print_array(t_pos *array, int N){
    // Print nicely the array of positions for debug purposes
    int i;
    for (i=0; i<N; i++){
        if (i%10 == 0){
            printf("\n|");
        }
        printf("%5d %3dx %3dy |", i, array[i].x, array[i].y);
    }
    printf("\n");
}

int** init_matrix(int L){
    // Allocate a matrix of int
    int **matrix = mycalloc(L, sizeof(int *));
    int i, j;
    for (i=0; i<L; i++){
        matrix[i] = mycalloc(L, sizeof(int));
    }
    return matrix;
}

void populate_matrix(int **matrix, double ro, int L, int N){
    // Populate the matrix with L*L*ro gas particles
    int n=0;
    int x, y;
    int i,j;
    // Set the matrix to -1
    for (i=0; i<L; i++)
        for (j=0; j<L; j++)
            matrix[i][j] = -1;
    // Method 1
    if (ro < 0.5){
        while(n < N){
            x = randrange(0, L);
            y = randrange(0, L);
            if (matrix[y][x] == -1){
                matrix[y][x] = n++;
            }
        }
    // Method 2
    } else {
        while(1){
            for (i=0; i<L; i++){
                for (j=0; j<L; j++){
                    if (randbool(ro) && matrix[i][j] == -1){
                        matrix[i][j] = n++;
                    }
                    if(n >= N){
                        return;
                    }
                }
            }
        }
    }
}

void populate_array(int** matrix, t_pos* pos, t_pos* abs_pos, int L, int N){
    // Sync the array of positions with the matrix
    int i,j;
    int p;
    for (i=0; i<L; i++){
        for(j=0; j<L; j++){
            p = matrix[i][j];
            if (p != -1){
                pos[p].x = j;
                pos[p].y = i;
                abs_pos[p].x = 0;
                abs_pos[p].y = 0;
            }
        }
    }
}

void update(int** matrix, t_pos *pos, t_pos *abs_pos, int L, int N){
    // Update every particle in the matrix
    int i;
    t_pos delta_pos;
    t_pos new_pos;
    for (i=0; i<N; i++){
        delta_pos.x = 0; delta_pos.y = 0;
        if (randbool(0.5)){ // Move x
            delta_pos.x = randbool(0.5) ? -1 : 1;
        } else { // Move y
            delta_pos.y = randbool(0.5) ? -1 : 1;
        }
        new_pos.x = mod(pos[i].x + delta_pos.x, L);
        new_pos.y = mod(pos[i].y + delta_pos.y, L);

        if (matrix[new_pos.y][new_pos.x] == -1){
            matrix[new_pos.y][new_pos.x] = i;
            matrix[pos[i].y][pos[i].x] = -1;
            abs_pos[i].x += delta_pos.x;
            abs_pos[i].y += delta_pos.y;
            pos[i] = new_pos;
        }
    }
}



double R2(t_pos *abs_pos, int N){
    // Calculate the average R^2 where R is the distance from the starting
    // Point of every particle.
    int i;
    double res = 0;
    for (i=0; i<N; i++){
        res += abs_pos[i].x*abs_pos[i].x + abs_pos[i].y*abs_pos[i].y;
    }
    return res/N;
}

double D(int** matrix, t_pos *pos, t_pos *abs_pos, int L, int N, double ro, int NSIM, int tmax){
    // Calculate lim t->+inf of <R^2>/(2*Dim*t) where the mean is calcuated
    // over many simulations.
    int i,j;
    double avg = 0;
    for (i=0; i<NSIM; i++){
        populate_matrix(matrix, ro, L, N);
        populate_array(matrix, pos, abs_pos, L, N);
        for(j=0; j<tmax; j++){
            update(matrix, pos, abs_pos, L, N);
        }
        avg += R2(abs_pos, N);
    }
    return avg/(NSIM*2*Dim*tmax);
}

double* A(int** matrix, t_pos *pos, t_pos *abs_pos, int L, int N, double ro, int NSIM, int tmax){
    // Calculate <R^2>/(2*Dim*t) for every t, where the mean is calcuated
    // over many simulations.
    int i,j;
    double *avg = mycalloc(tmax, sizeof(double));
    for (i=0; i<NSIM; i++){
        populate_matrix(matrix, ro, L, N);
        populate_array(matrix, pos, abs_pos, L, N);
        for(j=0; j<tmax; j++){
            update(matrix, pos, abs_pos, L, N);
            avg[j] += R2(abs_pos, N);
        }
    }
    for (i=0; i<tmax; i++){
        avg[i] = avg[i]/(NSIM*2*Dim*i);
    }
    return avg;
}
