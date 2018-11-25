#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "funzioni.h"


int main(){
    // Read parameters from input file
    FILE *input = fopen("input/input.dat", "r");
    double x0, v0, dt, tmax;
    int method;
    double params[5];
    fscanf(input, "%lf %lf %lf %lf", &x0, &v0, &dt, &tmax);
    fscanf(input, "%d", &method);
    fscanf(input, "%lf %lf %lf %lf %lf", &params[0], &params[1], &params[2], &params[3], &params[4]);
    /* PARAMS:
     * params[0] = phicode
     * params[1] = w2
     * params[2] = gamma
     * params[3] = a0
     * params[4] = WF
     */
    fclose(input);

    // Choose integration method
    t_state (*integrate)(t_state state, double dt, double params[]);
    switch (method){
        case 0:
            integrate = Eulero;
            break;
        case 1:
            integrate = Eulero_Cromer;
            break;
        case 2:
            integrate = RK2;
            break;
        case 3:
            integrate = RK4;
            break;
        default:
            fprintf(stderr, "Errore, metodo %d non riconosciuto\n", method);
            exit(1);
    }


    t_state state;
    state.x = x0;
    state.v = v0;
    state.t = 0;
    FILE *output = fopen("data/simulazione.dat", "w");
    while(state.t < tmax){
        state = integrate(state, dt, params);
        fprintf(output, "%lf %lf %lf\n", state.t, state.x, state.v);
    }
    fclose(output);

    return 0;
}
