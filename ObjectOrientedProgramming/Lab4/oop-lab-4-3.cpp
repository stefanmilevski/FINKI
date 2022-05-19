#include <iostream>
#include <cstring>
using namespace std;

class Avtomobil
{
private:
    char boja[20];
    char brend[20];
    char model[20];

public:
    Avtomobil(char boja[20] = "", char brend[20] = "", char model[20] = "")
    {
        strcpy(this->boja,boja);
        strcpy(this->brend,brend);
        strcpy(this->model,model);
    }

    Avtomobil & operator = (const Avtomobil & other)
    {
        if(this != &other)
        {
            strcpy(this->boja,other.boja);
            strcpy(this->brend,other.brend);
            strcpy(this->model,other.model);
        }
    }

    char * getBoja()
    {
        return this->boja;
    }

    char* getBrend()
    {
        return this->brend;
    }
    char* getModel()
    {
        return this->model;
    }

};



class ParkingPlac
{
private:
    char adresa[20];
    char * id;
    int cenaPoCas;
    int zarabotka;

    Avtomobil * avtomobili;
    int brojNaParkirani;

public:
    ParkingPlac()
    {
        strcpy(this->adresa, "");
        this->id = new char[0];
        strcpy(this->id, "");
        this->cenaPoCas = 0;
        this->zarabotka = 0;

        this->avtomobili = new Avtomobil[0];
        this->brojNaParkirani = 0;
    }

    ParkingPlac(char adresa[20],char * id,int cenaPoCas)
    {
        strcpy(this->adresa, adresa);
        this->id = new char[strlen(id)+1];
        strcpy(this->id, id);
        this->cenaPoCas = cenaPoCas;
        this->zarabotka = 0;

        this->avtomobili = new Avtomobil[0];
        this->brojNaParkirani = 0;

    }

    bool daliIstaAdresa(ParkingPlac & p)
    {
        if(strcmp(this->adresa, p.adresa) == 0)
        {
            return true;
        }
        return false;
    }

    void pecati()
    {
        if(this->zarabotka !=0)
        {
            cout << this->id << " " << this->adresa << " - " << this->zarabotka << " denari" << endl;
        }
        else
        {
            cout << this->id << " "<< this->adresa << endl;
        }
    }

    void platiCasovi(int casovi)
    {
        this->zarabotka += casovi * this-> cenaPoCas;
    }

    void parkirajVozilo(Avtomobil novoVozilo)
    {
        Avtomobil * tmp = new Avtomobil[this->brojNaParkirani+1];
        for(int i = 0; i < brojNaParkirani; i++)
        {
            tmp[i] = this->avtomobili[i];
        }
        tmp[brojNaParkirani++] = novoVozilo;
        delete[]avtomobili;
        avtomobili = tmp;
    }


    void pecatiParkiraniVozila()
    {
        cout << "Vo parkingot se parkirani slednite vozila:" << endl;
        for(int i = 0; i < this->brojNaParkirani; i++)
        {
            cout << i+1 << "." << this->avtomobili[i].getBoja() << " "  << this->avtomobili[i].getBrend()  << this->avtomobili[i].getModel() << endl;
        }
    }


    char * getId()
    {
        return this->id;
    }
};




int main()
{
    ParkingPlac p("aleksander","123",50);
    p.pecati();

    return 0;

}
