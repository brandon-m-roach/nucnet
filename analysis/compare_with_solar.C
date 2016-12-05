//---------------------------------------------------------
//
// This is a code that compares results of the network 
// calculations with solar abundances from Rauscher et al.
// Astrophys. J. 576 (2002) 323
//
// Results are saved into a file:
//	- ../results/ratio_to_solar.dat
//
//---------------------------------------------------------

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdint.h>

using namespace std;

int main()
{
int nuc_z, nuc_a;
double nuc_x;
double Solar[95][240], MassFrac[95][240], Ratio[95][240];

char inPath1[200], inPath2[200], outPath[200];
fstream filein1, filein2, fileout;

// input files
sprintf(inPath1, "../pprocess/outputs_Nov9/pp_X_Z_A.dat");
filein1.open(inPath1, fstream::in);
if(!filein1){
	cout<<"Error opening input file1"<<endl;
	return -1;
}
sprintf(inPath2, "../pprocess/outputs_Nov9/solar_massfrac.dat");
filein2.open(inPath2, fstream::in);
if(!filein2){
	cout<<"Error opening input file2"<<endl;
	return -1;
}

// output file
sprintf(outPath, "../pprocess/outputs_Nov9/ratio_to_solar.dat");
fileout.open(outPath, fstream::out  | fstream::trunc);
if(!fileout){
	cout<<"Error opening output file"<<endl;
	return -1;
}


// read data to arrays
while(!filein1.eof()){
	filein1 >> nuc_z >> nuc_a >> nuc_x;
	MassFrac[nuc_z][nuc_a]=nuc_x;
//	cout << "f1 " << nuc_z << " " << nuc_a << " " << MassFrac[nuc_z][nuc_a] << endl;
}
cout << "Loaded file1" << endl;
while(!filein2.eof()){
	filein2 >> nuc_z >> nuc_a >> nuc_x;
	Solar[nuc_z][nuc_a]=nuc_x;
//	cout << "f2 " << nuc_z << " " << nuc_a << " " << Solar[nuc_z][nuc_a] << endl;
}
cout << "Loaded file2" << endl;
// get the ratio for each of the nuclides and write it into an output file 
// loops over Z<85 as the code runs up to that value only
for(int ZZ=0;ZZ<85;ZZ++){
	for (int AA=0; AA<240; AA++){
		// do the calculations only if the solar abundance exists
		if (Solar[ZZ][AA]!=0) {
		Ratio[ZZ][AA] = MassFrac[ZZ][AA] / Solar[ZZ][AA];
		fileout << ZZ << " " << AA << " " << Ratio[ZZ][AA] <<endl;	
		}
	}
}
cout << "Done. Check output file: ../results/ratio_to_solar.dat" << endl;


}


