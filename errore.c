#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "funzioni.h"

double simple_oscill_energy(double x, double v, double w2);

int main(int argc, char* argv[]) {
    // Read parameters from input file
    //puts("hi");
    FILE *input = fopen("input/input_errore.dat", "r");
    FILE *output = fopen("data/energia_errore_vs_dt.dat", "w");
    double x0, v0, dt, tmax;
    int method;
    double params[5] = {0,0,0,0,0};
    fscanf(input, "%lf %lf %lf %lf", &x0, &v0, &dt, &tmax); 
    fscanf(input, "%d", &method);
    fscanf(input, "%lf", &params[1]);
    // Usiamo il pendolo semplice per lo studio dell'errore
    // perche' l'energia si conserva.
    /* PARAMS:
     * params[0] = 0
     * params[1] = w2
     * params[2] = 0
     * params[3] = 0
     * params[4] = 0
     */
    fclose(input);  
    
    t_state end;
    double E0 = simple_oscill_energy(x0, v0, params[1]);
    double E;
    for (; dt > 0.0001; dt/=1.1) {
			//puts("hi");
        end = simulate(x0, v0, dt, tmax+dt, params, method);
        //puts("hih");
        E = simple_oscill_energy(end.x, end.v, params[1]);
        fprintf(output, "%.12lf %.12lf\n", fabs(E-E0)/E0, dt);
    }
    return 0;
}

// E/2m per l'oscillatore armonico
double simple_oscill_energy(double x, double v, double w2) {
    return w2*x*x + v*v;
}
