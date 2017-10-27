#include <iostream>
#include <cstdlib>
#include <typeinfo>
#include <cstring>

using namespace std;

class cstudij{
	public: cstudij *pokazivac;

	virtual void unos()=0;
	virtual void ispis()=0;
};
class cpredmet:public cstudij{
	public: int sifra;
	public: char naziv[50];
	public: cpredmet(){
		cout << "Novi predmet.\n";
		pokazivac = NULL;
	}
	void unos(){
		cout << "Sifra predmeta: "; cin >> sifra;
		cout << "Naziv predmeta: "; cin.ignore();cin.getline(naziv, 50);
	}
	void ispis(){
		cout << "Sifra predmeta: " << sifra << endl;
		cout << "Naziv predmeta: " << naziv << endl;
	}
};
class cprijava:public cstudij{
	public: int sifra, mbs, sifrap;
	public: char rok[50];
	public: cprijava(){
		pokazivac = NULL;
		cout << "Nova prijava.\n";
	}
	void unos(){
		cout << "Sifra prijave: "; cin >> sifra;
		cout << "Maticni broj studenta: "; cin >> mbs;
		cout << "Sifra predmeta: "; cin >> sifrap;
		cout << "Rok: "; cin.ignore(); cin.getline(rok, 50);
	}
	void ispis(){
		cout << "Sifra prijave: " << sifra << endl;
		cout << "Maticni broj studenta: " << mbs << endl;
		cout << "Sifra predmeta: " << sifrap << endl;
		cout << "Rok: " << rok << endl;
	}
};
int main() {
	int izbornik, predmet=0, prijava=0, upredmet;
	cstudij *studij, *pom;
	char spredmet[10] = "8cpredmet", sprijava[10] = "8cprijava";
	do{
		cout << "1. Unos predmeta/unos prijava/ispis predmeta i prijava\n";
		cout << "2. Ispis predmeta/ispis prijava (odvojeno)\n";
		cout << "3. Ispis liste prijava zadanog predmeta (prema šifri predmeta)\n";
		cout << "4. (dodatni zadatak)\n9. Izlaz iz programa\n Unos:";
		cin >> izbornik;
		switch(izbornik){
			case 1:
					cout << "Novi predmet(p) ili novu prijavu(r)?\n Unos: ";
					cin.ignore();
					if(cin.get() == 'p'){
						cpredmet inpredmet;
						pom = studij;
						studij = &inpredmet;
						studij->unos();
						(studij->pokazivac) = pom;
					}
					else{
						cprijava inprijava;
						pom = studij;
						studij = &inprijava;
						studij->unos();
						(studij->pokazivac) = pom;
					}
				break;
			case 2:
				cout << "Broj predmeta i prijava\n-----------------------\n";
				pom = studij;
				do{
					if(strcmp(typeid(*pom).name(), spredmet)) predmet++;
					if(strcmp(typeid(*pom).name(), sprijava)) prijava++;
					pom=pom->pokazivac;
				}while((pom->pokazivac) != NULL);
				pom = studij;
				cout << "Broj predmeta: " << predmet << endl; predmet=0;
				cout << "Broj prijava: " << prijava << endl; prijava=0;
				cout << "Popis predmeta ili prijava?(p/r)\nUnos: ";
				cin.ignore();
				if(cin.get() == 'p'){
					do{
						if(strcmp(typeid(*pom).name(), spredmet)){
							pom->ispis();
						}
						pom=pom->pokazivac;
					} while((pom->pokazivac) != NULL);
				}
				else{
					if(strcmp(typeid(*pom).name(), sprijava)){
							pom->ispis();
						}
						pom=pom->pokazivac;
					} while((pom->pokazivac) != NULL);
				pom = studij;
				break;
				case 3:
					cout << "Broj predmeta i prijava\n-----------------------\n";
					pom = studij;
					do{
						if(strcmp(typeid(*pom).name(), spredmet)) predmet++;
						if(strcmp(typeid(*pom).name(), sprijava)) prijava++;
						pom=pom->pokazivac;
					}while((pom->pokazivac) != NULL);
					pom = studij;
					if(predmet == 0){
						cout << "Ne postoji predmet." << endl;
						break;
					}
					do{
						if(strcmp(typeid(*pom).name(), spredmet)){
							cout << static_cast<cpredmet*>(pom)->naziv;
						}
						pom=pom->pokazivac;
					}while(pom->pokazivac != NULL);
					break;
				}
	}while(izbornik != 9);
	
	system("PAUSE");
	return 0;
}
