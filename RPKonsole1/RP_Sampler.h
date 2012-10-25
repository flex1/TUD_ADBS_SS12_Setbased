#ifndef RP_SAMPLER_H
#define RP_SAMPLER_H

#include "ISampler.h"
#include "Element.h"
#include <vector>

class RP_Sampler : public ISampler
{
public:
	RP_Sampler(int ss, int ds);
	void Add(string* content); // fügt in datensatz und vl in sample hinzu
	void Delete(int id); // löscht auf alle fälle aus datensatz und sample
	vector<Element*> GetSample(); // Lesen des Samples
	vector<Element*> GetData(); // Lesen des Datensatzes
	~RP_Sampler(void);
private:
		int cg;	//eure counter
		int cb;
		int nextIndex;	// für neue Indexeinträge
		long int window_size; // gefordert vom interface
		int sampleSize;
		int datasetSize;
		vector<Element*> dataVector; // euer datensatz
		vector<Element*> sampleVector; // euer sample
		double GetRandom(); // zufallszahlengenerator goes here
		void InsertTintoS();
		void ShowDsAndSample(); // Konsolenausgabe für Datensatz und Sample
};

#endif
