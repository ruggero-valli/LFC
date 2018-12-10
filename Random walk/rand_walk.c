// Compilare con almeno C99

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
//#include <limits.h>

typedef struct t_point {
  int x;
  int y;
} t_point;


t_point advance1d(t_point point);
t_point advance(t_point point);
int rand_bool();
double distance_square(t_point point);

int main(int argc, char *argv[]) {
   if (argc != 3+1){
       printf("Usage: %s <N_PASSI> <N_SIM> <N_BIN>\n", argv[0]);
       printf(" N_PASSI: numero di passi per ogni simulazione\n");
       printf(" N_SIM: numero di storie da eseguire\n");
       printf(" N_BIN: numero di bin nell'istogramma\n");
       exit(1);
   }
  // Prendo argomenti
  int N_PASSI = atoi(argv[1]);
  int N_SIM = atoi(argv[2]);
  int N_BIN = atoi(argv[3]);
  //define N_BIN 20
  
  // PARTE IN UNA DIMENSIONE
  //double size1d = 3*sqrt(N_BIN);
  //double size2d = 3*(1/sqrt(2))*sqrt(N_BIN); //FARE QUESTO
  FILE* out1d = fopen("out1d.dat", "w");
  FILE* xt = fopen("xt.dat", "w");
  FILE* px = fopen("px.dat", "w");
  
  // Usiamo il tempo corrente come seed
  // perche' data la precisione di time lo
  // approssimiamo come numero random
  srand(time(NULL));
  int x = 0;
  int *arr = calloc(N_PASSI, sizeof(int));
  if (arr == NULL){
    fprintf(stderr, "Errore: Memoria terminata\n");
    exit(2);
  }
  
  // Per un istogramma migliore prendere pochi passi
  // e tante simulazioni per ottenere anche risultati 
  // verso gli estremi.
  int *hist = calloc(N_BIN, sizeof(int));
  if (hist == NULL){
    fprintf(stderr, "Errore: Memoria terminata\n");
    exit(2);
  }
  // verifica avg x(N_PASSI)^2 ~ N_PASSI
  int s, t;
  int norm_x;
  
  for (s =0; s < N_SIM; s++){
    x = 0;
    for (t=0; t < N_PASSI; t++) {
        // S indica il numero della simulazione
        // T il tempo
        fprintf(out1d, "S %d T %d X %d\n", s, t, x);
        arr[t] += x * x;
        x += (rand_bool() ? 1 : -1);
    }
    // Normalizzo x dall'intervallo [-N_PASSI, +N_PASSI]
    // all'intervallo [0, N_BIN]
    norm_x = (x + N_PASSI) / (2.0 * N_PASSI) *N_BIN;
    hist[norm_x] ++;
  }
  
  for (t=0; t<N_PASSI; t++){
    fprintf(xt, "%d %lf\n", t, ((double)arr[t])/(double)N_SIM);
  }
  
  for (t=0; t<N_BIN; t++){
    fprintf(px, "%lf %lf\n", ((2.0*N_PASSI)/N_BIN)*t - N_PASSI, ((double) hist[t])/N_SIM);
  }
  
  // PARTE IN DUE DIMENSIONI
  FILE* out2d = fopen("out2d.dat", "w");
  FILE* xt2d = fopen("xt2d.dat", "w");
  FILE* px2d = fopen("px2d.dat", "w");
  t_point pos;
  double d2;
  t_point norm_pos;
  for (t=0; t<N_PASSI; t++){
    arr[t] = 0;
  }
    // Per un istogramma migliore prendere pochi passi
  // e tante simulazioni per ottenere anche risultati 
  // verso gli estremi.
  //double hist2d[N_BIN][N_BIN] = {0};
  double (*hist2d)[N_BIN] = calloc(N_BIN, sizeof(double[N_BIN]));

  // verifica avg x(N_PASSI)^2 ~ N_PASSI
  for (s =0; s < N_SIM; s++){
    pos.x = 0;
    pos.y = 0;
    for (t=0; t < N_PASSI; t++) {
        fprintf(out2d, "S %d T %d X %d Y %d\n", s, t, pos.x, pos.y);
        //pos = advance(pos);
        d2 = distance_square(pos);
        arr[t] += d2;
        pos = advance(pos);
    }
    norm_pos.x = ((double) (pos.x + N_PASSI) / (2.0 * N_PASSI) )*N_BIN;
    norm_pos.y = ((double) (pos.y + N_PASSI) / (2.0 * N_PASSI) )*N_BIN;

    hist2d[norm_pos.x][norm_pos.y]++;
  }
  
  for (t=0; t<N_PASSI; t++){
    fprintf(xt2d, "%lf %lf\n", (double)t, ((double)arr[t])/(double)N_SIM);
  }
  
  int j;
  double norm_ind[2];
  for (t=0; t<N_BIN; t++){
    norm_ind[0] = ((2.0*N_PASSI)/N_BIN)*t - N_PASSI;
    for (j=0; j<N_BIN; j++){
       norm_ind[1] = ((2.0*N_PASSI)/N_BIN)*j - N_PASSI;
       // Svolgo la formula inversa per passare dall'indice
       // alle coordinate e divido il numero di volte si e' finiti in quella posizione
       // per il numero di simulazioni per ottenere la probabilita'
       fprintf(px2d, "%lf %lf %lf\n", norm_ind[0], norm_ind[1], hist2d[t][j]/N_SIM);
    }
  }
  fclose(out1d);
  fclose(xt);
  fclose(px);
  fclose(out2d);
  fclose(xt2d);
  fclose(px2d);
  
  free(arr);
  free(hist);
  free(hist2d);

}

t_point advance(t_point point) {
  t_point new;
  new.x = 0;
  new.y = 0;
  if (rand_bool()) {
    new.x = point.x + (rand_bool() ? 1 : -1);
    new.y = point.y;
  } else {
    new.x = point.x;
    new.y = point.y + (rand_bool() ? 1 : -1);
  }
  return new;
}

t_point advance1d(t_point point) {
  t_point new;
  new.x = point.x + (rand_bool() ? 1 : -1);
  new.y = point.y;
  return new;
}

double distance_square(t_point point){
    return point.x*point.x + point.y*point.y;
}

int rand_bool(){
    return (rand() / ( (double) RAND_MAX)) < 0.5;
}
