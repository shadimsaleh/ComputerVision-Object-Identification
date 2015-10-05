// ---------------------------------------------------------------------------
// LabeledImage.h
// Converts a binary image to a labeled image.
// 
// Author: Andrew Miloslavsky
// Date: October 2nd, 2015
// ---------------------------------------------------------------------------

#ifndef _LABELEDIMAGE_
#define _LABELEDIMAGE_

#include "Image.h"
#include "ObjectInfo.h"
#include <map>

class LabeledImage : public Image{

public:

	// ---------------------------------------------------------------------------
	// CONSTRUCTOR
	// Purpose: Constructs a labeled image from the image.
	//
	// Parameters:
	//		Parameter 1: Image file path
	//		Parameter 2: Convert this image?
	// ---------------------------------------------------------------------------
	LabeledImage( const char*, bool );

	~LabeledImage( void );
	
	// ---------------------------------------------------------------------------
	// Get_Objects
	// Purpose: Gets all the unique objects from the image.
	// ---------------------------------------------------------------------------
	std::map< int, ObjectInfo > get_objects( void ) const;

	// ---------------------------------------------------------------------------
	// Proces_Data
	// Purpose: Calculate the row center, column center, minimum inertia, and 
	//			orientation. Write the information to a database text 
	//			file, and creates a line from ( row center, column center )
	//			to the direction of the orientation on this image.
	// Parameters:
	// 		1: output path
	// ---------------------------------------------------------------------------
	void process_data( const char* output_file );

	// ---------------------------------------------------------------------------
	// Compare_To
	// Purpose: Compares this image to a database filled with the following values:
	//			label, center_x, center_y, minimum inertia, orientation separated
	//			by a space, in a line by line format. Each line represents a
	//			unique object.
	// Parameters:
	// 		1: database path
	// ---------------------------------------------------------------------------
	void compare_to( const char* database );
	
	// ---------------------------------------------------------------------------
	// Draw_Orientation
	// Purpose: Draws the orientation line depending on the input angle.
	//
	// Parameters:
	// 		1: Angle in RADIANS
	// ---------------------------------------------------------------------------
	void draw_orientation( const double angle );

private:

	// ---------------------------------------------------------------------------
	// Two_Pass
	// Purpose: Labels objects in a binary image with varying grey levels. 
	// ---------------------------------------------------------------------------
	void two_pass( void );
};

#endif