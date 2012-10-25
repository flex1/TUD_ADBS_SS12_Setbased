#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>
using namespace std;

class Element {

public:
	Element(int id, string inhalt);
	int GetId();
	void SetId(int id);
	string GetInhalt();
	void SetInhalt(string inhalt);
private:
	string inhalt;
	int id;
};

#endif