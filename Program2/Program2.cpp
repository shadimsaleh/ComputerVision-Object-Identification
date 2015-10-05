// ---------------------------------------------------------------------------
// Program2.cpp
// Labels objects in a binary image.
// 
// Author: Andrew Miloslavsky
// Date: October 2nd, 2015
// ---------------------------------------------------------------------------

#include <iostream>
#include "LabeledImage.h"

int main(int argc, char** argv){

	if(argc < 2){ 
		std::cout << "Not enough parameters! (2)" << std::endl;
		return -1;
	}

	const char* input_file = argv[ 1 ]; // input file
	const char* output_file = argv[ 2 ]; // output file

	// Create LabeledImage (Inherits from Image) on the heap in case of large file
	LabeledImage* lab = new LabeledImage( input_file, true );

	// Write/Create image
	writeImage( lab, output_file );

	delete lab; // Deallocate labeled image
	
	return 0;
}