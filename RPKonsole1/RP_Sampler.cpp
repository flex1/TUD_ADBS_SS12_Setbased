#include "ISampler.h"
#include "RP_Sampler.h"
#include <vector>
#include <string>
#include <iostream>
#include "Element.h"
#include <ctime>
#include <cstdlib>
#include <set>
#include <algorithm>
#include <functional>

using namespace std;

RP_Sampler::RP_Sampler(int ss, int ds)
{
	//-------------Variablen für RP------------------------------
	datasetSize = ds;
	sampleSize = ss; // Obere Grenze der Samplegröße
	/*Anzahl der "bad" unkompensierten Löschungen aus Datensatz UND Sample 
	(Samplegröße - 1)*/
	cb = 0; 
	/*Anzahl der "good" unkompensierten Löschungen aus Datensatz (OHNE Sample)*/
	cg = 0;
	// für neue Indexeinträge
	nextIndex = datasetSize;

	// Anlegen des Datensatzes
	dataVector = vector<Element*>(datasetSize);

	// Anlegen eines Samplevektors
	sampleVector = vector<Element*>(sampleSize);

	// Mögliche String-Elemente im Datensatz
	vector<string> inhaltmgl(9);
	inhaltmgl[0] = "Jacke";
	inhaltmgl[1] = "Hose";
	inhaltmgl[2] = "T-Shirt";
	inhaltmgl[3] = "Schuh";
	inhaltmgl[4] = "Cardigan";
	inhaltmgl[5] = "Pullover";
	inhaltmgl[6] = "Mantel";
	inhaltmgl[7] = "Hut";
	inhaltmgl[8] = "Schal";

	//####Zufallsgenerator...
	int rndmzahl;
	srand(static_cast<unsigned int>(time(NULL)));

	//##########Datensatz zufällig befüllen mit datasetSize Elementen + Ausgabe
	cout << "Datensatz mit "<< datasetSize << " Elementen: " << endl;
	cout << "ID\tBezeichnung"<< endl;
	for(int i=0;i<dataVector.size();i++){
		rndmzahl = rand()%inhaltmgl.size();
		dataVector.at(i) = new Element(i,inhaltmgl[rndmzahl]);
		cout << dataVector.at(i)->GetId() << "\t" << dataVector.at(i)->GetInhalt() << endl;
	}

	cout << "Sample mit "<< sampleSize << " Elementen: " << endl;
	cout << "ID\tBezeichnung"<< endl;

	//##############Berechnung des ersten Samples
	//###########Zufallszahlen ohne Wiederholung
	set<int> indexSet; // speichern der Indexe für Zufallszahlen ohne Wiederholung
	int count = 0;
	int backupSize;
	while (sampleVector[sampleSize-1]==NULL){
		rndmzahl = (rand()%dataVector.size());
		backupSize = indexSet.size();
		indexSet.insert(rndmzahl);
		if(backupSize<indexSet.size()){
			sampleVector[count]=dataVector.at(rndmzahl);
			cout << sampleVector[count]->GetId() << "\t" << sampleVector[count]->GetInhalt()<< endl;
			count++;
		}else{
			
		}
	}

}

double RP_Sampler::GetRandom() // Zufallszahl zwischen 0 und 1 für RP
{ 
	/* initialize random seed: */
	srand(static_cast<unsigned int>(time(NULL)));
	/* generate random number: */
	//double d = (rand() + 1.0) / (RAND_MAX + 2);
	return (double)(rand()%9999)/10000;
} 

//Einfügeschritt
void RP_Sampler::Add(string* content){

	//####Zufallsgenerator...
	int rndmzahl;
	srand(static_cast<unsigned int>(time(NULL)));

	auto ielem = new Element (nextIndex,*content);

	cout<< "Einfuegung------------------------------------" << endl;		
	//an Datensatz anfügen
	dataVector.push_back (ielem);
	nextIndex++;

	if ((cb+cg) == 0){
		cout<< cb << " -> cb cg <- " << cg << endl;
		if(sampleVector.size() < sampleSize){
			// !!! ############ !!! insert t into S
			cout<< "Sample " << sampleVector.size() << " < " << "M " << sampleSize << endl;
			cout<< ielem->GetId() << " in Sample eingefuegt ..." << endl;
			sampleVector.push_back(ielem);
		}else{
			float rdm1 = GetRandom();
			if(rdm1 < (float) sampleSize/((float) dataVector.size()+1)){
				//Overwrite a randomly selected element of S with t
				cout<< rdm1 << " ist kleiner als " << (float)sampleSize/(dataVector.size()+1) << endl;
				rndmzahl = (rand()%sampleVector.size());
				sampleVector.erase(sampleVector.begin()+rndmzahl);
				sampleVector.insert(sampleVector.begin()+rndmzahl, ielem);
			} else {
				cout<< rdm1 << " ist groesser gleich " << (float)sampleSize/(dataVector.size()+1) << endl;
				cout<< "hier passiert nix weiter" << endl;
			}
		}
	}else{
		float rdm2 = GetRandom();
		if(rdm2 < (float) cb/(cb+cg)){
			cout<< "rdm -> " << rdm2 << " ist kleiner als " << cb/(cb+cg) << " -> cb durch (cb+cg)" << endl;
			cb--;
			cout<< "cb auf " << cb << " vermindert" << endl;
			sampleVector.push_back(ielem);
			cout<< "Element " << ielem->GetId() << " in Sample eingefuegt ..." << endl;
		}else{
			cg--;
		}
	}
	cout<< "------------------------------------" << endl;
	ShowDsAndSample();
}

// Löschungsschritt
// TODO: Eingabe von Buchstaben und nicht vorhandenen Indizes abfangen
void RP_Sampler::Delete(int id){
	bool deleted = false;
	auto deleteEle = new Element(-1,"");
	cout<< "Loeschung------------------------------------" << endl;	
	//auf den Index = id eines Elements zugreifen ...
	for(int i=0; i<dataVector.size();i++){
		if(dataVector.at(i)->GetId()==id){
			cout << dataVector.at(i)->GetId() << " == " << id << endl;
			deleteEle = dataVector.at(i);
			cout<< "Element " << dataVector.at(i)->GetId() << " aus Datensatz loeschen" << endl;
			dataVector.erase(dataVector.begin()+i);
			deleted = true;
		}
	}	
	// RP Algorithmusschritt für DELETE
	if (deleted){
		bool b = false;
		//*******************************___________Algo bei Löschungen_____________
		for(int k=0; k<sampleVector.size(); k++){
			if(deleteEle->GetId() == sampleVector.at(k)->GetId()) {
				b = true;
				cout<< "im Sample gefunden: " << sampleVector.at(k)->GetId() << "\t" << sampleVector.at(k)->GetInhalt() << " wird geloescht" << endl;
				sampleVector.erase(sampleVector.begin()+k);
			}
		}
		if(b == true){ 
			cb++;
			cout<< "cb erhoeht auf: " << cb << endl;
		}
		else{
			cg++;
			cout<< "cg erhoeht auf: " << cg << endl;
		} 
		cout<< "------------------------------------" << endl;
		ShowDsAndSample();
	} else {
		cout<< "es wurde nix geloescht" << endl;
		cout<< "------------------------------------" << endl;
	}
}

// neuen Datensatz und neues Sample auf Konsole ausgeben
void RP_Sampler::ShowDsAndSample(){
	cout << "neuer Datensatz mit " << dataVector.size() << " Elementen: " << endl;
	cout << "ID\tBezeichnung"<< endl;
	for (int i = 0; i < dataVector.size(); ++i)
	{
		cout << dataVector.at(i)->GetId() << "\t" << dataVector.at(i)->GetInhalt() << endl;
	}

	cout << "neues Sample mit " << sampleVector.size() << " Elementen: " << endl;
	cout << "ID\tBezeichnung"<< endl;
	for (int i = 0; i < sampleVector.size(); ++i)
	{
		cout << sampleVector.at(i)->GetId() << "\t" << sampleVector.at(i)->GetInhalt() << endl;
	}
}

/*vector<Element> RP_Sampler::GetSample(){
	return sampleVector;
}*/

vector<Element*> RP_Sampler::GetSample(){
	return sampleVector;
}

vector<Element*> RP_Sampler::GetData(){
	return dataVector;
}

void RP_Sampler::InsertTintoS(){
	
}

RP_Sampler::~RP_Sampler(void)
{
}
