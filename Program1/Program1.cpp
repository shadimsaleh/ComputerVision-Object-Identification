// ---------------------------------------------------------------------------
// Program1.cpp
// Converts a grey-level image to a binary image.
// 
// Author: Andrew Miloslavsky
// Date: October 2nd, 2015
// ---------------------------------------------------------------------------

#include <iostream>
#include <cstdlib>
#include "BinaryImage.h" //Inherits from Image

int main( int argc, char** argv ){

	if( argc < 3 ) {
		std::cout << "Incorrect number of arguments (3 required)";
		return -1;
	}
	
	const char* input_file = argv[1]; // input file
	const double threshold_value = atof( argv[2] ); // gray-level threshold
	const char* output_file = argv[3]; // output file
	
	// Create BinaryImage(Inherits from Image) object on the heap in case of a large image file
	BinaryImage* bin = new BinaryImage( input_file, threshold_value );

	bin->setColors( 1 ); // Set PGM Header colors to 1 since it's a binary image
	
	writeImage( bin, output_file ); // Write 'image' object into the output file
	
	delete bin; // Deallocate binary image
	
	return 0;
}