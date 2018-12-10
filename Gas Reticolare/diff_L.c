#include "funzioni.h"
#include <string.h>


int main(int argv, char *argc[]){
    if (argv != 4){
        fprintf(stderr, "Error: 3 arguments expected\n"),
        printf("Usage:\n");
        printf("%s: <ro> <sim number> <max steps>\n", argc[0]);
        exit(1);
    }
    double ro = atof(argc[1]);
    double NSIM = atoi(argc[2]);
    int tmax = atoi(argc[3]);
    int L, Lmax = 100, dL = 20;
    int N, i;
    srand(time(NULL));

    char *gnuplot_commands[200] = {
        "set terminal png size 800,600 enhanced",
        "set title 'Coefficiente di diffusione nel tempo, per diversi valori di L'",
        "set xlabel 't'",
        "set ylabel 'A(t)'",
        "set grid",
        "set logscale y",
        "set output 'A_L.png'",
        "end"
    };

    FILE *gnu = popen("gnuplot -persist", "w");

    i=0;
    char *c;
    // Write the commands to the pipe
    c = gnuplot_commands[i];
    do {
        fprintf(gnu, "%s\n", c);
        i++;
        c = gnuplot_commands[i];
    } while (strcmp(c,"end") != 0);
    fprintf(gnu, "set label '{/Symbol r}=%.2lf' at screen 0.5, 0.8\n", ro);
    fprintf(gnu, "plot ");
    for (L = dL; L < Lmax; L += dL){
        fprintf(gnu, "'-' title 'L=%d', ", L);
    }
    fprintf(gnu, "\n");

    /*
    matrix contains in the cell i, j the number n of the
        particle in position i,j
    pos contains at position n, the t_pos struct with
        the coordinates of the nth particle
    abs_pos contains at position n, the t_pos struct with the x and y
        distance travelled by the nth particle since the beginning.
    */
    int **matrix = init_matrix(L);
    t_pos *pos, *abs_pos;
    double *diff; // Array with diff coefficient for every t
    for (L = dL; L < Lmax; L += dL){
        N = L*L*ro;
        pos = mycalloc(N, sizeof(t_pos));
        abs_pos = mycalloc(N, sizeof(t_pos));
        diff = A(matrix, pos, abs_pos, L, N, ro, NSIM, tmax);
        for (i=0; i<tmax; i++){
            fprintf(gnu, "%d %lf\n", i, diff[i]-diff[tmax-1]);
        }
        fprintf(gnu, "e\n");
        free(diff);
        free(pos);
        free(abs_pos);
    }

    pclose(gnu);
    for (i=0; i<L; i++){
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}
