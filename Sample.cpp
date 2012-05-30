#include "Sample.h"
#include "Element.h"
#include <iostream>
#include <vector>
#include <string>


Sample::Sample(vector<Element*> sVector, int oberg)
{
	
	 sampleVector = sVector;
	 obergrenze = oberg;

}

int Sample::getObergrenze(){
	return obergrenze;
}

void Sample::setObergrenze(int ogrenz){
	obergrenze = ogrenz;
}

void Sample::setElement(Element* e){
	element = e;
}

/*Element Sample::getElement(){
    return 0;
}*/

