#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <functional>
#include "Element.h"
#include "Datensatz.h"
#include "Sampler.h"
#include "Sample.h"

using namespace std;

double rndm() // Zufallszahl zwischen 0 und 1 für RP
{ 
	/* initialize random seed: */
	srand(static_cast<unsigned int>(time(NULL)));
	/* generate random number: */
	//double d = (rand() + 1.0) / (RAND_MAX + 2);
	return (double)(rand()%9999)/10000;
} 

int main() {
	//-------------Variablen für RP------------------------------

	/*Anzahl der "bad" unkompensierten Löschungen aus Datensatz UND Sample 
	(Samplegröße - 1)*/
		int cb = 0; 
  
	/*Anzahl der "good" unkompensierten Löschungen aus Datensatz (OHNE Sample)*/
		int cg = 0;

	int M; // Obere Grenze der Samplegröße

	int nextIndex;

	// Hallo
	cout << "BERECHNUNG EINES SAMPLES MITTELS RANDOM PAIRING ... "<< endl;

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

	//##############Festlegen der Anzahl der Elemente des Datensatzes...
	cout << "Festlegen des Datensatzes: "<< endl;
	char anzDsChar [256] = "";
	int anzDsInt;
	cout << "Wieviele Elemente soll der Datensatz enthalten? "<< endl;
	cin >> anzDsChar;
	anzDsInt= atoi(anzDsChar);
	nextIndex = anzDsInt;

	
	//#################Anlegen des Datensatzes
	vector<Element*> dataVector = vector<Element*>(anzDsInt);

	//####Zufallsgenerator...
	int rndmzahl;
	srand(static_cast<unsigned int>(time(NULL)));

	//##########Datensatz zufällig befüllen mit ansDsInt Elementen + Ausgabe
	cout << "Datensatz mit "<< anzDsInt << " Elementen: " << endl;
	cout << "ID___ Bezeichnung___"<< endl;
	for(int i=0;i<dataVector.size();i++){
		rndmzahl = rand()%inhaltmgl.size();
		dataVector.at(i) = new Element(i,inhaltmgl[rndmzahl]);
		cout << dataVector.at(i)->GetId() << "   " << dataVector.at(i)->GetInhalt() << endl;
	}

	//########Samplegröße festlegen
	cout << "Festlegen des Samples: "<< endl;
	char MChar [256] = "";
	//int M;
	cout << "Wieviele Elemente soll das Sample enthalten? "<< endl;
	cin >> MChar;
	M = atoi(MChar);

	cout << "Sample mit "<< M << " Elementen: " << endl;

	//##############Berechnung des ersten Samples
	//##############Zufallszahlen ohne Wiederholung
	// Anlegen eines Samplevektors
	vector<Element*> sampleVector = vector<Element*>(M);
	set<int> indexSet; // speichern der Indexe für Zufallszahlen ohne Wiederholung
	int count = 0;
	int backupSize;
	while (sampleVector[M-1]==NULL){
		rndmzahl = (rand()%dataVector.size());
		backupSize = indexSet.size();
		indexSet.insert(rndmzahl);
		if(backupSize<indexSet.size()){
			sampleVector[count]=dataVector.at(rndmzahl);
			cout << sampleVector[count]->GetId() << "   " << sampleVector[count]->GetInhalt()<< endl;
			count++;
		}else{
			
		}
	}

	// Element hinzufügen oder löschen?!----------------------
	string s;
	
	string di="";
	char elc [256] = "";
	string elbez ="";
	int eli=-1;

	while (true){
		cout << "Element loeschen(d),einfuegen(i) oder Programm beenden(e)?" << endl; 
		cin >> di;
		// löschen 
		if (di.compare("d")==0){
			cout << "Welches Element loeschen (Index)?" << endl;
			cin >> elc;
			eli= atoi(elc);
			auto deleteEle = new Element(-1,"");
			deleteEle = dataVector.at(eli);
			dataVector.erase(dataVector.begin()+eli);
		
			cout << "neuer Datensatz: " << endl;
			for (int i = 0; i < dataVector.size(); ++i)
			{
				cout << "Index " << dataVector.at(i)->GetId() << ": " << dataVector.at(i)->GetInhalt() << endl;
			}

			// RP Algorithmusschritt für DELETE (dataVector[eli])

			bool b = false;

			//*******************************___________Algo bei Löschungen_____________
			for(int k=0; k<sampleVector.size(); k++){
				if(deleteEle->GetId() == sampleVector.at(k)->GetId()) {
					b = true;
					cout<< "gefunden " << sampleVector.at(k)->GetInhalt() << endl;
					sampleVector.erase(sampleVector.begin()+k);
				}
			}

			if(b == true) cb++;
			else cg++;

			cout << "neues Sample mit " << sampleVector.size() << "Elementen: " << endl;

			for (int j = 0; j < sampleVector.size(); ++j){
				cout << "Index " << sampleVector.at(j)->GetId() << ": " << sampleVector.at(j)->GetInhalt() << endl;
			}

			cout << "cb " << cb << endl << "cg " << cg << endl;
		}





		 // ############### HINTEN einfügen (in DatenVector)
		if (di.compare("i")==0){
			cout << "Welches Element einfuegen (Bezeichnung)?" << endl;
			cin >> elbez;
			auto ielem = new Element (nextIndex,elbez);
			
			//an Datensatz anfügen
			dataVector.push_back (ielem);
			nextIndex++;


			cout << "cb: " << cb << endl;
			cout << "cg: " << cg << endl;
			if ((cb+cg) == 0){
				//cout << "cg1: " << cg << endl;
				if(sampleVector.size() < M){
					cout << "region1.1" << endl;
					// insert t into S
					sampleVector.push_back(ielem);
				}else{
					if(rndm() < (float) M/(dataVector.size()+1)){
						cout << "region1.2.1" << endl;
						//Overwrite a randomly selected element of S with t

						rndmzahl = (rand()%sampleVector.size());
						sampleVector.erase(sampleVector.begin()+rndmzahl);
						sampleVector.insert(sampleVector.begin()+rndmzahl, ielem);
						//cout << "randomzahl: " << rndmzahl << endl;
					} else {cout << "region1.2.2 "<< endl;}
				}
			}else{
				if(rndm() < cb/(cb+cg)){
					cout << "region2.1" << endl;
					cb--;
					sampleVector.push_back(ielem);
				}else{
					cout << "region2.2" << endl;
					cg--;
				}
			}

			cout << "neuer Datensatz: " << endl;
			for (int i = 0; i < dataVector.size(); ++i)
			{
				cout << "Index " << dataVector.at(i)->GetId() << ": " << dataVector.at(i)->GetInhalt() << endl;
			}
			cout << "neues Sample: " << endl;
			for (int i = 0; i < sampleVector.size(); ++i)
			{
				cout << "Index " << sampleVector.at(i)->GetId() << ": " << sampleVector.at(i)->GetInhalt() << endl;
			}

			cout << "cb " << cb << endl << "cg " << cg << endl;


		}
		 // ##############BEENDEN
		if (di.compare("e")==0) return 0;

	}
}
