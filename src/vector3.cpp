#include "vector3.h"

// constructor
vector3::vector3() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

vector3::vector3(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

// destructor
vector3::~vector3() {}

// basic operations
vector3 vector3::operator+ (vector3 v) 
{
	return vector3(this->x + v.x, this->y + v.y, this->z + v.z);
}

vector3 vector3::operator- (vector3 v) 
{
	return vector3(this->x - v.x, this->y - v.y, this->z - v.z);
}

vector3 operator* (const vector3& v, double u) 
{
	return vector3(v.x * u, v.y * u, v.z * u);
}

vector3 operator* (double u, const vector3& v) 
{
	return vector3(v.x * u, v.y * u, v.z * u);
}

double vector3::operator* (vector3 v) 
{
	return this->x * v.x + this->y * v.y + this->z * v.z;
}

vector3 vector3::cross(vector3 v1, vector3 v2) 
{
	double x1, y1, z1;
	x1 = v1.y * v2.z - v1.z * v2.y;
	y1 = v1.z * v2.x - v1.x * v2.z;
	z1 = v1.x * v2.y - v1.y * v2.x;
	return vector3(x1, y1, z1);
}

vector3 vector3::operator/ (double u) 
{
	return vector3(this->x / u, this->y / u, this->z / u);
}

// shorthands
void vector3::operator+=(vector3 v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
}

void vector3::operator-=(vector3 v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
}

void vector3::operator*=(double u)
{
	this->x *= u;
	this->y *= u;
	this->z *= u;
}

void vector3::operator/=(double u)
{
	this->x /= u;
	this->y /= u;
	this->z /= u;
}

// utility functions
double vector3::magnitude()
{
	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

vector3 vector3::normalize() 
{
	double magnitude = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	this->x /= magnitude;
	this->y /= magnitude;
	this->z /= magnitude;
	return vector3(this->x, this->y, this->z);
}

void vector3::setMagnitude(double newMag)
{
	double mag = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	this->x = this->x / mag * newMag;
	this->y = this->y / mag * newMag;
	this->z = this->z / mag * newMag;
}

std::string vector3::output()
{
	std::stringstream ss;
	ss << this->x << " " << this->y << " " << this->z;
	return ss.str();
}

vector3 vector3::random3d(double lower, double upper)
{
	double mag, theta, phi;
	mag = (double)rand() / RAND_MAX * (upper - lower) + lower;
	phi = 2 * M_PI * (double)rand() / RAND_MAX;
	theta = acos(2 * (double)rand() / RAND_MAX - 1);
	return vector3(mag * sin(theta) * cos(phi), mag * sin(theta) * sin(phi), mag * cos(theta));
}
