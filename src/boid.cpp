#include "boid.h"

// bounding box
double const bound = 200;
// force weighting
double const aliWeight = 1.5;
double const cohWeight = 0.5;
double const sepWeight = 0.5;
double const escWeight = 7.0;
double const chaWeight = 5.0;

// constructor
boid::boid()
{
	this->id = 0;
	this->type = 0;
	this->position *= 0;
	this->velocity *= 0;
	this->acceleration *= 0;
	this->viewradius = 0;
	this->viewangle = 0;
	this->maxforce = 0;
	this->maxspeed = 0;
	this->desiredseparation = 0;
}

boid::boid(int id, int type)
{
	// identifier
	this->id = id;
	this->type = type;
	// initial state
	this->position = vector3((double)rand() / RAND_MAX * bound, 
		(double)rand() / RAND_MAX * bound, 
		(double)rand() / RAND_MAX * bound);
	this->velocity = vector3::random3d(0.5, 1.5);
	this->acceleration *= 0;
	// boid properties
	switch (type) {
	case prey:
		this->viewradius = 50;
		this->viewangle = M_PI * 0.8;
		this->maxforce = 0.05;
		this->maxspeed = 2.0;
		this->desiredseparation = 10;
		break;
	case predator:
		this->viewradius = 70;
		this->viewangle = M_PI * 0.2;
		this->maxforce = 0.05;
		this->maxspeed = 1.0;
		this->desiredseparation = 100;
		break;
	default:
		this->viewradius = 0;
		this->viewangle = 0;
		this->maxforce = 0;
		this->maxspeed = 0;
		this->desiredseparation = 0;
	}
}

// destructor
boid::~boid() {}

// warping boids from one side to opposite
void boid::pbcwarp() {
	// check yz-planes
	if (this->position.x > bound) {
		this->position.x -= bound;
	}
	else if (this->position.x < 0) {
		this->position.x += bound;
	}
	// check xz-planes
	if (this->position.y > bound) {
		this->position.y -= bound;
	}
	else if (this->position.y < 0) {
		this->position.y += bound;
	}
	// check yz-planes
	if (this->position.z > bound) {
		this->position.z -= bound;
	}
	else if (this->position.z < 0) {
		this->position.z += bound;
	}
}

// separation between boids
vector3 boid::pbcseparation(boid boid) {
	vector3 dist;
	dist = boid.position - this->position;
	// check yz-planes
	if (dist.x > 0.5 * bound) {
		dist.x -= bound;
	}
	else if (dist.x < -0.5 * bound) {
		dist.x += bound;
	}
	// check xz-planes
	if (dist.y > 0.5 * bound) {
		dist.y -= bound;
	}
	else if (dist.y < -0.5 * bound) {
		dist.y += bound;
	}
	// check yz-planes
	if (dist.z > 0.5 * bound) {
		dist.z -= bound;
	}
	else if (dist.z < -0.5 * bound) {
		dist.z += bound;
	}
	return dist;
}

// field of view
bool boid::isWithinFOV(boid boid)
{
	// exclude self
	if (boid.id == this->id) {		
		return false;
	}
	// check within view radius
	vector3 dist = this->pbcseparation(boid);
	if (dist.magnitude() > viewradius) {	
		return false;
	}
	// check within view angle
	if ((dist.vector3::normalize() * this->velocity.vector3::normalize()) < cos(viewangle)) {	
		return false;
	}
	return true;
}

// behaviour: output force
vector3 boid::alignment(std::vector<boid>& boidList)
{
	vector3 steer;
	vector3 direction;
	int neighborcount = 0;
	for (boid& other : boidList) {
		vector3 dist = this->pbcseparation(other);
		double d = dist.magnitude();
		if (this->isWithinFOV(other) && other.type == this->type) {
			direction += other.velocity / d / d / d;
			neighborcount++;
		}
	}
	if (neighborcount > 0) {
		direction /= neighborcount;
		direction.setMagnitude(this->maxspeed);
		steer = direction - this->velocity;
		if (steer.magnitude() > this->maxforce) {
			steer.setMagnitude(this->maxforce);
		}
	}
	return steer;
}
vector3 boid::cohesion(std::vector<boid>& boidList)
{
	vector3 steer;
	vector3 target;
	vector3 direction;
	int neighborcount = 0;
	for (boid& other : boidList) {
		vector3 dist = this->pbcseparation(other);
		double d = dist.magnitude();
		if (this->isWithinFOV(other) && other.type == this->type) {
			target += dist / d / d / d;
			neighborcount++;
		}
	}
	if (neighborcount > 0) {
		target /= neighborcount;
		direction = target - this->position;
		direction.setMagnitude(this->maxspeed);
		steer = direction - this->velocity;
		if (steer.magnitude() > this->maxforce) {
			steer.setMagnitude(this->maxforce);
		}
	}
	return steer;
}
vector3 boid::separation(std::vector<boid>& boidList)	
{
	vector3 steer;
	vector3 direction;
	int neighborcount = 0;
	for (boid& other : boidList) {
		vector3 dist = this->pbcseparation(other);
		double d = dist.magnitude();
		if (this->isWithinFOV(other) && d < this->desiredseparation && other.type == this->type) {
			direction -= dist / d / d / d;
			neighborcount++;
		}
	}
	if (neighborcount > 0) {
		direction /= neighborcount;
		direction.setMagnitude(this->maxspeed);
		steer = direction - this->velocity;
		if (steer.magnitude() > this->maxforce) {
			steer.setMagnitude(this->maxforce);
		}
	}
	return steer;
}

vector3 boid::escape(std::vector<boid>& boidList)
{
	vector3 steer;
	vector3 direction;
	int neighborcount = 0;
	for (boid& other : boidList) {
		if (other.type == predator) {
			vector3 dist = this->pbcseparation(other);
			double d = dist.magnitude();
			if (this->isWithinFOV(other)) {
				direction -= dist / d / d / d;
				neighborcount++;
			}
		}
	}
	if (neighborcount > 0) {
		direction /= neighborcount;
		direction.setMagnitude(this->maxspeed);
		steer = direction - this->velocity;
		if (steer.magnitude() > this->maxforce) {
			steer.setMagnitude(this->maxforce);
		}
	}
	return steer;
}

vector3 boid::chase(std::vector<boid>& boidList)
{
	vector3 steer;
	vector3 direction;
	int neighborcount = 0;
	for (boid& other : boidList) {
		if (other.type == prey) {
			vector3 dist = this->pbcseparation(other);
			double d = dist.magnitude();
			if (this->isWithinFOV(other)) {
				direction += dist / d / d / d;
				neighborcount++;
			}
		}
	}
	if (neighborcount > 0) {
		direction /= neighborcount;
		direction.setMagnitude(this->maxspeed);
		steer = direction - this->velocity;
		if (steer.magnitude() > this->maxforce) {
			steer.setMagnitude(this->maxforce);
		}
	}

	return steer;
}

// total force
vector3 boid::totalforce(std::vector<boid>& boidList) {
	vector3 force;
	switch (type) {
	case prey:
		force = aliWeight * alignment(boidList) 
			+ cohWeight * cohesion(boidList) 
			+ sepWeight * separation(boidList) 
			+ escWeight * escape(boidList);
		break;
	case predator:
		force = chaWeight * chase(boidList) 
			+ sepWeight * separation(boidList);
		break;
	}
	return force;
}

// integrator
void boid::integrate(std::vector<boid>& boidList) {
	for (boid& boid : boidList){
		boid.position += boid.velocity + 0.5 * boid.acceleration;
		boid.pbcwarp();
	}
	for (boid& boid : boidList) {
		vector3 a_prev = boid.acceleration;
		boid.acceleration = boid.totalforce(boidList);
		boid.velocity += 0.5 * (boid.acceleration + a_prev);
	}
}
