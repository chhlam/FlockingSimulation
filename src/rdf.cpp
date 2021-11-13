#include "rdf.h"

double bound = 200;

rdf::rdf(int bintotal, std::vector<boid>& boidList) {
	this->binTotal = bintotal;
	this->rdfoutput.open("rdf_plot.csv");
	this->binwidth = 0.5 * bound / binTotal;
	this->boidtotal = boidList.size();
	this->accum.resize(binTotal);
	this->stepcount = 0;
	for (double bin = 0.5; bin < binTotal; bin++) {
		rdfoutput << bin * binwidth << ",";
	}
	rdfoutput << std::endl;
}

void rdf::get(std::vector<boid>& boidList)
{
	for (boid current : boidList) {
		for (boid other : boidList) {
			if (current.id != other.id) {
				vector3 dist;
				dist = current.pbcseparation(other);
				if (dist.magnitude() < 0.5 * bound) {
					int bin = (int)(dist.magnitude() / binwidth);
					accum[bin]++;
				}
			}
		}
	}
	this->stepcount++;
}

void rdf::reset()
{
	for (int bin = 0; bin < binTotal; bin++) {
		accum[bin] = 0;
	}
	stepcount = 0;
}

void rdf::output()
{
	double density = boidtotal / (bound * bound * bound);
	double norm = density * stepcount * boidtotal / 2;		// not double counted
	for (int bin = 0; bin < binTotal; bin++) {
		double shellVolume = 4.0 / 3.0 * M_PI * pow((double)(bin)*binwidth + binwidth, 3) - 4.0 / 3.0 * M_PI * pow((double)(bin)*binwidth, 3);		// = 4*pi/3(r+dr)^3 - 4*pi/3(r)^3
		double g = accum[bin] / norm / shellVolume;
		rdfoutput << g << ",";
	}
	rdfoutput << std::endl;
}