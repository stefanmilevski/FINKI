/* Да се напише класа Automobile во која се чуваат информации за марката на автомобилот (динамички алоцирана низа од знаци), регистрација (динамички алоцирана низа од 5 цели броја) и максимална брзина (цел број). За класата да се обезбедат set и get методите што се користат и да се преоптоварат следните оператори:

оператор == за споредување на два автомобила според регистрацијата

оператор << за печатење на податоци на автомобил во формат Marka:име Registracija:[x y z k l]

Да се напише класа RentACar за агенција за измајмување возила во која се чуваат информација за името на агенцијата (низа од 100 знци), низа од автомобили (динамички алоациана низа од објекти од класата Automobile) и број на автомобили со кој располага (цел број). Во класата RentACar да се напише конструктор со еден аргумент за иницијализација на името на агенцијата. При секое додавање на нов автомобил, динамички алоцираната низа да го зголемува капацитетот за 1 елемент. Во оваа класа да се преоптоварат операторите:

+= за додавање на нов автомобил во агенцијата и

-= за отстранување на даден автомобил од агенцијата (оној со иста регистрација).

Да се напише main функција во која се инстанцира објект од класата RentACar. Во овој објект да се додадат сите автомобили чии информации се читаат од тастатура со операторот +=. Меѓутоа, откриено е дека во внесувањето на податоците има грешка затоа што при обид да се додаде нов автомобил во агенцијата, увидено е дека таа регистрација веќе постои. Во последниот ред од влезот дадени се инфромации тој автомобил. Потребно е да се избрише автомобилот што претходно е погрешно внесен и да се додаде новиот.

На излез да се отпечатат името на агенцијата и листа на автомобили што таа ги изнајмува, а чија максимална брзина е поголема од 150. Последново да се направи со функција pecatiNadBrzina(int max) што треба да се дефинира во класата RentACar. */

#include <iostream>
#include <cstring>

using namespace std;

class Automobile
{
private:
    char * marka;
    int * registracija;
    int maxSpeed;
public:


    Automobile(char * marka ="",int * registracija = new int[5], int maxSpeed = 0)
    {
        this->marka = new char[strlen(marka)+1];
        strcpy(this->marka,marka);
        this->registracija = new int[5];
        for(int i = 0; i < 5; i++)
        {
            this->registracija[i] = registracija[i];
        }
        this->maxSpeed = maxSpeed;
    }

    int getSpeed()
    {
        return this->maxSpeed;
    }

    Automobile & operator = (const Automobile & a)
    {
        if(this != &a)
        {
            this->marka = new char[strlen(a.marka)+1];
            strcpy(this->marka,a.marka);
            this->registracija = a.registracija;
            for(int i = 0; i < 5; i++)
            {
                this->registracija[i] = a.registracija[i];
            }
            this->maxSpeed = a.maxSpeed;
        }
        return *this;

    }

    bool operator == (const Automobile & a)
    {
        for(int i = 0; i < 5; i++)
        {
            if(registracija[i] != a.registracija[i])
            {
                return false;
            }
        }
        return true;
    }

    friend ostream & operator << (ostream & out,const Automobile & a)
    {
        out << "Marka\t" <<  a.marka <<  "\tRegistracija[ ";
        for(int i = 0; i < 5; i++)
        {
            out <<  a.registracija[i] <<  " ";
        }
        out << "]" << endl;

    }
};

class RentACar
{
    char name[100];
    Automobile * cars;
    int numberOfCars;
public:
    RentACar(char * name =  "")
    {
        strcpy(this->name,name);
        this->numberOfCars = 0;
        this->cars = new Automobile[this->numberOfCars];
    }

    RentACar & operator += (const Automobile & a)
    {

        Automobile * tmp = new Automobile[numberOfCars+1];
        for(int i = 0; i < numberOfCars; i++)
        {
            tmp[i] = cars[i];
        }
        tmp[numberOfCars++] = a;
        delete [] cars;
        cars = tmp;
        return *this;

    }

    RentACar & operator -= (const Automobile & a)
    {

        int index = -1;
        for(int i = 0; i < numberOfCars; i++)
        {
            if(cars[i] == a)
            {
                index = i;
            }
        }

        Automobile * tmp = new Automobile[numberOfCars];
        for(int i = 0; i < numberOfCars; i++)
        {
            tmp[i] = cars[i];
        }

        for(int i=index+1; i<numberOfCars; i++)
        {
            tmp[i-1] = cars[i];
        }

        delete [] cars;
        --numberOfCars;
        cars = tmp;
        return *this;

    }

    friend ostream & operator << (ostream &out, const RentACar & rc)
    {
        for(int i = 0; i <rc.numberOfCars; i++)
        {
            out << rc.cars[i];
        }
        return out;
    }
    void pecatiNadBrzina(int maxS)
    {
        cout << this->name << endl;
        for(int i = 0; i < numberOfCars; i ++)
        {
            if(cars[i].getSpeed() > maxS)
            {
                cout << cars[i];
            }
        }



    }
};



int main()
{
    RentACar agencija("FINKI-Car");
    int n;
    cin>>n;

    for (int i=0; i<n; i++)
    {
        char marka[100];
        int regisracija[5];
        int maximumBrzina;

        cin>>marka;

        for (int i=0; i<5; i++)
            cin>>regisracija[i];

        cin>>maximumBrzina;

        Automobile nov=Automobile(marka,regisracija,maximumBrzina);

        //dodavanje na avtomobil
        agencija+=nov;

    }
    //se cita grehsniot avtmobil, za koj shto avtmobilot so ista registracija treba da se izbrishe
    char marka[100];
    int regisracija[5];
    int maximumBrzina;
    cin>>marka;
    for (int i=0; i<5; i++)
        cin>>regisracija[i];
    cin>>maximumBrzina;

    Automobile greshka=Automobile(marka,regisracija,maximumBrzina);

    //brishenje na avtomobil
    agencija-=greshka;

    agencija.pecatiNadBrzina(150);

    return 0;
}
