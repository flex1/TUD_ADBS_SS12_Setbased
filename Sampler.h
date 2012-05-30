#ifndef SAMPLER_H
#define SAMPLER_H

#include <string>
#include "Sample.h"
#include "Datensatz.h"
#include "Element.h"

using namespace std;

class Sampler {
public:
	 Sampler(Datensatz* d, Sample* s);
	 Sample* createSample(Datensatz* d);
	 void updateSample(Element* lastE, Sample* s); 
	 

private:
	Sample* s;
	 Datensatz* d;
	 Element* lastE;
	 int cg;
	 int cb;
	 
	
};

#endif