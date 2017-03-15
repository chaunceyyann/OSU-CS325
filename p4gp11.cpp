/**********************************************************
 *Group: 11
 *Term: Winter 2017
 *Class: CS_325_Analysis of Algorithms
 *Project 4
 *********************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stringstream;



int main(int argc, char *argv[]) {

	//check argument usage
	if (argc != 2) {
		printf("Usage: %s instance_file\n", argv[0]);
		exit(1);
	}


	std::ifstream ifs;	//for incoming problem instance
	std::ofstream ofs;	//for outgoing answer
	string filename;
	string outfile;
	string line1;
	string line2;
	int size = 50;
	int *temp;
	int *arr = new int[size];

	/******************************************************
	 *Import File Values
	 *****************************************************/
	 
	//read in file
	filename = argv[1];
	ifs.open(filename.c_str());

	//read data from file line by line
	ifs.clear();
	ifs.seekg(0, ifs.beg);

	while (!ifs.fail()) {

		//get each line
		std::getline(ifs, line2);
		stringstream ss(line2);


	 	//separate parts of line
	 	int n;
	 	int i = 0;
	 	while (ss >> n) {

	 		//copy number to array
			arr[i] = n;
			i++;

			//check size of array and incr if needed 
			if (i >= size) {

				size *= 2;
				temp = new int[size];

				//copy old values to new array
				for (int j = 0; j < i; j++)
					temp[j] = arr[j];

				//delete old pointer and repoint
				delete [] arr;
				arr = temp;
			}

	 	}
	}


	//open output file
	outfile = filename + ".tour";	
	ofs.open(outfile.c_str());

	if (ofs.fail()) {
		printf("Could not open output file\n");
	}


	//run algorithms


	//write results
		

	ofs.close();
	return 0;
}

