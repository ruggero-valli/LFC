#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "funzioni.h"


int main(){
    // Read parameters from input file
    FILE *input = fopen("input/input_fasi.dat", "r");
    double x0, v0, dt, tmax;
    int method;
    double params[5];
    double TF;
    fscanf(input, "%lf %lf %lf %lf", &x0, &v0, &dt, &tmax);
    fscanf(input, "%d", &method);
    fscanf(input, "%lf %lf %lf %lf %lf", &params[0], &params[1], &params[2], &params[3], &TF);
    params[4] = 2*M_PI/TF;
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
    double alpha;
    FILE *fasi = fopen("data/spazio_fasi.dat", "w");
    FILE *poincare = fopen("data/poincare.dat", "w");
    while(state.t < tmax*100){ // Keep integrating 100 times more, to have decent poincare section
        state = integrate(state, dt, params);
        // wrap angle between -pi and pi
        alpha = mod(state.x+M_PI, 2*M_PI)-M_PI;
        if (state.t < tmax){    // save phasespace only until tmax
            fprintf(fasi, "%lf %lf\n", alpha, state.v);
        }
        if (fmod(state.t, TF)<dt){
            fprintf(poincare, "%lf %lf\n", alpha, state.v);
        }
    }
    fclose(fasi);
    fclose(poincare);

    return 0;
}
