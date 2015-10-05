// ---------------------------------------------------------------------------
// BinaryImage.cpp
// Converts a grey-level image to a binary image.
// 
// Author: Andrew Miloslavsky
// Date: October 2nd, 2015
// ---------------------------------------------------------------------------

#include "BinaryImage.h"
#include <stdexcept>

// ---------------------------------------------------------------------------
// CONSTRUCTOR
// Purpose: Constructs a binary image from an image and calls a 
// conversion to binary format with a threshold value.
//
// Parameters:
//		Parameter 1: Image object initialized with greyscale image
//		Parameter 2: Threshold value
// ---------------------------------------------------------------------------
BinaryImage::BinaryImage( const Image& image, const int threshold ) : Image( image ){ 
	
	// Convert image to binary
	greyscale_to_binary( threshold ); 
}

// ---------------------------------------------------------------------------
// CONSTRUCTOR
// Purpose: Constructs a binary image from an image and calls a 
// conversion to binary format with a threshold value.
//
// Parameters:
//		Parameter 1: Image file path
//		Parameter 2: Threshold value
// ---------------------------------------------------------------------------
BinaryImage::BinaryImage( const char* file, const int threshold ){
	
	// Try to read file into 'image' object
	if(readImage( this, file ) == -1 ){
		if( !file )
			throw std::invalid_argument( "Invalid input file" );
		
		throw std::bad_alloc();
	}

	// Convert image to binary
	greyscale_to_binary( threshold );
}

BinaryImage::~BinaryImage( void ){ }

// ---------------------------------------------------------------------------
// GREYSCALE_TO_BINARY
// Purpose: Converts a greyscale image to a binary image using a threshold 
//			value.
//
// Parameters:
//		Parameter 1: Threshold value
// ---------------------------------------------------------------------------
void BinaryImage::greyscale_to_binary( int threshold_value ){
	
	for ( int i = 0; i < getNRows(); i++ ){
		for( int k = 0; k < getNCols(); k++ ){
			
			// Get pixel value at i, k
			const int pixel_value = getPixel( i,k );
			
			// Set pixel value at i, k to 0 or 255 (Black or White)
			setPixel( i, k, ( pixel_value < threshold_value ) ? 0 : 255 );
		}
	}
}