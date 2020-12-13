#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <conio.h>

using namespace std;

struct Osoba
{
    int id;
    string imie, nazwisko, numerTelefonu, email, adres;
};

void wyswietlDaneOsob (Osoba osoby[], int numerOsoby)
{
        cout << osoby[numerOsoby].id << endl;
        cout << osoby[numerOsoby].imie << endl;
        cout << osoby[numerOsoby].nazwisko << endl;
        cout << osoby[numerOsoby].numerTelefonu <<endl;
        cout << osoby[numerOsoby].email  << endl;
        cout << osoby[numerOsoby].adres << endl;
}

int wczytajOsobyZPLiku(Osoba osoby[])
{
    int id;
    string imie, nazwisko, numerTelefonu, email, adres;
    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::in);

    if (plik.good()== false)
    {
        cout << "Plik z ksiazka adresowa jeszcze nie istnieje." << endl;
        Sleep(3000);
        cout << "Aby dodac osobe do ksiazki adresowej wcisnij 1 w menu.";
        Sleep(4000);
        return 0;
    }

    string linia;
    int nrLinii = 1;
    int iloscOsob =0;

    while(getline(plik, linia))
    {
        switch(nrLinii)
        {
        case 1:
            osoby[iloscOsob].id            = atoi(linia.c_str());
            break;
        case 2:
            osoby[iloscOsob].imie          = linia;
            break;
        case 3:
            osoby[iloscOsob].nazwisko      = linia;
            break;
        case 4:
            osoby[iloscOsob].numerTelefonu = linia;
            break;
        case 5:
            osoby[iloscOsob].email         = linia;
            break;
        case 6:
            osoby[iloscOsob].adres         = linia;
            break;
        }

        if (nrLinii == 6)
        {
            iloscOsob ++;
            nrLinii = 0;
        }
        nrLinii ++;
    }
    plik.close();
    return iloscOsob;
}

int dodajOsobe(Osoba osoby[], int iloscOsob)
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

    int osobaId = iloscOsob + 1;

    osoby[iloscOsob].id = osobaId;
    osoby[iloscOsob].imie = imie;
    osoby[iloscOsob].nazwisko = nazwisko;
    osoby[iloscOsob].numerTelefonu = numerTelefonu;
    osoby[iloscOsob].email = email;
    osoby[iloscOsob].adres = adres;

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);
    if (plik.good())
    {
        plik << osobaId << endl;
        plik << imie << endl;
        plik << nazwisko << endl;
        plik << numerTelefonu << endl;
        plik << email << endl;
        plik << adres << endl;

        plik.close();

        cout << "Osoba zostala dodana." << endl;
        Sleep(2000);
    }

    else
    {
        cout << "Nie mozna otworzyc pliku: KsiazkaAdresowa.txt" << endl;
    }
    iloscOsob ++;
    return iloscOsob;
}

void wyswietlWszystkieKontakty(Osoba osoby[],int iloscOsob)
{
    system("cls");

    if (iloscOsob == 0)

        cout << "Ksiazka adresowa na razie jest pusta";

    for (int i=0; i<iloscOsob; i++)
    {
        wyswietlDaneOsob(osoby, i);
    }

}

void  wyszukajWgImienia(Osoba osoby[], int iloscOsob)
{
    string wprowadzoneImie;
    int licznik = 0;
    system("cls");
    cout << "Podaj imie:";
    cin >> wprowadzoneImie;

    for (int i=0; i<iloscOsob; i++)
    {
        if (wprowadzoneImie == osoby[i].imie)
        {
            wyswietlDaneOsob(osoby, i);
            licznik ++;
        }
    }

    if (licznik == 0)

        cout << "W ksiazce nie ma osoby o takim imieniu";
}

void wyszukajWgNazwiska (Osoba osoby[], int iloscOsob)
{
    string wprowadzoneNazwisko;
    int licznik = 0;
    system("cls");
    cout << "Podaj nazwisko:";
    cin >> wprowadzoneNazwisko;

    for (int i=0; i<iloscOsob; i++)
    {
        if (wprowadzoneNazwisko == osoby[i].nazwisko)
        {
            wyswietlDaneOsob(osoby, i);
            licznik++;
        }
    }

    if (licznik == 0)

        cout << "W ksiazce nie ma osoby o takim nazwisku";
}


int main()
{
    Osoba osoby[1000];
    int iloscOsob = 0;
    char wybor;

    iloscOsob = wczytajOsobyZPLiku(osoby);

    while (true)
    {
        system("cls");
        cout << "1. Dodaj osobe" << endl;
        cout << "2. Wyszukaj wg imienia" << endl;
        cout << "3. Wyszukaj wg nazwiska" << endl;
        cout << "4. Wyswietl wszystkie kontakty" << endl;
        cout << "9. Zakoncz program" << endl;
        cin >> wybor;

        if (wybor == '1')
        {
            iloscOsob = dodajOsobe(osoby, iloscOsob);
        }
        else if (wybor == '2')
        {
            wyszukajWgImienia (osoby, iloscOsob);
            getch();
        }
        else if (wybor == '3')
        {
            wyszukajWgNazwiska (osoby, iloscOsob);
            getch();
        }
        else if (wybor == '4')
        {
            wyswietlWszystkieKontakty(osoby, iloscOsob);
            getch();
        }
        else if (wybor == '9')
        {
            exit(0);
        }
    }

    return 0;
}
