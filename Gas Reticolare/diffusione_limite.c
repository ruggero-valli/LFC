#include "funzioni.h"
#include <string.h>


int main(int argv, char *argc[]){
    if (argv != 4){
        fprintf(stderr, "Error: 3 arguments expected\n"),
        printf("Usage:\n");
        printf("%s: <size> <sim number> <max steps>\n", argc[0]);
        exit(1);
    }
    int L = atoi(argc[1]);
    double NSIM = atoi(argc[2]);
    double tmax = atoi(argc[3]);
    double ro, dro = 0.01;
    int N, i;
    srand(time(NULL));

    char *gnuplot_commands[200] = {
        "f(x) = a*(1-x)**b + c*(1-x)**d",
        "fit f(x) 'diff_lim.dat' via a,b,c,d",
        "set terminal png size 800,600 enhanced",
        "set title 'Coefficiente di diffusione in funzione della densita'",
        "set xlabel '{/Symbol r}'",
        "set ylabel 'D({/Symbol r})'",
        "set grid",
        "set output 'D.png'",
        "plot 'diff_lim.dat' title 'data' pt 7 ps 0.6, f(x) title 'fit'",
        "end"
    };

    FILE *gnu = popen("gnuplot -persist", "w");
    FILE *out = fopen("diff_lim.dat", "w");

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
    double diff;
    for (ro = dro; ro < 1; ro += dro){
        N = L*L*ro;
        pos = mycalloc(N, sizeof(t_pos));
        abs_pos = mycalloc(N, sizeof(t_pos));
        diff = D(matrix, pos, abs_pos, L, N, ro, NSIM, tmax);
        fprintf(out, "%lf %lf\n", ro, diff);
        free(pos);
        free(abs_pos);
    }
    fclose(out);

    i=0;
    char *c;
    // Write the commands to the pipe
    c = gnuplot_commands[i];
    do {
        fprintf(gnu, "%s\n", c);
        i++;
        c = gnuplot_commands[i];
    } while (strcmp(c,"end") != 0);

    pclose(gnu);
    for (i=0; i<L; i++){
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}
