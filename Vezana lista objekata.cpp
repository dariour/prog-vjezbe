#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

class cstavka{
	public:
		int sifra;
		char naziv[50];
		int vrijednost;
		cstavka *sljedeci;
	public:
		void unos(){
			cstavka *pom;
			pom = this;
			while(pom->sljedeci!=NULL)
				pom=pom->sljedeci;
			cstavka *novi=new cstavka;
			cout << "Sifra: ";
			cin >> novi->sifra;
			cout << "Naziv: ";
			cin.ignore();
			cin.getline(novi->naziv, 50);
			cout << "Vrijednost: ";
			cin >> novi->vrijednost;
			novi->sljedeci=NULL;
			pom->sljedeci=novi;
		}
	public:
		void ispis(){
			cstavka *pom=this->sljedeci;
			while(pom!=NULL){
				cout << "Naziv: " << pom->naziv << endl;
				cout << "Sifra: " << pom->sifra << endl;
				cout << "Vrijednost: " << pom->vrijednost << endl;
				pom=pom->sljedeci;
			}
		}
	public:
		int brojstavki(){
			int broj=0;
			cstavka *pom=this->sljedeci;
			while(pom!=NULL){
				cout << "Naziv: " << pom->naziv << endl;
				cout << "Sifra: " << pom->sifra << endl;
				cout << "Vrijednost: " << pom->vrijednost << endl;
				pom=pom->sljedeci;
			}
		}
		public:
			int iznos(){
				int iznos = 0;
				cstavka *pom=this->sljedeci;
				while(pom!=NULL){
					iznos=iznos+pom->vrijednost;
					pom=pom->sljedeci;
				}
				return iznos;
			}
		public:
			void dealokacija(){
				cstavka *pom=this->sljedeci;
				cstavka *pom2;
				while(pom!=NULL){
					pom2=pom;
					delete pom2;
					pom=pom->sljedeci;
				}
			}
		cstavka(){
			this->sljedeci=NULL;
			cout << "Alociram stavku\n";
		}
		~cstavka(){
			cout << "Dealociram: " << this->naziv << endl;
		}
};
int main(){
	int izbor, broj_elem, redbr, brstav, izborpolje;
	cstavka *polje=NULL;
	char dealoc, aloc;
	cstavka *glava=NULL;
	do{
		cout << "1. Alokacija glave liste stavki, unos pojedine stavke, ispis svih racuna" << endl;
		cout << "2. Ispis svih stavki, ukupan iznos svih stavki, dealokacija liste stavki" << endl;
		cout << "3. Alokacija polja racuna/unos pojedinog racuna/ispis pojedinog racuna/dealokacija svih racuna" << endl;
		cout << "9. Izlaz iz programa\nIzbor: " << endl;
		cin >> izbor;
		switch(izbor){
			case 1:
				if(glava==NULL){
					cout << "0 - glava liste stavki nije alocirana" << endl;
					glava=new cstavka;
				}
				else{
					if(glava->sljedeci=NULL) cout << "1 - lista je prazna" << endl;
					else cout << "2. - lista sadrzi " << glava->brojstavki() << " stavki" << endl;
				}
				glava->unos();
				glava->ispis();
				break;
			case 2:
				if(glava==NULL){
					cout << "0 - glava liste stavki nije alocirana" << endl;
					break;
				}
				else{
					if(glava->sljedeci==NULL) cout << "1 - lista je prazna" << endl;
					else cout << "2 - lista sadrzi " << glava->brojstavki() << " stavki" << endl;
				}
				glava->ispis();
				cout << "Vrijednost stavki: " << glava->iznos() << endl;
				cout << "Zelite li dealocirati?(d/n): ";
				cin >> dealoc;
				if(dealoc=='d') glava->dealokacija();
				break;
			case 3:
				if(polje==NULL){
					cout << "Polje nije alocirano, zelite li alocirati?(d/n): ";
					cin >> aloc;
					if(aloc=='d'){
						cout << "Broj: ";
						cin >> broj_elem;
						polje = new cstavka[broj_elem];
					}
					else break;
				}
				cout << "1.Unos pojedinog racuna\n2.Ispis pojedinog racuna\n3.Dealokacija svih racuna\nIzbor: ";
				cin >> izborpolje;
				switch(izborpolje){
					case 1:
						do{
							cout << "Broj racuna: ";
							cin >> redbr;
						}while(redbr<0||redbr>broj_elem);
						cout << "Broj stavki: ";
						cin >> brstav;
						for(int i=0; i<brstav; i++){
							polje[redbr].unos();
						}
						break;
					case 2:
						do{
							cout << "Broj racuna: ";
							cin >> redbr;
						}while(redbr<0||redbr>broj_elem);
						polje[redbr].ispis();
						break;
					case 3:
						for(int i=0; i<broj_elem; i++){
							polje[i].dealokacija();
						}
						break;
				}
				break;
			default:
				break;
		}
	}while(izbor!=9);
	return 0;
}
