/*
Да се дефинира класа Pica за која ќе се чуваат податоци за:

име на пицата (низа од 15 знаци)
цена (цел број)
состојки (динамички алоцирана низа од знаци)
намалување на цената во проценти (цел број) - ако пицата не е на промоција намалувањето има вредност нула, во спротивно, вредност поголема од нула и не поголема од 100.
За потребите на оваа класа да се креираат потребните конструктори и да се напише соодветен деструктор. Дополнително за оваа класа да се дефинира функцијата:

pecati() - функција во која ќе се печатат податоците за пицата во следниот формат: име - состојки, цена.
istiSe(Pica p) - функција за споредба на две пици според состојките :
Да се дефинира класа Picerija во која се чуваат:

име (низа од максимум 15 знаци)
динмички алоцирана низа од објекти од класата Pica
број на пици (цел број)
За потребите на оваа класа да се дефинираат потребните конструктори и да се напише соодветен деструктор. Да се имплементираат и следниве методи:

dodadi (Pica P) - за додавање нова пица во пицеријата, но само ако не постои иста во низата (нема пица со исти состојки со пицата што треба да се додаде).
void piciNaPromocija() - се печатат сите пици од пицеријата што се на промоција во формат : име - состојки, цена, цена со попуст. */

#include <iostream>
#include <cstring>

using namespace std;

class Pica
{
private:
    char ime[15];
    int cena;
    char * sostojki;
    int namaluvanje;
public:
    Pica()
    {
        this->sostojki = new char[0];
        this->cena = 0;
        this->namaluvanje = 0;
    }

    Pica(char ime[15],int cena = 0,char * sostojki ="",int namaluvanje = 0)
    {
        strcpy(this->ime, ime);
        this->cena = cena;
        this->sostojki = new char[strlen(sostojki)+1];
        strcpy(this->sostojki,sostojki);
        this->namaluvanje = namaluvanje;
    }



    Pica(const Pica & other)
    {
        strcpy(this->ime, other.ime);
        this->cena = other.cena;
        this->sostojki = new char[strlen(other.sostojki)+1];
        strcpy(this->sostojki,other.sostojki);
        this->namaluvanje = other.namaluvanje;

    }

    Pica & operator = (const Pica & other)
    {
        if(this != &other)
        {
            delete [] sostojki;
            strcpy(this->ime, other.ime);
            this->cena = other.cena;
            this->sostojki = new char[strlen(other.sostojki)+1];
            strcpy(this->sostojki,other.sostojki);
            this->namaluvanje = other.namaluvanje;
        }
        return *this;
    }


    void pecati()
    {
        cout << this->ime << " - " << this->sostojki << ", " << this->cena << " ";
    }

    int getCena()
    {
        return this->cena;
    }
    int getNamaluvanje()
    {
        return this->namaluvanje;
    }

    bool istiSe(Pica & p)
    {
        if(strcmp(this->sostojki, p.sostojki) == 0)
        {
            return true;
        }
        return false;
    }


};


class Picerija
{
private:
    char ime[15];
    Pica * pici;
    int brojNaPici;
public:
    Picerija(char ime[15])
    {
        strcpy(this->ime,ime);
        this->brojNaPici=0;
    }

    Picerija(char ime[15],Pica * p, int brojNaPici = 0)
    {
        strcpy(this->ime,ime);
        this->pici = new Pica[brojNaPici];
        for(int i=0; i<brojNaPici; i++)
        {
            pici[i]=p[i];
        }
        this->brojNaPici=brojNaPici;
    }


    void setIme(char * ime)
    {
        strcpy(this->ime, ime);
    }

    char * getIme()
    {
        return this->ime;
    }

    bool checkIfPizzaAlreadyExists(Pica p)
    {
        bool flag = false;
        for(int i = 0; i < this->brojNaPici; i++)
        {
            if(pici[i].istiSe(p))
            {
                flag = true;
            }
        }
        return flag;
    }

    void dodadi(Pica p)
    {
        for(int i=0; i<brojNaPici; i++)
        {
            if(pici[i].istiSe(p)) return;
        }

        Pica *n = new Pica[brojNaPici+1];
        for(int i=0; i<brojNaPici; i++)
        {
            n[i] = pici[i];
        }
        n[brojNaPici]=p;
        pici = n;
        brojNaPici++;
    }

    void piciNaPromocija()
    {
        for(int i =0; i < this->brojNaPici; i++)
        {
            if(this->pici[i].getNamaluvanje() != 0)
            {
                this->pici[i].pecati();
                cout << pici[i].getCena() - (pici[i].getCena() * (( pici[i].getNamaluvanje() / 100.0))) << endl;
            }


        }
    }

};

int main ()
{

    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for(int i = 0; i < n; i++)
    {
        char imp[100];
        cin.get();
        cin.getline(imp,100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki,100);
        int popust;
        cin >> popust;
        Pica p(imp,cena,sostojki,popust);
        p1.dodadi(p);

    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp,100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki,100);
    int popust;
    cin >> popust;
    Pica p(imp,cena,sostojki,popust);
    p2.dodadi(p);

    cout<<p1.getIme()<<endl;
    cout<<"Pici na promocija:"<<endl;
    p1.piciNaPromocija();

    cout<<p2.getIme()<<endl;
    cout<<"Pici na promocija:"<<endl;
    p2.piciNaPromocija();

    return 0;
}


