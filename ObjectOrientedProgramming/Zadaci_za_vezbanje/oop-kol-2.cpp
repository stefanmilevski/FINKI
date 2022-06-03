/* Да се дефинира класа Vozac во која се чуваат информации за:

име (низа од максимум 100 знаци)
возраст (цел број)
број на трки (цел број)
дали е ветеран (да/не).
Да се преоптоварат:

операторот << за печатење кој ќе ги печати името, возраст, бројот на трки и дали е ветеран (се печати VETERAN)
операторот == за споредување на два возачи според заработувачката по трка.
Од оваа класа да се изведат две нови класи Avtomobilist и Motociklist.

За автомобилистот дополнително се чува:

цена на автомобилот (децимален број).
За мотоциклистот дополнително се чува:

моќност на мотор (цел број).
Заработувачката по трка на возачите се пресметува како:

за автомобилостот заработувачката по трка е $\frac{CENA_{AVTOMOBIL}}{5}$
за мотоциклистот заработувачката по трка е $MOKJNOST_NA_MOTOR * 20$
Секој автомобилист плаќа данок на заработка. Да се напишат соодветни методи за пресметување данок:

за автомобилисти: ако бројот на трки е поголем од 10 стапката на данок е 15% од заработката, инаку 10% од заработката.
за мотоциклисти: ако е ветеран стапката на данок е 25% од заработката, инаку 20% од заработката.
Да се напше надворешна функција soIstaZarabotuvachka која како аргументи прима низа од покажувачи од класата Vocac, нивниот број, како и покажувач кон ојбект од возач и враќа како резултат бројот на возачи кои имаат иста заработувачка по трка со проследениот возач. */


#include<iostream>
#include<cstring>
using namespace std;

class Vozac
{
protected:
    char ime[100];
    int age;
    int brojNaTrki;
    bool isVeteran;
public:
    Vozac(char * ime,int age = 0, int brojNaTrki =0,bool isVeteran = false)
    {
        strcpy(this->ime,ime);
        this->age =age;
        this->brojNaTrki = brojNaTrki;
        this->isVeteran = isVeteran;
    }

    friend ostream & operator << (ostream & out,const Vozac & v)
    {
        out << v.ime << endl << v.age << endl << v.brojNaTrki << endl;
        if(v.isVeteran)
        {
            out << "VETERAN" << endl;
        }
        return out;
    }

    virtual double zarabotuvaka() = 0;
    virtual double danok() = 0;

    bool operator == (Vozac * v)
    {
        if(this->zarabotuvaka() == v->zarabotuvaka())
        {
            return true;
        }
        return false;
    }

};

class Avtomobilist : public Vozac
{
    double cena;

public:
    Avtomobilist(char * ime,int age = 0, int brojNaTrki =0,bool isVeteran = false,double cena =0.0) : Vozac(ime,age,brojNaTrki,isVeteran)
    {
        this->cena = cena;
    }

    double zarabotuvaka()
    {
        return this->cena / 5;

    }

    double danok()
    {
        if(this->brojNaTrki > 10)
        {
            return zarabotuvaka() * 0.15;
        }
        return zarabotuvaka() * 0.1;
    }





};

class Motociklist: public Vozac
{
    int moknost;
public:
    Motociklist(char * ime,int age = 0, int brojNaTrki =0,bool isVeteran = false,int moknost = 0) : Vozac(ime,age,brojNaTrki,isVeteran)
    {
        this->moknost = moknost;
    }

    double zarabotuvaka()
    {
        return this->moknost * 20;

    }

    double danok()
    {
        if(this->isVeteran)
        {
            return zarabotuvaka() * 0.25;
        }
        return zarabotuvaka() * 0.2;
    }




};

int soIstaZarabotuvachka(Vozac ** lista,int n,Vozac * v)
{
    int counter = 0;
    for(int i = 0; i < n; i++)
    {
        if(lista[i]->zarabotuvaka()== v->zarabotuvaka())
        {
            counter++;
        }
    }
    return counter;
}


// vashiot kod ovde

int main()
{
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i)
    {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x)
        {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        }
        else
        {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i)
    {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i)
    {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}
