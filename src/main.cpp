#include <iostream>
#include <fstream>
#include "vector3.h"
#include "boid.h"
#include "rdf.h"

using namespace std;

int main() {
	int seed = 2;
	int stepTotal = 10000;
	int preytotal = 100;
	int predtotal = 5;

	// initiate flock & predator
	srand(seed);

	vector<boid> boidList;
	for (int i = 0; i < preytotal; i++) {
		boidList.push_back(boid(i, prey));
	}
	for (int j = 0; j < predtotal; j++) {
		boidList.push_back(boid(preytotal + j, predator));
	}
	ofstream animation;
	animation.open("animation.xyz");

	// rdf
	rdf rdf(50, boidList);

	ofstream avgvelocity;
	avgvelocity.open("avgvelocity_plot.csv");
	vector3 sum(1, 1, 1);

	// time evolution of the system
	for (int stepCount = 0; stepCount < stepTotal; stepCount++) {
		sum.setMagnitude(0);
		for (boid boid : boidList) {
			sum += boid.velocity;
		}
		sum /= boidList.size();
		avgvelocity << sum.magnitude() << endl;
		// update flock
		boid::integrate(boidList);
		// print frame
		if (stepCount % 1 == 0) {
			animation << boidList.size() << endl;
			animation << "comment line\n";
			for (boid boid : boidList) {
				switch (boid.type) {
				case prey:
					animation << "Ar " << boid.position.output() << endl;
					break;
				case predator:
					animation << "Co " << boid.position.output() << endl;
					break;
				}
				
			}
		}
		// radial distribution function
		rdf.get(boidList);
		if (stepCount % 500 == 0) {
			rdf.output();
			rdf.reset();
		}
	}

	return 0;
}