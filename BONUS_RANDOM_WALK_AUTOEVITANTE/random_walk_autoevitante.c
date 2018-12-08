#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define SIZE 320
#define N_SIMULAZIONI 15000
#define MAX_PASSI 300

typedef struct t_pos {
	int x;
	int y;
} t_pos;

t_pos advance(t_pos start_pos, int visited[SIZE][SIZE]);
int all_full_near(t_pos start_pos, int visited[SIZE][SIZE]); // 0 o 1
t_pos random_move(t_pos start_pos);
double r01();
int si_blocca(int visited[SIZE][SIZE], int n_passi); // 0 o 1
void azzera(int visited[SIZE][SIZE]);

int main() {
	// TEST
	
	// Test del generatore tra 0 e 1 sempre
	assert( 0 <= r01() <= 1);
	
	// Test che nel movimento casuale
	// almeno una coordinata non cambia
	// e che almeno una coordinata cambia di uno.
	t_pos test = {1, 2};
	t_pos result = random_move(test);
	assert(test.x == result.x || test.y == result.y);
	assert(test.x == result.x + 1 || test.x == result.x - 1 \
	   ||  test.y == result.y + 1 || test.y == result.y - 1);
	
	// Test che intorno a  `test = {1, 2};` sia tutto pieno
	int matrix_test[SIZE][SIZE] = { {0,0,0,0},
		                              {0,1,0,0},
		                              {1,0,1,0},
		                              {0,1,0,0} };
  assert(all_full_near(test, matrix_test));
	
	// Test di dove si muove con solo una possibilità
	// libera (test = {1,2} può andare solo a destra)
	int matrix_test2[SIZE][SIZE] = { {0,0,0,0},
		                               {0,1,0,0},
		                               {1,0,0,0},
		                               {0,1,0,0} };
  t_pos expected = {2, 2};
  t_pos result2 = advance(test, matrix_test2);
  //printf("expected: %d %d |result: %d %d\n", expected.x, expected.y, result2.x, result2.y);           
	assert( result2.x == expected.x && result2.y == expected.y);
	// FINE TEST
	
	
	srand(time(NULL));
	int visited[SIZE][SIZE] = {0};
	
	
	// fare attenzione ai bordi della matrice
	int n_passi, i, blocchi;
	for(n_passi = 0; n_passi < MAX_PASSI; n_passi++) {
	  blocchi = 0;
	  for( i=0; i < N_SIMULAZIONI; i++) {
	    blocchi += si_blocca(visited, n_passi);
	    azzera(visited);
	  }
	  printf("%d %lf\n", n_passi, blocchi / (double) N_SIMULAZIONI);
	}
	 
	
	
}

// Questo tiene conto del fatto che è autoevitante.
t_pos advance(t_pos start_pos, int visited[SIZE][SIZE] ) {
	//puts("start");
	if (all_full_near(start_pos, visited)) {
		//puts("inside if");
		return start_pos;
	}
	t_pos try;
	//puts("before loop");
	while (1) {
		try = random_move(start_pos);
		//printf("in loop try = %d %d\n", try.x, try.y); 
		if (visited[try.y][try.x] == 0) {
			return try;
		}
	}
}

int si_blocca(int visited[SIZE][SIZE], int n_passi) {
	t_pos pos = {0,0};
	t_pos new_pos;
	int i;
	for (i=0; i < n_passi; i++) {
		visited[pos.y][pos.x] = 1;
		new_pos = advance(pos, visited);
		if (pos.x > SIZE-2 || pos.y > SIZE-2 || -pos.x > SIZE-2 || -pos.y > SIZE-2) {
			return 0; // se arriva così lontano lo considero libero
		}
		// new_pos == pos
		if (new_pos.x == pos.x && new_pos.y == pos.y  ) {
			return 1; // la funzione advance ritorna la stessa posizione
			// se non si può muovere
		}
		pos = new_pos;
	}
	return 0;//ha svolto tutti i passi senza bloccarsi.
		
}

void azzera(int visited[SIZE][SIZE]) {
	int i,j;
	for (i=0; i < SIZE; i++) {
		for (j=0; j < SIZE; j++) {
			visited[i][j] = 0;
		}
	}
}

int all_full_near(t_pos start_pos, int visited[SIZE][SIZE] ) {
	int x = start_pos.x;
	int y = start_pos.y;
	return (visited[y+1][x] == 1 && visited[y-1][x] == 1 \
	     && visited[y][x+1] == 1 && visited[y][x-1] == 1);
}

t_pos random_move(t_pos start_pos) {
	t_pos new_pos;
  if (r01() < 0.5) {
		new_pos.x = start_pos.x + (r01() < 0.5 ? 1 : -1);
		new_pos.y = start_pos.y;
	} else {
		new_pos.x = start_pos.x;
		new_pos.y = start_pos.y + (r01() < 0.5 ? 1 : -1);
	}
	return new_pos;
}

double r01() {
    return (double)rand() / (double)RAND_MAX ;
}
