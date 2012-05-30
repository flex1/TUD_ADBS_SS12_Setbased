#include "Sampler.h"
#include <string>


Sampler::Sampler(Datensatz* data, Sample* samp){
	  d = data;
	  s = samp;
}

Sample* Sampler::createSample(Datensatz* data){
         return s;
}

void Sampler::updateSample(Element* le, Sample* sam){
	s = sam;
	lastE = le;
} 