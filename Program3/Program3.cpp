// ---------------------------------------------------------------------------
// Program3.cpp
// Calculates the area, center row, center column, inertial mass, and 
// orientation of labeled objects in the image. Lines are then drawn on
// objects to indicate their position and orientation.
// 
// Author: Andrew Miloslavsky
// Date: October 2nd, 2015
// ---------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <utility>
#include <set>
#include <cmath>
#include "LabeledImage.h"

int main(int argc, char** argv){

	if( argc < 3 ) {
		std::cout << "Not enough arguments! (3)" << std::endl;
		return -1;
	}

	const char* input_file = argv[ 1 ]; // input file
	const char* output_file = argv[ 2 ]; // output file
	const char* output_image = argv[ 3 ]; // output image

	// Create Labeled Image (Inherits from Image) on the heap in case of large image
	LabeledImage* lab = new LabeledImage( input_file, false );
	
	// Get objects & process the data
	lab->process_data( output_file );

	// Write/Create image
	writeImage( lab, output_image );

	delete lab;

	return 0;
}