// ---------------------------------------------------------------------------
// ObjectInfo.cpp
// Contains information about objects in an image. Also provides methods
// for calculating their minimal inertia, orientation, and midpoint.
// 
// Author: Andrew Miloslavsky
// Date: October 2nd, 2015
// ---------------------------------------------------------------------------

#include "ObjectInfo.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

// ---------------------------------------------------------------------------
// CalculateRowCenter
// Purpose: Calculates the row center using the area and EEi.
//
// Returns: Value of EEi/area, or -1 if invalid values
// ---------------------------------------------------------------------------
double ObjectInfo::calculateRowCenter( void ){ return ( eei / area ); }

// ---------------------------------------------------------------------------
// CalculateColCenter
// Purpose: Calculates the column center using the area and EEi.
//
// Returns: Value of EEj/area, or -1 if invalid values
// ---------------------------------------------------------------------------
double ObjectInfo::calculateColCenter( void ){ return ( eej / area ); }

// ---------------------------------------------------------------------------
// CalculateMinInertia
// Purpose: Calculates the minimum inertia using the area, row center, column
// 			center, EEi2, and EEj2.
// Returns: Value from minimum interia calculation
// ---------------------------------------------------------------------------
double ObjectInfo::calculateMinInertia( void ){ 

	// Get midpoint
	const double row_center = calculateRowCenter();
	const double col_center = calculateColCenter();

	const double a = eei2 - row_center * row_center * area;
	const double b = 2 * eeij  - 2 * row_center * col_center * area; 
	const double c = eej2 - col_center * col_center * area;

	const double angle = atan2( b, a - c );
	
	const double PI = 3.141592653589793;
	
	const double degrees = calculateOrientation() * 180 / PI; // Convert from radians to degrees
	
	const double theta_min = degrees / 2;
	
	const double e_min = E( theta_min, a, b, c );

	return e_min;
}

// ---------------------------------------------------------------------------
// CalculateOrientation
// Purpose: Calculates the orientation using the row center, column center,
// 			and an angle.
// Returns: Value from orientation calculation
// ---------------------------------------------------------------------------
double ObjectInfo::calculateOrientation( void ){ 
	
	// Get midpoint
	const double row_center = calculateRowCenter();
	const double col_center = calculateColCenter();

	const double a = eei2 - row_center * row_center * area;
	const double b = 2 * eeij  - 2 * row_center * col_center * area; 
	const double c = eej2 - col_center * col_center * area;
	
	return atan2( b, a - c );
}

// ---------------------------------------------------------------------------
// E
// Purpose: Inertia Mass calculator. Acts as a helper function for the method
//          calculateMinInertia.
// Returns: Value from inertia mass calculation
// ---------------------------------------------------------------------------
double ObjectInfo::E( const double theta, const double a, const double b, const double c ) const{

	return ( a * cos( theta ) * cos( theta ) )
		 - ( b * cos( theta ) * sin( theta ) ) 
		 + ( c * cos( theta ) * cos( theta ) );
}

// ---------------------------------------------------------------------------
// GETTER FUNCTIONS
// Purpose: Encapsulate class objects to facilitate proper OOP.
// Returns: Respective values
// ---------------------------------------------------------------------------

int ObjectInfo::getArea() const{
	return area;
}

int ObjectInfo::getEEi() const{
	return eei;
}

int ObjectInfo::getEEj() const{
	return eej;
}

int ObjectInfo::getEEi2() const{
	return eei2;
}

int ObjectInfo::getEEj2() const{
	return eej2;
}

int ObjectInfo::getEEij() const{
	return eeij;
}

// ---------------------------------------------------------------------------
// SETTER FUNCTIONS
// Purpose: Encapsulate class objects to facilitate proper OOP.
// Returns: Respective values
// ---------------------------------------------------------------------------

void ObjectInfo::setArea( const int i ){
	if( i >= 0 ) area = i;
	else throw std::invalid_argument("Can't set area to negative value!");
}

void ObjectInfo::setEEi( const int i ){
	if( i >= 0 ) eei = i;
	else throw std::invalid_argument("Can't set EEi to negative value!");
}

void ObjectInfo::setEEj( const int i ){
	if( i >= 0 ) eej = i;
	else throw std::invalid_argument("Can't set EEj to negative value!");
}

void ObjectInfo::setEEi2( const int i ){
	if( i >= 0 ) eei2 = i;
	else throw std::invalid_argument("Can't set EEi2 to negative value!");
}

void ObjectInfo::setEEj2( const int i ){
	if( i >= 0 ) eej2 = i;
	else throw std::invalid_argument("Can't set EEj2 to negative value!");
}

void ObjectInfo::setEEij( const int i ){
	if( i >= 0 ) eeij = i;
	else throw std::invalid_argument("Can't set EEij to negative value!");
}