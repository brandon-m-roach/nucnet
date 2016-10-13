//---------------------------------------------------------
//
// This is a code that searches the results of the network
// calculations for p-nuclei, compares the results with solar
// abundances from Rauscher et al.Astrophys. J. 576 (2002) 323
// and computes the overproduction factors as given in 
// Rapp et al. Astrophys. J 653 (2006) 474.
//
// Results are saved into a file:
//	- ../results/pnuclei_X_vs_solar.dat
//
//---------------------------------------------------------

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdint.h>

using namespace std;

int main()
{
char name[8];
int nuc_z, nuc_a;
double nuc_x;
double Solar[95][240]={0}, MassFrac[85][211]={0}, OverprodF[85][211]={0};
double F0 = 0;
double PnuclMF[85][211]={0};
int Pnucl[85][211];

char inPath1[200], inPath2[200], inPath3[200], outPath1[200], outPath2[200];
fstream filein1, filein2, filein3, fileout1, fileout2;

//input files
sprintf(inPath1, "../pprocess/output_rapp_fixed/pp_X_Z_A.dat");
filein1.open(inPath1, fstream::in);
if(!filein1){
	cout<<"Error opening input file1"<<endl;
	return -1;
}
sprintf(inPath2, "../pprocess/output_rapp_fixed/solar_massfrac.dat");
filein2.open(inPath2, fstream::in);
if(!filein2){
	cout<<"Error opening input file2"<<endl;
	return -1;
}
sprintf(inPath3, "../pprocess/output_rapp_fixed/p_nuclei.dat");
filein3.open(inPath3, fstream::in);
if(!filein3){
	cout<<"Error opening input file3"<<endl;
	return -1;
}

//output file
sprintf(outPath1, "../pprocess/output_rapp_fixed/pnuclei_X_vs_solar_beta_decayed.dat");
fileout1.open(outPath1, fstream::out  | fstream::trunc);
if(!fileout1){
	cout<<"Error opening output file"<<endl;
	return -1;
}



//read data to arrays
	while(!filein1.eof()){
		filein1 >> nuc_z >> nuc_a >> nuc_x;
		MassFrac[nuc_z][nuc_a]=nuc_x;
	}
	cout << "Loaded first input file" << endl;
	while(!filein2.eof()){
		filein2 >> nuc_z >> nuc_a >> nuc_x;
		Solar[nuc_z][nuc_a]=nuc_x;
	}
	cout << "Loaded second input file" << endl;
	while(!filein3.eof()){
		filein3 >> name >> nuc_z >> nuc_a;
		Pnucl[nuc_z][nuc_a]=1;
	}
	cout << "Loaded list of p-nuclei" << endl;

//sum all nuclides mass fraction for A equal to the mass of the p-nuclei and Z samller than for the p-nuclei (beta decay)
for(int ZZ=34;ZZ<81;ZZ++){
	for (int AA=0; AA<211; AA++){
		if (Pnucl[ZZ][AA]!=0){
			for (int i=81;i>=ZZ;i--){
				PnuclMF[ZZ][AA]=PnuclMF[ZZ][AA]+MassFrac[i][AA];
			}
		cout << ZZ << " " << AA << " " << PnuclMF[ZZ][AA] <<endl;
		}
	}
}
// the two nuclei that are shielded from beta decay by other p-nuclei of the same mass don't change:
PnuclMF[73][180]=MassFrac[73][180];
PnuclMF[57][138]=MassFrac[57][138];

//get the ratio for each of the nuclides and write it into an output file
for(int ZZ=0;ZZ<81;ZZ++){
	for (int AA=0; AA<211; AA++){
		if (Pnucl[ZZ][AA]!=0 && Solar[ZZ][AA]!=0) {
		OverprodF[ZZ][AA] = PnuclMF[ZZ][AA] / Solar[ZZ][AA];
		F0+=OverprodF[ZZ][AA];	
		}
	}
}

F0/=35.;
cout << "F0=  " << F0 << endl;

for(int ZZ=0;ZZ<81;ZZ++){
	for (int AA=0; AA<211; AA++){
		if (Pnucl[ZZ][AA]!=0 && Solar[ZZ][AA]!=0) {
		OverprodF[ZZ][AA] /= F0;
		fileout1 << ZZ << " " << AA << " " << PnuclMF[ZZ][AA] << " " << Solar[ZZ][AA] << " " << OverprodF[ZZ][AA] <<endl;	
		}
	}
}

cout << "Done. Check output files: ../pprocess/output_rapp/pnuclei_X_vs_solar_beta_decayed.dat" << endl;


}
