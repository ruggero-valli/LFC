#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct t_state{
    double x;
    double v;
    double t;
} t_state;


double phi(double x, double v, double t, double params[]);
t_state Eulero(t_state state, double dt, double params[]);
t_state Eulero_Cromer(t_state state, double dt, double params[]);
t_state RK2(t_state state, double dt, double params[]);
t_state RK4(t_state state, double dt, double params[]);
t_state simulate(double x0, double v0, double dt, double tmax, double params[], int method);
double linear_interpolation(double x1, double x2, double y1, double y2);

// Calculate the acceleration given the parameters and the state of the system
double phi(double x, double v, double t, double params[]){
    int phicode = params[0];
    double w2, gamma, a0, WF;
    switch(phicode){
        case 0:
            w2 = params[1];
            return -w2*state.x;
            break;
        case 1:
            w2 = params[1];
            gamma = params[2];
            a0 = params[3];
            WF = params[4];
            return -w2*sin(x) -gamma*v + a0*cos(WF*t);
            break;
        default:
            printf("Errore: phicode %d non riconosciuto\n", phicode);
            exit(2);
    }
}

// Integrate one step with Euler method
t_state Eulero(t_state state, double dt, double params[]){
   t_state new_state;
   new_state.x = state.x + state.v*dt;
   new_state.v = state.v + phi(state, params)*dt;
   new_state.t = state.t + dt;
   return new_state;
}

// Integrate one step with Euler-Cromer method
t_state Eulero_Cromer(t_state state, double dt, double params[]){
   t_state new_state;
   new_state.v = state.v + phi(state, params)*dt;
   new_state.x = state.x + new_state.v*dt;
   new_state.t = state.t + dt;
   return new_state;
}

// Integrate one step with Runge-Kutta method of second order
t_state RK2(t_state state, double dt, double params[]){
   double x = state.x, v = state.v, t = state.t;


   dx1 = v * dt;
   dv1 = phi(x, v, t, params);
   dx2 = v + dv1*(dt/2);
   dv2 = phi(x+dx2/2, v+dv1/2, t, params) + dt; // ???
   new_state.x = state.x + dx2*dt;
   new_state.v = state.v + dv2*dt;
   new_state.t = state.t + dt;
   return new_state;
}

// Integrate one step with Runge-Kutta method of fourth order
t_state RK4(t_state state, double dt, double params[]){
   t_state new_state = state;
   double k1[2], k2[2], k3[2], k4[2];
   k1[0] = state.v;
   k1[1] = phi(state, params);
   new_state.v = k1[1] = phi(state, params);
   k2[0] = state.v + k1[1]*dt/2;
   new_state.x = k2[0]
   k2[1] = phi(new_state, params);
   k3[0] = state.v + k2[1]*dt/2;
   k3[1] = phi(new_state, params); 
   k4[0] = state.v + k3[1]*dt;
   k4[1] = phi(state, params);
   new_state.x = state.x + (k1[0]+2*k2[0]+ 2*k3[0]+k4[0])/6*dt;
   new_state.v = state.v + (k1[1]+2*k2[1]+ 2*k3[1]+k4[1])/6*dt;
   new_state.t = state.t + dt;
   return new_state;
}

// Integrate the equation until tmax and return the final state
t_state simulate(double x0, double v0, double dt, double tmax, double params[], int method){
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
            printf("Errore: metodo %d non riconosciuto\n", method);
            exit(1);
    }
    t_state state;
    state.x = x0;
    state.v = v0;
    state.t = 0;
    while(state.t < tmax){
        state = integrate(state, dt, params);
    }
    return state;
}



// Find the x coordintate of the intersection between the x axis and the line
// passing for (x1, y1) and (x2, y2)
double linear_interpolation(double x1, double x2, double y1, double y2){
    return x1 - y1*(x1-x2)/(y1-y2);
}
