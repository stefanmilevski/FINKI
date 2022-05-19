/*

Да се дефинира класата Film во која се чуваат информации за:

име на филмот (динамички алоцирано поле од знаци)
мемориската зафатнина на филмот изразена во MB
жанр на филмот кој може да биде: акција, комедија или драма (енумерација zanr)
Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата.

Дополнително за оваа класа да се дефинира функцијата:

pecati() - функција во која ќе се печатат одделени со цртичка(-): мемориска зафатнина на филмот со постфикс MB и името на филмот во наводници.
Да се креира класата DVD во која се чуваат информации за :

низа од филмови снимени на DVD-то (Поле од најмногу 5 објекти од класата Film )
број на филмови снимени на DVD-то
меморискиот капацитет на DVD-то (во MB)
Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата.

Дополнително за оваа класа да се дефинираат методите:

dodadiFilm (Film f) - со кој се додава филмот f на DVDто, но само ако има доволно преостанато место (земајќи го предвид меморискиот капацитет на DVD-то и мемориската зафатнина на снимените филмови) и притоа да има помалку од 5 филмови на DVD-то.
pecatiFilmoviDrugZanr(zanr z) – со кој се печатат информациите за сите филмови кои НЕ се од жанрот zanr (акција, комедија или драма).
(дополнително барање):float procentNaMemorijaOdZanr(zanr z)- со кој се пресметува процентот на меморијата која ја зафаќаат филмовите од жанр z на DVD-то. */

#include <iostream>
#include <cstring>

using namespace std;

enum zanr {akcija, komedija, drama};


class Film
{
private:
    char * ime;
    int sizeInMB;
    zanr z;

public:
    Film()
    {
        this->ime = new char[0];
        strcpy(this->ime,"");
        this->sizeInMB = 0;
    }

    Film(char * ime,int sizeInMB,zanr z)
    {
        this->ime = new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->sizeInMB = sizeInMB;
        this->z = z;
    }

    Film & operator = (const Film & other)
    {
        if(this != &other)
        {
            delete[] ime;
            this->ime = new char[strlen(other.ime)+1];
            strcpy(this->ime,other.ime);
            this->sizeInMB = other.sizeInMB;
            this->z = other.z;

        }
        return *this;
    }

    int getMemory()
    {
        return this->sizeInMB;
    }



    zanr getZanr()
    {
        return this->z;
    }

    void pecati()
    {
        cout << this->sizeInMB << "MB-" <<  "\"" << this->ime << "\"" << endl;
    }


};

class DVD
{
private:
    Film * filmovi;
    int brojNaFilmovi;
    int memorijaNaDVD;

public:
    DVD(int memorijaNaDVD)
    {
        this->filmovi = new Film[0];
        this->brojNaFilmovi = 0;
        this->memorijaNaDVD = memorijaNaDVD;
    }
    ~DVD()
    {
        delete [] filmovi;
    }

    void dodadiFilm (Film f)
    {
        int totalMemory = 0;
        for(int i  = 0; i < this->brojNaFilmovi; i++)
        {
            totalMemory += filmovi[i].getMemory();
        }

        if(brojNaFilmovi < 5 && (totalMemory + f.getMemory()) <= this->memorijaNaDVD)
        {
            Film * tmp = new Film[this->brojNaFilmovi+1];
            for(int i = 0; i < this->brojNaFilmovi; i++)
            {
                tmp[i] = this->filmovi[i];
            }
            tmp[this->brojNaFilmovi++] = f;
            delete[]filmovi;
            this->filmovi = tmp;
        }
    }

    int getBroj()
    {
        return this->brojNaFilmovi;
    }

    Film & getFilm(int index)
    {
        return this->filmovi[index];
    }

    float procentNaMemorijaOdZanr(zanr z)
    {
        float memorijaOdFilmoviOdZanr = 0;
        float totalMemorija = 0;
        for(int i = 0; i < brojNaFilmovi; i++)
        {
            totalMemorija+= filmovi[i].getMemory();
            if(filmovi[i].getZanr() == z)
            {
                memorijaOdFilmoviOdZanr += filmovi[i].getMemory();
            }
        }
        return (memorijaOdFilmoviOdZanr / totalMemorija) * 100;
    }

    void pecatiFilmoviDrugZanr(zanr z)
    {


        for(int i = 0; i < this->brojNaFilmovi; i++)
        {
            if(this->filmovi[i].getZanr() != z)
            {
                filmovi[i].pecati();
            }
        }
    }


};

int main()
{
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, memorija, kojzanr;
    char ime[50];

    if (testCase == 1)
    {
        cout << "===== Testiranje na klasata Film ======" << endl;
        cin >> ime;
        cin >> memorija;
        cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
        Film f(ime, memorija, (zanr) kojzanr);
        f.pecati();
    }
    else if (testCase == 2)
    {
        cout << "===== Testiranje na klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        for (int i = 0; i < n; i++)
            (omileno.getFilm(i)).pecati();
    }
    else if (testCase == 3)
    {
        cout << "===== Testiranje na metodot dodadiFilm() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        for (int i = 0; i < omileno.getBroj(); i++)
            (omileno.getFilm(i)).pecati();
    }
    else if (testCase == 4)
    {
        cout << "===== Testiranje na metodot pecatiFilmoviDrugZanr() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        omileno.pecatiFilmoviDrugZanr((zanr) kojzanr);

    }
    else if (testCase == 5)
    {
        cout << "===== Testiranje na metodot pecatiFilmoviDrugZanr() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        omileno.pecatiFilmoviDrugZanr((zanr) kojzanr);

    }
    else if (testCase == 6)
    {
        cout<<"===== Testiranje na metodot procentNaMemorijaOdZanr() od klasata DVD =====" <<endl;
        DVD omileno(40);
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        cout<<"Procent na filmovi od dadeniot zanr iznesuva: "<<omileno.procentNaMemorijaOdZanr((zanr) kojzanr)<<"%\n";

    }

    return 0;
}
