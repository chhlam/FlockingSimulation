#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include "vector3.h"

enum boidType {
	prey,
	predator
};

class boid
{
public:
	// identifier
	int id;
	int type;
	// states
	vector3 position;
	vector3 velocity;
	vector3 acceleration;
	// traits
	double viewradius;
	double viewangle;
	double maxforce;
	double maxspeed;
	double desiredseparation;

	// constructor
	boid();
	boid(int id, int type);

	// destructor
	~boid();

	// periodic boundary condition
	void pbcwarp();
	vector3 pbcseparation(boid boid);

	// field of view
	bool isWithinFOV(boid boid);

	// behaviour: output force
	vector3 alignment(std::vector<boid>& boidList);
	vector3 cohesion(std::vector<boid>& boidList);
	vector3 separation(std::vector<boid>& boidList);
	vector3 escape(std::vector<boid>& boidList);
	vector3 chase(std::vector<boid>& boidList);

	// total force
	vector3 totalforce(std::vector<boid>& boidList);

	// integrator
	static void integrate(std::vector<boid>& boidList);
};

