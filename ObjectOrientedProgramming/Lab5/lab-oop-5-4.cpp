/*
Да се креира класа за претставување на планинарско друштво во која ќе се чуваат информации за името на друштвото (динамички алоцирана низа од знаци), број на поминати тури (цел број) и број на членови во планинарското друштво (цел број). За оваа класа да се напише:

оператор + за собирање на две друштва што како резултат враќа друштво со број на членови еднаков на збирот од членовите од двете друштва, а останатите атрибути на резултантното друштво ги добиваат вредностите на соодветните атрибути од друштвото со поголем број на членови

оператори >, < за споредба во однос на бројот на членови во планинарските друштва

оператор << за печатење на информациите за планинарското друштво

Да се напише функција што на влез прима низа од планинарски друштва и вкупен број на друштва во низата и го печати планинарското друштво што има најголем број на членови . */

#include <iostream>
#include <string.h>
using namespace std;

class PlDrustvo
{
public:
    char * name;
    int numberOfTours;
    int members;
public:
    PlDrustvo(char * name ="Default",int numberOfTours = 0,int members =0)
    {
        this->name = new char[strlen(name)+1];
        strcpy(this->name,name);
        this->numberOfTours = numberOfTours;
        this->members = members;
    }

    PlDrustvo & operator = (const PlDrustvo & other)
    {
        if(this != &other)
        {
            this->name = new char[strlen(other.name)+1];
            strcpy(this->name,other.name);
            this->numberOfTours = other.numberOfTours;
            this->members = other.members;
        }
    }

    PlDrustvo operator + (const PlDrustvo & other)
    {
        PlDrustvo tmp;
        tmp.members = this->members + other.members;

        if(this->members > other.members)
        {
            tmp.name = new char[strlen(this->name)+1];
            strcpy(tmp.name,this->name);
            tmp.numberOfTours = this->numberOfTours;
        }
        else
        {
            tmp.name = new char[strlen(other.name)+1];
            strcpy(tmp.name,other.name);
            tmp.numberOfTours = other.numberOfTours;
        }

        return tmp;
    }

    friend bool operator>(const PlDrustvo& drustvo1, const PlDrustvo& drustvo2){
        return (drustvo1.members > drustvo2.members);
    };
    friend bool operator<(const PlDrustvo& drustvo1, const PlDrustvo& drustvo2){
        return (drustvo1.members < drustvo2.members);
    };


    int getMembers()
    {
        return this->members;
    }

    friend ostream & operator << (ostream & out,const PlDrustvo & pl)
    {
        out<< "Ime: " << pl.name << " Turi: " << pl.numberOfTours << " Clenovi: " << pl.members << endl;
    }
};

void najmnoguClenovi(PlDrustvo * PlDrustva,int number)
{
    PlDrustvo tmp;
    for(int i = 0; i < number; i++)
    {
        if(tmp.getMembers() < PlDrustva[i].getMembers())
        {
            tmp = PlDrustva[i];
        }
    }
    cout << "Najmnogu clenovi ima planinarskoto drustvo: ";
    cout << tmp;
}

int main()
{
    PlDrustvo drustva[3];
    PlDrustvo pl;
    for (int i=0; i<3; i++)
    {
        char ime[100];
        int brTuri;
        int brClenovi;
        cin>>ime;
        cin>>brTuri;
        cin>>brClenovi;
        PlDrustvo p(ime,brTuri,brClenovi);
        drustva[i] = p;

    }

    pl = drustva[0] + drustva[1];
    cout<<pl;

    najmnoguClenovi(drustva, 3);

    return 0;
}
