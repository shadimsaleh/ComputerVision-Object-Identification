// ---------------------------------------------------------------------------
// Program4.cpp
// Compares a labeled image to database containing label, center row, center
// column, inertial mass, and orientation. It then draws lines on the image
// to indicate a match between a database entry and an object in the image.
// 
// Author: Andrew Miloslavsky
// Date: October 2nd, 2015
// ---------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include "LabeledImage.h"

int main(int argc, char** argv){

	if( argc < 4 )
	{
		std::cout << "Not enough arguments! (4)" << std::endl;
		return -1;
	}

	const char* input_image = argv[ 1 ];
	const char* database = argv[ 2 ];
	const char* output_image = argv[ 3 ];

	// Create new labeled image 
	LabeledImage* lab = new LabeledImage( input_image, false );

	// Compare the labeled image to the database
	lab->compare_to( database );

	// Write/Create image
	writeImage( lab, output_image );

	delete lab; // Free memory

	return 0;
}