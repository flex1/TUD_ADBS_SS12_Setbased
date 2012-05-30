#ifndef DATENSATZ_H
#define DATENSATZ_H

#include <string>
#include "Element.h"
#include <vector>

using namespace std;

class Datensatz {
public:
	 Datensatz(vector<Element*> dataVector);
	 Element* getElement();
	 void insertElement(vector<Element*> dataVecTor, Element* e);
	 void deletion(vector<Element*> dataVec, Element* e); 
	 Element* e;

private:
	int groesse;
	vector<Element*> dataVector;
	
};

#endif