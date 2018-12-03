#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "funzioni.h"


int main(){
    // Read parameters from input file
    FILE *input = fopen("input/input_biforcazione.dat", "r");
    FILE *output = fopen("data/biforcazione.dat", "w");
    if (input == NULL || output==NULL){
      fprintf(stderr, "Missing directory: Please create ./data/ ./input/ and ./plots/ before running.");
      exit(0);
    }
    double x0, v0, dt, tmax;
    int method;
    double params[5];
    double TF;
    double a0, a1, da; // ampiezza della forzante, iniziale, finale e intervallo
    fscanf(input, "%lf %lf %lf %lf", &x0, &v0, &dt, &tmax);
    fscanf(input, "%d", &method);
    fscanf(input, "%lf %lf", &params[1], &params[2]);
    fscanf(input, "%lf %lf %lf %lf", &a0, &a1, &da, &TF);
    params[0]=1;  // Effetto presente solo per il pendolo smorzato
    params[4] = 2*M_PI/TF; // Converto il periodo in pulsazione
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
    double a;
    for (a=a0; a<a1; a+=da){
      state.x = x0;
      state.v = v0;
      state.t = 0;
      params[3]=a;
      while(state.t < tmax){
        state = integrate(state, dt, params);
    }
    fprintf(output, "%lf %lf\n", a, state.v);
    }
  fclose(output);
  return 0;
}
