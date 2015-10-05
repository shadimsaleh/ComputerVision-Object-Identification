// ---------------------------------------------------------------------------
// BinaryImage.h
// Converts a grey-level image to a binary image.
// 
// Author: Andrew Miloslavsky
// Date: October 2nd, 2015
// ---------------------------------------------------------------------------

#ifndef _BINARYIMAGE_
#define _BINARYIMAGE_

#include "Image.h"

class BinaryImage : public Image{

public:
	// ---------------------------------------------------------------------------
	// CONSTRUCTOR
	// Purpose: Constructs a binary image from an image and calls a 
	// conversion to binary format with a threshold value.
	//
	// Parameters:
	//		Parameter 1: Image object initialized with greyscale image
	//		Parameter 2: Threshold value
	// ---------------------------------------------------------------------------
	BinaryImage( const Image&, const int );

	// ---------------------------------------------------------------------------
	// CONSTRUCTOR
	// Purpose: Constructs a binary image from an image and calls a 
	// conversion to binary format with a threshold value.
	//
	// Parameters:
	//		Parameter 1: Image file path
	//		Parameter 2: Threshold value
	// ---------------------------------------------------------------------------
	BinaryImage( const char*, const int );

	~BinaryImage( void );

private:

	// ---------------------------------------------------------------------------
	// GREYSCALE_TO_BINARY
	// Purpose: Converts a greyscale image to a binary image using a threshold 
	//			value.
	//
	// Parameters:
	//		Parameter 1: Threshold value
	// ---------------------------------------------------------------------------
	void greyscale_to_binary( const int threshold_value );
};

#endif