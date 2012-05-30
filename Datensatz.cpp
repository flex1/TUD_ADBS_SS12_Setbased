#include <string>
#include "Datensatz.h"
#include "Element.h"
#include <vector>
#include "time.h"
#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;

Datensatz::Datensatz(vector<Element*> dataVec){
	dataVector = dataVec;
	srand(time(NULL));
    
/*//dataVector = new vector<Element>(10);
dataVector[0] = new Element("Hose");
dataVector[1] = new Element("Hose");
dataVector[2] = new Element("Hose");
dataVector[3] = new Element("Hose");
dataVector[4] = new Element("Hose");
dataVector[5] = new Element("Hose");
dataVector[6] = new Element("Hose");
dataVector[7] = new Element("Hose");
dataVector[8] = new Element("Hose");
dataVector[9] = new Element("Hose");
for (int i = 0; i < dataVector.size(); ++i)
{
cout << "Content " << i << ": " << dataVector.at(i) << endl;
}*/
}

void Datensatz::insertElement(vector<Element*> dataVec, Element* ele){
		dataVector = dataVec;
		e = ele;
		//dataVector[].erase(e);
}

void Datensatz::deletion(vector<Element*> dataVec, Element* ele){
	 
	    dataVector = dataVec;
		e = ele;
		
		//dataVector[].erase(e);
} 

Element* Datensatz::getElement(){
	return e;
}
