#include "Element.h"
#include <string>

using namespace std;


//constructor
Element::Element(int iid, string iinhalt) {
	id = iid;
	inhalt = iinhalt;
}

//getters and setters
int Element::GetId(){
	return id;
}

void Element::SetId(int id1){
	id = id1;
}

string Element::GetInhalt(){
	return inhalt;
}

void Element::SetInhalt(string in){
	inhalt = in;
}
