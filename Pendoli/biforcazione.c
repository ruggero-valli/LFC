#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "funzioni.h"

// Diminuire N per un risultato piu' rapido ma meno preciso
#define N 100 // Numero di periodi della forzante da aspettare
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
    fscanf(input, "%lf %lf %lf", &x0, &v0, &dt);
    fscanf(input, "%d", &method);
    fscanf(input, "%lf %lf", &params[1], &params[2]);
    fscanf(input, "%lf %lf %lf %lf", &a0, &a1, &da, &TF);
    params[0]=1;  // Effetto di biforcazione presente solo per il pendolo smorzato
    params[4] = 2*M_PI/TF; // Converto il periodo in pulsazione
    tmax = N*TF;
    /* PARAMS:
    * params[0] = phicode
    * params[1] = w2
    * params[2] = gamma
    * params[3] = a0
    * params[4] = WF
    */

    fclose(input);

    t_state end;
    double a;
    for (a=a0; a<a1; a+=da){
        params[3]=a;
        end = simulate(x0, v0, dt, tmax, params, method);
        fprintf(output, "%lf %lf\n", a, end.v);
    }
    fclose(output);
    return 0;
}
