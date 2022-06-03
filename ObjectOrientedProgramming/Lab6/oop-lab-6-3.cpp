/* Со цел да се подобри системот Мој Термин, со воведување функционалност за пресметување плати за лекарите за еден месец, од Министерството за здравство на Република Македонија, ги добивате следните задачи:

Да се креира класа Lekar во која што ќе се чуваат:

факсимил на докторот (цел број)
име (низа од максимум 10 знаци)
презиме (низа од максимум 10 знаци)
почетна плата (децимален број)
За класата да се имплементираат методите:

void pecati(): Печати информации за лекарот во формат Факсимил: име презиме

double plata(): ја враќа платата на лекарот

Да се креира класа MaticenLekar која што наследува од Lekar и во неа се чуваат дополнителни информации за:

број на пациенти со којшто лекарот соработувал во текот на месецот (цел број)
котизации наплатени од пациентите во текот на месецот (динамички алоцирана низа од децимални броеви)
За класата да се препокријат методитe:

void pecati() : ги печати основните информации за лекарот, а во нов ред го печати и просекот од наплатените котизации

double plata(): ја враќа платата на матичниот лекар

Платата на матичниот лекар се пресметува со зголемување на основната плата за 30% од просекот од наплатените котизации за месецот */


#include<iostream>
#include<cstring>
using namespace std;

class Lekar
{
protected:
    int faksimil;
    char ime[10];
    char prezime[11];
    double osnovnaPlata;

    void copy(Lekar & other)
    {
        this->faksimil = other.faksimil;
        strcpy(this->ime,other.ime);
        strcpy(this->prezime,other.prezime);
        this->osnovnaPlata = other.osnovnaPlata;
    }

public:

    Lekar(int faksimil = 0,char * ime = "",char * prezime = "",double osnovnaPlata = 0)
    {
        this->faksimil = faksimil;
        strcpy(this->ime,ime);
        strcpy(this->prezime,prezime);
        this->osnovnaPlata = osnovnaPlata;
    }

    Lekar(Lekar & other)
    {
        copy(other);
    }

    void pecati()
    {
        cout << faksimil << ": " << ime << " " << prezime << endl;
    }

    double plata()
    {
        return this->osnovnaPlata;
    }
};

class MaticenLekar : public Lekar
{
    int brojNaPacienti;
    double * kotizacii;

public:
    MaticenLekar(int faksimil = 0,char * ime = "",char * prezime = "",double osnovnaPlata= 0,int brojNaPacienti = 0,double * kotizacii = new double[0]) : Lekar(faksimil,ime,prezime,osnovnaPlata)
    {
        this->brojNaPacienti;
        this->kotizacii = new double[this->brojNaPacienti];
        for(int i = 0; i < this->brojNaPacienti; i++)
        {
            this->kotizacii[i] = kotizacii[i];
        }
    }

    MaticenLekar(Lekar & other,int brojNaPacienti = 0,double * kotizacii = new double[0]) : Lekar(other)
    {
        this->brojNaPacienti = brojNaPacienti;
        this->kotizacii = new double[this->brojNaPacienti];
        for(int i = 0; i < this->brojNaPacienti; i++)
        {
            this->kotizacii[i] = kotizacii[i];
        }
    }
    double average(){
        double sum = 0;
        for(int i = 0; i < this->brojNaPacienti; i++)
        {
            sum += kotizacii[i];
        }
        return sum / this->brojNaPacienti;
    }

    double plata()
    {
        return (Lekar::plata() + (average() *0.3));
    }
    void pecati()
    {
        Lekar::pecati();
        cout << "Prosek na kotizacii: " << average() << endl;
    }



};




int main()
{
    int n;
    cin>>n;
    int pacienti;
    double kotizacii[100];
    int faksimil;
    char ime [20];
    char prezime [20];
    double osnovnaPlata;

    Lekar * lekari = new Lekar [n];
    MaticenLekar * maticni = new MaticenLekar [n];

    for (int i=0; i<n; i++)
    {
        cin >> faksimil >> ime >> prezime >> osnovnaPlata;
        lekari[i] = Lekar(faksimil,ime,prezime,osnovnaPlata);
    }

    for (int i=0; i<n; i++)
    {
        cin >> pacienti;
        for (int j=0; j<pacienti; j++)
        {
            cin >> kotizacii[j];
        }
        maticni[i]=MaticenLekar(lekari[i],pacienti,kotizacii);
    }

    int testCase;
    cin>>testCase;

    if (testCase==1)
    {
        cout<<"===TESTIRANJE NA KLASATA LEKAR==="<<endl;
        for (int i=0; i<n; i++)
        {
            lekari[i].pecati();
            cout<<"Osnovnata plata na gorenavedeniot lekar e: "<<lekari[i].plata()<<endl;
        }
    }
    else
    {
        cout<<"===TESTIRANJE NA KLASATA MATICENLEKAR==="<<endl;
        for (int i=0; i<n; i++)
        {
            maticni[i].pecati();
            cout<<"Platata na gorenavedeniot maticen lekar e: "<<maticni[i].plata()<<endl;
        }
    }

    delete [] lekari;
    delete [] maticni;

    return 0;
}
