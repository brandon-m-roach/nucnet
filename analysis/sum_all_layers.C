//---------------------------------------------------------
//
// This is a code that sums up results of the network 
// calculations for all the SN layers included.
//
// Results are saved in two files:
//	- ../results/pp_X_Z_A.dat - containing abundances 
//		of all the simulated nuclides
//	- ../results/pp_X_A.dat - abundances summed for a
//		give mass number
//
// NOTE: the code outputs abundances not the mass fractions.
// For a given nuclide: MassFraction = Abundance * A
//---------------------------------------------------------

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

using namespace std;

int main()
{

int nuc_z, nuc_a;
double nuc_x, nuc_dx;
double MassFrac1[85][211], MassFrac2[85][211], wMassFrac[85][211], MassFracA[211];
//star properties from Rapp et al. Astrophys. J 653 (2006) 474
double LayerM[14]={1.9336, 1.9658, 2.0085, 2.0508, 2.1037, 2.1564, 2.2090, 2.2614, 2.3136, 2.3655, 2.4171, 2.4684, 2.5249, 2.5825};
double StarMass;
string line;

int zone;
char inPath1[200], inPath2[200], outPath1[200], outPath2[200];
fstream filein1, filein2, fileout1, fileout2;

//--------------------------------------------------------------------------------get the total mass of all simulated star layers

StarMass = LayerM[13]-LayerM[0];



//ouput files
sprintf(outPath1, "../pprocess/output_rapp_fixed/pp_X_Z_A.dat");
fileout1.open(outPath1, fstream::out  | fstream::trunc);
if(!fileout1){
	cout<<"Error opening output file1"<<endl;
	return -1;
}
sprintf(outPath2, "../pprocess/output_rapp_fixed/pp_X_A.dat");
fileout2.open(outPath2, fstream::out  | fstream::trunc);
if(!fileout2){
	cout<<"Error opening output file2"<<endl;
	return -1;
}



//------------------------------------------------------------------------------------------------------loop over all input files
for(zone=0; zone<13; zone++){

	//zero the MassFrac arrays
	for (int i=0; i<85; i++){
		for(int j=0;j<211;j++){
			MassFrac1[i][j]=0;
			MassFrac2[i][j]=0;
		}
	}

	//input files
	sprintf(inPath1, "../pprocess/output_rapp_fixed/pp_%i-last.dat", zone+158);
	filein1.open(inPath1, fstream::in);
	if(!filein1){
		cout<<"Error opening input file1"<<endl;
		return -1;
	}
	sprintf(inPath2, "../pprocess/output_rapp_fixed/pp_%i-last.dat", zone+158+1);
	filein2.open(inPath2, fstream::in);
	if(!filein2){
		cout<<"Error opening input file2"<<endl;
		return -1;
	}

	cout << "Processing zone: " << zone+158 << endl;

	//read the input file into MassFrac array
	//skip the header
	for (int i=0;i<4;i++){
		getline(filein1,line);
	}
	//get data
	while(!filein1.eof()){
		filein1 >> nuc_z >> nuc_a >> nuc_x >> nuc_dx;
		MassFrac1[nuc_z][nuc_a]=nuc_x * nuc_a; //calculate the mass fraction and put it in the table
	}
	//skip the header
	for (int i=0;i<4;i++){
		getline(filein2,line);
	}
	//get data
	while(!filein2.eof()){
		filein2 >> nuc_z >> nuc_a >> nuc_x >> nuc_dx;
		MassFrac2[nuc_z][nuc_a]=nuc_x * nuc_a; //calculate the mass fraction and put it in the table
	}


	//add the current zone to the final abundance array wMassFrac
	for (int i=0; i<85; i++){
		for(int j=0;j<211;j++){
			// sum of all the mass fractions of given nuc_z and nuc_a from all layers weighted by the layers masses
			wMassFrac[i][j] = wMassFrac[i][j] + 0.5 * ((MassFrac2[i][j]+MassFrac1[i][j])*(LayerM[zone+1] - LayerM[zone]));
			// in case something weird was produced
 			if(wMassFrac[i][j]<0 || wMassFrac[i][j]>1){
				cout << i << " " << j << " " << wMassFrac[i][j] << endl;			
			}
		}
	}

	filein1.close();
	filein2.close();
}

//-----------------------------------------------divide the wMassFrac by total star mass to get mass fractions rather than masses
for (int AA=0; AA<211; AA++){
	for(int ZZ=0;ZZ<85;ZZ++){
		wMassFrac[ZZ][AA] = wMassFrac[ZZ][AA] / StarMass;
	}
}


//zero the MassFracA array
for (int i=0; i<211; i++){
		MassFracA[i]=0;
}


//-------------------------------------------------------------------------------------------------sum abundances for given nuc_a
for (int AA=0; AA<211; AA++){
	for(int ZZ=0;ZZ<85;ZZ++){
		MassFracA[AA] = MassFracA[AA] + wMassFrac[ZZ][AA];
	}
}


//print final abundances
//for(int j=0;j<211;j++){
//	cout << j << " " << MassFracA[j] << endl;
//}

//-------------------------------------------------------------------------------------------------------write results into files
// write only non-zero values (most of the array is empty) 
// loop truncated as the code goes up to Z<85 only
for (int i=0; i<85;i ++){
	for (int j=0; j<211; j++){
		if(wMassFrac[i][j]!=0){
		fileout1 << i << " " << j << " " << wMassFrac[i][j] << endl;	
		}
	}
}
for (int j=0; j<211; j++){
	fileout2 << j << " " << MassFracA[j] << endl;	
}

cout << "Done. Check output files: ../results/pp_X_Z_A.dat and ../results/pp_X_A.dat." << endl;


}
