#ifndef SAMPLE_H
#define SAMPLE_H

#include <string>
#include <vector>
#include "Element.h"

using namespace std;

class Sample {
public:
	 Sample(vector<Element*> sampleVector, int obergrenze);
	 //Element getElement();
	 int getObergrenze();
	 void setObergrenze(int obergrenze);
	 void setElement(Element* e);
	 Element* element;

private:
	vector<Element*> sampleVector;
	int obergrenze;
	
	
};

#endif