#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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
int populate_matrix(int **matrix, int L, double ro);
t_pos* init_array(int **matrix, int L, int N);
void update(int **matrix, t_pos *pos, t_pos *abs_pos, int L, int N);

void* mycalloc(int N, int size){
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
    return rand()*INVRANDMAX > p;
}

double mod(double x, double m){
    // Compute x mod. m. Result is in [0,m)
    return fmod(fmod(x, m) + m, m);
}

void print_matrix(int **matrix, int L){
    int i, j;
    for (i=0; i<L; i++){
        for(j=0; j<L; j++){
            printf("%5d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void print_array(t_pos *array, int N){
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
    // Alloc a matrix of int and set it to -1
    int **matrix = mycalloc(L, sizeof(int *));
    int i, j;
    for (i=0; i<L; i++){
        matrix[i] = mycalloc(L, sizeof(int));
        for (j=0; j<L; j++){
            matrix[i][j] = -1;
        }
    }
    return matrix;
}

int populate_matrix(int **matrix, int L, double ro){
    // Populate the matrix with L*ro gas particles
    int N = 0;
    int x, y;
    if (ro < 0.5){ // method 1
        while(N < L*L*ro){
            x = randrange(0, L);
            y = randrange(0, L);
            if (matrix[y][x] == -1){
                matrix[y][x] = N++;
            }
        }
    } else { // method 2
        int i,j;
        for (i=0; i<L; i++){
            for (j=0; j<L; j++){
                if (randbool(ro)){
                    matrix[i][j] = N++;
                }
            }
        }
    }
    return N;
}

t_pos* init_array(int** matrix, int L, int N){
    // Create and sync the array of positions with the matrix
    t_pos *pos = mycalloc(N, sizeof(t_pos));
    int i,j;
    int p;
    for (i=0; i<L; i++){
        for(j=0; j<L; j++){
            p = matrix[i][j];
            if (p != -1){
                pos[p].x = j;
                pos[p].y = i;
            }
        }
    }
    return pos;
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
