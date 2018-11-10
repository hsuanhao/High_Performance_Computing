// read_data.cpp 
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
#include <vector>
using namespace std;
//#include "least_squares.hpp"

int main()
{
  

    int n= 1651; //number of data points
    
    //Record position and velocity with considering Air resistance
    std::vector<double> time  (n);
    std::vector<double> yplot (n);  
    std::vector<double> yplot_air (n);
    std::vector<double> vyplot(n);
    std::vector<double> vyplot_air(n);
    std::vector<double> ydiff (n);
    std::vector<double> vydiff(n);

    // read the rocket_b.data
    string file_name("rocket_b.data");

    ifstream data_file(file_name.c_str());
    if (data_file.fail()) {
        cerr << "cannot open " << file_name << endl;
	return 0;
    } else
      cout << " reading data file: " << file_name << endl;

    string line; 
    int j = 0; 
    while (getline(data_file, line) && j < n) {
        if (line.c_str()[0] != '#') {    
	  stringstream sline(line);
	  int number=0;
	  double t=0., x=0., y=0., vx=0., vy=0.;
	  sline >> number >> t >> x >> y >> vx >> vy;
	  

	  time[j] = t; 
          yplot[j] = y;
          vyplot[j] = vy;
	  ++j; 
	}
    }
    data_file.close();

    // read the rocket_c.data
    string Rocket_air("rocket_c.data");

    ifstream data_file2(Rocket_air.c_str());
    if (data_file2.fail()) {
        cerr << "cannot open " << Rocket_air << endl;
	return 0;
    } else
      cout << " reading data file: " << Rocket_air << endl;

    string line2; 
    int k = 0; 
    while (getline(data_file2, line2) && k < n) {
        if (line2.c_str()[0] != '#') {    
	  stringstream sline(line2);
	  int number=0;
	  double t=0., x=0., y=0., vx=0., vy=0.;
	  sline >> number >> t >> x >> y >> vx >> vy;
	  
          yplot_air[k] = y;
          vyplot_air[k] = vy;
	  ++k; 
	}
    }
    data_file2.close();

    //Calculate the difference
    for(int i=0; i<n; i++){
      ydiff[i] = yplot[i] - yplot_air[i];
      vydiff[i] = vyplot[i] - vyplot_air[i];
    }

    //* Print out the plotting variables: 
    // time, ydiff, vydiff
  ofstream dataFile("rocket_diff.data");
     dataFile << "#" << '\t' << "time" << '\t'
          << "y_diff" << '\t' << "vy_diff"<< endl;
     for (int s = 0; s < n; s++) {
       dataFile << s << '\t' << time[s] << '\t'
                << ydiff[s] << '\t' << vydiff[s] << '\n';
     }
     dataFile.close();

    
   return 0;
}
