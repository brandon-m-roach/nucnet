//---------------------------------------------------------
//
// Script that runs through the text output file of the calculations
// and extracts the time steps into separate text files.
// Everything in the input file that comes before the first 
// line that contains "t= " is ignored.
//
// ./extract_time_steps text_file zone_number
//
// Results are saved in:
// ../results/zone$zone_num/pp_zone$zone_num-$step.dat
//
//---------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

int main(int argc, char* argv[])
{
	int step;
	int zone;
	string line, time, dtime, t9, rho;
	size_t found, trash1, trash2;
	char inPath[200], outPath[200], dirPath[200];;
	fstream filein, fileout;

	if (argc!=3){
		cout << endl <<"		Wrong input parameters!" <<endl<<"		Use: ./extract_time_steps  path_to_file	zone_number" <<endl<<endl;
		return -1;
	}

	//input file
	strcpy (inPath,argv[1]);
	
	filein.open(inPath, fstream::in);
	if(!filein){
		cout<<"Error opening input file"<<endl;
		return -1;
	}

	zone = atoi(argv[2]);
	step = 0;
//	sprintf(dirPath,"/evtdata/spyrou-sim/network_calculations/simon/pprocess/results/zone%i",zone);
//	rmdir(dirPath);
//	mkdir(dirPath,777);

	while(!filein.eof()){
		getline(filein,line);
		if(!line.empty()){  // if line is not empty...
			trash1=line.find("1 - xsum");  
			trash2=line.find("Ye");		
			if(trash1!=0 && trash2!=0){	// doesnt contain checksum...or electron density...
					found=line.find("t =");
					if(found==0){	// if it has time data
						//open ouput file
						sprintf(outPath, "../pprocess/output_rapp_fixed/zone%i/pp_zone_%i_%i.dat", zone, zone, step);
						step++; //increment step # for the next file
						fileout.open(outPath, fstream::out  | fstream::trunc);
						if(!fileout){
							cout<<"Error opening output file"<<endl;
							return -1;
						}
						// and put time, temperature and density in the file
						time = line.substr(4,10);
						dtime = line.substr(21,10);
						t9 = line.substr(38,10);
						rho = line.substr(63,10);
						fileout << time << endl << dtime << endl << t9 << endl << rho << endl;
					}	
					else{ // it has to be an abundance data -> put that into the file
						fileout << line << endl;
					}

			}
			else{
				if (trash2==0){
					cout << "Finished step: " << step-1 <<endl;
					fileout.close(); // if found Ye of checksum -> end of abundance data -> get ready for a new file
				}
			}
		}

	}


}
