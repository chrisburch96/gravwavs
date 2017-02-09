/*
		GRAVITATIONAL WAVES DATA GENERATION GROUP
		
				NOISE GENERATION ROUTINE
*/

#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

#define C_PI 3.1415926536

using namespace std;

struct Signal{ //Struct to throw signals around
	
	int len; //Number of samples
	vector<double> time; //Vector of times
	vector<double> amplitude; //Amplitude of sample
	
};

Signal sigDriver( double (*generator)(), Signal sig); //adds noise to signal
double noiseGenGaussian(); //Returns a single sample of gaussian noise
Signal readSigFile(string filename); //Reads csv file into signal
int writeSigFile(string filename, Signal sig); //Writes signal to csv

int main(){
	
	string filename;
	cout<<"enter file name \n";
	cin >> filename;
	
	Signal sig = readSigFile(filename);
	
	Signal nSig = sigDriver(noiseGenGaussian, sig);
	
	writeSigFile("noisy_sig.csv", nSig);
	
	return 0;
	
}

Signal readSigFile(string filename){ //Reads signal from a csv file (but doesn't)
	
	Signal sig;
	ifstream sigFile(filename.c_str());
	int index=0;
	
	string line;
	
	while(sigFile.good()){
		
		getline(sigFile, line,',');
		sig.time[index] = atof(line);
		
		getline(sigFile, line);
		sig.amplitude[index] = atof(line);
		
		index += 1;
		
	}
	
	sig.len = index;
	
	return sig;
	
}

int writeSigFile(string filename, Signal sig){
	
	ofstream outFile;
	outFile.open(filename.c_str());
	
	for(int i=0, i<sig.len, i++){
		
		outFile<<sig.time[i]<<","<<sig.amplitude[i]<<"\n";
		
	}
	
	outFile.close();
	
	return 0;
	
}

Signal sigDriver( double (*generator)(), Signal sig){ //Takes a noise generator and applies it to each value in the signal

	int samples = sig.len; //Number of samples
	
	for(int i = 0; i<samples; i++){
		
		sig.amplitude[i] += (*generator)();

	}

}

/*
		LITERALLY COPIED FROM SOMEBODY ONLINE
		
		MUST BE CHANGED SO AS NOT TO VIOLATE UNIVERSITY/HUMAN RIGHTS LAW
		
		DON'T LET IT BE SEEN BY ANY MEMBERS OF STAFF
*/
double noiseGenGaussian(){/* Generates additive white Gaussian Noise samples with zero mean and a standard deviation of 1. */
 
  double temp1;
  double temp2;
  double result;
  int p;

  p = 1;

  while( p > 0 )
  {
	temp2 = ( rand() / ( (double)RAND_MAX ) ); /*  rand() function generates an
                                                       integer between 0 and  RAND_MAX,
                                                       which is defined in stdlib.h.
                                                   */

    if ( temp2 == 0 )
    {// temp2 is >= (RAND_MAX / 2)
      p = 1;
    }// end if
    else
    {// temp2 is < (RAND_MAX / 2)
       p = -1;
    }// end else

  }// end while()

  temp1 = cos( ( 2.0 * (double)C_PI ) * rand() / ( (double)RAND_MAX ) );
  result = sqrt( -2.0 * log( temp2 ) ) * temp1;

  return result;	// return the generated random sample to the caller

}// end AWGN_generator()
/*
		CONSIDER YOURSELF WARNED
*/
