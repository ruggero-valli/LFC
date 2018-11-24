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
            return -w2*x;
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
   new_state.v = state.v + phi(state.x, state.v, state.t, params)*dt;
   new_state.t = state.t + dt;
   return new_state;
}

// Integrate one step with Euler-Cromer method
t_state Eulero_Cromer(t_state state, double dt, double params[]){
   t_state new_state;
   new_state.v = state.v + phi(state.x, state.v, state.t, params)*dt;
   new_state.x = state.x + new_state.v*dt;
   new_state.t = state.t + dt;
   return new_state;
}

// Integrate one step with Runge-Kutta method of second order
t_state RK2(t_state state, double dt, double params[]){
   double x = state.x, v = state.v, t = state.t;
   t_state new_state;


   double dx1 = v * dt;
   double dv1 = dt*phi(x, v, t, params);

   double dx2 = dt*(v + dv1/2.0);
   double dv2 = dt*phi(x+dx1/2.0, (v + dv1/2.0), (t+dt/2.0), params);

   new_state.x = state.x + dx2*dt;
   new_state.v = state.v + dv2*dt;
   new_state.t = state.t + dt;
   return new_state;
}


// Integrate one step with Runge-Kutta method of fourth order
t_state RK4(t_state state, double dt, double params[]){
	
   double x = state.x, v = state.v, t = state.t;
   t_state new_state;


   double dx1 = v * dt;
   double dv1 = dt*phi(x, v, t, params);

   double dx2 = dt*(v + dv1/2.0);
   double dv2 = dt*phi(x+dx1/2.0, (v + dv1/2.0), (t+dt/2.0), params);

   double dx3 = dt*(v + dv2/2.0);
   double dv3 = dt*phi(x+dx2/2.0, (v + dv2/2.0), (t+dt/2.0), params);

   double dx4 = dt*(v + dv3);
   double dv4 = dt*phi(x+dx3, (v + dv3), (t+dt), params);

   new_state.x = state.x + ((dx1 + 2*dx2 + 2*dx3 + dx4)/6.0);
   new_state.v = state.v + ((dv1 + 2*dv2 + 2*dv3 + dv4)/6.0);
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
