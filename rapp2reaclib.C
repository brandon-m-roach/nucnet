#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

int main(int argc, char* argv[]){

char line[200], line1[200], line2[200], line3[200];
char chapter;
int index=1;

ifstream inFile("save_reaclib_correct_chapters.wolf");
if(!inFile){
	cout << "Couldn't open input file" << endl; 
	exit(1);
}

while(!inFile.eof()){
	inFile.getline(line,200);
	//cout << line << endl;
	if (line[0]!=' '){ 
		chapter=line[0];
		inFile.getline(line,100);
		inFile.getline(line,100);
		//read in the next reaction		
		inFile.getline(line1,100);	
		inFile.getline(line2,100);
		inFile.getline(line3,100);
	}
	else{
		strcpy(line1,line);
		inFile.getline(line2,100);
		inFile.getline(line3,100);	
	}
	
	char filename[30];
	
	sprintf(filename,"rapp_rates_original/reac%d.dat",index);
	ofstream outFile(filename);

	//cout << chapter << endl;

	outFile << chapter << endl;
	//this line ^ is the one that has gone wrong
	//check save_reaclib.wolf to see where it's
	//getting the reaclib chapter from
	//I can't find any evidence of the chapter in save_reaclib.wolf
	//This means it must have some sort of 'dictionary' to convert
	//right!?!?!?!?!?

	//solution: for reac1.dat thru reac1442.dat, the value of chapter is 1
	//since they're all beta decays
	//use sed to replace the ^@ in the file with 1


	outFile << line1 << endl;
	outFile << line2 << endl;
	outFile << line3 << endl;
	outFile.close();	index++;
}


return 0;
}
