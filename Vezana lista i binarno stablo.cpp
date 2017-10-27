#include <iostream>
#include <cstring>
#include "biblioteka_vrijeme.cc"
using namespace std;
// Struktura za element vezane liste
struct telement{
    int red_br;
    char naziv[20];
    float cijena;
    float kolicina;
    float vrijeme;
    telement *sljedeci;
    telement *prethodni;
}; // struct
// Struktura za element binarnog stabla
struct tstablo{
    int red_br;
    char naziv[20];
    float cijena;
    float kolicina;
    float vrijeme;
    tstablo *lijevo;
    tstablo *desno;
}; // struct
// Funkcija za izracun velicine liste
int lista_velicina(telement *lista){
    int broj_elemenata = 0;
    for(telement* element = lista->sljedeci; element; element = element->sljedeci)
        broj_elemenata++;
    return broj_elemenata;
}
// Funkcija za dodavanje elementa na kraj vezane liste
void unos_kraj(telement *lista){
    // Trazenje posljednjeg elementa liste
    telement *novi, *zadnji;
    zadnji = lista;
    while(zadnji->sljedeci)
        zadnji = zadnji->sljedeci;
    // Alokacija novog elementa liste
    novi = new telement;
    novi->prethodni = zadnji; // Povezivanje novog s prethodnim elementom
    zadnji->sljedeci = novi; // Povezivanje prethodnog s novim elementom
    novi->sljedeci = NULL; // S ovim oznacavamo kraj liste
    // Unos vrijednosti za zadnji element
    cout << "Unos novog elementa" << endl;
    cout << "-------------------" << endl;
 
 	do{
	    vrijeme_pocetak();
	    cout << "Redni broj robe: ";
	    cin >> novi->red_br;
	    cout << "Naziv robe: ";
	    unos(novi->naziv);
	    cout << "Cijena: ";
	    cin >> novi->cijena;
	    cout << "Kolicina: ";
	    cin >> novi->kolicina;
	    cout << "Ukupna vrijednost: " << novi->cijena * novi->kolicina << " kn" << endl;
	    vrijeme_kraj();
	    novi->vrijeme = vrijeme_proteklo()/1000;
	    cout << "Vrijeme unosa: " << novi->vrijeme << endl << endl;
	    if ((novi->kolicina)*(novi->cijena) > 1000){
	    	cout << "Ukupna vrijednost je veca od 1000!" << endl << endl;
	    }
	}while((novi->kolicina)*(novi->cijena) > 1000);    
 
    // Ispis broja elemenata
    int brojac = 0;
    for(telement* element = lista->sljedeci; element; element = element->sljedeci){
        brojac++;
    }
    cout << "Broj elemenata: " << brojac << endl;
    brojac = 0;
}
 
void unos_pocetak(telement *lista, int broj_elemenata){
    telement *novi, *sljedeci;
    // Unos elementa na pocetak ukoliko se elementi vec nalaze u listi
    if (broj_elemenata > 0)
        sljedeci = lista->sljedeci;
    // Alokacija novog elementa liste
    novi = new telement;
    novi->prethodni = lista; // Povezivanje novog elementa sa glavom liste
    lista->sljedeci = novi; // Povezivanje glave liste s novim elementom
    // Povezivanje sa sljedecim elementom
    if (broj_elemenata > 0)
        novi->sljedeci = sljedeci; // Povezivanje novog elementa sa sljedecim
    else
        novi->sljedeci = NULL; // Ako nema sljedeceg elementa, sljedeci element je NULL
    // Povezivanje sa prethodnim elementom
    if (broj_elemenata > 0)
        sljedeci->prethodni = novi; // Povezivanje sljedeceg elementa s novim
  
 	do{
	    vrijeme_pocetak();
	    cout << "Redni broj robe: ";
	    cin >> novi->red_br;
	    cout << "Naziv robe: ";
	    unos(novi->naziv);
        cout << "Cijena: ";
        cin >> novi->cijena;
        cout << "Kolicina: ";
        cin >> novi->kolicina;
	    cout << "Ukupna vrijednost: " << novi->cijena * novi->kolicina << " kn" << endl;
	    vrijeme_kraj();
	    novi->vrijeme = vrijeme_proteklo()/1000;
	    cout << "Vrijeme: " << novi->vrijeme << endl << endl;
	    if ((novi->kolicina)*(novi->cijena) > 1000){
	    	cout << "Ukupna vrijednost je veca od 1000!" << endl << endl;
	    }
	}while((novi->kolicina)*(novi->cijena) > 1000);
  
    // Pronalazak zadnjeg elementa u listi
    telement *element = lista->sljedeci;
    while(element->sljedeci)
        element = element->sljedeci;
 
    // Prolazak kroz polje unatrag
    do{
        cout << "Redni broj: " << element->red_br << endl << "Naziv: " << element->naziv << endl << "Vrijednost: " <<
        element->cijena * element->kolicina << endl << "Vrijeme: " << element->vrijeme << endl;
        element = element -> prethodni;
    }while(element != lista); // do-while
}
 
void sort_uzlazno(tstablo *stablo){
    static tstablo *korijen = stablo;
    if (stablo == NULL)
        return; // Sidro rekurzije
    sort_uzlazno(stablo->lijevo); // Prolazi lijevom stranom
    if (stablo != korijen)
        cout << "Redni broj: " << stablo->red_br << endl << "Naziv: " << stablo->naziv << endl << "Cijena: " <<
        stablo->cijena << endl << "Kolicina: " << stablo->kolicina << endl << "Vrijeme: " << stablo->vrijeme << endl;
    sort_uzlazno(stablo->desno); // Prolazi desnom stranom
}
 
void sort_silazno(tstablo *stablo){
    static tstablo *korijen = stablo;
    if(stablo == NULL)
        return; // Sidro rekurzije
    sort_silazno(stablo->desno); // Prolazi desnom stranom
    if(stablo != korijen)
        cout << "Redni broj: " << stablo->red_br << endl << "Naziv: " << stablo->naziv << endl << "Cijena: " <<
        stablo->cijena << endl << "Kolicina: " << stablo->kolicina << endl << "Vrijeme: " << stablo->vrijeme << endl;
    sort_silazno(stablo->lijevo); // Prolazi lijevom stranom
}
 
void upis_stablo(telement *lista, tstablo *stablo){
    // Unos podataka iz liste u binarno stalo
    // Prolazenje kroz cijelu listu
    for(telement *element = lista->sljedeci; element; element = element->sljedeci){
        // Redni broj je kljuc (broj) prema kojem se stvara binarno stablo
        int broj = element->red_br;
        tstablo *zadnji, *novi;
        int dalje = 1;
        zadnji = stablo;
        do{
            if(broj > zadnji->red_br){
                if(zadnji->desno != NULL)
                    zadnji = zadnji->desno;
                else{
                    novi = new tstablo;
                    zadnji->desno = novi;
                    novi->red_br = broj;
                    strcpy(novi->naziv, element->naziv);
                    novi->cijena = element->cijena;
                    novi->kolicina = element->kolicina;
                    novi->vrijeme = element->vrijeme;
                    novi->lijevo = NULL;
                    novi->desno = NULL;
                    dalje = 0;
                } // else
            } // if
            else{
                if(zadnji->lijevo != NULL)
                    zadnji = zadnji->lijevo;
                else{
                    novi = new tstablo;
                    zadnji->lijevo = novi;
                    novi->red_br = broj;
                    strcpy(novi->naziv, element->naziv);
                    novi->cijena = element->cijena;
                    novi->kolicina = element->kolicina;
                    novi->vrijeme = element->vrijeme;
                    novi->lijevo = NULL;
                    novi->desno = NULL;
                    dalje = 0;
                } // else
            } // else
        }while(dalje == 1);
    } // for
 
    char izbor;
    cout << "Zelite li silazan (s) ili uzlazan ispis (u) (s/u): ";
    cin >> izbor;
    // Ispis podataka iz binarnog stabla
    if (izbor == 'u')
        sort_uzlazno(stablo);
    else
        sort_silazno(stablo);
}
 
void dealokacija(tstablo *stablo){
    if(stablo->lijevo)
        dealokacija(stablo->lijevo);
    if(stablo->desno)
        dealokacija(stablo->desno);
    stablo->lijevo = NULL;
    stablo->desno = NULL;
    return;
}
  
int main(){
    int izbor;
    // Alokacija glave vezane liste (1)
    telement *lista = NULL;
    // Alokacija korijena binarnog stabla (1)
    tstablo *stablo = NULL;
 
    do{
        cout << "Izbornik" << endl;
        cout << "--------" << endl;
        cout << "0. Alokacija glave vezane liste i korijena binarnog stabla" << endl;
        cout << "1. Dodavanje elementa na kraj dvostruko vezane liste" << endl;
        cout << "2. Dodavanje elementa na pocetak dvostruko vezane liste" << endl;
        cout << "3. Binarno stablo (kreiranje i ispis)" << endl;
        cout << "9. Izlaz iz programa" << endl;
        cout << "Izbor: ";
        cin >> izbor;
        cout << endl;
 
        switch(izbor){
            case 0:
                // Provjera da li je alocirana glava vezane liste
                if (lista)
                    cout << "Glava vezane liste je vec alocirana." << endl;
                else{
                    // Alokacija glave vezane liste (2)
                    lista = new telement;
                    lista->sljedeci = NULL;
                    lista->prethodni = NULL;
                    cout << "Uspjesno ste alocirali glavu vezane liste." << endl;
                } // else
                // Provjera da li je alociran korijen binarnog stabla
                if(stablo)
                    cout << "Korijen binarnog stabla je vec alociran." << endl;
                else{
                    // Alokacija korijena stabla (2)
                    stablo = new tstablo;
                    stablo->lijevo = NULL;
                    stablo->desno = NULL;
                    cout << "Uspjesno ste alocirali korijen binarnog stabla." << endl;
                } // else
                cout << endl;
                break;
 
            case 1:
                if (lista)
                    cout << "Trenutni broj elemenata liste: " << lista_velicina(lista) << endl << endl;
                if (lista)
                    unos_kraj(lista);
                if (!lista)
                    cout << "Lista nije alocirana. Odaberite opciju 0!" << endl;
                cout << endl;
                break;
 
            case 2:
                if (lista)
                    unos_pocetak(lista, lista_velicina(lista));
                if (!lista)
                    cout << "Lista nije alocirana. Odaberite opciju 0!" << endl;
                cout << endl;
                break;
 
            case 3:
                if (!lista && !stablo){
                    cout << "Lista ili stablo nije alocirano. Odaberite opciju 0!" << endl << endl;
                    break;
                } // if
                if (lista->sljedeci == NULL){
                    cout << "Lista je prazna." << endl << endl;
                    break;
                } // if
                if (lista && stablo)
					cout << "Stablo vec postoji" << endl;
                	dealokacija(stablo);
                    upis_stablo(lista, stablo);
                cout << endl;
                break; 
            default:
                break;
        } // switch
    } while (izbor != 9); // do-while
    return 0;
}
