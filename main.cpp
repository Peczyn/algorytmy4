#include <iostream>
#import <random>
using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(0, 3);

struct Osoba
{
    string imie;
    int wiek;
    int zarobki;
    Osoba* next;

};

struct Kolejka
{
    Osoba* head;
    Osoba* tail;

    void dodajOsobe(Osoba* klient);
    Osoba* zdejmijOsobe();
};

Kolejka* PetlaCzasowa(int liczbaiteracji)
{
    Kolejka* kolejka = new Kolejka;
    for(int i=1; i<=liczbaiteracji; i++)
    {
        int x = dis(gen);
        if(x<3)
        {
            Osoba* temp = new Osoba;
            temp->imie = "Klient"+to_string(i);
            temp->wiek = 20+i;
            temp->zarobki = 1000*i+x*2137;
            kolejka->dodajOsobe(temp);
        }
        if(x==0)
        {
            Osoba* nowy = kolejka->zdejmijOsobe();
            kolejka->dodajOsobe(nowy);
        }
    }
    return kolejka;
}


int SrednieZarobki(Kolejka* &kolejka)
{
    Kolejka* temp = new Kolejka;
    int licznik=0;
    int zarobki=0;
    while(kolejka->head)
    {
        zarobki+=kolejka->head->zarobki;
        licznik++;
        temp->dodajOsobe(kolejka->zdejmijOsobe());
    }
    while(temp->head)
    {
        kolejka->dodajOsobe(temp->zdejmijOsobe());
    }
    cout << "Srednie zarobki: "<< zarobki/licznik << endl;
    return zarobki/licznik;
}


Osoba* Przedzial(Kolejka* &kolejka,int min,int max)
{
    Osoba* wybrancy = new Osoba;
    Kolejka* przechowalnia = new Kolejka;
    while(kolejka->head)
    {
        Osoba* temp = kolejka->zdejmijOsobe();
        przechowalnia->dodajOsobe(temp);
        if(temp->zarobki>=min && temp->zarobki<=max)
        {
            if(wybrancy->imie.empty())
            {
                wybrancy=temp;
            }
            else
            {
                temp->next=wybrancy;
                wybrancy=temp;
            }
        }
    }
    while(przechowalnia->head)
    {
        kolejka->dodajOsobe(przechowalnia->zdejmijOsobe());
    }
    return wybrancy;
};


void ZmienDaneNaPozycji(Kolejka* &kolejka, int pozycja)
{
    int licznik =0;
    int czyzmieniono = 0;
    Kolejka* temp = new Kolejka;
    while(kolejka->head)
    {
        if(licznik==pozycja)
        {
            Osoba* edit = kolejka->zdejmijOsobe();
//            cout << "Podaj zmienione imie: ";
//            cin >> edit->imie;
//            cout << "Podaj zmieniony wiek: ";
//            cin >> edit->wiek;
//            cout << "Podaj zmienione zarobki: ";
//            cin >> edit->zarobki;
            edit->imie = "Marcin";
            edit->wiek = 66;
            edit->zarobki = INT_MAX;
            temp->dodajOsobe(edit);
            czyzmieniono=1;
        }
        else
        {
            temp->dodajOsobe(kolejka->zdejmijOsobe());
        }

        licznik++;
    }
    if(czyzmieniono==0)
    {
        cout<< "Zly indeks do zmiany!";
    }
    while(temp->head)
    {
        kolejka->dodajOsobe(temp->zdejmijOsobe());
    }
    return;
}




int main() {
    Kolejka* kolejka = PetlaCzasowa(20);
    int srednia = SrednieZarobki(kolejka);
    Osoba* wybrani = Przedzial(kolejka,1000,10000);
    ZmienDaneNaPozycji(kolejka,2);


    return 0;
}






void Kolejka::dodajOsobe(Osoba* klient) {
    if(!head)
    {
        head = new Osoba;
        head->imie = klient->imie;
        head->wiek = klient->wiek;
        head->zarobki = klient->zarobki;
        tail = head;
    }
    else
    {
        tail->next = new Osoba;
        tail=tail->next;
        tail->imie = klient->imie;
        tail->wiek = klient->wiek;
        tail->zarobki = klient->zarobki;
    }
}

Osoba *Kolejka::zdejmijOsobe() {
    if(!head)
    {
        cout << "Kolejka jest pusta!";
        return nullptr;
    }
    Osoba* temp = new Osoba;
    temp->imie = head->imie;
    temp->wiek = head->wiek;
    temp->zarobki = head->zarobki;
    head=head->next;
    if(!head)
    {
        tail=nullptr;
    }
    temp->next=nullptr;
    return temp;
}

/*
W banku jest czynne tylko jedno stanowisko obsługujące klientów. Napisz przy pomocy kolejki FIFO
reprezentację takiej sytuacji zakładając, że:
• Każdy klient jest obiektem z polami: imię, wiek, zarobki,
• W każdej jednostce czasu* istnieje 50% szans na to, że do banku wejdzie następny klient,
• W każdej jednostce czasu* istnieje 25% szans na to, że klient będzie musiał uzupełnić
dokumenty (trafi wtedy na koniec kolejki),
1. Napisz funkcję, która policzy średnie zarobki wszystkich klientów stojących w kolejce(3.0),
2. Napisz funkcję, która zwróci listę klientów których zarobki mieszczą się w zadanym
przedziale(4.0),
3. Napisz funkcję, która pozwoli na edycję danych klienta na wybranej pozycji w kolejce(5.0).
 */