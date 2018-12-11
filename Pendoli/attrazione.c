#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "funzioni.h"


int main(){
	
	  // Read parameters from input file
    FILE *input = fopen("input/input_attrazione.dat", "r");
    FILE *output = fopen("data/attrazione_out.dat", "w");
    if (input == NULL || output == NULL){
      fprintf(stderr, "Missing directory: Please create ./data/ ./input/ and ./plots/ before running.");
      exit(0);
    }
    double x0, v0, dt, tmax;
    int method;
    double params[5];
    double TF;
    fscanf(input, "%lf %lf", &dt, &tmax);
    fscanf(input, "%d", &method);
    fscanf(input, "%lf %lf %lf %lf", &params[1], &params[2], &params[3], &TF);
    /* PARAMS:
     * params[0] = phicode
     * params[1] = w2
     * params[2] = gamma
     * params[3] = a0
     * params[4] = WF
     */
     params[0] = 1; // L'effetto caotico si manifesta solo con il pendolo

  t_state end;  
  for (x0=-M_PI; x0<M_PI; x0+=M_PI/500) {
		for (v0=-M_PI; v0<M_PI; v0+=M_PI/500) {
			end = simulate(x0, v0, dt, tmax, params, method);
			fprintf(output, "%lf %lf %lf\n", x0, v0, end.v);
		}			
	}
	
	fclose(input);
  fclose(output);

}
