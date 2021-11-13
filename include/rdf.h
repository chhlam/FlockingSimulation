#pragma once
#include <vector>
#include <fstream>
#include "boid.h"
#include "vector3.h"

class rdf
{
public:
	int binTotal;		// total number of bins for accumulator
	double binwidth;	// bin width
	double boidtotal;
	std::vector<double> accum;	// accumulator
	int stepcount;	// number of step accumulated
	std::ofstream rdfoutput;		// output directory

	rdf(int bintotal, std::vector<boid>& boidList);
	void setup();
	void get(std::vector<boid>& boidList);
	void reset();
	void output();
};

