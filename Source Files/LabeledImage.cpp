// ---------------------------------------------------------------------------
// LabeledImage.cpp
// Converts a binary image to a labeled image.
// 
// Author: Andrew Miloslavsky
// Date: October 2nd, 2015
// ---------------------------------------------------------------------------

#include "LabeledImage.h"
#include "DisjSets.h"
#include <set>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cmath>

// ---------------------------------------------------------------------------
// CONSTRUCTOR
// Purpose: Constructs a labeled image from the image.
//
// Parameters:
//		Parameter 1: Image file path
//		Parameter 2: Convert this image?
// ---------------------------------------------------------------------------
LabeledImage::LabeledImage( const char* path, bool convert ){

	// Try to read file into this object
	if( readImage( this, path ) == -1 ){
		if( !path )
			throw std::invalid_argument( "Invalid input file" );
		
		throw std::bad_alloc();
	}

	// Convert this image?
	if( convert )
		two_pass(); // Run two pass sequential labeling algorithm
}

LabeledImage::~LabeledImage( void ){ }

// ---------------------------------------------------------------------------
// Two_Pass
// Purpose: Labels objects in a binary image with varying grey levels. 
// ---------------------------------------------------------------------------
void LabeledImage::two_pass( void ){

	// Cache rows & columns
	const int current_rows = getNRows();
	const int current_cols = getNCols();

	// Vector for labels of dimensions [rows][columns]
	std::vector< std::vector<int> > labels(
		current_rows,
		std::vector<int>(current_cols, 0));

	// Create disjoint sets
	DisjSets disjSets( current_rows * current_cols );

	// Current label
	int current_label = 1;

	// First pass
	for ( int i = 0; i < current_rows; i++ ){
		for( int j = 0; j < current_cols; j++ ){
			
			const int pixel_value = getPixel( i, j );

			if( pixel_value != 0 ){

				// 4 way connectivity
				// Only check left and up (West & North)
				const int neighbor1 = ( i > 0 ) ? getPixel( i - 1, j ) 
											    : 0;
				const int neighbor2 = ( j > 0 ) ? getPixel( i, j - 1 ) 
										        : 0;

				if( neighbor1 != 0 
					&& neighbor2 == 0 ){

					// Take label of left pixel
					labels[ i ][ j ] = labels[ i-1 ][ j ];
				}
				else if( neighbor1 == 0 
					&& neighbor2 != 0 ){

					// Take label of upper pixel
					labels[ i ][ j ] = labels[ i ][ j-1 ];
				}
				else if( neighbor1 != 0 
					&& neighbor2 != 0 ){

					// Get neighbors
					int min_label = std::min( labels[ i-1 ][ j ], labels[ i ][ j-1 ] );
					int max_label = std::max( labels[ i-1 ][ j ], labels[ i ][ j-1 ] );

					// If neighbors aren't equivalent
					if( labels[ i ][ j-1 ] != labels[ i-1 ][ j ] )
					{
						// Get set representatives
						int f1 = disjSets.find( max_label );
						int f2 = disjSets.find( min_label );

						// If set representatives aren't the same
						// Create a Union between the set reps of the neighbors
						if( f1 != f2 )
							disjSets.unionSets( f1, f2 );
					}

					// Take smallest label...
					labels[ i ][ j ] = min_label;
				}
				// No neighbors, give it a new label
				else
					labels[ i ][ j ] = current_label++;
			}
		}
	}

	// Create set to count total number of objects
	// This is needed in order to call the setColors() method
	std::set< int > total_objects;

	// Second pass
	for ( int i = 0; i < current_rows; i++ ){
		for( int j = 0; j < current_cols; j++ ){
			
			if( getPixel( i, j ) != 0 ) {

				// Get set representative for the pixel
				const int set = disjSets.find( labels[ i ][ j ] );
				
				total_objects.insert( set ); // Get unique labels/sets

				// Color pixel based off of index in the unique set,
				// in order to guarantee a unique color for up to 255 objects
				setPixel( i, j, std::distance( total_objects.begin(), total_objects.find( set ) ) + 1 ); 
			}
		}
	}
	
	// Set image colors to number of unique objects
	// This is set in order to differentiate greylevels betwen image objects
	setColors( total_objects.size() ); 
}

// ---------------------------------------------------------------------------
// Get_Objects
// Purpose: Gets all the unique objects from the image.
// ---------------------------------------------------------------------------
std::map< int, ObjectInfo > LabeledImage::get_objects( void ) const{

	const double rows = getNRows();
	const double cols = getNCols();

	// Create map of label -> object info
	std::map< int, ObjectInfo > objects;
	
	// Raster Scan
	int current_label = 0;
	for ( int i = 0; i < rows; i++ ){
		for ( int j = 0; j < cols; j++ ){
			
			current_label = getPixel( i , j );
			
			if( current_label ){

				ObjectInfo& obj = objects[ current_label ];

				// Update EEj, EEj2, EEi, EEi2, EEij, and area
				obj.area++;
				obj.eei += i;
				obj.eej += j;
				obj.eei2 += ( i * i );
				obj.eej2 += ( j * j );
				obj.eeij += ( i * j );
			}
		}
	}

	return objects;
}

// ---------------------------------------------------------------------------
// Process_Data
// Purpose: Calculate the row center, column center, minimum inertia, and 
//			orientation. Write the information to a database text 
//			file, and creates a line from ( row center, column center )
//			to the direction of the orientation on this image.
// Parameters:
// 		1: output path
// ---------------------------------------------------------------------------
void LabeledImage::process_data( const char* output_file ){

	std::map< int, ObjectInfo > objects = get_objects();

	// Create database
	std::ofstream database ( output_file );

	// Calculate object centers, min moments, and orientation
	// & Write them to the database
	std::map< int, ObjectInfo >::iterator it;
	for ( it = objects.begin(); it != objects.end(); it++ ){
		
		const int label = it->first;
		const double row_center = it->second.calculateRowCenter();
		const double col_center = it->second.calculateColCenter();
		const double min_inertia = it->second.calculateMinInertia();
		const double orientation = it->second.calculateOrientation();

		database << label << " "; // Write label
		database << row_center << " "; // Write row center
		database << col_center << " "; // Write column center
		database << min_inertia << " "; // Write min inertia
		database << orientation << " "; // Write orientation in RADIANS
		database << it->second.area; // Write area
		database << std::endl;

		// Normalized direction vector
		std::pair< double, double > direction_vector( cos( orientation ), sin( orientation ) );

		// Draw orientation line through object
		Image* im = this;
		line( im
			, row_center
			, col_center
			, ( row_center + ( direction_vector.first  * 60 ) )
			, ( col_center + ( direction_vector.second * 60 ) )
			, label + 1 );
		
		// Finish drawing orientation line through object
		 line( im
		 	, row_center
		 	, col_center
		 	, ( row_center - ( direction_vector.first  * 60 ) )
		 	, ( col_center - ( direction_vector.second * 60 ) )
		 	, label + 1 );
			 
		// Mark a black dot at ( row_center, col_center )
		setPixel( row_center, col_center, 0 );
	}
}

// ---------------------------------------------------------------------------
// Compare_To
// Purpose: Compares this image to a database filled with the following values:
//			label, center_x, center_y, minimum inertia, orientation separated
//			by a space, in a line by line format. Each line represents a
//			unique object.
// Parameters:
// 		1: database path
// ---------------------------------------------------------------------------
void LabeledImage::compare_to( const char* database ){

	// Create map of label -> object info
	std::map< int, ObjectInfo > objects = get_objects();

	// Read from database
	std::ifstream db( database );

	std::string	file_line;

	// Iterate through each object in the database
	while( std::getline( db, file_line ) ){

		std::istringstream ss( file_line );
		std::vector< std::string > values;

		// Save object values into array
		while( ss ){

			std::string str;
			ss >> str;
			values.push_back( str );
		}

		// Get objects from array
		const double rc1 = atof( values[ 1 ].c_str() );
		const double cc1 = atof( values[ 2 ].c_str() );
		const double inertia1 = atof( values[ 3 ].c_str() );
		const double orientation1 = atof( values[ 4 ].c_str() );
		const double area1 = atof( values[ 5 ].c_str());

		// Placeholder for object with closest area
		ObjectInfo* min_area_diff = 0;

		// Threshold for area matching
		const double threshold = 500;

		// Calculate object centers, min moments, and orientation
		// & Compare them to the database
		std::map< int, ObjectInfo >::iterator it;
		for ( it = objects.begin(); it != objects.end(); it++ ){
			
			const double rc2 = it->second.calculateRowCenter();
			const double cc2 = it->second.calculateColCenter();
			const double inertia2 = it->second.calculateMinInertia();
			const double orientation2 = it->second.calculateOrientation();

			const double area2 = it->second.area;
			const double eei_2 = it->second.eei; 

			// Get object with min area
			if( std::abs( area1 - area2 ) < 500 )
				min_area_diff = &it->second;
		}
		
		// Match by area found
		if( min_area_diff ){
			
			// Normalized direction vector
			std::pair< double, double > dv( cos( min_area_diff->calculateOrientation() ), sin( min_area_diff->calculateOrientation() ) );
			
			// Mark the found objects
			Image* im = this;
			line( im
				, min_area_diff->calculateRowCenter()
				, min_area_diff->calculateColCenter()
				, ( min_area_diff->calculateRowCenter() + ( dv.first  * 60 ) )
				, ( min_area_diff->calculateColCenter() + ( dv.second * 60 ) )
				, 255 );
				
			// Mark the found objects
			line( im
				, min_area_diff->calculateRowCenter()
				, min_area_diff->calculateColCenter()
				, ( min_area_diff->calculateRowCenter() - ( dv.first  * 60 ) )
				, ( min_area_diff->calculateColCenter() - ( dv.second * 60 ) )
				, 255 );
				
			// Mark a black dot at ( row_center, col_center )
			setPixel( min_area_diff->calculateRowCenter(), min_area_diff->calculateColCenter(), 0 );
		}
	}
}