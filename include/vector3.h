#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <sstream>
#include <string>

class vector3
{
public:
	double x;
	double y;
	double z;

	// constructor
	vector3 ();
	vector3 (double x, double y, double z);

	// destructor
	~vector3 ();

	// basic operations
	vector3 operator+ (vector3 vector);	// addtion of two vectors
	vector3 operator- (vector3 vector);	// subtraction of two vectors
	friend vector3 operator* (const vector3& vector, double scalar);	// multiplication of scalar & vector
	friend vector3 operator* (double scalar, const vector3& vector);	// same as above
	double operator* (vector3 vector);		// dot product
	static vector3 cross(vector3 vector1, vector3 vector2);		// cross product
	vector3 operator/ (double scalar);		// division of vector by scalar

	// shorthands
	void operator+= (vector3 vector);	// addtion of two vectors
	void operator-= (vector3 vector);	// addtion of two vectors
	void operator*= (double scalar);	// addtion of two vectors
	void operator/= (double scalar);	// addtion of two vectors

	// utility functions
	double magnitude();							// return magnitude of vector
	vector3 normalize();						// normalize vector to magnitude 1
	void setMagnitude(double magnitude);		// resize vector to desired magnitude
	std::string output();						// output vector components
	static vector3 random3d(double lower, double upper);	// generate random vector
};

