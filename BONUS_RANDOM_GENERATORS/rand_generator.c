#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int minimal_standard(int previous_rand);
int next_randu(int previous_rand);
double box_muller(double uniform, double uniform2);
double rand01();

int main() {
	
	
	FILE* out_randu = fopen("points_randu.dat", "w");
	FILE* out_min_st = fopen("points_minimal_standard.dat", "w");
	FILE* out_gauss = fopen("gauss_points.dat", "w");
	//puts("hi");
  int i,j,r=1;
  for (i=0; i<2000; i++) {
		for (j=0; j < 3; j++) {
			fprintf(out_randu, "%d ", r);
		  r = next_randu(r);
		}
		fprintf(out_randu,"\n");
	}
	
	r=1;
	for (i=0; i<2000; i++) {
		for (j=0; j < 3; j++) {
			fprintf(out_min_st, "%d ", r);
		  r = minimal_standard(r);
		}
		fprintf(out_min_st,"\n");
	}

  for (i=0; i < 50000;i++) {
		fprintf(out_gauss, "%lf\n", box_muller(rand01(), rand01()));
	}
	
	fclose(out_randu);
	fclose(out_min_st);
	fclose(out_gauss);
}

int minimal_standard(int previous_rand) {
  return (previous_rand * 16807) % 0x7FFFFFFF;//previous_rand * a + b;
}

// Cattivo generatore, riportato per motivi storici
// Per mostrare graficandolo che
// i punti si dispongono su piani.
int next_randu(int previous_rand) {
  return (previous_rand * 65539) % 0x80000000;
}

double box_muller(double uniform, double uniform2) {
	return sqrt(-2*log(uniform)) * cos(2*M_PI*uniform2);
}


double rand01() {
	return (double)rand() / (double)RAND_MAX ;
}
