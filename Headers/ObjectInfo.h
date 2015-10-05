// ---------------------------------------------------------------------------
// ObjectInfo.h
// Stores information about objects in an image and 
// 
// Author: Andrew Miloslavsky
// Date: October 2nd, 2015
// ---------------------------------------------------------------------------

#ifndef _OBJECTINFO_
#define _OBJECTINFO_

class ObjectInfo{

public:
	
  // ---------------------------------------------------------------------------
  // CalculateRowCenter
  // Purpose: Calculates the row center using the area and EEi.
  //
  // Returns: Value of EEi/area, or -1 if invalid values
  // ---------------------------------------------------------------------------
  double calculateRowCenter( void );
  
  // ---------------------------------------------------------------------------
  // CalculateColCenter
  // Purpose: Calculates the column center using the area and EEi.
  //
  // Returns: Value of EEj/area, or -1 if invalid values
  // ---------------------------------------------------------------------------
  double calculateColCenter( void );
  
  // ---------------------------------------------------------------------------
  // CalculateMinInertia
  // Purpose: Calculates the minimum inertia using the area, row center, column
  // 			center, EEi2, and EEj2.
  // Returns: Value from minimum interia calculation
  // ---------------------------------------------------------------------------
  double calculateMinInertia( void );
  
  // ---------------------------------------------------------------------------
  // CalculateOrientation
  // Purpose: Calculates the orientation using the row center, column center,
  // 			and an angle.
  // Returns: Value from orientation calculation
  // ---------------------------------------------------------------------------
  double calculateOrientation( void );

  // ---------------------------------------------------------------------------
  // GETTER FUNCTIONS
  // Purpose: Encapsulate class objects to facilitate proper OOP.
  // Returns: Respective values
  // ---------------------------------------------------------------------------
  int getArea( void ) const;
  int getEEi( void ) const;
  int getEEj( void ) const;
  int getEEi2( void ) const;
  int getEEj2( void ) const;
  int getEEij( void ) const;
  
  // ---------------------------------------------------------------------------
  // SETTER FUNCTIONS
  // Purpose: Encapsulate class objects to facilitate proper OOP.
  // Returns: Respective values
  // ---------------------------------------------------------------------------
  void setArea( const int );
  void setEEi( const int );
  void setEEj( const int );
  void setEEi2( const int );
  void setEEj2( const int );
  void setEEij( const int );

  // ---------------------------------------------------------------------------
  // Data Variables
  // Purpose: Store respective object values.
  // ---------------------------------------------------------------------------
  int area;
  int eei;
  int eej;
  int eei2;
  int eej2;
  int eeij;
  
private:

  // ---------------------------------------------------------------------------
  // E
  // Purpose: Inertia Mass calculator. Acts as a helper function for the method
  //          calculateMinInertia.
  // Returns: Value from inertia mass calculation
  // ---------------------------------------------------------------------------
	double E( const double, const double, const double, const double ) const;
  
};

#endif