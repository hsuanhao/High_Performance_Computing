//Problem1_Rocket.cpp

// balle - Program to compute the trajectory of a baseball
//         using the Euler method.
// Adapted from Garcia, Numerical Methods for Physics, 2nd Edition
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
using namespace std;

int main() {
  /*In what follows, we set all vectors upward be positive. */

  //* Set initial position and velocity of the rocket
  double r1[2], v1[2], r[2], v[2], accel[2];

  //Enter initial height (meters) from the surface of earth:
  double y1 = 0.0;
  r1[0] = 0;  r1[1] = y1;     // Initial vector position
  //Enter initial speed in y-direction (m/s):
  double speed =0.0; 
  const double pi = 3.141592654; 
  v1[0] = 0.0;                     // Initial velocity (x)
  v1[1] = speed;                   // Initial velocity (y)
  r[0] = r1[0];  r[1] = r1[1];     // Set initial position and velocity
  v[0] = v1[0];  v[1] = v1[1];             
  
  double airFlag, rho;
  cout << "Air resistance? (Yes:1, No:0): "; 
  cin >> airFlag; //Consider air resistance or not. 
  
  /*Choose Algorithm*/
  int euler = 0;
  cout << "Use Euler (0), Euler-Cromer (1), or Midpoint(2) ? "; 
  cin >> euler;

  //* Loop until the maxStep
  // Enter time step, tau (sec):
  double tau = 0.1;  
  int iStep, maxStep = 1651;   //1651 Maximum number of steps
  //Record position and velocity with considering Air resistance
  std::vector<double> time  (maxStep);
  std::vector<double> xplot (maxStep);  
  std::vector<double> yplot (maxStep);
  std::vector<double> vyplot(maxStep);
  std::vector<double> vxplot(maxStep);
  

  //* Set physical parameters (mass, Cd, etc.)
  double Cd = 0.35;      // Drag coefficient (dimensionless)
  double area = 25.0;  // Cross-sectional area of projectile (m^2)
  double grav = 9.81;    // Gravitational acceleration (m/s^2)
  double mass = 2970000.0;   // Initial Mass of rocket (kg)
  double G = 6.67384e-11; // Gravitational constant (m^3 kg^-1 s^-2)
  double M = 5.97219e24;  // Mass of Earth (kg)  
  double R = 6371e3;      // Mean radius of Earth (m)
  double B = 17212.0;     // Burning rate (kg/s)

  for( iStep=0; iStep<maxStep; iStep++ ) {

    //* Record position (computed and theoretical) for plotting
    xplot[iStep] = r[0];   // Record trajectory for plot
    yplot[iStep] = r[1];
    vxplot[iStep] = v[0];
    vyplot[iStep] = v[1];
    double t = (iStep)*tau;     // Current time
    time[iStep] = t;
    // Gravitation change with the distance
    grav = G*M/((r[1]+R)*(r[1]+R));                   
    // Mass change with time
    double m1 = mass - B*t; // final mass of rocket
    // Applied force by burning (N)    
    double F_app = 34020e3;
    // Acceleration from applied force (m/s)
    double Accel_app = F_app/m1; 
    
    if( airFlag == 0 )
    rho = 0;  // No air resistance
    else
    rho = 1.2*exp(-r[1]/10000.0); // Density of air (kg/m^3)
    double air_const = -0.5*Cd*rho*area/mass;  // Air resistance constant

    //Check code whether correct or not 
    cout << "t= " << t << ";m= "<< m1 << ";h= " << r[1]
         << ";x= "<< r[0] << ";time= " << time[iStep]
         << ";rho= " << rho << "; g= " << grav 
         << ";Acce_app = " << Accel_app << endl;
    
    //* Calculate the acceleration of the ball 
    double normV = sqrt( v[0]*v[0] + v[1]*v[1] );
    accel[0] = air_const*normV*v[0];   // Air resistance
    accel[1] = air_const*normV*v[1];   // Air resistance
    accel[1] += (-1.0)*grav + Accel_app;   // Gravity & applied force
  
    //* Calculate the new position and velocity using Euler method
    if ( euler == 0 ) {       // Euler step
      r[0] += tau*v[0];                 
      r[1] += tau*v[1];                 
      v[0] += tau*accel[0];     
      v[1] += tau*accel[1];     
    } else if ( euler == 1 ) {// Euler-Cromer step
      v[0] += tau*accel[0];     
      v[1] += tau*accel[1];     
      r[0] += tau*v[0];                 
      r[1] += tau*v[1];                 
    } else {                  // Midpoint step
      double vx_last = v[0];
      double vy_last = v[1];
      v[0] += tau*accel[0];     
      v[1] += tau*accel[1];     
      r[0] += tau*0.5*(v[0] + vx_last);                 
      r[1] += tau*0.5*(v[1] + vy_last);
    }
    /*
    //* If ball reaches ground (y<0), break out of the loop
    if( r[1] < 0 )  {
      xplot[iStep] = r[0];  // Record last values computed
	  yplot[iStep] = r[1];
      break;                  // Break out of the for loop
    } 
    */
     
  }
  
  //* Print maximum range and time of flight
    cout << "Maximum height is " << yplot[iStep-1] << " meters" << endl;
    cout << "Time of flight is " << (iStep-1)*tau << " seconds" << endl;
    cout << "Maximum speed is " << vyplot[iStep-1] << " m/s" << endl;
    //Note that iStep becomes 1651, not 1650.


  //* Print out the plotting variables: 
  //    xplot, yplot, xNoAir, yNoAir
  ofstream dataFile("rocket.data");
     dataFile << "#" << '\t' << "time" << '\t'
          << "xplot" << '\t' << "yplot" << '\t' 
          << "vxplot" << '\t' << "vyplot" << '\t'
          << endl;
     for (int s = 0; s < maxStep; s++) {
       dataFile << s << '\t' << time[s] << '\t'
                << xplot[s] << '\t' << yplot[s] << '\t'
                << vxplot[s] << '\t' << vyplot[s] << '\t'
                << '\n';
     }
     dataFile.close();
/*
  ofstream plotOut("plot.txt"),
    noAirOut("noAirPlot.txt");
  int i;
  for( i=0; i<iStep; i++ ) {
    plotOut << xplot[i] << " ";
    plotOut << yplot[i] << endl;
  }
  for( i=0; i<iStep; i++ ) {
    noAirOut << xNoAir[i] << " ";
    noAirOut << yNoAir[i] << endl;
  }
*/
  return 0;
}
