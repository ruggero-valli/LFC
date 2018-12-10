#include "funzioni.h"

int main(int argv, char *argc[]){
    if (argv != 3){
        fprintf(stderr, "Error: 2 arguments expected\n"),
        printf("Usage:\n");
        printf("%s: <size> <density>\n", argc[0]);
        exit(1);
    }
    int L = atoi(argc[1]);
    double ro = atof(argc[2]);
    srand(time(NULL));
    int i;

    /*
    matrix contains in the cell i, j the number n of the
        particle in position i,j
    pos contains at position n, the t_pos struct with
        the coordinates of the nth particle
    abs_pos contains at position n, the t_pos struct with the x and y
        distance travelled by the nth particle since the beginning.
    */
    int N = L*L*ro;
    int **matrix = init_matrix(L);
    t_pos *pos = mycalloc(N, sizeof(t_pos));
    t_pos *abs_pos = mycalloc(N, sizeof(t_pos));
    populate_matrix(matrix, ro, L, N);
    populate_array(matrix, pos, abs_pos, L, N);

    print_matrix(matrix, L);
    print_array(pos, N);
    print_array(abs_pos, N);
    update(matrix, pos, abs_pos, L, N);
    print_matrix(matrix, L);
    print_array(pos, N);
    print_array(abs_pos, N);

    for (i=0; i<L; i++){
        free(matrix[i]);
    }
    free(matrix);
    free(pos);
    free(abs_pos);
    return 0;
}
