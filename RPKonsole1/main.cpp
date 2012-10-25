#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <functional>
#include "Element.h"
#include "RP_Sampler.h"
#include "ISampler.h"

using namespace std;

int main() {

	// Hallo
	cout << "BERECHNUNG EINES SAMPLES MITTELS RANDOM PAIRING ... "<< endl;

	//##############Festlegen der Anzahl der Elemente des Datensatzes...
	cout << "Festlegen des Datensatzes: "<< endl;
	char anzDsChar [256] = "";
	int anzDsInt;
	cout << "Wieviele Elemente soll der Datensatz enthalten? "<< endl;
	cin >> anzDsChar;
	anzDsInt= atoi(anzDsChar);

	//########Samplegröße festlegen
	cout << "Festlegen des Samples: "<< endl;
	char MChar [256] = "";
	//int M;
	cout << "Wieviele Elemente soll das Sample enthalten? "<< endl;
	cin >> MChar;
	int M = atoi(MChar);

	/*
	* Aufruf des Samplers
	*/
	auto sampler = new RP_Sampler(M,anzDsInt);

	// Element hinzufügen oder löschen?! oder beenden ----------------------
	string s;
	
	string di="";
	char elc [256] = "";
	string elbez ="";
	int eli=-1;

	// Schleife in main ...
	while (true){
		cout << "Element loeschen(d),einfuegen(i) oder Programm beenden(e)?" << endl; 
		cin >> di;
		// ############### Löschen 
		if (di.compare("d")==0){
			cout << "Welches Element loeschen (ID)?" << endl;
			cin >> elc;
			eli= atoi(elc);
			//if (eli < sampler->GetData().size()) ...

			sampler->Delete(eli);

		}

		 // ############### HINTEN einfügen (in DatenVector)
		if (di.compare("i")==0){
			cout << "Welches Element einfuegen (Bezeichnung)?" << endl;
			cin >> elbez;

			sampler->Add(&elbez);

		}
		 // ##############BEENDEN
		if (di.compare("e")==0) return 0;

	}
}
