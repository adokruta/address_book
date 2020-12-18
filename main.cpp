#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <vector>
#include <cstdio>

using namespace std;

struct Adresat
{
    int id, idUzytkownika;
    string imie, nazwisko, numerTelefonu, email, adres;
};

struct Uzytkownik
{
    int id;
    string nazwa, haslo;
};

string wyodrebnijPierwszyWyraz (string &wyrazDoSkrocenia)
{
    string pierwszyWyraz;
    string przerywnik = "|";
    int pozycja = wyrazDoSkrocenia.find(przerywnik);
    pierwszyWyraz = wyrazDoSkrocenia.substr(0, pozycja);
    wyrazDoSkrocenia = wyrazDoSkrocenia.erase(0,pozycja+1);

    return pierwszyWyraz;
}

int zwrocNrID ()
{
    fstream plik;
    string linia;
    int idOstatniegoAdresata = 0;

    plik.open("KsiazkaAdresowa.txt", ios::in);

    if (plik.good()== true)
    {
        while(getline(plik,linia))
        {
            idOstatniegoAdresata = atoi(wyodrebnijPierwszyWyraz(linia).c_str());
        }
    }
    plik.close();
    return idOstatniegoAdresata+1;
}
int rejestracja (vector <Uzytkownik> &uzytkownicy, int iloscUzytkownikow)
{
    string nazwa, haslo;
    int idUzytkownika = iloscUzytkownikow + 1;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwa;
    int i = 0;
    while(i < iloscUzytkownikow)
    {
        if(uzytkownicy[i].nazwa == nazwa)
        {
            cout << "Taki uzytkownik istnieje. Podaj inna nazwe: ";
            cin >> nazwa;
            i = 0;
        }
        else
        {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    cin >> haslo;

    Uzytkownik pojedynczyUzytkownik;

    pojedynczyUzytkownik.nazwa = nazwa;
    pojedynczyUzytkownik.haslo = haslo;
    pojedynczyUzytkownik.id = idUzytkownika;

    uzytkownicy.push_back(pojedynczyUzytkownik);

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out | ios::app);
    if (plik.good())
    {
        plik << idUzytkownika << "|" << nazwa << "|" << haslo << endl;
        plik.close();
        cout << "Uzytkownik zostal dodany." << endl;
        Sleep(2000);
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: Uzytkownicy.txt" << endl;
    }
    cout << "Konto zalozone.";
    Sleep(2000);
    return iloscUzytkownikow+1;
}

int logowanie (vector <Uzytkownik> &uzytkownicy, int iloscUzytkownikow)
{
    if(iloscUzytkownikow == 0)
    {
        cout << "Nie ma obecnie zadnego uzytkownika. Zarejestruj sie.";
        getch();
        return 0;
    }
    else
    {
    string nazwa, haslo;
    cout << "Podaj nazwe: ";
    cin >> nazwa;
    int i = 0;
        while(i < iloscUzytkownikow)
        {
            if(uzytkownicy[i].nazwa == nazwa)
            {
                for(int proby =0; proby <3; proby++)
                {
                    cout << "Podaj haslo. Pozostalo prob " << 3 - proby << ": ";
                    cin >> haslo;
                    if(uzytkownicy[i].haslo == haslo)
                    {
                        cout << endl << "Zalogowales sie." << endl;
                        Sleep(2000);
                        return uzytkownicy[i].id;
                    }
                }
                cout <<"Podales 3 razy bledne haslo. Nastapi powrot do MENU logowania...";
                Sleep(3000);
                return 0;
            }
            i++;
        }
        cout <<"Nie ma uzytkownika z takim loginem." << endl;
        Sleep(3000);
        return 0;
    }
}

void zmienHaslo (vector <Uzytkownik> &uzytkownicy, int iloscUzytkownikow, int idZalogowanegoUzytkownika)
{
    system("cls");
    string haslo;
    cout <<"Podaj nowe haslo: ";
    cin >> haslo;
    for (int i=0; i < iloscUzytkownikow; i++)
    {
        if (uzytkownicy[i].id == idZalogowanegoUzytkownika)
        {
            uzytkownicy[i].haslo = haslo;
            cout <<"Haslo zostalo zmienione." << endl;
            Sleep(2000);
        }
    }
}

void wyswietlDaneOsob (vector <Adresat> &adresaci, int numerOsoby)
{
    cout <<  adresaci[numerOsoby].id << "|";
    cout <<  adresaci[numerOsoby].idUzytkownika << "|";
    cout <<  adresaci[numerOsoby].imie << "|";
    cout <<  adresaci[numerOsoby].nazwisko << "|";
    cout <<  adresaci[numerOsoby].numerTelefonu << "|";
    cout <<  adresaci[numerOsoby].email << "|";
    cout <<  adresaci[numerOsoby].adres << "|" << endl;
}



int wczytajUzytkownikowZPLiku(vector <Uzytkownik> &uzytkownicy)
{
    string nazwa, haslo;

    Uzytkownik pojedynczyUzytkownik;
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::in);

    if (plik.good()== false)
    {
        return 0;
    }

    string linia;
    int iloscUzytkownikow = 0;

    while(getline(plik,linia))
    {
        pojedynczyUzytkownik.id         = atoi(wyodrebnijPierwszyWyraz(linia).c_str());
        pojedynczyUzytkownik.nazwa      = wyodrebnijPierwszyWyraz(linia);
        pojedynczyUzytkownik.haslo      = wyodrebnijPierwszyWyraz(linia);

        uzytkownicy.push_back(pojedynczyUzytkownik);

        iloscUzytkownikow++;
    }
    plik.close();
    return iloscUzytkownikow;
}

void wczytajAdresatowZPLiku(vector <Adresat> &adresaci, int idZalogowanegoUzytkownika)
{
    string imie, nazwisko, numerTelefonu, email, adres;

    Adresat osoba;
    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::in);

    if (plik.good()== false && idZalogowanegoUzytkownika != 0)
    {
        system("cls");
        cout << "Plik z ksiazka adresowa jeszcze nie istnieje." << endl;
        Sleep(2000);
        cout << "Aby dodac osobe do ksiazki adresowej wcisnij 1 w menu.";
        Sleep(3000);
    }

    string linia;
    int iloscOsob = 0;

    while(getline(plik,linia))
    {
        osoba.id            = atoi(wyodrebnijPierwszyWyraz(linia).c_str());
        osoba.idUzytkownika = atoi(wyodrebnijPierwszyWyraz(linia).c_str());
        osoba.imie          = wyodrebnijPierwszyWyraz(linia);
        osoba.nazwisko      = wyodrebnijPierwszyWyraz(linia);
        osoba.numerTelefonu = wyodrebnijPierwszyWyraz(linia);
        osoba.email         = wyodrebnijPierwszyWyraz(linia);
        osoba.adres         = wyodrebnijPierwszyWyraz(linia);

        if(osoba.idUzytkownika == idZalogowanegoUzytkownika)
        {
            adresaci.push_back(osoba);
        }

        iloscOsob++;
    }
    plik.close();
}

void dodajOsobe(vector <Adresat> &adresaci, int idZalogowanegoUzytkownika)
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

    int AdresatId = zwrocNrID();

    Adresat osoba;

    osoba.id            = AdresatId;
    osoba.idUzytkownika = idZalogowanegoUzytkownika;
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
        plik << AdresatId << "|" << idZalogowanegoUzytkownika << "|"<< imie << "|" << nazwisko << "|" << numerTelefonu << "|" << email << "|" << adres << "|" << endl;
        plik.close();
        cout << "Adresat zostal dodany." << endl;
        Sleep(2000);
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: KsiazkaAdresowa.txt" << endl;
    }
}

void wyswietlWszystkieKontakty(vector <Adresat> &adresaci)
{
    system("cls");

    if (adresaci.empty() == true)
        cout << "Ksiazka adresowa na razie jest pusta";
    else
    {
        for (int i=0; i<adresaci.size(); i++)
        {
            wyswietlDaneOsob(adresaci, i);
        }
    }
}

void  wyszukajWgImienia(vector <Adresat> &adresaci)
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

void wyszukajWgNazwiska (vector <Adresat> &adresaci)
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

void zapiszZmianyWKontakcie (vector<Adresat> &adresaci, int idZalogowanegoUzytkownika, int idAdresata, int pozycjaWWektorze)
{
    fstream plik, plikTymczasowy;
    string linia;
    Adresat osoba;
    plik.open("KsiazkaAdresowa.txt", ios::in);
    if (plik.good())
    {
        plikTymczasowy.open("Adresaci_tymczasowy.txt", ios::out );
        if (plikTymczasowy.good())
        {
            while(getline(plik,linia))
            {
                string bufor = linia;
                osoba.id = atoi(wyodrebnijPierwszyWyraz(linia).c_str());
                if (osoba.id == idAdresata)
                {
                    plikTymczasowy << idAdresata<< "|" <<   idZalogowanegoUzytkownika << "|"<< adresaci[pozycjaWWektorze].imie << "|" << adresaci[pozycjaWWektorze].nazwisko << "|" << adresaci[pozycjaWWektorze].numerTelefonu << "|" <<adresaci[pozycjaWWektorze].email << "|" <<adresaci[pozycjaWWektorze].adres << "|" << endl;
                }
                else
                {
                    plikTymczasowy << bufor << endl;
                }
            }
            plikTymczasowy.close();
        }
        plik.close();
        remove("KsiazkaAdresowa.txt");
        rename("Adresaci_tymczasowy.txt","KsiazkaAdresowa.txt");
    }
}

void usunKontaktZPliku(int idAdresata)
{
    fstream plik, plikTymczasowy;
    string linia;
    Adresat osoba;
    plik.open("KsiazkaAdresowa.txt", ios::in);
    if (plik.good())
        {
            plikTymczasowy.open("Adresaci_tymczasowy.txt", ios::out );
            if (plikTymczasowy.good())
            {
                 while(getline(plik,linia))
                    {
                        string bufor = linia;
                        osoba.id = atoi(wyodrebnijPierwszyWyraz(linia).c_str());
                        if (osoba.id != idAdresata)
                        {
                           plikTymczasowy << bufor << endl;
                        }
                    }
                plikTymczasowy.close();
            }
            plik.close();
            remove("KsiazkaAdresowa.txt");
            rename("Adresaci_tymczasowy.txt","KsiazkaAdresowa.txt");
        }
}

void edytujKontakt (vector<Adresat> &adresaci,  int idZalogowanegoUzytkownika)
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
                zapiszZmianyWKontakcie(adresaci, idZalogowanegoUzytkownika, podanyNrID, i);
                break;
            case 2:
                cout << "Podaj nowe nazwisko:";
                cin >> nowaDana;
                adresaci[i].nazwisko = nowaDana;
                zapiszZmianyWKontakcie(adresaci, idZalogowanegoUzytkownika, podanyNrID, i);
                break;
            case 3:
                cout << "Podaj nowy numer telefonu:";
                cin >> nowaDana;
                adresaci[i].numerTelefonu = nowaDana;
                zapiszZmianyWKontakcie(adresaci, idZalogowanegoUzytkownika, podanyNrID, i);
                break;
            case 4:
                cout << "Podaj nowy Email:";
                cin >> nowaDana;
                adresaci[i].email = nowaDana;
                zapiszZmianyWKontakcie(adresaci, idZalogowanegoUzytkownika, podanyNrID, i);
                break;
            case 5:
                cout << "Podaj nowe Adres:";
                cin >> nowaDana;
                adresaci[i].adres = nowaDana;
                zapiszZmianyWKontakcie(adresaci, idZalogowanegoUzytkownika, podanyNrID, i);
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
                usunKontaktZPliku(podanyNrID);
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
    vector <Uzytkownik> uzytkownicy;
    int iloscUzytkownikow = 0;
    int idZalogowanegoUzytkownika = 0;
    char wybor;

    iloscUzytkownikow = wczytajUzytkownikowZPLiku(uzytkownicy);

    while (true)
    {
        if (idZalogowanegoUzytkownika == 0)
        {
            system("cls");

            cout << "KSIAZKA ADRESOWA" << endl;
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "3. Zamknij program" << endl;
            cout << "Twoj wybor:";
            cin >> wybor;

              if (wybor == '1')
            {
                system("cls");
                iloscUzytkownikow = rejestracja(uzytkownicy, iloscUzytkownikow);
            }

            else if (wybor == '2')
            {
                system("cls");
                idZalogowanegoUzytkownika = logowanie(uzytkownicy, iloscUzytkownikow);
                wczytajAdresatowZPLiku(adresaci, idZalogowanegoUzytkownika);
            }
            else if (wybor == '3')
            {
                  exit(0);
            }
        }

        else
        {
            system("cls");
            cout << "KSIAZKA ADRESOWA" << endl;
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj po imieniu" << endl;
            cout << "3. Wyszukaj po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Edytuj adresata" << endl;
            cout << "6. Usun adresata" << endl;
            cout << "7. Zmien haslo" << endl;
            cout << "8. Wyloguj sie" << endl;
            cout << "Twoj wybor:";
            cin >> wybor;

            if (wybor == '1')
            {
                dodajOsobe(adresaci, idZalogowanegoUzytkownika);
            }
            else if (wybor == '2')
            {
                wyszukajWgImienia (adresaci);
                getch();
            }
            else if (wybor == '3')
            {
                wyszukajWgNazwiska (adresaci);
                getch();
            }
            else if (wybor == '4')
            {
                wyswietlWszystkieKontakty(adresaci);
                getch();
            }
            else if (wybor == '5')
            {
                edytujKontakt(adresaci, idZalogowanegoUzytkownika);
                getch();
            }
            else if (wybor == '6')
            {
                usunKontakt(adresaci);
                getch();
            }
            else if (wybor == '7')
            {
                zmienHaslo(uzytkownicy, iloscUzytkownikow, idZalogowanegoUzytkownika);
                getch();
            }
              else if (wybor == '8')
            {
                idZalogowanegoUzytkownika = 0;
                adresaci.clear();
            }
        }
    }
    return 0;
}

