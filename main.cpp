#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <vector>

using namespace std;

struct Adresat
{
    int id;
    string imie, nazwisko, numerTelefonu, email, adres;
};

void wyswietlDaneOsob (vector <Adresat> &adresaci, int numerOsoby)
{
    cout <<  adresaci[numerOsoby].id << "|";
    cout <<  adresaci[numerOsoby].imie << "|";
    cout <<  adresaci[numerOsoby].nazwisko << "|";
    cout <<  adresaci[numerOsoby].numerTelefonu << "|";
    cout <<  adresaci[numerOsoby].email << "|";
    cout <<  adresaci[numerOsoby].adres << "|" << endl;
}

string wyodrebnijPierwszyWyraz (string &wyrazDoSkrocenia)
{
    string pierwszyWyraz;
    string przerywnik = "|";
    int pozycja = wyrazDoSkrocenia.find(przerywnik);
    pierwszyWyraz = wyrazDoSkrocenia.substr(0, pozycja);
    wyrazDoSkrocenia = wyrazDoSkrocenia.erase(0,pozycja+1);

    return pierwszyWyraz;
}

int wczytajOsobyZPLiku(vector <Adresat> &adresaci)
{
    int id;
    string imie, nazwisko, numerTelefonu, email, adres;

    Adresat osoba;
    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::in);

    if (plik.good()== false)
    {
        cout << "Plik z ksiazka adresowa jeszcze nie istnieje." << endl;
        Sleep(1000);
        cout << "Aby dodac osobe do ksiazki adresowej wcisnij 1 w menu.";
        Sleep(1000);
        return 0;
    }

    string linia;
    int iloscOsob = 0;

    while(getline(plik,linia))
    {
        osoba.id            = atoi(wyodrebnijPierwszyWyraz(linia).c_str());
        osoba.imie          = wyodrebnijPierwszyWyraz(linia);
        osoba.nazwisko      = wyodrebnijPierwszyWyraz(linia);
        osoba.numerTelefonu = wyodrebnijPierwszyWyraz(linia);
        osoba.email         = wyodrebnijPierwszyWyraz(linia);
        osoba.adres         = wyodrebnijPierwszyWyraz(linia);

        adresaci.push_back(osoba);

        iloscOsob++;
    }
    plik.close();
    return iloscOsob;
}

int dodajOsobe(vector <Adresat> &adresaci, int iloscOsob)
{
    string imie, nazwisko, numerTelefonu, email, adres;

    system("cls");
    cout << "Dodawanie osoby" << endl;
    cout << "Podaj imie uzytkownika: ";
    cin >> imie;
    cout << "Podaj nazwisko uzytkownika: ";
    cin >> nazwisko;
    cout << "Podaj numer telefonu uzytkownika: ";
    cin.sync();
    getline(cin, numerTelefonu);
    cout << "Podaj email uzytkownika: ";
    cin >> email;
    cout << "Podaj adres uzytkownika: ";
    cin.sync();
    getline(cin, adres);

    int AdresatId;

    if(adresaci.size() == 0)
        AdresatId = 1;
    else
    AdresatId = adresaci[adresaci.size()-1].id+1;

    Adresat osoba;

    osoba.id            = AdresatId;
    osoba.imie          = imie;
    osoba.nazwisko      = nazwisko;
    osoba.numerTelefonu = numerTelefonu;
    osoba.email         = email;
    osoba.adres         = adres;

    adresaci.push_back(osoba);

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);
    if (plik.good())
    {
        plik << AdresatId << "|" << imie << "|" << nazwisko << "|" << numerTelefonu << "|" << email << "|" << adres << "|" << endl;
        plik.close();
        cout << "Adresat zostal dodany." << endl;
        Sleep(2000);
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: KsiazkaAdresowa.txt" << endl;
    }
    iloscOsob ++;
    return iloscOsob;
}

void wyswietlWszystkieKontakty(vector <Adresat> &adresaci,int iloscOsob)
{
    system("cls");
    if (iloscOsob == 0)
        cout << "Ksiazka adresowa na razie jest pusta";

    for (int i=0; i<adresaci.size(); i++)
    {
        wyswietlDaneOsob(adresaci, i);
    }
}

void  wyszukajWgImienia(vector <Adresat> &adresaci, int iloscOsob)
{
    string wprowadzoneImie;
    int licznik = 0;
    system("cls");
    cout << "Podaj imie:";
    cin >> wprowadzoneImie;

    for (int i=0; i<adresaci.size(); i++)
    {
        if (wprowadzoneImie == adresaci[i].imie)
        {
            wyswietlDaneOsob(adresaci, i);
            licznik ++;
        }
    }
    if (licznik == 0)
        cout << "W ksiazce nie ma osoby o takim imieniu";
}

void wyszukajWgNazwiska (vector <Adresat> &adresaci, int iloscOsob)
{
    string wprowadzoneNazwisko;
    int licznik = 0;
    system("cls");
    cout << "Podaj nazwisko:";
    cin >> wprowadzoneNazwisko;

    for (int i=0; i<adresaci.size(); i++)
    {
        if (wprowadzoneNazwisko == adresaci[i].nazwisko)
        {
            wyswietlDaneOsob(adresaci, i);
            licznik++;
        }
    }
    if (licznik == 0)
        cout << "W ksiazce nie ma osoby o takim nazwisku";
}

void zapiszZmianyWKontakcie (vector<Adresat> &adresaci)
{
    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out);
    if (plik.good())
    {
        for(int i=0; i<adresaci.size(); i++)
        {
            plik << adresaci[i].id << "|" << adresaci[i].imie << "|" << adresaci[i].nazwisko << "|" << adresaci[i].numerTelefonu << "|" << adresaci[i].email << "|" << adresaci[i].adres << "|" << endl;
        }
        plik.close();
    }
}

void edytujKontakt (vector<Adresat> &adresaci)
{
    system("cls");
    int podanyNrID, wybor, licznik = 0;
    string nowaDana;
    cout << "Podaj nr ID kontaktu:";
    cin >> podanyNrID;

    for(int i=0; i < adresaci.size(); i++)
    {
        if(podanyNrID == adresaci[i].id)
        {
            cout << "Wybierz dane do edycji:" << endl;
            cout << "1. Imie" << endl;
            cout << "2. Nazwisko" << endl;
            cout << "3. Numer telefonu" << endl;
            cout << "4. Email" << endl;
            cout << "5. Adres" << endl;
            cout << "6. Powrot do MENU" << endl;
            cout << "Twoj wybor:";
            cin >> wybor;

            switch(wybor)
            {
            case 1:
                cout << "Podaj nowe imie:";
                cin >> nowaDana;
                adresaci[i].imie = nowaDana;
                zapiszZmianyWKontakcie(adresaci);
                break;
            case 2:
                cout << "Podaj nowe nazwisko:";
                cin >> nowaDana;
                adresaci[i].nazwisko = nowaDana;
                zapiszZmianyWKontakcie(adresaci);
                break;
            case 3:
                cout << "Podaj nowy numer telefonu:";
                cin >> nowaDana;
                adresaci[i].numerTelefonu = nowaDana;
                zapiszZmianyWKontakcie(adresaci);
                break;
            case 4:
                cout << "Podaj nowy Email:";
                cin >> nowaDana;
                adresaci[i].email = nowaDana;
                zapiszZmianyWKontakcie(adresaci);
                break;
            case 5:
                cout << "Podaj nowe Adres:";
                cin >> nowaDana;
                adresaci[i].adres = nowaDana;
                zapiszZmianyWKontakcie(adresaci);
                break;
            case 6:
                break;
            }
            break;
        }
        else if (podanyNrID != adresaci[i].id)
        {
            licznik++;
            if(licznik == adresaci.size())
                cout << "Nie ma w ksiazce adresowej osoby z takim ID";
        }
    }
}

void usunKontakt (vector <Adresat> &adresaci)
{
    system ("cls");
    int podanyNrID, licznik = 0;
    char znak;
    cout << "Podaj nr ID kontaktu do usunecia:";
    cin >> podanyNrID;

    for (auto elem = adresaci.begin(); elem != adresaci.end(); elem++)
    {
        if ( elem -> id == podanyNrID)
        {
            cout << "Czy na pewno chcesz usunac kontakt?" << endl << "Jezeli tak nacisnij t:";
            cin >> znak;
            if (znak == 't')
            {
                adresaci.erase(elem);
                cout << "Kontakt usuniety.";
                zapiszZmianyWKontakcie(adresaci);
                break;
            }
            else
                break;
        }
        if (elem -> id != podanyNrID)
        {
            licznik++;
            if(licznik == adresaci.size())
                cout << "Nie ma w ksiazce adresowej osoby z takim ID";
        }
    }
}

int main()
{
    vector <Adresat> adresaci;
    int iloscOsob = 0;
    char wybor;

    iloscOsob = wczytajOsobyZPLiku(adresaci);

    while (true)
    {
        system("cls");
        cout << "KSIAZKA ADRESOWA" << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Edytuj adresata" << endl;
        cout << "6. Usun adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        cout << "Twoj wybor:";
        cin >> wybor;

        if (wybor == '1')
        {
            iloscOsob = dodajOsobe(adresaci, iloscOsob);
        }
        else if (wybor == '2')
        {
            wyszukajWgImienia (adresaci, iloscOsob);
            getch();
        }
        else if (wybor == '3')
        {
            wyszukajWgNazwiska (adresaci, iloscOsob);
            getch();
        }
        else if (wybor == '4')
        {
            wyswietlWszystkieKontakty(adresaci, iloscOsob);
            getch();
        }
        else if (wybor == '5')
        {
            edytujKontakt(adresaci);
            getch();
        }
        else if (wybor == '6')
        {
            usunKontakt(adresaci);
            getch();
        }
        else if (wybor == '9')
        {
            exit(0);
        }
    }
    return 0;
}

